#include "CharacterObject.h"
#include <sstream>

//---- CONSTRUCTEURS -----//

CharacterObject::CharacterObject()
{
}

CharacterObject::CharacterObject(int closedZones, int corners, double blackWhiteRatio, std::vector<char> vector, std::string label)
	:mClosedZones{ closedZones },
	mCorners{ corners },
	mBlackWhiteRadio{ blackWhiteRatio },
	mPixelsVectorNumeric{ deserializeVector(vector) },
	mLabel{ label }
{
	mWidth = mNormalizedWidth;
	mHeight = mNormalizedHeight;
}

CharacterObject::CharacterObject(Magick::Image img)
	:ImageObject(img),
	mKnnResults{ std::map < std::string, double>()},
	mLabel{""}
{
}

//---- DESTRUCTEUR -----//

CharacterObject::~CharacterObject()
{

}

//---- GETTERS -----//

int CharacterObject::getClosedZones()
{
	return mClosedZones;
}

double CharacterObject::getRatio()
{
	return mBlackWhiteRadio;
}

int CharacterObject::getCorners()
{
	return mCorners;
}

Magick::Image CharacterObject::getImage()
{
	return mImg;
}

std::vector<ImageTools::pixels_s> CharacterObject::getPixelsVector()
{
	return mPixelsVector;
}

std::vector<uint8_t> CharacterObject::getPixelsVectorNumeric()
{
	return mPixelsVectorNumeric;
}

std::vector<char> CharacterObject::getSerializedVector()
{
	return serializeVector();
}

std::string CharacterObject::getLabel()
{
	return mLabel;
}

std::string CharacterObject::getFileName()
{
	return mFileName;
}

std::vector<double> CharacterObject::getVectorOfFeatures()
{
	return std::vector<double> {
		mClosedZones*1.00, mBlackWhiteRadio, mCorners*1.00, 0.00
	};
}

std::map<std::string, double> CharacterObject::getKnnResults()
{
	return mKnnResults;
}

//---- SETTERS ----//

void CharacterObject::setLabel(std::string label)
{
	mLabel = label;
}

void CharacterObject::setKnnResults(std::map<std::string, double> results)
{
	mKnnResults = results;
}

//---- PROCESSUS ----//

	//----Fonction du processus principal
	//1. Sauvegarder l'image en jpg pour l'affichage
	//2. Ajout d'une bordure noire
	//3. Normalisation de la taille
	//4. Extractions de features :
	//		Zones fermées, ratio pixel blanc/pixel noir, coins
	//5. Convertir le vecteur de pixels en vecteur numérique (0 pour noir, 1 pour blanc)

bool CharacterObject::process()
{
	bool result{ true };

	saveImage(rand());

	std::vector<ImageTools::pixels_s> vBorder = ImageTools::addBorder(pixelsToVector(mImg), mWidth, mHeight);
	mHeight = ImageTools::modifySizeBorder(mHeight);
	mWidth = ImageTools::modifySizeBorder(mWidth);
	mImg = pixelsToImage(vBorder);

	normalize();
	mPixelsVector = pixelsToVector(mImg);

	mClosedZones = findClosedZones(mPixelsVector);
	mBlackWhiteRadio = calcBlackWhiteRatio(mPixelsVector);
	mCorners = ImageTools::cornerDetection(mPixelsVector, mWidth, mHeight);
	mPixelsVectorNumeric = ImageTools::pixelsToBinaryNumeric(mPixelsVector);

	return result;
}

//normaliser l'image à une taille par défaut
//en utilisant la classe ImageMagick
void CharacterObject::normalize(void)
{
	mWidth = mNormalizedWidth;
	mHeight = mNormalizedHeight;
	mImg.resize(Magick::Geometry(mNormalizedSize));
}

//----- EXTRACTION DE FEATURES -----//

	//--Trouver les zones fermées avec la classe ImageTools
	//1. firstPixel = premier pixel au-delà d'une bordure blanche
	//2. appeler la fonction isClosedRegion à partir de ce pixel
	//3. si région fermée trouvée, trouver verticalement le prochain pixel au-delà d'une bordure blanche
	//4. répéter 2,3 jusqu'à ce que 2 retourne faux ou 3 retourne -1
