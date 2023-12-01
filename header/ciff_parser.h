#ifndef CIFF_PARSER_H
#define CIFF_PARSER_H

#include <stdexcept>
#include "types.h"

// A CIFF f�jl nyers b�jtjait �rtelmes adatokk� alak�tja, �s visszadja egy CAFF strukt�r�ban.
CIFF parseCIFFFile(ciffFileData& ciffData);

// Kiolvassa �s ellen�rzi a header adatait, �s be�rja �ket a CIFF strukt�r�ba
void parseCIFFHeader(ciffFileData& ciffData, CIFF& ciff);

// Kiolvassa �s ellen�rzi a pixeleket, �s be�rja �ket a CIFF strukt�r�ba
// Felt�telezi, hogy a CIFF f�jl pixelek el�tti r�sz�t t�r�lt�k.
void parseCIFFPixels(ciffFileData& ciffData, CIFF& ciff);

#endif // !CIFF_PARSER_H

