#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char *key) {
    int used[26] = {0};
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;

            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

void findPosition(char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepareText(char *input, char *output) {
    int k = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char ch = toupper(input[i]);

            if (ch == 'J')
                ch = 'I';

            output[k++] = ch;
        }
    }

    output[k] = '\0';
}

void encrypt(char *text, char *result) {
    int len = strlen(text);
    int k = 0;

    for (int i = 0; i < len; i += 2) {
        char a = text[i];
        char b = text[i + 1];

        int r1, c1, r2, c2;
        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2) {
            result[k++] = matrix[r1][(c1 + 1) % 5];
            result[k++] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            result[k++] = matrix[(r1 + 1) % 5][c1];
            result[k++] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            result[k++] = matrix[r1][c2];
            result[k++] = matrix[r2][c1];
        }
    }

    result[k] = '\0';
}

int main() {
    char key[100], input[1000];
    char text[1000], prepared[1000], encrypted[1000];

    printf("Enter keyword: ");
    scanf("%s", key);

    getchar();

    printf("Enter plaintext: ");
    fgets(input, sizeof(input), stdin);

    createMatrix(key);

    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    prepareText(input, text);

    int len = strlen(text);
    int k = 0;

    for (int i = 0; i < len; i++) {
        prepared[k++] = text[i];

        if (i + 1 < len && text[i] == text[i + 1]) {
            prepared[k++] = 'X';
        }
    }

    if (k % 2 != 0)
        prepared[k++] = 'X';

    prepared[k] = '\0';

    encrypt(prepared, encrypted);

    printf("\nPrepared plaintext: %s\n", prepared);
    printf("Ciphertext: %s\n", encrypted);

    return 0;
}
