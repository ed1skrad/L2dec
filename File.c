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
                char *tmp = realloc(str, (currSize+1)*sizeof(char));
                if (tmp == NULL) {
                    free(str);
                    fclose(file);
                    return 0;
                }
                str = tmp;
                str[currSize] = c;
                currSize++;
                continue;
            }

            currSize++;
            char *tmp = realloc(str, currSize*sizeof(char));
            if (tmp == NULL) {
                free(str);
                fclose(file);
                return 0;
            }
            str = tmp;
            str[currSize-1] = '\0';

            if(*wordDec == NULL || (*wordDec)[*numberOfWords-1].secondWord != NULL)
            {
                (*numberOfWords)++;
                struct WordDecompress *tmp = realloc(*wordDec, (*numberOfWords)*sizeof(struct WordDecompress));
                if (tmp == NULL) {
                    free(*wordDec);
                    free(str);
                    fclose(file);
                    return 0;
                }
                *wordDec = tmp;
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
                char *tmp = realloc(str, (currSize+1)*sizeof(char));
                if (tmp == NULL) {
                    free(str);
                    fclose(file);
                    return 0;
                }
                str = tmp;
                str[currSize] = c;
                currSize++;
            }
            else {
                currSize++;
                char *tmp = realloc(str, currSize*sizeof(char));
                if (tmp == NULL) {
                    free(str);
                    fclose(file);
                    return 0;
                }
                str = tmp;
                str[currSize-1] = '\0';

                char **tmp_words = realloc(*words, ((*wordsSize) + 1) * sizeof(char *));
                if (tmp_words == NULL) {
                    free(*words);
                    free(str);
                    fclose(file);
                    return 0;
                }
                *words = tmp_words;

                (*words)[*wordsSize] = strdup(str);

                if ((*words)[*wordsSize] == NULL) {
                    free(*words);
                    free(str);
                    fclose(file);
                    return 0;
                }

                (*wordsSize)++;

                str = calloc(2, sizeof(char));

                if (str == NULL) {
                    free(*words);
                    fclose(file);
                    return 0;
                }

                str[0] = c;
                str[1] = '\0';

                tmp_words = realloc(*words, ((*wordsSize) + 1) * sizeof(char *));

                if (tmp_words == NULL) {
                    free(*words);
                    free(str);
                    fclose(file);
                    return 0;
                }

                *words = tmp_words;

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

