#ifndef DATABASELOADING_H
#define DATABASELOADING_H

#include <QWidget>
#include "ui_DatabaseLoading.h"
#include "MainController.h"

class DatabaseLoading : public QWidget
{
	Q_OBJECT

public:
	DatabaseLoading(MainController * controller, QWidget *parent = Q_NULLPTR);
	~DatabaseLoading();

	void progressBarStep(int step);

private:
	Ui::DatabaseLoading ui;
};

#endif //DATABASE_LOADING