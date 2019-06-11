#ifndef IMAGEOPERATIONTOOLS_H
#define IMAGEOPERATIONTOOLS_H

#include "Magick++.h"
#include <vector>
#include <queue>
#include <list>

//---------------------------//
// Classe ImageTools    	 //
//							 //
// Contient des fonctions	 //
// statiques et des outils   //
// pour faire des opérations //
// sur des images.			 //
//---------------------------//

class ImageTools
{

public:
	ImageTools() {};

	//---- pixels_s ----//
	//structure interne pour stocker
	//les données d'un pixel
	//(conçue pour assurer l'indépendance de la classe)

	struct pixels_s {
		int r, g, b, a;

		pixels_s() {}

		pixels_s(int r, int g, int b, int a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		bool operator==(const pixels_s &l)
		{
			int test{ r + g + b - l.r - l.g - l.b };

			if (test < 50 && test > -50) return true;
			else return false;
		}

		bool operator!=(const pixels_s l)
		{
			return (!(operator==(l)));
		}

	};

	//constantes publiques
	static const pixels_s mWhite, mBlack, mRed;
	static const int borderSize;

	//détection des contours
	std::vector<pixels_s> static findEdges(std::vector<pixels_s> v, int imgWidth, int imgHeight);

	//remplissage par diffusion
	static void floodFill(std::vector<pixels_s> & v, int width, int height, pixels_s target, pixels_s rep, int firstPixel);

	//détection des coins
	int static cornerDetection(std::vector<pixels_s> v, int imgWidth, int imgHeight);

	//détection des zones fermées
	bool static isClosedRegion(std::vector<pixels_s> v, int firstPixel, pixels_s border, pixels_s inside, int width, int height);
 
	//trouver un pixel dans une image
	int static findInsidePixel(std::vector<pixels_s> v, pixels_s firstTarget, pixels_s secondTarget, int width, int startPos = 0);
	int static findPixelHorizontal(std::vector<pixels_s> v, int startPos, pixels_s target, bool order = true, int width = 0, bool nextLine = true);
	int static findPixelVertical(std::vector<pixels_s> v, int width, int startPos, pixels_s target, bool order = true, int jump = 0, int jumpDown = 0);

	//ajouter une bordure noire à une image
	std::vector<pixels_s> static addBorder(std::vector<ImageTools::pixels_s> v, int width, int height);
	static int modifySizeBorder(int width);

	//conversion vecteur de pixels -> vecteur d'entier 8 bits
	std::vector<uint8_t> static pixelsToBinaryNumeric(std::vector<ImageTools::pixels_s> vPixels);

	//convolution avec un filtre gaussien
	//pour un vecteur de pixels_s
	static std::vector<ImageTools::pixels_s> gaussianFilterAlgo(std::vector<ImageTools::pixels_s> imageData, int width, int height);
	
	//extraction de blobs
	static std::vector<std::vector<pixels_s>> blobProcess(std::vector<pixels_s> img, int width, int height);
	static std::vector<int> blobExtraction(std::vector<pixels_s> &v, int width, int height, int & nbLabels);
	static void mapBlob(std::vector<int>& blobScores, std::vector<pixels_s>& vImg, int & labelCount, int pixelPos, int width, pixels_s background);

private:
	//constantes privées : filtres
	static const std::vector<int> mSobelX, mSobelY;
	static const std::vector<double> mGaussian3x3;

	//pour la détection des contours
	//filtre de Sobel
	std::vector<std::pair<int, int>> static sobelFilterAlgo(std::vector<pixels_s> imageData, int width, int height);
	//calculer le score d'un pixel après Sobel
	int static calcMagnitude(int sobelX, int sobelY);
	//convertir en noir et blanc selon Sobel
	std::vector<pixels_s> static convertToBinary(std::vector<int> score, int width, int height);

	//convolution avec un filtre gaussien (utilisées à l'interne seulement)
	//pour un vecteur de données simples
	std::vector<double> static gaussianFilterAlgo(std::vector<int> imageData, int width, int height);
	//surcharge pour un vecteur de données en pair
	std::vector<std::pair<double, double>> static gaussianFilterAlgo(std::vector<std::pair<int, int>> imageData, int width, int height);

	//détection des coins selon Harris
	//algorithme complet
	std::vector<double> static harrisAlgo(std::vector<std::pair<double, double>> gaussianPower, std::vector<double> gaussianXYProduct, int width, int height);
	//création de la matrice M sous la forme :
	//[ sommation Ix^2,	sommation Ix*Iy
	//  sommation Ix*Iy, sommation Iy^2]
	std::vector<double> static harrisSummedUpMatrix(int pixelIndex, std::vector<std::pair<double, double>> gaussianPower,
		std::vector<double> gaussianXYProduct, std::vector<int> window);
	//calcul du score Harris selon la matrice M
	double static harrisScore(std::vector<double> harrisRep);

	//utilitaires
	//permet de retrouver une fenêtre 3x3 autour d'un pixel
	std::vector<int> static build3X3Window(int width);
	//luminance d'un pixel selon ses données RGB
	int static getRGBLuminance(pixels_s p);
	//insérer des pixels dans un vecteur échantillon selon un vecteur de pixels d'une image
	//puis les convertir s'ils remplissent une condition
	template <typename T>
	void static pushAndConvertAdjacentPixels(std::list<int> & q, std::vector<T> & v, int pixel, T condition, T change, int width);
	//retourne vrai si le pixel est à une extrémité de l'image
	bool static isBorderPixel(int pixel, int width, int height);
};

#endif //IMAGEOPERATIONTOOLS_H