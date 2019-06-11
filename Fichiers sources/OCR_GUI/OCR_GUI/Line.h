#ifndef LINE_H
#define LINE_H
#include "ImageObject.h"
#include "CharacterObject.h"

//--------------------------//
// Classe Line				//
//							//
// Modélise une unique		//
// ligne.					//
// Contient une liste		//
// d'objets caractères		//
//--------------------------//

class Line : public ImageObject
{
private:
	std::vector<CharacterObject> mCharactersList;

public:
	Line();
	Line(Magick::Image img);
	bool process();
	std::vector<CharacterObject> getCharactersList();
	void clearData();
	~Line();

};

#endif //LINE_H

