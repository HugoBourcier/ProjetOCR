#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "FullImage.h"
#include <string>
#include <vector>
#include "Constants.h"
#include "CharacterObject.h"
#include "DatabaseHelper.h"
#include "kNNAlgo.h"
#include <map>
//#include "MainWindow.h"
#include <QtWidgets/QApplication>

//------------------------------//
// Classe MainController		//
//								//
// Comme son nom l'indique,		//
// contrôleur principal faisant //
// le lien entre les objetes.	//
// Interagit avec un object		//
// FullImage pour déclencher	//
// le processus d'analyse.		//
//------------------------------//

class MainWindow;

class MainController
{
public:
	//constructeurs, destructeurs
	MainController();
	MainController(const std::string path);
	~MainController();
	//executer le GUI
	int exec(int argc, char * argv[]);
	//processus d'analyse de l'image
	bool processImage();
	//getters, setters
	std::vector<std::string> getLabels();
	void setPath(std::string path);
	CharacterObject getCharacterAt(int index);
	//communication avec kNN
	CharacterObject * getCharFromKNN(int index);
	void identifyChar(int index);
	void identifyAll();
	//database
	void buildFromDatabaseStruct();
	bool insertIntoDatabase(std::vector<std::string> labels);
	std::string getLabelFromDB(std::string labelId);
	void addToDatabase(QString label, int index);
	//clear
	void clearData();
	//envoyer message au GUI
	void startProcessGUI(std::string message);
	void endProcessGUI(std::string message);

private:
	FullImage mImg;
	std::vector<int> mSpacePositions;
	DatabaseHelper mDH;
	kNNAlgo mKnnController;
	MainWindow * mMainWindow;
	QApplication * mApp;
	std::string mPath;
	bool mDatabaseLoaded{ false };
	std::vector<CharacterObject> mCharacterVector;

};

#endif //MAINCONTROLLER_H
