#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

// Egy CAFF fájl bájtjai
typedef vector<uint8_t> caffFileData;

// Egy CIFF fájl bájtjai (header + pixelek)
typedef vector<uint8_t> ciffFileData;

// Egy CIFF fájl pixeljeinek bájtjai (1 pixel = 4 byte (RGBA, az A mindig 0))
typedef vector<uint8_t> RGBAImage;

// Egy CIFF fájl adatai "értelmes" formában
// A captiont és a tagst logikusabb lenne a CAFF-ban tárolni (feltéve hogy minden CIFF-nél ugyanaz), de így egyszerûbb
struct CIFF
{
	uint64_t duration;	// a duration, a width és a heigth minden frame-nek ugyanaz kéne legyen?
	uint64_t size;		// Szerintem nem, viszont mintha a gif.h ezt feltételezné...
	uint64_t width;		// a gif.h a durationt századmásodpercben kéri!
	uint64_t heigth;
	string caption;		// minden ciffnek ugyanaz a caption és a tagek, vagy mindnek más?
	vector<string> tags;	// a caption ugyanaz kell legyen (mivel a jsonben csak egy van), tegyük fel hogy a tags is. Kell ezt ellenõrizni?
	RGBAImage image;
};

// Egy CAFF fájl adatai "értelmes" formában
struct CAFF
{
	string creator;
	string createdAt;
	uint64_t numberOfAnimationBlocks; // az uint64_t 8 bájt? Szerintem igen, és nem várunk elõjeles érétkeket, tehát szerintem ez jó
	vector<CIFF> ciffBlocks;
};

// Segédfüggvény uint8_t-kbõl uint16_t létrehozásához
uint16_t from_uint8_t_array_to_uint16_t(uint8_t arr[]);

// Segédfüggvény uint8_t-kbõl uint64_t létrehozásához
uint64_t get_uint64_t_from_bytes(vector<uint8_t> bytes, unsigned offset);

#endif // !TYPES_H

