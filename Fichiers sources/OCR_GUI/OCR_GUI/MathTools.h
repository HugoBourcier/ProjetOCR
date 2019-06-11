#ifndef MATHTOOLS_H
#define MATHTOOLS_H

#include <vector>

//--------------------------//
// Classe kNNAlgo        	//
//							//
// Classe contenant des		//
// fonctions statiques pour //
// quelques opérations		//
// mathématiques.			//
//--------------------------//

class MathTools
{
public:
	MathTools() {};
	
	//distance euclidienne
	template <typename T>
	static double euclideanDistance(std::vector<T> v1, std::vector<T> v2, std::vector<double> weight = std::vector<double>());
	//déterminant d'une matrice 2x2
	double static determinant2X2(std::vector<double>);
	//trace d'une matrice
	double static traceMatrix(std::vector<double> matrix, int width, int height);
	//multiplication d'une matrice
	std::vector<int> static multiplyMatrix(std::vector<int> m1, std::vector<int> m2, int height, int width);
};

//Distance euclidienne
template<typename T>
double MathTools::euclideanDistance(std::vector<T> v1, std::vector<T> v2, std::vector<double> weight)
{
	double sum{ 0 };

	for (size_t i{ 0 }; i < v1.size(); ++i) { sum += (weight[i] * pow(v1[i] - v2[i], 2)); }

	return sqrt(sum);
}

#endif //MATHTOOLS_H
