//
// Created by User on 26.03.2023.
//
int punctuationMark(char c) {
    char marks[] = " \t\n\"'.(),?!-=";
    int i = 0;
    for(i = 0; i < 13; i++) {
        if(c == marks[i])
            return 1;
    }
    return 0;
}