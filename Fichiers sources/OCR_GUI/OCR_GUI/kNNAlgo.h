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
// des données avec un		//
// algo KNN.				//
//--------------------------//

class kNNAlgo
{
public:
	kNNAlgo();
	~kNNAlgo();

	//structure interne modélisant un caractère
	//(version simplifiée de la classe CharacterObject)
	struct character_s {
		std::string label;
		std::vector<double> coordinates;
		std::vector<uint8_t> pixelsMap;
		double knnScore;
	};

private:
	//constantes privées
	const std::vector<double> weightedDistance{ 250.0,2.0,4.0,6.0 };
	//variables privées
	double mWeightClosedZones, mWeightRatio, mWeightCorners, mWeightPixels;
	std::vector<kNNAlgo::character_s> mDataset;

	//retourner les k meilleurs éléments du dataset trié
	std::map<std::string, double> getBestLabels(int kBest);
	//template calculant la distance euclidienne entre deux vecteurs
	template <typename T >
	double calcScore(std::vector<T> vectorTarget, std::vector<T> vectorDataset, std::vector<double> weight = std::vector<double>());

public:
	//ajouter un élément au dataset
	void addToDataset(std::string label, std::vector<double> coordo, std::vector<uint8_t> pixelsMap);
	//trouver l'étiquette ayant le meilleur score parmi un map <étiquette, score>
	std::string kNNVerdict(std::map<std::string, double> scores);
	//ajuster le poids relatifs des features depuis l'extérieur
	void setWeight(std::vector<double> listWeight);
	//processus principal
	std::map<std::string, double> process(kNNAlgo::character_s targetCharacter, int kBest);

};

#endif //KNNALGO