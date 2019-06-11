#include "MainController.h"
#include <filesystem>
#include <fstream>
#include "MainWindow.h"
#include "DatabaseLoading.h"
#include <sstream>
#include <thread>
#include <qdebug.h>
#include <exception>


//----- CONSTRUCTEURS / DESTRUCTEUR -----// 

MainController::MainController()
{
	std::experimental::filesystem::create_directory("img");
}

MainController::MainController(const std::string path)
	:mImg{ path }
{
}

MainController::~MainController()
{
	std::experimental::filesystem::remove_all("./img");
	delete mMainWindow;
	delete mApp;
}

//------- GETTER / SETTER --------//

std::vector<std::string> MainController::getLabels()
{
	std::vector<std::string> vLabels;

	for (auto c : mCharacterVector) { vLabels.push_back(c.getLabel()); }

	return vLabels;
}

CharacterObject MainController::getCharacterAt(int index)
{
	return mCharacterVector.at(index-1);
}


void MainController::setPath(std::string path)
{
	mPath = path;
}

void MainController::clearData()
{
	mCharacterVector.clear();
	mImg.clearData();
	mSpacePositions.clear();
}

//---------- FONCTIONS DU PROCESSUS GLOBAL -----------//

//Fonction exécutée pour lancer le GUI
//Retourne la boucle Qt de l'applications
int MainController::exec(int argc, char * argv[])
{
	mApp = new QApplication(argc, argv);
	mMainWindow = new MainWindow(this);
	mMainWindow->setFixedSize(820, 700);
	mMainWindow->show();
	mApp->setStyle("windows");
	return mApp->exec();
}

//Lance le processus d'extraction des caractères
//pour l'image complète.
//	1. Affichage "extraction en cours"
//	2. Traiter l'image
//	3. Chercher les données des caractères obtenus et les insérer dans un vecteur.
//	4. Pour chaque caractère : ajouter au combo pour l'affichage.
//	5. Changer l'image affichée pour l'image avec les contours mis en relief.
//	6. Affichage "extraction terminée".
bool MainController::processImage()
{
	bool result{ true };
	clearData();
	try {
		startProcessGUI(MSG_IDENTIFICATION_START);
		
		mImg.setPath(mPath);
		mImg.process();

		std::vector<CharacterObject> tempVec = mImg.getData();

		for (int i{ 0 }; i < tempVec.size(); ++i) {
			if (tempVec[i].getLabel() == "SPACE") {mSpacePositions.push_back(i);}
			else {mCharacterVector.push_back(tempVec[i]);}
		}

		for (auto c : mCharacterVector) {
			mMainWindow->addCharToCombo_fromCTL(c.getFileName().c_str());
		}

		mMainWindow->changeImage_fromCTL("img/contours.jpg");
		endProcessGUI(MSG_IDENTIFICATION_END);
		
	}
	catch (std::exception e) {
		endProcessGUI(MSG_IDENTIFICATION_FAIL);
	}

	return result;
}


//-------- FONCTIONS-LIENS ENTRE LE GUI ET L'ALGO KNN -------//

//Traiter un caractère via l'algorithme Knn
//selon son index dans le vecteur
//via l'objet de la classe knnAlgo.
CharacterObject * MainController::getCharFromKNN(int index)
{
	CharacterObject * c{ &(mCharacterVector.at(index)) };
	kNNAlgo::character_s c_s{ "", c->getVectorOfFeatures(), c->getPixelsVectorNumeric(), 0 };
	mKnnController.setWeight(mMainWindow->getWeight());
	c->setKnnResults(mKnnController.process(c_s, mMainWindow->getValueSlider()));
	c->setLabel(mKnnController.kNNVerdict(c->getKnnResults()));
	return c;
}

//Lancer le processus d'identification d'un caractère
//via l'object de classe knnAlgo.
void MainController::identifyChar(int index)
{
	startProcessGUI(MSG_IDENTIFICATION_START);

	CharacterObject * c{ getCharFromKNN(index) };
	mMainWindow->displayKnnResults_fromCTL(c->getKnnResults(), c->getLabel());

	endProcessGUI(MSG_IDENTIFICATION_END);
}

//Identifie l'ensemble des caractères.
//Les affiche dans un label.
void MainController::identifyAll()
{
	startProcessGUI(MSG_IDENTIFICATION_START);
	std::string res{ "" };

	for (size_t i { 0 }; i < mCharacterVector.size(); ++i) {
		CharacterObject * c{ getCharFromKNN(i) };
		res += c->getLabel();
	}

	for (auto s : mSpacePositions) {
		res.insert(s, " ");
	}

	mMainWindow->displayAllKnnResults_fromCTL(res);
	endProcessGUI(MSG_IDENTIFICATION_END);
}


