#include "lib/cifras.h"
#include "lib/asym.h"
#include "lib/analise.h"
#include "iostream"

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "Formato: " << *argv << " <op> " << "<possíveis parâmetros> " << '\n';
        exit(1);
    }
    char op = atoi(*(argv+1));

    if(argc == 2 && (op == 0 || op == 1)){
        char aux[9];
        sprintf(aux,"%s",op?"<key>":"<shift>");
        std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << aux << '\n';
        exit(1);
        free(aux);
    }
    else if(argc == 2 && (op == 2)){
        std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << "<PQ> " << "<E>" << '\n';
        exit(1);
    }
    else if(argc == 2 && (op == 3)){
        std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << "<P> " << "<Q> " << "<E>" << '\n';
        exit(1);
    }
    else if(argc == 2 && (op == 4)){
        std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << '\n';
        exit(1);
    }
    else if(argc == 2 && (op == 5)){
        std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << " <letra_inicial> " << " <letra_substituta> " << '\n';
        exit(1);
    }

    char *filename = *(argv+2);
    key chave;
    param_ rsa;
    char a,b;

    switch(op){
        case 0:
        chave.shift = atoi(*(argv+3));
        encryptCaesar(filename,chave.shift);
        break;

        case 1:
        chave.key = *(argv+3);
        encryptVigenere(filename,chave.key);
        break;

        case 2:
        rsa.pq = atoi(*(argv+3));
        rsa.e = atoi(*(argv+4));
        rsa.first_alpha = 10;
        encryptRSA(filename,rsa.first_alpha,rsa.pq,rsa.e);
        break;

        case 3:
        rsa.p = atoi(*(argv+3));
        rsa.q = atoi(*(argv+4));
        rsa.e = atoi(*(argv+5));
        rsa.first_alpha = 10;
        decryptRSA(filename,rsa.p,rsa.q,rsa.e,rsa.first_alpha);
        break;

        case 4:
        freqAnalysis(filename);
        break;

        case 5:
        a = argv[3][0];
        b = argv[4][0];
        change_letter(filename,a,b);
        break;

        default:
        std::cout << "Operação inválida.\n";
        break;
    }
    
    return 0;
}