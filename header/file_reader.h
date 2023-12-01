#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <limits>
#include "types.h"

// Beolvassa a megadott �tvonalon tal�lhat� CAFF f�jl b�jtjait, nem vizsg�lva annak tartalm�t
caffFileData readCAFFFile(const char* filePath);

// Meg�llap�tja egy f�jl m�rtet�t; felt�telezi hogy a stream meg van nyitva; a bez�r�s nem az � felel�ss�ge.
std::streamsize getFileLength(std::ifstream& file); // Ha ezekkel a const dolgokkal baj van, ink�bb t�r�lj�k!

#endif
