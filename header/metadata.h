#ifndef METADATA_H
#define METADATA_H

#include <fstream>
#include "types.h"

// Kiírja a CAFF metaadatait egy (jelenleg) json fájlba.
void createCAFFMetadata(const char* path, CAFF caff);

#endif // !

