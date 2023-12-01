#include "caff_parser.h"

using std::invalid_argument;
using std::string;
using std::to_string;

CAFF parseCAFFFile(caffFileData& caffData) {
    CAFF caff;
    parseCAFFHeader(caffData, caff);
    parseCAFFCredits(caffData, caff);
    parseCAFFAnimations(caffData, caff);
    return caff;
}

void parseCAFFHeader(caffFileData& caffData, CAFF& caff) {
    if (caffData[0] != 1)
        throw invalid_argument("Invalid header value");

    if (caffData[9] != 'C' || caffData[10] != 'A' || caffData[11] != 'F' || caffData[12] != 'F')
        throw invalid_argument("Invalid magic value");

    uint64_t numberOfCiffs = get_uint64_t_from_bytes(caffData, 21);
    if (numberOfCiffs == 0)
        throw invalid_argument("Number of CIFFs cannot be 0!");

    caff.numberOfAnimationBlocks = numberOfCiffs;

    // a headerre nincs késõbb szükség, így törölhetjük
    caffData.erase(caffData.begin(), caffData.begin() + 29);
}

void parseCAFFCredits(caffFileData& caffData, CAFF& caff) {
    if (caffData[0] != 2)
        throw invalid_argument("Invalid header value");

    uint8_t yearBytes[2] = { caffData[9], caffData[10] };
    uint16_t year = from_uint8_t_array_to_uint16_t(yearBytes);
    uint8_t month = caffData[11], day = caffData[12], hour = caffData[13], minute = caffData[14];
    if (year < 1990 || year > 2023 ||
        month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        hour > 23 ||
        minute > 59)
        throw invalid_argument("Invalid creation date");

    uint64_t creatorLength = get_uint64_t_from_bytes(caffData, 15);

    string creator;
    for (uint64_t i = 0; i < creatorLength; i++) {
        char newChar = (char)caffData[23 + i];
        if ((newChar >= 'A' && newChar <= 'Z') || (newChar >= 'a' && newChar <= 'z') || newChar == ' ' || newChar == '-')
            creator += newChar;
        else
            throw invalid_argument("Invalid creator name!");
    }

    string monthString = month < 10 ? "0" + to_string(month) : to_string(month),
        dayString = day < 10 ? "0" + to_string(day) : to_string(day),
        hourString = hour < 10 ? "0" + to_string(hour) : to_string(hour),
        minuteString = minute < 10 ? "0" + to_string(minute) : to_string(minute);
    caff.createdAt = to_string(year) + "/" + monthString + "/" + dayString + " " + hourString + ":" + minuteString;

    caff.creator = creator;

    // a creditsre nincs késõbb szükség, így törölhetjük
    // WARNING: conversion from 'uint64_t' to 'const int', possible loss of data
    caffData.erase(caffData.begin(), caffData.begin() + 23 + creatorLength);
}

void parseCAFFAnimations(caffFileData& caffData, CAFF& caff) {
    for (uint64_t i = 0; i < caff.numberOfAnimationBlocks; i++) {
        if (caffData[0] != 3)
            throw invalid_argument("Invalid header value");

        uint64_t ciffBlockSize = get_uint64_t_from_bytes(caffData, 1) - 8;
        if (ciffBlockSize == 0)
            throw invalid_argument("Animation block size cannot be 0!");

        uint64_t duration = get_uint64_t_from_bytes(caffData, 9);

        // a caffData[17] a CIFF bájtok kezdete, caffData[17+ciffBlockSize] az elsõ ami már nem
        ciffFileData ciffData;
        for (uint64_t i = 0; i < ciffBlockSize; i++)
            ciffData.push_back(caffData[17 + i]);

        CIFF ciff = parseCIFFFile(ciffData);
        ciff.duration = duration / 10;

        caff.ciffBlocks.push_back(ciff);

        // erre az animation blokkra nincs késõbb szükség, így törölhetjük
        // WARNING: conversion from 'uint64_t' to 'const int', possible loss of data
        caffData.erase(caffData.begin(), caffData.begin() + 17 + ciffBlockSize);
    }
}