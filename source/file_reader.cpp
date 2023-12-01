#include "file_reader.h"

using std::runtime_error;

caffFileData readCAFFFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (file.good()) {
        std::streamsize length = getFileLength(file);
        char* fileData = new char[length];
        file.read(fileData, length);
        caffFileData caffData;
        for (uintmax_t i = 0; i < length; i++)
            caffData.push_back((uint8_t)fileData[i]);
        delete[] fileData;
        file.close();
        return caffData;
    }
    else {
        file.close();
        throw runtime_error("An error occured when opening the file");
    }
}

std::streamsize getFileLength(std::ifstream& file) {
    file.ignore(std::numeric_limits<std::streamsize>::max());
    std::streamsize length = file.gcount();
    file.clear();   //  Since ignore will have set eof.
    file.seekg(0, std::ios_base::beg); // Visszatérünk az elejére.
    return length;
}