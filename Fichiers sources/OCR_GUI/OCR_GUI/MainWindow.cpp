#include "MainWindow.h"
#include <qfiledialog.h>
#include <qdebug.h>

MainWindow::MainWindow(MainController * controller, QWidget *parent)
	: QMainWindow(parent),
	mController{controller}
{
	ui.setupUi(this);
	this->setFixedSize(1680, 1120);
	ui.analyzeBtn->setDisabled(true);
	ui.algoBtn->setDisabled(true);
	connect(ui.openFileBtn, SIGNAL(released()), this, SLOT(openFileBtn_pressed()));
	connect(ui.analyzeBtn, SIGNAL(released()), this, SLOT(analyzeBtn_pressed()));
	connect(this, SIGNAL(pBar(int)), this, SLOT(progressBarStep(int)));
	connect(this, SIGNAL(statusLbl(QString)), this, SLOT(changeStatus(QString)));
	connect(this, SIGNAL(charCombo(QString)), this, SLOT(addCharToCombo(QString)));
	connect(ui.charCombo, SIGNAL(currentTextChanged(QString)), this, SLOT(comboSelect(QString)));
	connect(this, SIGNAL(triggerPBar(bool)), this, SLOT(triggerProgressBar(bool)));
	connect(ui.algoBtn, SIGNAL(released()), this, SLOT(analyze()));
	connect(this, SIGNAL(knnResults(std::map<std::string, double>, std::string)), this, SLOT(displayKnnResults(std::map<std::string, double>, std::string)));
	connect(this, SIGNAL(changeImage(std::string)), this, SLOT(changeImageDisplay(std::string)));
	connect(ui.addToDBBtn, SIGNAL(released()), this, SLOT(addToDatabase()));
	connect(ui.btnIdentifyAll_2, SIGNAL(released()), this, SLOT(analyzeAll()));
	connect(this, SIGNAL(allKnnResults(std::string)), this, SLOT(displayAllKnnResults(std::string)));
}

//----- SLOTS À L'INTERNE -----//

void MainWindow::openFileBtn_pressed()
{
	ui.algoBtn->setDisabled(true);
	QString path{ QFileDialog::getOpenFileName(this, QDir::currentPath(), "Open", "JPG files (*.jpg)") };
	if (path != "") {
		mController->setPath(path.toUtf8().constData());
		QImage img = QImage(path).scaled(ui.fullImageView->width(), ui.fullImageView->height(), Qt::KeepAspectRatio);
		ui.fullImageView->setPixmap(QPixmap::fromImage(img));
		ui.analyzeBtn->setDisabled(false);
	}
}

void MainWindow::emptyEverything()
{
	//for (int i{ 0 }; i < ui.charCombo->count(); ++i) {
	//	ui.charCombo->removeItem(i);
	//	
	//}
	ui.charCombo->clear();
	ui.charLabel->clear();
	ui.lblClosedZones->setText("Nombre de zones fermees : - ");
	ui.lblCorners->setText("Nombre de coins selon Harris : -");
	ui.lblRatio->setText("Ratio pixels blancs/pixels noirs : -");
	ui.knnVerdictEdit->setText("-");
	ui.knnResLabel->setText("Aucun resultat a afficher.");
	ui.lblIdentifyAll_2->setText(" ... ");
	mController->clearData();
}

void MainWindow::analyzeBtn_pressed()
{
	emptyEverything();
	mController->buildFromDatabaseStruct();
	mController->processImage();
	ui.algoBtn->setDisabled(false);
}

void MainWindow::progressBarStep(int step)
{
	ui.progressBar->setValue(step);
}

void MainWindow::triggerProgressBar(bool check)
{
	
	QProgressBar * pBar{ui.progressBar};

	if (check) {pBar->setMinimum(100);} 
	else { pBar->setMinimum(0); }

	pBar->setValue(0);

}

void MainWindow::changeStatus(QString msg)
{
	ui.statusLabel->setText(msg);
	ui.statusLabel->repaint();
}