//--------- LIEN AVEC LA BASE DE DONNÉES ---------//

	//retrouve les données de la BD
	//les envoie à l'objet kNNAlgo
void MainController::buildFromDatabaseStruct()
{
	if (!mDatabaseLoaded) {
		mDatabaseLoaded = true;
		mMainWindow->changeStatus_fromCTL(MSG_LOADING_DATA.c_str());

		mDH.openDatabase(NOM_BD);
		mDH.select(DATASET_TABLE, COLONNES_DATASET_MINUSBLOB, "", "");

		std::list<std::map<std::string, std::string>> results{ mDH.getResults() };
		mDH.selectBLOB(DATASET_TABLE, COLONNES_DATASET_BLOB.front(), "", "");
		std::list<std::vector<char>> resultsBlob{ mDH.getResultsBlob() };
		double step{ 1.00 / results.size()*1.00 * 100.00 }, count{ 0 };

		for (auto m : results) {

			std::string label{ getLabelFromDB(m["label_id"]) };

			mKnnController.addToDataset(label,
				std::vector<double> { std::stod(m["nbClosedZones"]), std::stod(m["blackWhiteRatio"]), std::stod(m["nbCorners"]) },
				CharacterObject::deserializeVector(resultsBlob.front()));

			resultsBlob.pop_front();
			count += step;

			if (int(count) > 0) { mMainWindow->makeProgress_bar_fromCTL(int(count)); }
		}

		endProcessGUI(MSG_LOADING_END);
	}
}

	//fonction permettant de retourner l'étiquette d'un caractère
	//à partir du ID d'une rangée de la base de données
std::string MainController::getLabelFromDB(std::string labelId)
{
	mDH.select(LABELS_TABLE, std::list<std::string>{"character"}, "id", labelId);
	return mDH.getResults().front()["character"];
}

	//ajout d'un caractère à la base de données
	//à partir du GUI
void MainController::addToDatabase(QString label, int index)
{
	startProcessGUI(MSG_LOADING_LETTER);

	mDH.openDatabase(NOM_BD);

	std::string tempStr(label.toLatin1().data());
	std::string tempStrForSelect("\'" + tempStr + "\'");

	mDH.select(LABELS_TABLE, std::list<std::string>{"id"}, "character", tempStrForSelect);
	std::string labelId{ mDH.getResults().front()["id"] };

	const std::list<std::string> values{
			std::to_string(mCharacterVector[index].getClosedZones()),
			std::to_string(mCharacterVector[index].getRatio()),
			std::to_string(mCharacterVector[index].getCorners()),
			"?",
			labelId
	};
	mDH.insertWithBlob(DATASET_TABLE, COLONNES_DATASET, values, mCharacterVector[index].getSerializedVector());
	mDH.closeDatabase();

	endProcessGUI(MSG_LOADING_LETTER_END);
}

//------- MESSAGE DE PROCESSUS EN COURS VERS LE GUI -------//

void MainController::startProcessGUI(std::string message) {
	mMainWindow->changeStatus_fromCTL(message.c_str());
	mMainWindow->makeProgress_bar_fromCTL(100);
}

void MainController::endProcessGUI(std::string message) {
	mMainWindow->changeStatus_fromCTL(message.c_str());
	mMainWindow->makeProgress_bar_fromCTL(0);
}

//----------- FONCTIONS UTILITAIRES-------------//
//		non utilisées par le programme actif

//Fonction pour l'insertion de masse de caractères.
//A été utilisée pour la consolidation de la base de données.
bool MainController::insertIntoDatabase(std::vector<std::string> labels)
{
	size_t nbCarac{ mCharacterVector.size() };
	bool result;

	mDH.openDatabase(NOM_BD);

	for (int i{ 0 }; i < nbCarac; ++i) {

		mDH.select(LABELS_TABLE, std::list<std::string>{"id"}, "character", labels[i]);
		std::string labelId{ mDH.getResults().front()["id"] };

		const std::list<std::string> values{
			std::to_string(mCharacterVector[i].getClosedZones()),
			std::to_string(mCharacterVector[i].getRatio()),
			std::to_string(mCharacterVector[i].getCorners()),
			"?",
			labelId
		};
		result = mDH.insertWithBlob(DATASET_TABLE, COLONNES_DATASET, values, mCharacterVector[i].getSerializedVector());
	}

	mDH.closeDatabase();

	clearData();

	return true;
}