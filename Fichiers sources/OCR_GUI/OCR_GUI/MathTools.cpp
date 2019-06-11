#include "MathTools.h"

//Déterminant d'une matrice
double MathTools::determinant2X2(std::vector<double> matrix)
{
	double det{ ((matrix[0] * matrix[3]) - (matrix[1] * matrix[2])) };
	return det;
}

//Trace d'une matrice
double MathTools::traceMatrix(std::vector<double> matrix, int width, int height)
{
	double sum{ 0 };
	int count{ 0 };

	for (int i{ 0 }; i < width; ++i) {
		sum += matrix[(i*width) + count];
		++count;
	}

	return sum;
}

//Mulitplication de matrices.
//height = hauteur de la première matrice
//width = hauteur de la seconde matrice
std::vector<int> MathTools::multiplyMatrix(std::vector<int> m1, std::vector<int> m2, int height, int width)
{
	std::vector<int> results(height*width);
	int dot;

	for (int k{ 0 }; k < height; ++k) {

		for (int i{ 0 }; i < width; ++i) {
			dot = 0;
			for (int j{ 0 }; j < width; ++j) dot += m1[(k*width) + j] * m2[(j*width) + i];
			results[(k*width) + i] = dot;
		}
	}

	return results;
}