int CharacterObject::findClosedZones(std::vector<ImageTools::pixels_s> v)
{
	int nb{ 0 }, nextPixel{ 0 },
		firstPixel{ ImageTools::findInsidePixel(v, ImageTools::mWhite, ImageTools::mBlack, mWidth) };
	bool test{ true };

	while (test && firstPixel != -1) {
		test = ImageTools::isClosedRegion(v, firstPixel, ImageTools::mWhite, ImageTools::mBlack, mWidth, mHeight);
		if (test) {
			++nb;
			firstPixel = ImageTools::findPixelVertical(v, mWidth, ImageTools::findPixelVertical(v, mWidth, firstPixel, ImageTools::mWhite), ImageTools::mBlack);
		}
	}

	return nb;
}

//--Ratio pixels noirs vs pixels blancs
double CharacterObject::calcBlackWhiteRatio(std::vector<ImageTools::pixels_s> v)
{
	int white{ (int)std::count_if(v.begin(), v.end(), [](ImageTools::pixels_s p) { return p == ImageTools::mWhite; }) };
	int black{ (int)v.size() - white };
	return black * 1.0 / white * 1.0;
}

//---- SÉRIALISATION DU VECTEUR DE PIXELS NUMÉRIQUE ---//

	//Transformer un vecteur de pixels_s en vecteur de char
	//pour l'insertion dans la base de données.
std::vector<char> CharacterObject::serializeVector()
{
	std::ostringstream os;
	size_t size{ mPixelsVectorNumeric.size() };

	os.write(reinterpret_cast<char const *>(&size), sizeof(size));
	os.write(reinterpret_cast<char const*>(mPixelsVectorNumeric.data()), size * sizeof(uint8_t));

	std::string s{ os.str() };
	std::vector<char> vChar(s.begin(), s.end());
	changeNullValues(vChar);
	return vChar;
}

	//Transformer un vecteur de char en vecteur de pixels_s.
std::vector<uint8_t> CharacterObject::deserializeVector(std::vector<char> vChar)
{
	std::stringstream ss;
	std::vector<uint8_t> vPixels;
	size_t size;

	restoreNullValues(vChar);
	for (char c : vChar) { ss << c; }

	ss.read(reinterpret_cast<char *> (&size), sizeof(size));
	vPixels.resize(size);
	ss.read(reinterpret_cast<char *> (vPixels.data()), size * sizeof(uint8_t));

	return vPixels;
}

	//Patch broche à foin.
	//Les infos binaires du vector contiennent des char null.
	//Pour les inclure, remplacer par 'X' vers la BD et vice-versa
void CharacterObject::changeNullValues(std::vector<char> & vChar)
{
	for (auto & c : vChar) { if (c == '\0') { c = 'X'; } }
}

void CharacterObject::restoreNullValues(std::vector<char> & vChar)
{
	for (auto & c : vChar) { if (c == 'X') { c = '\0'; } }
}

//----- SURCHARGES ----//

//operator==
CharacterObject CharacterObject::operator=(CharacterObject c)
{
	if (this != &c) {
		swap(*this, c);
	}

	return *this;
}

//fonction swap
void swap(CharacterObject & c1, CharacterObject & c2)
{
	using std::swap;
	swap(c1.mBlackWhiteRadio, c2.mBlackWhiteRadio);
	swap(c1.mClosedZones, c2.mClosedZones);
	swap(c1.mCorners, c2.mCorners);
	swap(c1.mPixelsVector, c2.mPixelsVector);
	swap(c1.mPixelsVectorNumeric, c2.mPixelsVectorNumeric);
	swap(c1.mLabel, c2.mLabel);
}

//---- UTILITAIRES ----//

void CharacterObject::saveImage(int count)
{
	mFileName = "char" + std::to_string(count);
	mImg.write("img/"+mFileName+".jpg");
}

