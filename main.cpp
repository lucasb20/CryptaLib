#include "lib/cifras.h"
#include "lib/asym.h"
#include "lib/analise.h"

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "Formato: " << *argv << " <op> " << "<possíveis parâmetros> " << std::endl;
        exit(1);
    }
    char op = atoi(*(argv+1));

    if(argc == 2){
        switch(op){
            case 0 ... 1:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << " <key or shift> " << std::endl;
            break;
            case 2:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << "<PQ> " << "<E>" << std::endl;
            break;
            case 3:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << "<P> " << "<Q> " << "<E>" << std::endl;
            break;
            case 4:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << std::endl;
            break;
            case 5:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << " <letra_inicial> " << " <letra_substituta> " << std::endl;
            break;
            case 6:
            std::cout << "Formato: " << *argv << " " << *(argv+1) << " <arquivo.txt> " << " <arquivo_trocas.txt> " << std::endl;
            break;
        }
        exit(1);
    }

    char *filename = *(argv+2);
    std::string key_file;
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

        case 6:
        key_file = *(argv+3);
        change_letter(filename,key_file);
        default:
        std::cout << "Operação inválida.\n";
        break;
    }
    
    return 0;
}