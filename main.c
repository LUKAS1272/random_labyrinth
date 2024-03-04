#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct cords {
    int y;
    int x;
} cords;

cords* createCords(int yIndex, int xIndex) {
    cords* result = malloc(sizeof(cords));

    result->y = yIndex;
    result->x = xIndex;

    return result;
}

int main() {
    // --------------------------------------- //
    int fogPercentage = 20;
    int wallsPercentage = 20;
    int pacManMode = 0;

    int sizeY = 10;
    int sizeX = 10;
    int numberOfProblems = 10;
    // --------------------------------------- //

    if (fogPercentage + wallsPercentage >= 100) {
        printf("fogPercentage (%d) + wallsPercentage (%d) must be less than 100\n", fogPercentage, wallsPercentage);
        return 1;
    } else if (fogPercentage < 0 || wallsPercentage < 0) {
        printf("fogPercentage (%d) and wallsPercentage (%d) must not be less than 0\n", fogPercentage, wallsPercentage);
        return 1;
    }

    srand(time(NULL));

    char** field = malloc(sizeY * sizeof(char*));
    for (int i = 0; i < sizeY; i++)
        field[i] = malloc(sizeX * sizeof(char));
    
    int numberOfPaths = 0;
    int pathLength = 1;
    cords** paths = malloc(pathLength * sizeof(cords*));

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            char currentChar = 'n';

            if ((y == 0 || y == sizeY - 1 || x == 0 || x == sizeX - 1) && !pacManMode) {
                currentChar = '#';
            } else {
                int random = rand() % 100;

                if (random < fogPercentage) {
                    currentChar = 'f';
                } else if (random < fogPercentage + wallsPercentage) {
                    currentChar = '#';
                } else {
                    currentChar = '.';

                    if (numberOfPaths == pathLength) {
                        pathLength *= 2;
                        paths = realloc(paths, pathLength * sizeof(cords*));
                    }

                    paths[numberOfPaths++] = createCords(y, x);
                }
            }
            field[y][x] = currentChar;
        }
    }

    if (numberOfPaths == 0) {
        printf("There are no possible starting / ending points - try lowering the fogPercentage (%d) or wallsPercentage (%d)\n", fogPercentage, wallsPercentage);
        return 1;
    }

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++)
            printf("%c", field[y][x]);
        printf("\n");
    }

    printf("-\n");
    for (int i = 0; i < numberOfProblems; i++) {
        cords* start = paths[rand() % numberOfPaths];
        cords* end = paths[rand() % numberOfPaths];

        printf("%d %d %d %d\n", start->y, start->x, end->y, end->x);
    }
    
    return 0;
}