void MainWindow::addCharToCombo(QString name)
{
	ui.charCombo->addItem(name);
	ui.charCombo->repaint();
}

void MainWindow::analyze()
{
	mController->identifyChar(ui.charCombo->currentIndex());
}

void MainWindow::analyzeAll()
{
	mController->identifyAll();
}

void MainWindow::comboSelect(QString name)
{
	if (ui.charCombo->count() > 0) {
		QImage img = QImage("img/" + name + ".jpg").scaled(ui.charLabel->width(), ui.charLabel->height(), Qt::KeepAspectRatio);
		ui.charLabel->setPixmap(QPixmap::fromImage(img));
		ui.charLabel->repaint();
		CharacterObject c{ mController->getCharacterAt(name.split("char")[1].toInt()) };
		ui.lblClosedZones->setText("Nombre de zones fermees : " + QString::number(c.getClosedZones()));
		ui.lblClosedZones->repaint();
		ui.lblCorners->setText("Nombre de coins selon Harris : " + QString::number(c.getCorners()));
		ui.lblCorners->repaint();
		ui.lblRatio->setText("Ratio pixels blancs/pixels noirs : " + QString::number(c.getRatio()));

		if (c.getLabel() != "") { displayKnnResults(c.getKnnResults(), c.getLabel()); }
		else {
			ui.knnResLabel->setText("Aucun resultat a afficher.");
			ui.knnVerdictEdit->setText("-");
		}

		ui.knnResLabel->repaint();
		ui.knnVerdictEdit->repaint();
		ui.lblRatio->repaint();
	}
}

void MainWindow::displayKnnResults(std::map<std::string, double> kBests, std::string best)
{
	QLabel * knn{ ui.knnResLabel };
	knn->setText("Resultats...\n");
	int count{ 1 };

	for (auto p : kBests) {
		std::string res{ std::to_string(count) + " : " + p.first + ", score : " + std::to_string(p.second) + "\n" };
		knn->setText(knn->text() + res.c_str());
		++count;
	}

	knn->repaint();
	ui.knnVerdictEdit->setText(best.c_str());
	ui.knnVerdictEdit->repaint();
}

void MainWindow::displayAllKnnResults(std::string results)
{
	ui.lblIdentifyAll_2->setText(results.c_str());
}

int MainWindow::getValueSlider()
{
	return ui.knnSlider->value();
}

std::vector<double> MainWindow::getWeight()
{
 	return std::vector<double> { ui.closedZonesEdit->text().toDouble(),
							   ui.ratioEdit->text().toDouble(),
							   ui.cornersEdit->text().toDouble(),
								ui.pixelMapEdit->text().toDouble()};
}

void MainWindow::changeImageDisplay(std::string path)
{
	QImage img = QImage(path.c_str()).scaled(ui.fullImageView->width(), ui.fullImageView->height(), Qt::KeepAspectRatio);
	ui.fullImageView->setPixmap(QPixmap::fromImage(img));
	ui.analyzeBtn->setDisabled(false);
}

void MainWindow::addToDatabase()
{
	mController->addToDatabase(ui.knnVerdictEdit->text(), ui.charCombo->currentIndex());
}

//----- SLOTS POUR LE CONTRÔLEUR ----//

void MainWindow::changeStatus_fromCTL(QString msg)
{
	emit statusLbl(msg);
}

void MainWindow::makeProgress_bar_fromCTL(int step)
{
	emit pBar(step);
}

void MainWindow::addCharToCombo_fromCTL(QString name)
{
	emit charCombo(name);
}

void MainWindow::triggerProgressBar_fromCTL(bool check)
{
	emit triggerPBar(check);
}

void MainWindow::displayKnnResults_fromCTL(std::map<std::string, double> kBests, std::string best)
{
	emit knnResults(kBests, best);
}

void MainWindow::displayAllKnnResults_fromCTL(std::string results)
{
	emit allKnnResults(results);
}

void MainWindow::changeImage_fromCTL(std::string path)
{
	emit changeImage(path);
}


