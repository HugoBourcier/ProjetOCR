#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include "sqlite3.h"
#include <Constants.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "Constants.h"

//--------------------------//
// Classe DatabaseHelper	//
//							//
// Objet effectuant des		//
// requête à la base de 	//
// données. (sqlite)		//
//--------------------------//

class DatabaseHelper
{
private:
	sqlite3 * mDB;
	//pour entreposer les résultats des select : 
	std::list<std::map<std::string, std::string>> mResults;
	std::list<std::vector<char>> mResultsBlob;

public:
	//constructeur, desctructeur
	DatabaseHelper();
	~DatabaseHelper();

	//ouverture, fermeture
	bool openDatabase(std::string databaseName);
	bool closeDatabase(void);

	//exécution d'une requête sans retour (ex, CREATE TABLE)
	bool executeStatementNoReturn(std::string sqlStatement);

	//insertions
	bool insert(std::string tableName, std::list<std::string> columns, std::list<std::string> values);
	bool insertWithBlob(std::string tableName, std::list<std::string> columns, std::list<std::string> values, std::vector<char> blob);

	//select + fonctions callback 
	bool select(std::string tableName, std::list<std::string> columns, std::string whereV1, std::string whereV2);
	int static callback(void *data, int argc, char **argv, char **azColName);
	bool selectBLOB(std::string tableName, std::string columns, std::string whereV1, std::string whereV2);
	int static callbackBlob(void * object, int argc, char ** argv, char ** azColName);

	//ajouter à la variable locale des résultats
	void addToResults(std::map<std::string, std::string> resMap);
	void addToResults(std::vector<char> resV);

	//utilitaires
	void addValuesToStatement(std::string & statement, std::list<std::string> values);

	//getters
	std::list< std::map<std::string, std::string>> getResults();
	std::list<std::vector<char>> getResultsBlob();
};

#endif //DATABASEHELPER_H
