#include "ImageTools.h"
#include "MathTools.h"
#include <math.h>
#include <numeric>
#include <qdebug.h>

//-------- INITIALISATION DES CONSTANTES ----------//

const ImageTools::pixels_s ImageTools::mWhite = { 255,255,255,1 },
ImageTools::mBlack = { 0,0,0,1 },
ImageTools::mRed = { 255,0,0,1 };

const std::vector<int>
ImageTools::mSobelX{
-1, 0, 1,
-2, 0, 2,
-1, 0, 1 },
ImageTools::mSobelY{
-1, -2, -1,
0, 0, 0,
1, 2, 1
};

const std::vector<double>
ImageTools::mGaussian3x3{
0.102059, 0.115349, 0.102059,
0.115349, 0.130371, 0.115349,
0.102059, 0.115349, 0.102059
};

const int ImageTools::borderSize{ 5 };

//------------------- ALGOS AVEC FILTRE GAUSSIEN ---------------------//

	//Convolution qui applique un filtre gausséen
	//sur un vecteur de pixels
std::vector<ImageTools::pixels_s> ImageTools::gaussianFilterAlgo(std::vector<ImageTools::pixels_s> imageData, int width, int height)
{
	std::vector<pixels_s> results(imageData.size());
	std::vector<int> window{ build3X3Window(width) };

	for (int i{ 0 }; i < imageData.size(); ++i) {
		int count{ 0 };
		pixels_s tempValues(0, 0, 0, 0);
		if (isBorderPixel(i, width, height)) {
			for (int j{ 0 }; j < window.size(); ++j) {
				pixels_s p{ imageData[j] };
				tempValues.r += p.r* mGaussian3x3[count];
				tempValues.g += p.g* mGaussian3x3[count];
				tempValues.b += p.b* mGaussian3x3[count];
				++count;
			}
		}
		else {
			for (auto w : window) {
				pixels_s p{ imageData[i + w] };
				tempValues.r += p.r* mGaussian3x3[count];
				tempValues.g += p.g* mGaussian3x3[count];
				tempValues.b += p.b* mGaussian3x3[count];
				++count;
			}
		}

		results[i] = pixels_s(tempValues.r, tempValues.g, tempValues.b, 255);
	}

	return results;
}

	//Convolution qui applique un filtre gausséen
	//sur un vecteur de nombres entiers.
std::vector<double> ImageTools::gaussianFilterAlgo(std::vector<int> imageData, int width, int height)
{
	std::vector<double> results(imageData.size()), tempValues(9);
	std::vector<int> window{ build3X3Window(width) };
	double score;

	for (int i{ 0 }; i < imageData.size(); ++i) {
		int count{ 0 };
		if (!isBorderPixel(i, width, height)) {
			for (auto w : window) {
				tempValues[count] = imageData[i + w] * mGaussian3x3[count];
				++count;
			}
			double sum{ std::accumulate(tempValues.begin(), tempValues.end(), 0.00) };
			results[i] = sum / 9;
		}
		else {
			results[i] = 0.00;
		}
	}

	return results;
}

	//Convolution qui applique un filtre gausséen
	//sur un vecteur de pair <entier, entier>
	//(fonction utilisée dans la détection des points de Harris)
std::vector<std::pair<double, double>> ImageTools::gaussianFilterAlgo(std::vector<std::pair<int, int>> imageData, int width, int height)
{
	std::vector<std::pair<double, double>> results(imageData.size()), tempValues(9);
	std::vector<int> window{ build3X3Window(width) };
	double score;

	for (int i{ 0 }; i < imageData.size(); ++i) {
		int count{ 0 };
		if (!isBorderPixel(i, width, height)) {
			for (auto w : window) {
				tempValues[count].first = imageData[i + w].first * mGaussian3x3[count];
				tempValues[count].second = imageData[i + w].second * mGaussian3x3[count];
				++count;
			}
			double sumX{ 0 }, sumY{ 0 };

			for (int j{ 0 }; j < 9; ++j) {
				sumX += tempValues[j].first;
				sumY += tempValues[j].second;
			}

			results[i].first = sumX / 9.00;
			results[i].second = sumY / 9.00;
		}
		else {
			results[i] = std::make_pair(0.00, 0.00);
		}
	}

	return results;
}

//------------------ DÉTECTION DES CONTOURS -------------------//

