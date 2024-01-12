#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //parse user input
    char *hashType;
    char *hashFile;
    char *wordlist;

    if (argc != 4) {
        printf("Usage: %s <hash-type> <hash-file> <dictionary-file>\n", argv[0]);
        return 1;
    }


}

