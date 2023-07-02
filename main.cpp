#include "lib/algs.h"

int main(int argc, char **argv){
    if(argc != 3){
        printf("Formato: %s <arquivo.txt> <operação> \n",*argv);
        printf("'arquivo.txt' é o arquivo com o texto a ser lido.\n");
        printf("'operação' pode ser 0 para criptografar, e 1 para descriptografar.\n");
        exit(1);
    }

    char op = atoi(*(argv+2));
    char *filename = *(argv+1);

    switch (op)
    {
    case 0:
        encryptCaesar(filename);
        break;
    case 1:
        decryptCaesar(filename);
        break;
    default:
        std::cout << "ERRO. Operação inválida.\n";
    }

    return 0;
}