//Fonction du processus global
//	1. Applique le filtre sur le vecteur de pixels
//	2. Calcule la magnitude pour chacun des résultats
//	3. Retourne un vecteur noir et blanc selon les résultats
std::vector<ImageTools::pixels_s> ImageTools::findEdges(std::vector<ImageTools::pixels_s> v, int imgWidth, int imgHeight)
{
	std::vector<int> pixelMagnitude(v.size());
	std::fill(pixelMagnitude.begin(), pixelMagnitude.end(), 0);

	std::vector<std::pair<int, int>> sobelResult{ sobelFilterAlgo(v, imgWidth, imgHeight) };

	for (int i{ 0 }; i < v.size(); ++i) {
		pixelMagnitude[i] = calcMagnitude(sobelResult[i].first, sobelResult[i].second);
	}

	return convertToBinary(pixelMagnitude, imgWidth, imgHeight);
}

//Fonction qui applique le filtre de Sobel pour trouver les contours
//Retourne un vecteur de pair ou chaque element = (score selon X, score selon Y)
//Ne s'intéresse qu'aux pixels autour desquels peut être tracée une zone de 3x3
	//(ne regarde pas le cadre)

std::vector<std::pair<int, int>> ImageTools::sobelFilterAlgo(std::vector<ImageTools::pixels_s> imageData, int width, int height)
{
	std::vector<std::pair<int, int>>
		sobelScores(imageData.size());
	std::vector<int> window{ build3X3Window(width) };

	for (int i{ 0 }; i < imageData.size(); ++i) {

		int sobelScoreX{ 0 }, sobelScoreY{ 0 };

		if (!isBorderPixel(i, width, height)) {
			for (int j{ 0 }; j < window.size(); ++j) {

				int l{ getRGBLuminance(imageData[i + window[j]]) };

				sobelScoreX += (l*mSobelX[j]);
				sobelScoreY += (l*mSobelY[j]);
			}
			sobelScores[i] = std::make_pair(abs(sobelScoreX), abs(sobelScoreY));
		}
	}

	return sobelScores;
}

//Calcul la magnitude d'un pixel selon le score du filtre de Sobel
//+ élevé = + de chance d'être un contour
int ImageTools::calcMagnitude(int sobelX, int sobelY)
{
	return std::round(sqrt(pow(sobelX, 2) + pow(sobelY, 2)));
}

//Conversion en couleurs binaires (noir ou blanc)
//selon les résultats de l'algorithme de Sobel
std::vector<ImageTools::pixels_s> ImageTools::convertToBinary(std::vector<int> sobelScore, int width, int height)
{
	int max{ *(std::max_element(sobelScore.begin(), sobelScore.end())) };
	int threshold{ int(max*0.25) };

	std::vector<pixels_s> pixels;

	for (size_t i{ 0 }; i < sobelScore.size(); ++i) {
		if (sobelScore[i] < threshold) { pixels.push_back(mBlack); }
		else { pixels.push_back(mWhite); }
	}

	return pixels;
}

//-------------- EXTRACTION DE BLOBS ---------------//

	//Fonction du processus d'extraction des blobs.
	//1. Étiqueter un vecteur de la même taille que l'image selon les blobs trouvés (fonction blobExtraction()).
	//2. Transférer les étiquettes dans un vecteur séparé.
	//3. Retourner un vecteur de vecteur de pixels contenant les blobs individuels.
std::vector < std::vector<ImageTools::pixels_s>> ImageTools::blobProcess(std::vector<pixels_s> img, int width, int height)
{
	int nbLabels{ 0 };
	std::vector<int> blobScore{ ImageTools::blobExtraction(img, width, height, nbLabels) };
	std::vector<std::vector<pixels_s>> vBlobResults;

	for (int i{ 0 }; i < nbLabels-1; ++i) { vBlobResults.push_back(std::vector<pixels_s>(img.size()));}

	for (size_t i{ 0 }; i < blobScore.size(); ++i) {
		int blobLabel{ blobScore[i] };
		if (blobLabel != 0) { vBlobResults[blobLabel - 1][i] = img[i]; }
	}

	return vBlobResults;
}

	//Parcourir le vecteur pour mapper les blobs (amas de pixels qui ont une bordure commune).
	//Le vecteur retourné identifie les positions des blobs selon
	//des étiquettes sous forme de nombres entiers.
	//Effectue en même temps un flood fill des blobs trouvés.
	//L'image est parcourue colonne par colonne.
