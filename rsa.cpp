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

    mpz_class aux;

    while(fin.get(ch)){
        num = ch;
        if(isalpha(ch)){
            num = islower(ch)?(ch-97+first_alp):(ch-65+first_alp);
            #ifdef DEBUG
            printf("ch: %c[%s][%d]\t num: %d\n",ch,isalpha(ch)?"yes":"not",ch,num);
            #endif
            aux = findmod(num,e,pq);
            num = aux.get_ui();
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

mpz_class findmod(const int a, const int e, const int pq){
    mpz_class res;
    mpz_class a_mpz = a;
    mpz_class e_mpz = e;
    mpz_class pq_mpz = pq;
    mpz_powm(res.get_mpz_t(), a_mpz.get_mpz_t(), e_mpz.get_mpz_t(), pq_mpz.get_mpz_t());
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
    bool neg_aux;

    mpz_class decod_num = search_mod(p,q,e);
    mpz_class aux;
    while(fin.get(ch)){
        if(ch == '\\'){
            neg_aux = false;
            fin.get(ch);
            if(ch == '-'){
                neg_aux = true;
                fin.get(ch);
            }
            num[0] = ch;
            fin.get(ch);
            num[1] = ch;
            fin.get(ch);
            fout.put(neg_aux?-atoi(num):atoi(num));
            continue;
        }
        num[0] = ch;
        fin.get(ch);
        num[1] = ch;
        ch = atoi(num);
        
        #ifdef DEBUG
        printf("num = {%c, %c}\t ch = %d\n",num[0],num[1],ch);
        #endif
        
        aux = search_val(ch,decod_num,p*q);
        ch = aux.get_ui();
        ch+=97-alpha;

        #ifdef DEBUG
        printf("ch: %c[%d]\n",ch,ch); 
        #endif

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
        std::cout << "O inverso de " << e << " modulo " << num_mod << " não existe." << '\n';
        return 0;
    }
    else {
        return aux;
    }
}

mpz_class search_val(const unsigned a, mpz_class decod_num,const unsigned pq){
    mpz_class res;
    mpz_class a_mpz = a;
    mpz_class pq_mpz = pq;
    mpz_powm(res.get_mpz_t(), a_mpz.get_mpz_t(), decod_num.get_mpz_t(), pq_mpz.get_mpz_t());
    return res;
}