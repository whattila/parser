#ifndef CAFF_PARSER_H
#define CAFF_PARSER_H

#include <stdexcept>
#include <string>
#include <format>
#include "types.h"
#include "ciff_parser.h"

// A CAFF f�jl nyers b�jtjait �rtelmes adatokk� alak�tja, �s visszadja egy CAFF strukt�r�ban.
CAFF parseCAFFFile(caffFileData& caffData);

// Kiolvassa �s ellen�rzi a header adatait, �s be�rja �ket a CAFF strukt�r�ba
void parseCAFFHeader(caffFileData& caffData, CAFF& caff);

// Kiolvassa �s ellen�rzi a credits adatait, �s be�rja �ket a CAFF strukt�r�ba.
// Felt�telezi, hogy az adatok credits el�tti r�sz�t t�r�lt�k.
void parseCAFFCredits(caffFileData& caffData, CAFF& caff);

// Kiolvassa �s ellen�rzi az animation blokkok adatait, feldolgozza a CIFF parser seg�ts�g�vel, majd be�rja �ket a CAFF strukt�r�ba.
// Felt�telezi, hogy az adatok animations el�tti r�sz�t t�r�lt�k.
void parseCAFFAnimations(caffFileData& caffData, CAFF& caff);

#endif // !CAFF_PARSER_H

