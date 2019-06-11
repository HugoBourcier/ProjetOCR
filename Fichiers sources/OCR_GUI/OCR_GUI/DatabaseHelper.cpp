#include "DatabaseHelper.h"
//#include <iostream>


DatabaseHelper::DatabaseHelper()
{
}


DatabaseHelper::~DatabaseHelper()
{
}

//------ GETTER ------//


std::list<std::map<std::string, std::string>> DatabaseHelper::getResults()
{
	return mResults;
}

std::list<std::vector<char>> DatabaseHelper::getResultsBlob()
{
	return mResultsBlob;
}

//----- OUVRIR ET FERMER ------//

bool DatabaseHelper::openDatabase(std::string databaseName)
{
	return sqlite3_open(databaseName.c_str(), &mDB);
}

bool DatabaseHelper::closeDatabase(void)
{
	return sqlite3_close(mDB);
}

//------ EXECUTER UNE REQUÊTE ------//

bool DatabaseHelper::executeStatementNoReturn(std::string sqlStatement)
{
	return sqlite3_exec(mDB, sqlStatement.c_str(), NULL, 0, NULL);
}

//----- FONCTIONS PERMETTANT LE SELECT ------//

//exécuter la requête select
bool DatabaseHelper::select(std::string tableName, std::list<std::string> columns, std::string whereV1, std::string whereV2)
{
	mResults.clear();
	std::string statement{ "SELECT " };

	for (std::list<std::string>::iterator it = columns.begin(); it != columns.end(); ++it) {
		statement += *it;
		if (*it != columns.back()) statement += ",";
	}

	statement += " FROM " + tableName;

	if (whereV1 != "") { statement += " WHERE " + whereV1 + " = " + whereV2 + ";"; }
	else { statement += ";"; }

	return sqlite3_exec(mDB, statement.c_str(), callback, this, NULL);
}

//fonction appelée pour chaque résultat du select
//insérer les données sous la forme d'un map dans la liste mResults
// 1 map = 1 colonne
int DatabaseHelper::callback(void * object, int argc, char ** argv, char ** azColName)
{
	std::map<std::string, std::string> results;

	for (int i{ 0 }; i < argc; ++i) {
		results.insert(std::pair<std::string, std::string>(azColName[i], argv[i] ? argv[i] : NULL));
	}

	DatabaseHelper * const db = static_cast<DatabaseHelper*>(object);
	db->addToResults(results);

	return 0;
}

//reçoit en paramètre un map,l'intègre à la liste des résultats
void DatabaseHelper::addToResults(std::map<std::string, std::string> resMap)
{
	mResults.push_back(resMap);
}
//reçoit en paramètre un vector<char>, l'intègre aux résultats de blobs
void DatabaseHelper::addToResults(std::vector<char> resV)
{
	mResultsBlob.push_back(resV);
}

//recuperer un BLOB
bool DatabaseHelper::selectBLOB(std::string tableName, std::string column, std::string whereV1, std::string whereV2)
{
	mResultsBlob.clear();
	std::string statement{ "SELECT " + column + " FROM " + tableName + ";" };

	return sqlite3_exec(mDB, statement.c_str(), callbackBlob, this, NULL);

	//return true;
}

//fonction appelee pour chaque resultat du selectBlob
int DatabaseHelper::callbackBlob(void * object, int argc, char ** argv, char ** azColName)
{
	std::vector<char> results;

	results.push_back(*argv[0]);

	while (*argv[0]++) { results.push_back(*argv[0]); }

	DatabaseHelper * const db = static_cast<DatabaseHelper*>(object);
	db->addToResults(results);

	return 0;
}

//-------- INSERT -------- //

bool DatabaseHelper::insert(std::string tableName, std::list<std::string> columns, std::list<std::string> values)
{
	std::string statement{ "INSERT INTO " + tableName + " " };

	addValuesToStatement(statement, columns);
	statement.append(" VALUES ");
	addValuesToStatement(statement, values);
	//std::cout << statement;
	sqlite3_exec(mDB, statement.c_str(), NULL, 0, NULL);
	//std::cout << sqlite3_errmsg(mDB);
	return true;
}

bool DatabaseHelper::insertWithBlob(std::string tableName, std::list<std::string> columns, std::list<std::string> values, std::vector<char> blob)
{
	std::string statement{ "INSERT INTO " + tableName + " " };

	addValuesToStatement(statement, columns);
	statement.append(" VALUES ");
	addValuesToStatement(statement, values);

	sqlite3_stmt *stmt = NULL;
	int rc = sqlite3_prepare_v2(mDB,
		statement.c_str(),
		-1, &stmt, NULL);
	rc = sqlite3_bind_blob(stmt, 1, blob.data(), blob.size(), SQLITE_STATIC);
	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	//std::cout << "Resultat : " << sqlite3_errmsg(mDB) << std::endl;
	return true;
}

//------ FONCTIONS UTILITAIRES ------//

//ajouter une série de valeurs entre parenthèses 
void DatabaseHelper::addValuesToStatement(std::string & statement, std::list<std::string> values)
{
	statement.append("(");

	for (std::list<std::string>::iterator it = values.begin(); it != values.end(); ++it) {
		statement.append(*it);
		if (std::next(it) != values.end()) statement += ",";
		else statement.append(")");
	}
}


