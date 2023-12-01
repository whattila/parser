#ifndef FILE_READER_H
#define FILE_READER_H

#include <fstream>
#include <limits>
#include "types.h"

// Beolvassa a megadott útvonalon található CAFF fájl bájtjait, nem vizsgálva annak tartalmát
caffFileData readCAFFFile(const char* filePath);

// Megállapítja egy fájl mértetét; feltételezi hogy a stream meg van nyitva; a bezárás nem az õ felelõssége.
std::streamsize getFileLength(std::ifstream& file); // Ha ezekkel a const dolgokkal baj van, inkább töröljük!

#endif
