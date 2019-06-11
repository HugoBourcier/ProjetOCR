#ifndef CHARACTEROBJECT_H
#define CHARACTEROBJECT_H

#include "ImageObject.h"
#include <string>

//--------------------------//
// Classe CharacterObject	//
//							//
// Modélise un unique		//
// caractère.				//
//--------------------------//

class CharacterObject : public ImageObject
{
protected:
	std::string mLabel;

private:
	//features
	int mClosedZones, mCorners;
	double mBlackWhiteRadio;
	std::vector<ImageTools::pixels_s> mPixelsVector;
	std::vector<uint8_t> mPixelsVectorNumeric;

	const int mNormalizedHeight{ 50 }, mNormalizedWidth{ 40 };
	const std::string mNormalizedSize{ "40x50!" };
	std::string mFileName;
	std::map<std::string, double> mKnnResults;

public:
	CharacterObject();
	CharacterObject(int closedZones, int corners, double blackWhiteRatio, std::vector<char> vector, std::string label);
	CharacterObject(Magick::Image img);
	~CharacterObject();

	bool process();

	void normalize(void);

	//extraction des features
	int findClosedZones(std::vector<ImageTools::pixels_s> v);
	double calcBlackWhiteRatio(std::vector < ImageTools::pixels_s> v);

	void saveImage(int count);

	//serialisation + patch pour remplacer les char nuls
	std::vector<char> serializeVector();
	static std::vector<uint8_t> deserializeVector(std::vector<char> vChar);
	void changeNullValues(std::vector<char>& vChar);
	static void restoreNullValues(std::vector<char>& vChar);

	//getters, setters
	int getClosedZones();
	double getRatio();
	int getCorners();
	Magick::Image getImage();
	std::vector<ImageTools::pixels_s> getPixelsVector();
	std::vector<uint8_t> getPixelsVectorNumeric();
	std::vector<char> getSerializedVector();
	std::string getLabel();
	std::string getFileName();
	std::vector<double> getVectorOfFeatures();
	std::map<std::string, double> getKnnResults();
	void setLabel(std::string label);
	void setKnnResults(std::map<std::string, double> results);

	//surchages d'opérateurs et de fonctions
	CharacterObject operator=(CharacterObject c);
	friend void swap(CharacterObject & c1, CharacterObject & c2);

};

#endif //CHARACTEROBJECT_Hs