std::vector<int> ImageTools::blobExtraction(std::vector<pixels_s> &v, int width, int height, int & nbLabels)
{
	pixels_s backgroundPixel{ mBlack }, foregroundPixel{ mWhite };
	int labelCount{ 1 };
	std::vector<int> blobScore(v.size());
	std::fill(blobScore.begin(), blobScore.end(), 0);
	int pixelPos{ 0 }, rowCount{ 0 }, colCount{ 0 };

	while (colCount < width) {
		
		pixelPos = rowCount * width + colCount;
		++rowCount;
		if (rowCount >= height) {
			rowCount = 0;
			++colCount;
		}

		if (!isBorderPixel(pixelPos, width, height) && v[pixelPos] == foregroundPixel && blobScore[pixelPos] == 0) {
			int floodFillStart{findPixelVertical(v, width, pixelPos + 10, mBlack, true, 0)};

			if (floodFillStart > 0) {
				if (isClosedRegion(v, floodFillStart, mWhite, mBlack, width, height)) {
					floodFill(v, width, height, mWhite, mBlack, floodFillStart);
				}
			}
			
			mapBlob(blobScore, v, labelCount, pixelPos, width, backgroundPixel);
		}
	}

	nbLabels = labelCount;
	return blobScore;
}

	//"Map" un blob à partir d'un pixel donné.
	//Parcourt le vecteur à la façon remplissage par diffusion 
	//	à la recherche de pixels adjacents qui != background, les étiquette en conséquence.
	//Incrémente le compteur d'étiquette.
void ImageTools::mapBlob(std::vector<int> & blobScore, std::vector<pixels_s> & vImg, int & labelCount, int pixelPos, int width, pixels_s background)
{
	std::list<int> q;
	int window[] = { -width, width, -1, 1 };

	q.push_front(pixelPos);

	while (!q.empty()) {
		int px{ q.front() };
		q.pop_front();
		for (auto p : window) {
			int windowPos{ px + p };
			if (windowPos > 0 && windowPos < vImg.size()
				&& px % width != 0 && px % width != width - 1
				&& vImg[windowPos] != background && blobScore[windowPos] != labelCount) {
				blobScore[windowPos] = labelCount;
				q.push_front(windowPos);
			}
		}
	}

	++labelCount;
}

//-------------- REMPLISSAGE ---------------//


	//Fonction qui prend en paramètre un pixel et une image
	//et qui effectue une conversion target vers rep
	//tant qu'il y a des pixels de type target.
void ImageTools::floodFill(std::vector<pixels_s> & v, int width, int height, pixels_s target, pixels_s rep, int firstPixel)
{
	int pos[] = { -width, width, -1, 1 };

	std::list<int> q, temp;
	q.push_front(firstPixel);
	v[firstPixel] = target;

	while (!q.empty()) {
		int px{ q.front() };
		q.pop_front();
		ImageTools::pushAndConvertAdjacentPixels(q, v, px, rep, target, width);
	}

}

//------------- TROUVER LES RÉGIONS FERMÉES -------------------//

bool ImageTools::isClosedRegion(std::vector<pixels_s> v, int firstPixel, pixels_s border, pixels_s inside, int width, int height)
{
	bool closedRegion{ true };
	std::list<int> q;
	std::vector<int> window{ build3X3Window(width) };
	q.push_front(firstPixel);
	v[firstPixel] = border;

	while (closedRegion && !q.empty()) {
		int px{ q.front() };
		q.pop_front();
		if (ImageTools::isBorderPixel(px, width, height)) {
			closedRegion = false;
			break;
		}
		ImageTools::pushAndConvertAdjacentPixels(q, v, px, inside, border, width);
	}

	return closedRegion;
}

// ---------- FONCTIONS POUR TROUVER DES PIXELS SPÉCIFIQUES DANS UNE IMAGE -------------//

//trouve un pixel de type secondTarget se trouvant tout de suite après un pixel de type firstTarget
//à partir du milieu de l'image
int ImageTools::findInsidePixel(std::vector<pixels_s> v, pixels_s firstTarget, pixels_s secondTarget, int width, int startPos)
{
	if (startPos == 0) {
		return findPixelVertical(v, width, findPixelVertical(v, width, width / 2, firstTarget), secondTarget);
	}
	else {
		return findPixelVertical(v, width, findPixelVertical(v, width, startPos, firstTarget), secondTarget);
	}
}

//chercher un pixel cible sur l'axe horizontal
//par défaut, nextLine = true : on continue sur les prochaines lignes
//nextLine = false : on arrête à la fin de la ligne (width nécessaire)
//par défaut, order = true : vers la droite
//order = false : vers la gauche
//retourne l'indice
int ImageTools::findPixelHorizontal(std::vector<pixels_s> v, int startPos, pixels_s target, bool order, int width, bool nextLine)
{
	int count{ startPos }, o{ order ? 1 : -1 };
	uint64_t stop{ nextLine ? v.size() :
			(o == 1 ? int(ceil(startPos*1.0 / width * 1.0)) * width : int(floor(startPos*1.0 / width * 1.0)) * width) };
	bool test = true;

	while (test) {

		if (o == 1) {
			if (count > stop) test = false;
		}
		else {
			if (count < stop) test = false;
		}

		if (count < 0) break;
		if (v[count] == target)
			return count;

		count += o;
	}

	return -1;
}

