#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_LENGTH 256
#define MAX_WORD_LENGTH 100

void readHashFile(const char *hashFile, char hashes[][MAX_HASH_LENGTH], int *numHashes) {
    FILE *file = fopen(hashFile, "r");
    if (file == NULL) {
        perror("Error opening hash file");
        exit(1);
    }

    char line[MAX_HASH_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        strcpy(hashes[*numHashes], line);
        (*numHashes)++;
    }

    fclose(file);
}


void readDictionary(const char *wordlist, void (*hashFunc)(const char*, char*)) {
    FILE *file = fopen(wordlist, "r");
    if (file == NULL) {
        perror("Error opening dictionary file");
        exit(1);
    }

    char word[MAX_WORD_LENGTH];
    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\n")] = 0; // Remove newline
        char hashedWord[MAX_HASH_LENGTH];
        hashFunc(word, hashedWord);
        // Compare hashedWord with your hashes here
    }

    fclose(file);
}

// Placeholder for hash function (replace with real hash function)
void simpleHashFunc(const char *input, char *output) {
    // Simple hash: just returns the first three characters (for illustration)
    strncpy(output, input, 3);
    output[3] = '\0';
}


int main(int argc, char *argv[]) {
    //parse user input
    char *hashType;
    char *hashFile;
    char *wordlist;

    if (argc != 4) {
        printf("Usage: %s <hash-type> <hash-file> <dictionary-file>\n", argv[0]);
        return 1;
    }

    hashType = argv[1];
    hashFile = argv[2];
    wordlist = argv[3];

    printf("Hash Type: %s\n", hashType);
    printf("Hash File: %s\n", hashFile);
    printf("Dictionary File: %s\n", wordlist);

    char hashes[1000][MAX_HASH_LENGTH]; // Adjust size as necessary
    int numHashes = 0;
    readHashFile(hashFile, hashes, &numHashes);

    readDictionary(wordlist, simpleHashFunc);


    return 0;


}

