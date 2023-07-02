#include "lib/algs.h"

int main(int argc, char **argv){
    if(argc != 3){
        printf("Formato: %s <arquivo.txt> <num>\n",*argv);
        printf("'arquivo.txt' é o arquivo com o texto a ser lido.\n");
        printf("'num' é número do deslocamento na ordem do alfabeto.\n");
        exit(1);
    }

    char *filename = *(argv+1);
    char shift = atoi(*(argv+2));

    encryptCaesar(filename,shift);
    
    return 0;
}