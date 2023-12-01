#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

// Egy CAFF f�jl b�jtjai
typedef vector<uint8_t> caffFileData;

// Egy CIFF f�jl b�jtjai (header + pixelek)
typedef vector<uint8_t> ciffFileData;

// Egy CIFF f�jl pixeljeinek b�jtjai (1 pixel = 4 byte (RGBA, az A mindig 0))
typedef vector<uint8_t> RGBAImage;

// Egy CIFF f�jl adatai "�rtelmes" form�ban
// A captiont �s a tagst logikusabb lenne a CAFF-ban t�rolni (felt�ve hogy minden CIFF-n�l ugyanaz), de �gy egyszer�bb
struct CIFF
{
	uint64_t duration;	// a duration, a width �s a heigth minden frame-nek ugyanaz k�ne legyen?
	uint64_t size;		// Szerintem nem, viszont mintha a gif.h ezt felt�telezn�...
	uint64_t width;		// a gif.h a durationt sz�zadm�sodpercben k�ri!
	uint64_t heigth;
	string caption;		// minden ciffnek ugyanaz a caption �s a tagek, vagy mindnek m�s?
	vector<string> tags;	// a caption ugyanaz kell legyen (mivel a jsonben csak egy van), tegy�k fel hogy a tags is. Kell ezt ellen�rizni?
	RGBAImage image;
};

// Egy CAFF f�jl adatai "�rtelmes" form�ban
struct CAFF
{
	string creator;
	string createdAt;
	uint64_t numberOfAnimationBlocks; // az uint64_t 8 b�jt? Szerintem igen, �s nem v�runk el�jeles �r�tkeket, teh�t szerintem ez j�
	vector<CIFF> ciffBlocks;
};

// Seg�df�ggv�ny uint8_t-kb�l uint16_t l�trehoz�s�hoz
uint16_t from_uint8_t_array_to_uint16_t(uint8_t arr[]);

// Seg�df�ggv�ny uint8_t-kb�l uint64_t l�trehoz�s�hoz
uint64_t get_uint64_t_from_bytes(vector<uint8_t> bytes, unsigned offset);

#endif // !TYPES_H

