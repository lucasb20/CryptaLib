#include "lib/analise.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <cstring>
#include <iostream>

class ocorr{
    private:
    size_t qtd;
    std::vector<std::vector<char>> array;
    public:
    ocorr(size_t num){
        this->qtd = num;
    }
    void criar_carac(char c){
        std::vector<char> aux(2);
        aux.push_back(c);
        aux.push_back(1);
        this->array.push_back(aux);
        this->qtd++;
    }
    bool present_(char c){
        for(int i = 0; i < qtd; i++){
            if(this->array[i][0] == c){
                return true;
            }
        }
        return false;
    }
    size_t getQtd(){
        return this->qtd;
    }
    void do_ocorr(char c){
        for(int i = 0; i < this->qtd; i++){
            if(this->array[i][0]==c){
                this->array[i][1]++;
            }
        }
    }
};

void freqAnalysis(const char *name){
    std::ifstream fin(name,std::ios::in);
    if(!(fin.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char *outname = (char*) malloc(6+strlen(name));

    sprintf(outname,"stats_%s",name);

    std::ofstream fout(outname,std::ios::trunc);

    free(outname);
    
    if(!(fout.is_open())){
        std::cout << "Erro ao criar o arquivo.\n";
        exit(1);
    }

    ocorr dif_(0);

    char ch;

    while(fin.get(ch)){
        if(!(dif_.present_(ch))){
            dif_.criar_carac(ch);
        }
        else{

        }
    }

    if(!(dif_.getQtd())){
        fout << "Arquivo vazio.\n";
        return;
    }
    else{
        fout << "Há " << dif_.getQtd() << " caracteres diferentes.\n"; 
        
    }

    fin.close();
}