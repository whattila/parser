#include "types.h"

using std::invalid_argument;

uint16_t from_uint8_t_array_to_uint16_t(uint8_t arr[]) {
    uint16_t res;
    std::memcpy(&res, arr, sizeof(uint16_t));
    return res;
}

uint64_t get_uint64_t_from_bytes(vector<uint8_t> bytes, unsigned offset) {
    if (bytes.size() - offset < 8)
        throw invalid_argument("Source size is smaller than 8!");

    uint8_t arr[8];
    for (unsigned i = 0; i < 8; i++)
        arr[i] = bytes[offset + i];

    uint64_t res;
    std::memcpy(&res, arr, sizeof(uint64_t));
    return res;
}

