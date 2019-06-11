#include "Line.h"
#include <sstream>
#include <qdebug.h>

Line::Line()
{
}

Line::~Line()
{
}

Line::Line(Magick::Image img)
	:ImageObject(img)
{
}

//---Fonction process principale
//1. Identifier + remplir (flood fill) les blobs et les ins�rers dans un vecteur
//2. Pour chacun des vecteurs contenant un blob :
//			Couper les lignes vides verticales vides
//			Si valide, couper les lignes horizontales vides
//			Cr�er un objet caract�re � partir de l'image
//			Pousser l'objet dans la liste des caract�res
//3. Appeler process() pour chacun des caract�res
bool Line::process()
{
	bool result{ true };

	std::vector<std::vector<ImageTools::pixels_s>> blobsIdentified { ImageTools::blobProcess(pixelsToVector(mImg), mWidth, mHeight) };

	for (auto v : blobsIdentified) {
	
		Magick::Image img{ pixelsToImage(v) };
		std::vector<Magick::Image> croppedImageVertical{ cropLines(img, findCropLines(img, img.columns(), img.rows(), 0), 0) };
	
		if (croppedImageVertical.size() > 0) {
			if (croppedImageVertical[0].columns() > 10) {
				Magick::Image i{ croppedImageVertical[0] };
				if (i.columns() > 10) {

					std::vector<int> linesToCrop{ findCropLines(i, i.rows(), i.columns(), 1) };
					std::vector<Magick::Image> croppedImageHorizontal;

					if (linesToCrop.size() > 0) { croppedImageHorizontal = cropLines(i, linesToCrop, 1); }
					else { croppedImageHorizontal.push_back(i); }

					mCharactersList.push_back(CharacterObject(croppedImageHorizontal[0]));
				}
			}
		}
	}

	for (auto & c : mCharactersList) { c.process(); }

	return result;
}

//Retourne la liste des caract�res
std::vector<CharacterObject> Line::getCharactersList()
{
	return mCharactersList;
}

//Effacer la liste des caract�res.
void Line::clearData()
{
	mCharactersList.clear();
}


