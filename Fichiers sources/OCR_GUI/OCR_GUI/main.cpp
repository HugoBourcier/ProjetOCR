#include "MainController.h"
#include <QtWidgets/QApplication>
#include "Constants.h"
#include <stdlib.h>
#include <windows.h>
#include <qdebug.h>
#include <Magick++.h>
#include <iostream>
#include <string>
#include <conio.h>

int main(int argc, char *argv[])
{
	try {
		qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
		MainController c;
		return c.exec(argc, argv);
	}
	catch (std::exception e) {
		qDebug() << "Exception : " << e.what();
		return 0;
	}

	//DatabaseHelper dh;
	//QString s("A");
	//std::string tempString(s.toLatin1().data());
	//std::string toAdd("\'" + tempString + "\'");
	//dh.openDatabase(NOM_BD);
	//dh.select(LABELS_TABLE, std::list<std::string>{"id"}, "character", toAdd);
	//std::cout << dh.getResults().front()["id"];
	//return 0;
	//std::string path;
	//std::cout << "Entrer path : ";
	//std::cin >> path;
	//Magick::Image img;
	//img.read(path);
	//std::cout << img.isOpaque();
	//getch();
}
