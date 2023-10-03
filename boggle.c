/**
 * PUC MINAS
 * Computer Science Course
 * 2023 - 2o. Semester
 * Boogle Game
 * EPITECH - C test
 * @author - Camila Lacerda Grandini
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>

#define EXITERRORCODE 84

int rolsAndCols = 0;

bool isValid(int x, int y, char word[], int pos, char grid[][rolsAndCols]) {
    return (x >= 0 && x < rolsAndCols && y >= 0 && y < rolsAndCols && grid[x][y] == word[pos]);
}

int searchWord(int x, int y, char word[], int pos, char grid[][rolsAndCols]) {
    if (word[pos] == '\0') {
        return true; // The entire word has been found
    }

    if (isValid(x, y, word, pos, grid)) {
        // Check all adjacent cells
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int dir = 0; dir < 8; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (searchWord(newX, newY, word, pos + 1, grid)) {
                grid[x][y] = toupper(grid[x][y]);

                return true;
            }
        }
    }

    return false;
}

void printGrid(char grid[][rolsAndCols]){
    for (int i = 0; i < rolsAndCols; i++) {
        for (int j = 0; j < rolsAndCols; j++) {
            printf("+----");
        }

        printf("+\n");

        for (int j = 0; j < rolsAndCols; j++) {
            printf("| %c  ", grid[i][j]);
        }

        printf("|\n");
    }

    for (int j = 0; j < rolsAndCols; j++) {
        printf("+----");
    }

    printf("+\n");
}

bool findWord(char word[], char matrixGrid[][rolsAndCols]){
    int found = false;

    for (int i = 0; i < rolsAndCols; i++) {
        for (int j = 0; j < rolsAndCols; j++) {
            if (searchWord(i, j, word, 0, matrixGrid)) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    return found;
}

void toMatrix(char matrix[][rolsAndCols], char str[]) {
    int index = 0;

    for (int i = 0; i < rolsAndCols; i++) {
        for (int j = 0; j < rolsAndCols; j++) {
            matrix[i][j] = str[index++];
        }
    }
}

char* cleanString(char string[]) {
    int length = strlen(string);

    if (length <= 2) {
        return strdup(string);
    }

        char* newString = (char*)malloc(length - 2);

        if (newString == NULL) {
            perror("Erro na alocação de memória");
            exit(EXIT_FAILURE);
        }

        for (int i = 3; i < length - 3; i++) {
            newString[i-3] = string[i];
        }

        newString[length - 2] = '\0';

    return newString;
}

int main(int argc, char *argv[]) {
    int opt;

    char *grid = "i";
    int size = 4;
    char *word = "i";

    while ((opt = getopt(argc, argv, "g:s:w:")) != -1) {
        switch (opt) {
            case 'g':
                grid = optarg;
                break;
            case 's':
                size = atoi(optarg);
                break;
            case 'w':
                word = optarg;
                break;
            default:
                fprintf(stderr, "Uso: %s -g GRID [-s SIZE] [-w WORD]\n", argv[0]);
                exit(EXITERRORCODE);
        }
    }
    
    rolsAndCols = size;

    char matrixGrid[size][size];

    if((strlen(grid)) != (size*size) && strlen(grid) != (((size*size) + 6))){
        fprintf(stderr, "ERROR: The string provided doesn't contain the amount of characters necessary!!!\n");
        
        exit(EXITERRORCODE);
    }

    char *newGrid;

    if(strlen(grid) == ((size*size) + 6)){
        newGrid = cleanString(grid);
    }
    else{
        newGrid = grid;
    }

    toMatrix(matrixGrid, newGrid);

    char newWord[20];

    bool wordFound = false;
    
    if(strcmp(word, "i") == 0){
        printGrid(matrixGrid);
        scanf("%99s", newWord);

        wordFound = findWord(newWord, matrixGrid);
        word = newWord;
    }   
    else{
        wordFound = findWord(word, matrixGrid);
    }

    if (wordFound) {
        printGrid(matrixGrid);
    } else {
        printf("The word \"%s\" is not in the grid.\n", word);
        exit(0);
    }

    return 0;
}
