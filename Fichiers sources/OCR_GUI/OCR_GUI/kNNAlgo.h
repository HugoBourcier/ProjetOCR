#ifndef KNNALGO_H
#define KNNALGO_H

#include <string>
#include "CharacterObject.h"
#include "MathTools.h"

//--------------------------//
// Classe kNNAlgo        	//
//							//
// Classe contenant des		//
// fonctions statiques et	//
// des outils pour analyser	//
// des donn�es avec un		//
// algo KNN.				//
//--------------------------//

class kNNAlgo
{
public:
	kNNAlgo();
	~kNNAlgo();

	//structure interne mod�lisant un caract�re
	//(version simplifi�e de la classe CharacterObject)
	struct character_s {
		std::string label;
		std::vector<double> coordinates;
		std::vector<uint8_t> pixelsMap;
		double knnScore;
	};

private:
	//constantes priv�es
	const std::vector<double> weightedDistance{ 250.0,2.0,4.0,6.0 };
	//variables priv�es
	double mWeightClosedZones, mWeightRatio, mWeightCorners, mWeightPixels;
	std::vector<kNNAlgo::character_s> mDataset;

	//retourner les k meilleurs �l�ments du dataset tri�
	std::map<std::string, double> getBestLabels(int kBest);
	//template calculant la distance euclidienne entre deux vecteurs
	template <typename T >
	double calcScore(std::vector<T> vectorTarget, std::vector<T> vectorDataset, std::vector<double> weight = std::vector<double>());

public:
	//ajouter un �l�ment au dataset
	void addToDataset(std::string label, std::vector<double> coordo, std::vector<uint8_t> pixelsMap);
	//trouver l'�tiquette ayant le meilleur score parmi un map <�tiquette, score>
	std::string kNNVerdict(std::map<std::string, double> scores);
	//ajuster le poids relatifs des features depuis l'ext�rieur
	void setWeight(std::vector<double> listWeight);
	//processus principal
	std::map<std::string, double> process(kNNAlgo::character_s targetCharacter, int kBest);

};

#endif //KNNALGO