#include "lib/algs.h"

int main(int argc, char **argv){
    if(argc != 4){
        printf("Formato: %s <arquivo.txt> <shift or key> <op>\n",*argv);
        exit(1);
    }

    char *filename = *(argv+1);
    char shift;
    char *key;
    char op = atoi(*(argv+3));

    switch(op){
        case 0:
        shift = atoi(*(argv+2));
        encryptCaesar(filename,shift);
        break;

        case 1:
        key = *(argv+2);
        encryptVigenere(filename,key);
        break;

        default:
        std::cout << "Operação inválida.\n";
        break;
    }
    
    return 0;
}