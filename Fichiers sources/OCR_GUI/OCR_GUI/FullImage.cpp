#include "FullImage.h"
//#include <iostream>
#include <sstream>
#include <qdebug.h>

FullImage::FullImage()
{

}

FullImage::FullImage(const std::string path)
	:mPath{ path }
{
}


FullImage::~FullImage()
{
}

void FullImage::setPath(std::string path)
{
	mPath = path;
}

//---Fonction du processus principal
//1. Normaliser l'image si trop petite ou trop grande
//2. Appliquer filtre gausséen
//3. Détection des contours
//4. Envoyer vers processLines()
bool FullImage::process()
{
	bool result{ true };

	mImgSrc.read(mPath);
	mImg = mImgSrc;
	mWidth = mImgSrc.columns();
	mHeight = mImgSrc.rows();

	if (mWidth < 500 || mHeight < 500) { normalize(); }
	else if (mWidth > 1600 || mHeight > 1600) { normalize(false); }

	std::vector<ImageTools::pixels_s> vPixels{ pixelsToVector(mImg) };

	for (int i{ 0 }; i < 4; ++i) { vPixels = ImageTools::gaussianFilterAlgo(vPixels, mWidth, mHeight);}
	
	vPixels = ImageTools::findEdges(vPixels, mWidth, mHeight);

	mImg = pixelsToImage(vPixels);
	mImg.write("img/contours.jpg");
	
	processLines(mImg);

	return result;
}

void FullImage::normalize(bool up)
{
	if (up) {
		mWidth *= 2;
		mHeight *= 2;
	}
	else {
		mWidth /= 3;
		mHeight /= 3;
	}
	std::stringstream ss;
	ss << mWidth << "x" << mHeight << "!";
	mImg.resize(Magick::Geometry(ss.str()));
}

//-----Process ligne par ligne
//1. Séparer l'image en lignes
//2. Appeler process() pour chaque ligne
bool FullImage::processLines(Magick::Image img)
{
	bool result{ true };

	std::vector<Magick::Image> croppedImg{ cropLinesProcess(img, mWidth, mHeight)};

	for (auto i : croppedImg) {
		if (i.rows() > 20) { mLinesList.push_back(Line(i)); }
	}

	for (auto & l : mLinesList) { l.process();}

	return result;
}

//Remplit un vecteur de caractères à partir de chacune des lignes.
//Retourne le vecteur.
std::vector<CharacterObject> FullImage::getData()
{
	std::vector<CharacterObject> vCharacters;
	int count{ 1 };

	for (auto l : mLinesList) {
		for (auto & c : l.getCharactersList()) {
			c.saveImage(count);
			vCharacters.push_back(c);
			count++;
		}
		vCharacters.push_back(SpaceCharacter());
	}

	return vCharacters;
}

//Efface la liste de lignes après avoir appelé clearData sur chacun d'entre elles.
void FullImage::clearData()
{
	for (auto l : mLinesList) { l.clearData(); }
	mLinesList.clear();
}
