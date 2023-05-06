#include "Initialization.h"

int main() {
    const char* filename = getFileName();
    const char* decompressedFileName = getFileCompressedName();
    Decompress(filename, decompressedFileName);
}
