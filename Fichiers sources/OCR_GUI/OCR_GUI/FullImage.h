#ifndef FULLIMAGE_H
#define FULLIMAGRE_H

#include "Magick++.h"
#include "ImageObject.h"
#include "SpaceCharacter.h"
#include "Line.h"

//--------------------------//
// Classe FullImage			//
//							//
// Modélise l'image			//
// complète à analyser.		//
// Après opérations,		//
// contient une liste de	//
// lignes.
//--------------------------//

class FullImage : public ImageObject
{
private:
	Magick::Image mImgSrc;
	std::string mPath;
	std::vector<Line> mLinesList;

	const int normalizeScale{ 2 };

public:
	FullImage();
	FullImage(const std::string path);
	~FullImage();

	void setPath(std::string path);

	bool process();
	void normalize(bool up = true);
	bool processLines(Magick::Image img);

	std::vector<CharacterObject> getData();
	void clearData();
};

#endif //FULLIMAGE_H
