#include "kNNAlgo.h"
#include <iostream>

kNNAlgo::kNNAlgo()
{
}

kNNAlgo::~kNNAlgo()
{
}

//---- AJOUTER UN CARACTÈRE AU DATASET -----//

void kNNAlgo::addToDataset(std::string label, std::vector<double> coordo, std::vector<uint8_t> pixelsMap)
{
	mDataset.push_back(character_s{ label, coordo, pixelsMap, 0.008 });
}

//----- CALCULER LA DISTANCE EUCLIDIENNE ENTRE DEUX VECTEURS ----//

template<typename T>
double kNNAlgo::calcScore(std::vector<T> vectorTarget, std::vector<T> vectorDataset, std::vector<double> weight)
{
	if (weight.size() <= 0) { weight = std::vector<double>(vectorTarget.size(), 1.00); }

	return MathTools::euclideanDistance<T>(vectorTarget, vectorDataset, weight);
}

//------ PROCESSUS GLOBAL -----//
//	1. Pour chaque caractère du dataset:
//			Calculer la distance entre ses pixels et les pixels de la cible
//			Ajouter ce score au vecteur de features
//			Calculer la distance entre les features et les feaetures de la cible
//	2. Ordonner le dataset selon les résultats
//	3. Retourner un map <étiquette, score> contenant les meilleurs scores.
std::map<std::string, double> kNNAlgo::process(kNNAlgo::character_s targetCharacter, int kBest)
{
	std::vector<double> weight{ mWeightClosedZones, mWeightRatio, mWeightCorners, mWeightPixels };
	
	for (auto & c : mDataset) {
		std::vector<double> dataCoordinates{ c.coordinates };
		dataCoordinates.push_back(calcScore<uint8_t>(targetCharacter.pixelsMap, c.pixelsMap));
		c.knnScore = MathTools::euclideanDistance(targetCharacter.coordinates, dataCoordinates, weight);
	}

	std::sort(mDataset.begin(), mDataset.end(),
		[](kNNAlgo::character_s c1, kNNAlgo::character_s c2) -> bool {return c1.knnScore < c2.knnScore; });

	return getBestLabels(kBest);
} 

//Construire un map <étiquette, score> contenant les k meilleurs scores
//à partir du dataset préalablement trié.
std::map<std::string, double> kNNAlgo::getBestLabels(int kBest)
{
	std::map<std::string, double> bestScores;
	double max{ 0 };
	std::string result;

	for (int i{ 0 }; i < kBest; ++i) {
		bestScores[mDataset[i].label] += 1000*(1.0/(pow((mDataset[i].knnScore),2.0)+1.0));
		if (bestScores[mDataset[i].label] > max) {
			max = bestScores[mDataset[i].label];
			result = mDataset[i].label;
		}
	}

	return bestScores;
}

//Retourne l'étiquette ayant le meilleur score à partir d'un map <étiquette, score>.
std::string kNNAlgo::kNNVerdict(std::map<std::string, double> scores)
{
	auto p{ std::max_element(scores.begin(), scores.end(),
			[](std::pair<std::string,double> p1, std::pair<std::string,double> p2) { return p1.second < p2.second; }) };
	return p->first;
}

//Ajuster le poids relatif des features selon un vecteur externe.
void kNNAlgo::setWeight(std::vector<double> listWeight)
{
	mWeightClosedZones = listWeight[0];
	mWeightRatio = listWeight[1];
	mWeightCorners = listWeight[2];
	mWeightPixels = listWeight[3];
}