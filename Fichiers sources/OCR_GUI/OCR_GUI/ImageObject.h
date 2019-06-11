#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include "Magick++.h"
#include <string>
#include <inttypes.h>
#include <vector>
#include <map>
#include "ImageTools.h"

//----------------------------------//
// Classe abstraite ImageObject		//
//									//
// Tout ce qui est dérivé d'une		//
// image en hérite.					//
// La fonction virtuelle process()	//
// doit être reprise dans ces		//
// objets.							//
//----------------------------------//


class ImageObject
{
protected:
	Magick::Image mImg;
	int mWidth, mHeight;

public:
	ImageObject();
	ImageObject(Magick::Image img);
	~ImageObject();

	Magick::Image getImg();
	int getWidth();
	int getHeight();

	virtual bool process() = 0;

	//Fonctions de conversion entre une image Magick++ et la structure pixels_s
	//D'une image vers un vecteur de pixels_s
	std::vector<ImageTools::pixels_s> pixelsToVector(Magick::Image img);
	//D'un vector de pixels_s vers une image
	Magick::Image pixelsToImage(std::vector<ImageTools::pixels_s> pixels);

	//Fonctions pour couper une image en sections
	std::vector<Magick::Image> cropLinesProcess(Magick::Image img, int width, int height);
	std::vector<int> findCropLines(Magick::Image img, int size1, int size2, bool order);
	std::vector<Magick::Image> cropLines(Magick::Image img, std::vector<int> whiteLines, bool cut);
	Magick::Image crop(Magick::Image img, int xLeft, int yTop, int width, int height);
};

#endif //IMAGEOBJECT_H
