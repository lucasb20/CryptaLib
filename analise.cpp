#include "lib/analise.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <cstring>

//define DEBUG

class ocorr{
    public:
    size_t qtd;
    std::vector<char> array_char;
    std::vector<size_t> array_size;
    ocorr(size_t num){
        this->qtd = num;
    }
    void criar_carac(char c){
        this->array_char.push_back(c);
        this->array_size.push_back(1);
        this->qtd++;
    }
    bool present_(char c){
        for(int i = 0; i < qtd; i++){
            if(this->array_char[i] == c){
                return true;
            }
        }
        return false;
    }
    void do_ocorr(char c){
        for(int i = 0; i < this->qtd; i++){
            if(this->array_char[i]==c){
                this->array_size[i]++;
                #ifdef DEBUG
                printf("Ocorrência: %c[%ld]\n",array_char[i],array_size[i]);
                #endif
                return;
            }
        }
    }
    void show_pos(char *ch, size_t *n,int i){
        *ch = this->array_char[i];
        *n = this->array_size[i];
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

    size_t num;

    while(fin.get(ch)){
        #ifdef DEBUG
        printf("Chegando %c. (%s)\n",ch,dif_.present_(ch)?"Já pertence.":"Não pertence.");
        #endif
        if(!(dif_.present_(ch))){
            dif_.criar_carac(ch);
        }
        else{
            dif_.do_ocorr(ch);
        }
    }

    if(!(dif_.qtd)){
        fout << "Arquivo vazio.\n";
        return;
    }
    else{
        bubbleSort(dif_.array_size,dif_.array_char);
        fout << "Há " << dif_.qtd << " caracteres diferentes.\n"; 
        for(int i = dif_.qtd - 1; i >= 0; i--){
            dif_.show_pos(&ch,&num,i);
            fout << ch << '[' << (int)ch << ']' << " -> " << num << '\n';
        }
    }

    fin.close();
}

void bubbleSort(std::vector<size_t>&v,std::vector<char>&_char){
    size_t n = v.size();

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                _swap(v[j], v[j + 1]);
                _swap(_char[j],_char[j+1]);
            }
        }
    }
}

void _swap(size_t &a, size_t &b){
    size_t temp = a;
    a = b;
    b = temp;
}

void _swap(char &a, char &b){
    char temp = a;
    a = b;
    b = temp;
}