//cherche un pixel cible sur l'axe vertical
//cherche sur une seule colonne (sauf si jump)
//par défaut, order = true : vers le bas
//order = false : vers le haut
//retourne l'indice
//si jump != 0, saut de x pixels vers la droite en changeant de colonne
//si jumpDown != 0, saut de x pixels vers le bas plutôt que d'un seul
int ImageTools::findPixelVertical(std::vector<pixels_s> v, int width, int startPos, pixels_s target, bool order, int jump, int jumpDown)
{
	int targetPixel{ startPos }, jumpSize{ jump },
		o{ order ? 1 : -1 };

	while (true) {
		int pos{ targetPixel + (o*width + jumpSize) };

		if (pos < 0) { break; }
		if (pos > v.size()) { break; }

		if (v[pos] == target) { return pos; }

		targetPixel = pos+jumpDown;
	}

	return -1;
}


//----------------- DÉTECTION DES COINS (HARRIS CORNER DETECTOR) -------- //


//Fonction du processus global
int ImageTools::cornerDetection(std::vector<pixels_s> v, int imgWidth, int imgHeight)
{
	int vectorSize{ (int)v.size() };
	std::vector<std::pair<int, int>> sobelScore{ sobelFilterAlgo(v, imgWidth, imgHeight) },
		sobelScorePower(vectorSize);
	std::vector<int> sobelScoreXYProduct(vectorSize);

	//modifier les scores de Sobel :
	//X^2, Y^2, X*Y
	std::transform(sobelScore.begin(), sobelScore.end(), sobelScorePower.begin(),
		[](std::pair<int, int> i) { return std::make_pair(i.first*i.first, i.second*i.second); });
	std::transform(sobelScore.begin(), sobelScore.end(), sobelScoreXYProduct.begin(),
		[](std::pair<int, int> i) { return i.first*i.second; });

	//appliquer filtre Gaussien sur les résultats
	std::vector<std::pair<double, double>> gaussianPower{ gaussianFilterAlgo(sobelScorePower, imgWidth, imgHeight) };
	std::vector<double> gaussianXYProduct{ gaussianFilterAlgo(sobelScoreXYProduct, imgWidth, imgHeight) };

	std::vector<double> harris = harrisAlgo(gaussianPower, gaussianXYProduct, imgWidth, imgHeight);

	return std::count_if(harris.begin(), harris.end(), [](double d) {return d == 1; });
}

//Algorithme de détection des coin de Harris
std::vector<double> ImageTools::harrisAlgo(std::vector<std::pair<double, double>> gaussianPower,
	std::vector<double> gaussianXYProduct, int width, int height)
{
	int vectorSize{ (int)gaussianXYProduct.size() };
	std::vector<double> scores(vectorSize), harrisRep(vectorSize);
	std::fill(scores.begin(), scores.end(), 0);
	std::fill(harrisRep.begin(), harrisRep.end(), 0);
	std::vector<double> matrixM;
	std::vector<int> window{ build3X3Window(width) };
	double max{ 0 }, threshold{ 0.7 };

	for (int i{ 0 }; i < vectorSize; ++i) {
		if (!isBorderPixel(i, width, height)) {
			matrixM = harrisSummedUpMatrix(i, gaussianPower, gaussianXYProduct, window);
			double score = harrisScore(matrixM);

			if (score > max) { max = score; }

			scores[i] = score;
		}
	}

	for (int i{ 0 }; i < scores.size(); ++i) {
		if (scores[i] > threshold*max && scores[i] >= scores[i - width - 1]
			&& scores[i] >= scores[i - width + 1] && scores[i] >= scores[i + width - 1]
			&& scores[i] >= scores[i + width + 1])
		{
			harrisRep[i] = 1;
		}
	}

	return harrisRep;
}

