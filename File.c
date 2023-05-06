#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Initialization.h"

//
// Created by User on 26.03.2023.
//
FILE* openFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    return file;
}

int fileConverting(const char* filename, struct WordDecompress** wordDec, int* numberOfWords, char*** words, int* wordsSize) {
    FILE *file = openFile(filename);


    char* str = NULL;
    int currSize = 0;
    char c;
    int ln = 0;

    while(1) {
        c = (char)getc(file);
        if(c == EOF) {
            break;
        }

        if(ln == 0) {
            if(c != ' ' && c != '\n') {
                str = realloc(str, (currSize+1)*sizeof(char));
                str[currSize] = c;
                currSize++;
                continue;
            }

            currSize++;
            str = realloc(str, currSize*sizeof(char));
            str[currSize-1] = '\0';

            if(*wordDec == NULL || (*wordDec)[*numberOfWords-1].secondWord != NULL)
            {
                (*numberOfWords)++;
                *wordDec = realloc(*wordDec, (*numberOfWords)*sizeof(struct WordDecompress));
                (*wordDec)[*numberOfWords-1].firstWord = NULL;
                (*wordDec)[*numberOfWords-1].secondWord = NULL;
            }

            if((*wordDec)[*numberOfWords-1].firstWord== NULL)
                (*wordDec)[*numberOfWords-1].firstWord = str;
            else if((*wordDec)[*numberOfWords-1].secondWord == NULL)
                (*wordDec)[*numberOfWords-1].secondWord = str;

            if(c == '\n')
                ln = 1;

            str = NULL;
            currSize = 0;
        }
        else {
            if(punctuationMark(c) == 0) {
                str = realloc(str, (currSize+1)*sizeof(char));
                str[currSize] = c;
                currSize++;
            }
            else {
                currSize++;
                str = realloc(str, currSize*sizeof(char));
                str[currSize-1] = '\0';

                *words = realloc(*words, ((*wordsSize) + 1) * sizeof(char *));
                (*words)[*wordsSize] = strdup(str);
                (*wordsSize)++;

                str = calloc(2, sizeof(char));
                str[0] = c;
                str[1] = '\0';

                *words = realloc(*words, ((*wordsSize) + 1) * sizeof(char *));
                (*words)[*wordsSize] = str;
                (*wordsSize)++;

                str = NULL;
                currSize = 0;
            }
        }
    }

    fclose(file);
    free(str);

    return 1;
}

