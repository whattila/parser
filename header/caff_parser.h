#ifndef CAFF_PARSER_H
#define CAFF_PARSER_H

#include <stdexcept>
#include <string>
#include "types.h"
#include "ciff_parser.h"

// A CAFF fájl nyers bájtjait értelmes adatokká alakítja, és visszadja egy CAFF struktúrában.
CAFF parseCAFFFile(caffFileData& caffData);

// Kiolvassa és ellenőrzi a header adatait, és beírja őket a CAFF struktúrába
void parseCAFFHeader(caffFileData& caffData, CAFF& caff);

// Kiolvassa és ellenőrzi a credits adatait, és beírja őket a CAFF struktúrába.
// Feltételezi, hogy az adatok credits előtti részét törölték.
void parseCAFFCredits(caffFileData& caffData, CAFF& caff);

// Kiolvassa és ellenőrzi az animation blokkok adatait, feldolgozza a CIFF parser segítségével, majd beírja őket a CAFF struktúrába.
// Feltételezi, hogy az adatok animations előtti részét törölték.
void parseCAFFAnimations(caffFileData& caffData, CAFF& caff);

#endif // !CAFF_PARSER_H

