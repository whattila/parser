#include "metadata.h"

using std::fstream;
using std::endl;
using std::runtime_error;

void createCAFFMetadata(const char* path, CAFF caff) {
	fstream jsonFile(path, fstream::out);
	if (jsonFile.good()) {
		jsonFile << "{" << endl;

		jsonFile << "\"creator\": \"" << caff.creator << "\"," << endl;
		jsonFile << "\"createdAt\": \"" << caff.createdAt << "\"," << endl;
		jsonFile << "\"caption\": \"" << caff.ciffBlocks[0].caption << "\"," << endl;

		jsonFile << "\"tags\": [";
		for (uintmax_t i = 0; i < caff.ciffBlocks[0].tags.size(); i++) {
			jsonFile << "\"" << caff.ciffBlocks[0].tags[i] << "\"";
			if (i != caff.ciffBlocks[0].tags.size() - 1)
				jsonFile << ", ";
		}
		jsonFile << "]" << endl;

		jsonFile << "}";
		jsonFile.close();
	}
	else {
		jsonFile.close();
		throw runtime_error("An error occured when opening the file");
	}
}