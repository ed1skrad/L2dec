#include "Initialization.h"
#include <stdio.h>
#include <string.h>
//
// Created by User on 26.03.2023.
//
int Decompress(const char* filename, const char* output) {
    struct WordDecompress* wordDec = NULL;
    int numberOfWords = 0;
    char** words = NULL;
    int wordsSize = 0;
    if(fileConverting(filename, &wordDec, &numberOfWords, &words, &wordsSize) == 0)
        return 1;
    FILE* file = fopen(output, "w");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    for (int i = 0; i < wordsSize; i++) {
        int founded = 0;
        for(int j = 0; j < numberOfWords; j++) {
            if(wordDec[j].firstWord == NULL || wordDec[j].secondWord == NULL)
                continue;
            if(strcmp(words[i], wordDec[j].firstWord) == 0)
            {
                founded = 1;
                fprintf(file, "%s", wordDec[j].secondWord);
            }
            else if(strcmp(words[i], wordDec[j].secondWord) == 0)
            {
                founded = 1;
                fprintf(file, "%s", wordDec[j].firstWord);
            }
            if(founded == 1)
                break;
        }
        if(founded == 0)
            fprintf(file, "%s", words[i]);
    }
    fclose(file);
    return 0;
}

