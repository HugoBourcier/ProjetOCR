#include "ImageObject.h"
#include <sstream>
#include <cstdlib>
#include <qdebug.h>

ImageObject::ImageObject()
{
}

ImageObject::ImageObject(Magick::Image img)
{
	mImg = img;
	mWidth = img.columns();
	mHeight = img.rows();
}

ImageObject::~ImageObject()
{
}

//----- GETTERS / SETTERS --------///

Magick::Image ImageObject::getImg()
{
	return mImg;
}

int ImageObject::getWidth()
{
	return mWidth;
}

int ImageObject::getHeight()
{
	return mHeight;
}

//------- CONVERSION IMAGEMAGICK <> PIXELS_S ------//

//À partir d'une image, créé une représentation de ses pixels
//dans un vecteur.
std::vector<ImageTools::pixels_s> ImageObject::pixelsToVector(Magick::Image img)
{
	MagickCore::Quantum * pixels = img.getPixels(0, 0, img.columns(), img.rows());

	std::vector<ImageTools::pixels_s> v;

	int range{ 256 };

	for (size_t i{ 0 }; i < mHeight; ++i) {
		for (size_t j{ 0 }; j < mWidth; ++j) {

			Magick::Color c = img.pixelColor(j, i);

			v.push_back(ImageTools::pixels_s(
				c.quantumRed() / range, c.quantumGreen() / range,
				c.quantumBlue() / range, c.quantumAlpha() / range
			));
		}
	}

	return v;
}

//À partir d'un vecteur de pixels, créer une image Magick
Magick::Image ImageObject::pixelsToImage(std::vector<ImageTools::pixels_s> pixels)
{
	std::stringstream imgSize;
	imgSize << mWidth << "x" << mHeight;
	Magick::Image newImage(Magick::Geometry(mWidth, mHeight, 0, 0), Magick::ColorRGB(0, 0, 0));

	for (int i{ 0 }; i < mHeight; ++i) {
		for (int j{ 0 }; j < mWidth; ++j) {

			ImageTools::pixels_s p{ pixels[mWidth*i + j] };

			if (p != ImageTools::mBlack) {
				Magick::ColorRGB c((1.0*p.r) / 255.0,
					(1.0*p.g) / 255.0,
					(1.0*p.b) / 255.0);

				newImage.pixelColor(j, i, c);
			}
		}
	}

	return newImage;
}

//------ FONCTIONS DE COUPURES -------//

//Rogner une image
Magick::Image ImageObject::crop(Magick::Image img, int xLeft, int yTop, int width, int height)
{
	Magick::Geometry g(width, height, xLeft, yTop);

	try {
		img.crop(g);
		img.repage();
	}
	catch (Magick::WarningOption e) {
		;
	}
	return img;
}

//Trouver des lignes complètement noires à couper.
//size1 = à comparer pour la première boucle, size2 = pour la deuxième boucle
//order = 1 : trouver lignes horizontales, 0: trouver lignes verticales
std::vector<int> ImageObject::findCropLines(Magick::Image img, int size1, int size2, bool order)
{
	Magick::ColorRGB white("white"), c;
	std::vector<int> whiteLines;
	int whiteCount;

	for (int i{ 0 }; i < size1; ++i) {
		whiteCount = 0;
		for (int j{ 0 }; j < size2; ++j) {

			order ? c = img.pixelColor(j, i) : c = img.pixelColor(i, j);

			if (c == white) {
				whiteCount++;
				if (whiteCount > 2) {
					whiteLines.push_back(i);
					break;
				}
			}
		}
	}

	return whiteLines;
}

//Trancher une image en plusieurs sections
//type = 1 : couper horizontalement, 0 : couper verticalement
std::vector<Magick::Image> ImageObject::cropLines(Magick::Image img, std::vector<int> whiteLines, bool cut)
{
	int startLine{ 0 }, modifier{ 0 };
	std::vector<Magick::Image> v;

	for (auto l{ whiteLines.begin() }; l != whiteLines.end(); ++l) {

		int val = *l, next = *std::next(l);

		if (startLine == 0) { startLine = val; }
		else {
			if (next == val + 1) { 
				continue; 
			}
			else if (next != val + 1 || l == whiteLines.end()) {
				if (cut) { v.push_back(crop(img, 0, startLine, mWidth, val - startLine)); }
				else { v.push_back(crop(img, startLine, 0, val - startLine, mHeight)); }
				startLine = 0;
			}
		}
	}
	return v;
}

std::vector<Magick::Image> ImageObject::cropLinesProcess(Magick::Image img, int width, int height)
{
	std::vector<int> cropList{ findCropLines(img, height, width, 1)};
	std::vector<Magick::Image> imgList{ cropLines(img, cropList, 1) };

	return imgList;
}

