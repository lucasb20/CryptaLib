#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <gmpxx.h>

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
            #ifdef DEBUG
            printf("ch: %c[%s]\t num: %d\n",ch,isalpha(ch)?"yes":"not",num);
            #endif
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
    #ifdef DEBUG
    printf("%d^%d == %d (mod %d)\n",a,e,res,pq);
    #endif
    return res;
}

void decryptRSA(const char *name, const unsigned p, const unsigned q, const unsigned e,const int alpha){
    std::ifstream fin(name,std::ios::in);
    if(!(fin.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char *decry_name = (char*) malloc(strlen(name) + 6);
    sprintf(decry_name,"decry_%s",name);

    std::ofstream fout(decry_name,std::ios::trunc);
    if(!(fout.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char ch, num[] = {'0','0'};

    mpz_class decod_num = search_mod(p,q,e);
    while(fin.get(ch)){
        if(ch == '\\'){
            fin.get(ch);
            num[0] = ch;
            fin.get(ch);
            num[1] = ch;
            fin.get(ch);
            fout.put(atoi(num));
            continue;
        }
        num[0] = ch;
        fin.get(ch);
        num[1] = ch;
        ch = atoi(num);
        printf("num = {%c, %c}\t ch = %d\n",num[0],num[1],ch);
        ch = search_val(ch,decod_num,p*q);
        printf("ch: %c[%d]\n",ch,ch);
        ch+=65;

        fout.put(ch);
    }

    free(decry_name);
    fin.close();
    fout.close();
}

mpz_class search_mod(const unsigned p,const unsigned q,const unsigned e){
    mpz_class num_mod = (p-1)*(q-1);
    mpz_class e_mpz = e;
    mpz_class aux;
    if (mpz_invert(aux.get_mpz_t(), e_mpz.get_mpz_t(), num_mod.get_mpz_t()) == 0){
        std::cout << "O inverso de " << e << " modulo " << num_mod << " nao existe." << '\n';
        return 0;
    }
    else {
        return aux;
    }
}

unsigned search_val(const unsigned a, const unsigned decod_num,const unsigned pq){
    unsigned res;
    res = pow_int(a,decod_num);
    printf("res: %d\n",res);
    res = res % pq;
    return res;
}

unsigned pow_int(unsigned a, unsigned exp){
    unsigned res = 1;
    for(int i=0; i<exp; i++)res*=a;
    return res;
}