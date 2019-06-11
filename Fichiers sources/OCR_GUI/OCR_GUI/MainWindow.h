#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "MainController.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(MainController * controller, QWidget *parent = Q_NULLPTR);
	Q_SLOT void makeProgress_bar_fromCTL(int step);
	Q_SLOT void addCharToCombo_fromCTL(QString name);
	Q_SLOT void triggerProgressBar_fromCTL(bool check);
	Q_SLOT void displayKnnResults_fromCTL(std::map<std::string, double> kBests, std::string best);
	Q_SLOT void changeImage_fromCTL(std::string path);
	Q_SLOT void displayAllKnnResults_fromCTL(std::string results);
	Q_SLOT void changeStatus_fromCTL(QString msg);
	int getValueSlider();
	std::vector<double> getWeight();


private:
	Ui::MainWindowClass ui;
	MainController * mController;

private slots:
	void openFileBtn_pressed();
	void emptyEverything();
	void analyzeBtn_pressed();
	void progressBarStep(int step);
	void triggerProgressBar(bool check);
	void changeStatus(QString msg);
	void addToDatabase();
	void addCharToCombo(QString name);
	void analyze();
	void analyzeAll();
	void comboSelect(QString name);

	void changeImageDisplay(std::string path);
	void displayKnnResults(std::map<std::string, double> kBests, std::string best);
	void displayAllKnnResults(std::string results);

signals:
	void statusLbl(QString msg);
signals:
	void pBar(int step);
signals:
	void charCombo(QString name);
signals:
	void triggerPBar(bool check);
signals:
	void knnResults(std::map<std::string, double> kBests, std::string best);
signals:
	void changeImage(std::string path);
signals:
	void allKnnResults(std::string results);

};
