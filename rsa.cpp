#include "lib/asym.h"

void encryptRSA(const char *name, const int first_alp, const unsigned pq, const unsigned e){
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
            //printf("ch: %c[%s]\t num: %d\n",ch,isalpha(ch)?"yes":"not",num);
            num = findmod(num,e,pq);
            if(num < 10)fout<<0;
            fout << num;
        }
        else{
            fout << "\\" << num << "\\";
        }
    }

    fin.close();
    fout.close();
}

unsigned findmod(const int a, const int e, const int pq){
    unsigned res;
    res = pow(a,e);
    res %= pq;
    //printf("%d^%d == %d (mod %d)\n",a,e,res,pq);
    return res;
}

void decryptRSA(){

}