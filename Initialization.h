//
// Created by User on 26.03.2023.
//

#ifndef DECOMPRESSION_INITIALIZATION_H
#define DECOMPRESSION_INITIALIZATION_H
struct WordDecompress{
    char* firstWord;
    char* secondWord;
};
int punctuationMark(char c);
int fileConverting(const char* filename, struct WordDecompress** wordDec, int* numberOfWords, char*** words, int* wordsSize);
int Decompress(const char* filename, const char* output);
char* getFileName();
char* getFileCompressedName();
#endif //DECOMPRESSION_INITIALIZATION_H
