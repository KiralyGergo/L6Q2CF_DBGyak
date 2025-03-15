#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 100

void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

int main() {
    char filename[MAX_LINE];
    char line[MAX_LINE];
    
    // Fájlnév beolvasása
    printf("File name: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Hiba a fájlnév beolvasása közben!\n");
        return 1;
    }

    // Sorvégi újsor karakter eltávolítása
    filename[strcspn(filename, "\n")] = '\0';

    // Fájl megnyitása írásra
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Hiba a fájl megnyitásakor");
        return 1;
    }

    // Adatok beolvasása a végjel (#) eléréséig
    printf("Adatok bevitele (teljes nev + neptunkód, '#' a befejezéshez):\n");
    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        if (line[0] == '#' && line[1] == '\n') break;  // Ha csak egy # van egy sorban
        
        fputs(line, file);
    }

    fclose(file);

    // Fájl újranyitása olvasásra
    file = fopen(filename, "r");
    if (!file) {
        perror("Hiba a fájl újranyitásakor");
        return 1;
    }

    printf("\nMentett adatok nagybetűsen:\n");

    // Sorok beolvasása, nagybetűsítése és kiírása
    while (fgets(line, sizeof(line), file)) {
        to_uppercase(line);
        printf("%s", line);
    }

    fclose(file);
    return 0;
}