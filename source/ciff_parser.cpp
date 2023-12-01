#include "ciff_parser.h"

using std::invalid_argument;
using std::string;
using std::vector;

CIFF parseCIFFFile(ciffFileData& ciffData) {
	CIFF ciff;
	parseCIFFHeader(ciffData, ciff);
	parseCIFFPixels(ciffData, ciff);
	return ciff;
}

void parseCIFFHeader(ciffFileData& ciffData, CIFF& ciff) {
	const uint64_t headerConstantPartSize = 36;

	if (ciffData[0] != 'C' || ciffData[1] != 'I' || ciffData[2] != 'F' || ciffData[3] != 'F')
		throw invalid_argument("Invalid magic value");

	uint64_t captionAndTagsSize = get_uint64_t_from_bytes(ciffData, 4) - headerConstantPartSize,
		contentSize = get_uint64_t_from_bytes(ciffData, 12),
		width = get_uint64_t_from_bytes(ciffData, 20),
		heigth = get_uint64_t_from_bytes(ciffData, 28);
	uint64_t headerSize = headerConstantPartSize + captionAndTagsSize;

	if (contentSize != width * heigth * 3)
		throw invalid_argument("Invalid content size!");

	if (ciffData[headerSize - 1] != '\0')
		throw invalid_argument("Invalid tags string format!");

	string caption;
	for (uintmax_t i = headerConstantPartSize; ciffData[i] != '\n' && i < headerSize; i++)
		caption += (char)ciffData[i];

	uint64_t captionOffset = headerConstantPartSize + caption.length() + 1; // + 1, mert átugorjuk a '\n'-t
	vector<string> tags;
	string currentTag;
	for (uint64_t i = captionOffset; i < headerSize; i++) {
		if (ciffData[i] == '\n' || ciffData[i] == '\r')
			throw invalid_argument("Invalid tags!");
		if (ciffData[i] != '\0')
			currentTag += ciffData[i];
		else {
			tags.push_back(currentTag);
			currentTag.clear();
		}
	}

	ciff.size = contentSize;
	ciff.width = width;
	ciff.heigth = heigth;
	ciff.caption = caption;
	ciff.tags = tags;
	ciffData.erase(ciffData.begin(), ciffData.begin() + headerSize);
}

void parseCIFFPixels(ciffFileData& ciffData, CIFF& ciff) {
	if (ciff.size != ciffData.size() || ((ciff.width == 0 || ciff.heigth == 0) && ciffData.size() != 0))
		throw invalid_argument("Invalid number of pixels!");

	// a ciff blokk méretét korábban egy uint64_t típusú változóban adták meg
	for (uint64_t i = 0; i < ciffData.size(); i += 3) {
		ciff.image.push_back(ciffData[i]);
		ciff.image.push_back(ciffData[i + 1]);
		ciff.image.push_back(ciffData[i + 2]);
		ciff.image.push_back(0);
	}
}