#include "DatabaseLoading.h"

DatabaseLoading::DatabaseLoading(MainController * controller, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

DatabaseLoading::~DatabaseLoading()
{
}


void DatabaseLoading::progressBarStep(int step)
{
	ui.progressBar->setValue(ui.progressBar->value() + step);
}