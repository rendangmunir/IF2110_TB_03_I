#include <stdio.h>
#include "includeADT.h"

int main() {
    FILE *configFile = fopen("../cfg/pengguna.config", "w");

    if (configFile == NULL) {
        perror("Unable to open config file.\n");
        return 1;
    }

    START();
    while (currentChar != MARK) {
        fprintf(configFile, "%c", currentChar);
        ADV();
    }

    fclose(configFile);

    return 0;
}