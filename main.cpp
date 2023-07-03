#include "lib/cifras.h"
#include "lib/asym.h"

int main(int argc, char **argv){
    if(argc != 4){
        printf("Formato: %s <arquivo.txt> <key> <op>\n",*argv);
        exit(1);
    }

    char *filename = *(argv+1);
    key chave;
    char op = atoi(*(argv+3));

    switch(op){
        case 0:
        chave.shift = atoi(*(argv+2));
        encryptCaesar(filename,chave.shift);
        break;

        case 1:
        chave.key = *(argv+2);
        encryptVigenere(filename,chave.key);
        break;

        case 2:
        chave.shift = atoi(*(argv+2));
        encryptRSA(filename,10,33,7);
        break;

        default:
        std::cout << "Operação inválida.\n";
        break;
    }
    
    return 0;
}