//Construction d'une matrice agglomérant les résultats de Sobel
//pour un pixel, sous la forme [ Ix^2	Ix*Iy
//								 Ix*Iy	Iy^2 ]
std::vector<double> ImageTools::harrisSummedUpMatrix(int pixelIndex, std::vector<std::pair<double, double>> gaussianPower,
	std::vector<double> gaussianXYProduct, std::vector<int> window)
{
	int windowSize{ 9 };
	std::vector<double> m(4), pixelWindowX, pixelWindowY;

	for (int i{ 0 }; i < windowSize; ++i) {
		std::pair<int, int> pixelScore{ gaussianPower[pixelIndex + window[i]] };
		pixelWindowX.emplace_back(abs(pixelScore.first));
		pixelWindowY.emplace_back(abs(pixelScore.second));
	}

	for (int i{ 0 }; i < windowSize; ++i) {
		double xScore{ pixelWindowX[i] }, yScore{ pixelWindowY[i] },
			xyScore{ gaussianXYProduct[i] };
		m[0] += xScore;
		m[1] += xyScore;
		m[2] += xyScore;
		m[3] += yScore;
	}

	return m;
}

//R = det(M)*k(trace(M)^2

double ImageTools::harrisScore(std::vector<double> harrisRep)
{
	double k{ 0.04 };
	double det{ MathTools::determinant2X2(harrisRep) },
		trace{ MathTools::traceMatrix(harrisRep, 2, 2) };
	double score{ det - k * (pow(trace,2)) };
	return score;
}

//----- -FONCTIONS UTILITAIRES -------//

//Construit un vecteur de neuf valeurs.
//Ces valeurs, additionnées les uns à la suite des autres à l'index d'un pixel, permettent
//d'atteindre les pixles dans une fenêtre de type :
//			X X X
//			X P X
//			X X X
std::vector<int> ImageTools::build3X3Window(int width)
{
	return std::vector<int> {	-width - 1, -width, -width + 1,
		-1, 0, 1,
		width - 1, width, width + 1};
}


//Retourne la luminance d'un pixel selon ses données RGB
int ImageTools::getRGBLuminance(pixels_s p)
{
	return std::round(0.2126*p.r + 0.7152*p.g + 0.0722 * p.b);
}

//Prend en paramètre une liste de pixels (échantillon pour opérations futures) 
//et un vecteur de pixel (l'image complète).
//Ajoute à la liste 4 pixels x selon la fenêtre :
//			X
//		  X P X
//			x
//S'ils correspondent au pixel condition, ils sont transformés en le pixel chang.
//Utilisée pour le floodFill et la détection des zones fermées
template <typename T>
void ImageTools::pushAndConvertAdjacentPixels(std::list<int> & q, std::vector<T> & v, int pixel, T condition, T change, int width)
{
	int nbPixels{ 4 }, pos[] = { -width, width, -1, 1 };

	for (int i{ 0 }; i < nbPixels; ++i) {
		int j{ pixel + pos[i] };
		if (j > 0 && j < v.size() && v[j] == condition) {
			v[j] = change;
			q.push_front(j);
		}
	}

}

//Retourne vrai si le pixel est à une des extrémités de l'image
bool ImageTools::isBorderPixel(int pixel, int width, int height)
{
	bool test{ (pixel % width == 0 || pixel % width == width - 1 || pixel < width || pixel >(height - 1)*width) };
	return test;
}

//Ajouter une bordure noire de taille 5 pixels à une image
std::vector<ImageTools::pixels_s> ImageTools::addBorder(std::vector<ImageTools::pixels_s> v, int width, int height)
{
	int borderSize{ 5 }, gap{ borderSize * 2 };

	for (int j{ 0 }; j < borderSize*(width + gap); ++j) { v.insert(v.begin(), ImageTools::mBlack); }

	for (int i{ borderSize*(width + gap) }; i < v.size(); i += (width + gap)) {
		int count{ 1 };
		for (int j{ 0 }; j < borderSize; ++j) {
			v.insert(v.begin() + i, ImageTools::mBlack);
			if (i + width + borderSize < v.size()) { v.insert(v.begin() + i + width + count, ImageTools::mBlack); }
			count++;
		}
	}

	for (int i{ 0 }; i < borderSize*(width + gap); ++i) { v.push_back(ImageTools::mBlack); }

	return v;
}

int ImageTools::modifySizeBorder(int size)
{
	return size += (ImageTools::borderSize * 2);
}

//convertir un vecteur de pixels binaires en vecteur d'entiers 8 bits
//	1 pour blanc, 0 pour noir
std::vector<uint8_t> ImageTools::pixelsToBinaryNumeric(std::vector<ImageTools::pixels_s> vPixels)
{
	std::vector<uint8_t> vNumeric;

	for (ImageTools::pixels_s p : vPixels) {
		p == ImageTools::mWhite ? vNumeric.push_back(1) : vNumeric.push_back(0);
	}

	return vNumeric;
}