#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char *message, char *key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];

        if (isalpha(ch)) {
            if (islower(ch))
                message[i] = tolower(key[ch - 'a']);
            else
                message[i] = toupper(key[ch - 'A']);
        }
    }
}

void decrypt(char *message, char *key) {
    for (int i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];

        if (isalpha(ch)) {
            char lower = tolower(ch);

            for (int j = 0; j < 26; ++j) {
                if (key[j] == lower) {
                    if (islower(ch))
                        message[i] = 'a' + j;
                    else
                        message[i] = 'A' + j;
                    break;
                }
            }
        }
    }
}

int main() {
    char message[1000];
    char key[27];

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter 26-letter substitution key: ");
    scanf("%26s", key);

    if (strlen(key) != 26) {
        printf("Invalid key! Key must contain 26 unique letters.\n");
        return 1;
    }

    encrypt(message, key);
    printf("Encrypted message: %s", message);

    decrypt(message, key);
    printf("Recovered plaintext: %s", message);

    return 0;
}
