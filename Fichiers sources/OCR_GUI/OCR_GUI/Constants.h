#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>
#include <list>

//----------------------//
//						//
// CONSTANTES GLOBALES	//
//						//
//----------------------//

//------ POUR LA BASE DE DONNÉES ------//

	//nom BD
static const std::string NOM_BD{ "OCR_database.db" };

//création de tables
static const std::string
DATASET_TABLE{ "dataset" }, LABELS_TABLE{ "labels" },
CREATE_LABELS_TABLE
{ "CREATE TABLE labels(id INTEGER PRIMARY KEY NOT NULL,"
				" character TEXT NOT NULL);" },
	CREATE_DATASET_TABLE
{ "CREATE TABLE dataset(id INTEGER PRIMARY KEY NOT NULL, "
				"nbClosedZones INTEGER NOT NULL, "
				"blackWhiteRatio REAL NOT NULL, "
				"nbCorners INTEGER NOT NULL, "
				"pixelsVector BLOB NOT NULL, "
				"label_id INTEGER NOT NULL, "
					"FOREIGN KEY (label_id) REFERENCES labels(id));" };

//noms colonnes table dataset
static const std::list<std::string> COLONNES_DATASET{ "nbClosedZones", "blackWhiteRatio", "nbCorners", "pixelsVector", "label_id" };
static const std::list<std::string> COLONNES_DATASET_MINUSBLOB{ "nbClosedZones", "blackWhiteRatio", "nbCorners", "label_id" };
static const std::list<std::string> COLONNES_DATASET_BLOB{ "pixelsVector" };

//supprimer les tables
static const std::string
DROP_TABLE_LABELS
{ "DROP TABLE labels;" },
DROP_TABLE_DATASET
{ "DROP TABLE DATASET;" };

//pour l'insertion de labels de l'alphabet
static const std::vector<std::string>
ALPHABET({ "\"A\"", "\"B\"", "\"C\"", "\"D\"","\"E\"","\"F\"","\"G\"",
		"\"H\"" ,"\"I\"" ,"\"J\"" ,"\"K\"" ,"\"L\"" ,"\"M\"" ,"\"N\"",
		"\"O\"" ,"\"P\"" ,"\"Q\"" ,"\"R\"" ,"\"S\"" ,"\"T\"" ,
		"\"U\"", "\"V\"", "\"W\"", "\"X\"", "\"Y\"", "\"Z\"" });

//------- MESSAGES POUR LE GUI -----//
static const std::string
MSG_IDENTIFICATION_START{ "Status : Identification en cours..." },
MSG_IDENTIFICATION_END{ "Status : Fin de l'identification!" },
MSG_IDENTIFICATION_FAIL{ "Status : Echec de l'identification." },
MSG_LOADING_DATA{ "Status : Chargement du dataset..." },
MSG_LOADING_END{ "Status : Fin du chargement!" },
MSG_LOADING_LETTER{ "Status : Chargement d'une nouvelle lettre..." },
MSG_LOADING_LETTER_END{"Status : Fin de l'ajout !"};



#endif //CONSTANTS_H
