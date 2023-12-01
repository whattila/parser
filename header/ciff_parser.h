#ifndef CIFF_PARSER_H
#define CIFF_PARSER_H

#include <stdexcept>
#include "types.h"

// A CIFF fájl nyers bájtjait értelmes adatokká alakítja, és visszadja egy CAFF struktúrában.
CIFF parseCIFFFile(ciffFileData& ciffData);

// Kiolvassa és ellenõrzi a header adatait, és beírja õket a CIFF struktúrába
void parseCIFFHeader(ciffFileData& ciffData, CIFF& ciff);

// Kiolvassa és ellenõrzi a pixeleket, és beírja õket a CIFF struktúrába
// Feltételezi, hogy a CIFF fájl pixelek elõtti részét törölték.
void parseCIFFPixels(ciffFileData& ciffData, CIFF& ciff);

#endif // !CIFF_PARSER_H

