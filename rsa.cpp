#include "lib/asym.h"

void encryptRSA(const char *name, const int first_alp, const int pq, const int e){
    std::ifstream fin(name,std::ios::in);
    if(!(fin.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char *encry_name = (char*) malloc(strlen(name) + 6);
    sprintf(encry_name,"encry_%s",name);

    std::ofstream fout(encry_name,std::ios::trunc);
    if(!(fout.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char ch;
    int num;

    while(fin.get(ch)){
        num = ch;
        if(isalpha(ch)){
            num = islower(ch)?(ch-97+first_alp):(ch-65+first_alp);
        }

        fout << num << ' ';


    }

    fin.close();
    fout.close();
}

int mod_(){

}

void decryptRSA(){

}