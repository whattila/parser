#ifndef CAFF_PARSER_H
#define CAFF_PARSER_H

#include <stdexcept>
#include <string>
#include <format>
#include "types.h"
#include "ciff_parser.h"

// A CAFF fájl nyers bájtjait értelmes adatokká alakítja, és visszadja egy CAFF struktúrában.
CAFF parseCAFFFile(caffFileData& caffData);

// Kiolvassa és ellenõrzi a header adatait, és beírja õket a CAFF struktúrába
void parseCAFFHeader(caffFileData& caffData, CAFF& caff);

// Kiolvassa és ellenõrzi a credits adatait, és beírja õket a CAFF struktúrába.
// Feltételezi, hogy az adatok credits elõtti részét törölték.
void parseCAFFCredits(caffFileData& caffData, CAFF& caff);

// Kiolvassa és ellenõrzi az animation blokkok adatait, feldolgozza a CIFF parser segítségével, majd beírja õket a CAFF struktúrába.
// Feltételezi, hogy az adatok animations elõtti részét törölték.
void parseCAFFAnimations(caffFileData& caffData, CAFF& caff);

#endif // !CAFF_PARSER_H

