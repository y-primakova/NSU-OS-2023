#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.");
        return -1;
    }
    char buff[BUFSIZ];
    FILE *fpin = fopen(argv[1], "r");
    if (fpin == NULL) {
        perror("Fopen failed.");
        return -1;
    }
    FILE *fpout = popen("tr [:lower:] [:upper:]", "w");
    if (fpout == NULL) {
        perror("Popen failed.");
        fclose(fpin);
        return -1;
    }
    while (fgets(buff, BUFSIZ, fpin) != NULL) {
        if (fputs(buff, fpout) == EOF) {
            perror("Fputs failed.");
            fclose(fpin);
            pclose(fpout);
            return -1;
        }
    }
    fclose(fpin);
    pclose(fpout);
    return 0;
}
