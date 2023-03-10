#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool compare(int line1[6], int line2[6]) {
    for (int i = 0; i < 6; i++) {
        if (line1[i] != line2[i] || line1[i] == 2 || line2[i] == 2) {
            return false;
        }
    }
    return true;
}

bool checkTooMuch(int grid[6][6]) {
    for (int row = 0; row < 6; row++) {
        int count0 = 0;
        int count1 = 0;
        for (int index = 0; index < 6; index++) {
            if (grid[row][index] == 0) {
                count0++;
            } else if (grid[row][index] == 1) {
                count1++;
            }
        }
        if (count0 > 3 || count1 > 3) {
            return false;
        }
    }
    
    for (int column = 0; column < 6; column++) {
        int count0 = 0;
        int count1 = 0;
        for (int index = 0; index < 6; index++) {
            if (grid[index][column] == 0) {
                count0++;
            } else if (grid[index][column] == 1) {
                count1++;
            }
        }
        if (count0 > 3 || count1 > 3) {
            return false;
        }
    }

    return true;
}

bool checkFollowing(int grid[6][6]) {
    for (int row = 0; row < 6; row++) {
        for (int index = 0; index < 4; index++) {
            if (grid[row][index] == grid[row][index + 1] && grid[row][index + 1] == grid[row][index + 2] && grid[row][index] != 2) {
                return false;
            }
        }
    }
    
    for (int column = 0; column < 6; column++) {
        for (int index = 0; index < 4; index++) {
            if (grid[index][column] == grid[index + 1][column] && grid[index + 1][column] == grid[index + 2][column] && grid[index][column] != 2) {
                return false;
            }
        }
    }

    return true;
}

bool checkRepetitions(int grid[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i != j && compare(grid[i], grid[j])) {
                return false;
            }
        }
    }

    for (int i = 0; i < 6; i++) {

        int column1[6];
        for (int index = 0; index < 6; index++) {
            column1[index] = grid[index][i];
        }

        for (int j = 0; j < 6; j++) {

            int column2[6];
            for (int index = 0; index < 6; index++) {
                column2[index] = grid[index][j];
            }

            if (i != j && compare(column1, column2)) {
                return false;
            }
        }
    }

    return true;
}

bool verify(int grid[6][6]) {
    // Trop de 0 / 1
    if (!checkTooMuch(grid)) {
        return false;
    }

    // Plus de 2 successifs
    if (!checkFollowing(grid)) {
        return false;
    }
    
    // Doublons
    if (!checkRepetitions(grid)) {
        return false;
    }

    return true;
}

bool complete(int grid[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (grid[i][j] == 2) {
                return false;
            }
        }
    }
    return true;
}

void generate(int solution[6][6], int (*user)[6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (rand()%2 == 0) {
                user[i][j] = solution[i][j];
            }
        }
    }
}

void generateEasy(int solution[6][6], int (*user)[6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            user[i][j] = solution[i][j];
        }
    }
    user[rand()%6][rand()%6] = 2;
}

void show(int grid[6][6]) {
    if (complete(grid)) {
        printf("------SOLUTION-------\n");
    } else {
        printf("---------------------\n");
    }
    printf("    0--1--2--3--4--5\n");
    for (int i = 0; i < 6; i++) {
        printf(" %d>", i);
        for (int j = 0; j < 6; j++) {
            if (grid[i][j] != 2) {
                printf(" %d ", grid[i][j]);
            } else {
                printf(" * ");
            }
            
        }
        printf("\n");
    }
    printf("---------------------\n");
}

void saisie(int (*grid)[6]) {
        int i, j, v;
        bool first = true;
        while (first || grid[i][j] != 2) {
            printf("Entrez l'indice i (Ligne) : ");
            scanf("%d", &i);
            printf("\nEntrez l'indice j (Colonne) : ");
            scanf("%d", &j);
            printf("\nEntrez la valeur : ");
            scanf("%d", &v);
            while (v < 0 || v > 1) {
                printf("\nMerci d'entrer uniquement 0 ou 1 !");
                printf("\nEntrez la valeur : ");
                scanf("%d", &v);
            }
            
            first = false;
        }
        grid[i][j] = v;
        show(grid);
}

int main() {
    srand(time(NULL));

    int solution[6][6] = {{0, 1, 0, 0, 1, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0}, {0, 1, 0, 1, 0, 1}, {1, 0, 1, 1, 0, 0}, {0, 1, 1, 0, 1, 0}};
    int user[6][6] = {{2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2}};

    show(solution);

    int easy;
    printf("Voulez vous une grille facile (1 = oui / 2 = non) ?\n");
    scanf("%d", &easy);

    if (easy == 1) {
        generateEasy(solution, user);
    } else {
        generate(solution, user);
    }
    

    show(user);

    while (!complete(user))
    {
        saisie(user);
    }

    if (verify(user)) {
        printf("Bravo, vous avez gagne !\n");
    } else {
        printf("Vous ferez mieux la prochaine fois :(\n");
    }

    system("pause");
    return 0;
}