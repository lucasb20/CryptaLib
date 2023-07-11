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
    double _percent(char c){
        size_t _c=0,total=0;
        double percent=0;
        for(int i = 0; i < this->array_size.size(); i++){
            if(array_char[i] == 10 or array_char[i] == 32)continue;
            total += this->array_size[i];
            if(array_char[i]==c){
                _c += this->array_size[i];
            }
        }
        if(total > 0)percent = ((double)_c)/total;
        return percent;
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
            fout << ch << '[' << (int)ch << ']' << " -> " << num << " -> " << (dif_._percent(ch))*100 << '%' << '\n';
        }
    }

    fout.close();
    fin.close();
}

void change_letter(const char *name, const char a, const char b){
    std::ifstream fin(name,std::ios::in);
    if(!(fin.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char *outname = (char*) malloc(6+strlen(name));

    sprintf(outname,"modif_%s",name);

    std::ofstream fout(outname,std::ios::trunc);

    free(outname);
    
    if(!(fout.is_open())){
        std::cout << "Erro ao criar o arquivo.\n";
        exit(1);
    }

    char ch;
    while(fin.get(ch)){
        if(ch == a){
            fout.put(b);
        }
        else{
            fout.put(ch);
        }
    }

    fin.close();
    fout.close();
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

void change_letter(const char *name, std::string keys){
    std::ifstream fin(name,std::ios::in);
    if(!(fin.is_open())){
        std::cout << "Erro ao ler o arquivo.\n";
        exit(1);
    }

    char *outname = (char*) malloc(6+strlen(name));

    sprintf(outname,"modif_%s",name);

    std::ofstream fout(outname,std::ios::trunc);
    
    free(outname);

    if(!(fout.is_open())){
        std::cout << "Erro ao criar o arquivo.\n";
        exit(1);
    }

    std::ifstream fkeys(keys,std::ios::in);
    
    if(!(fkeys.is_open())){
        std::cout << "Erro ao criar o arquivo.\n";
        exit(1);
    }

    char ch;
    std::vector<std::string> to_change;
    std::string aux;

    while(fkeys.get(ch)){
        #ifdef DEBUG
        printf("Checando %c[%d] :: aux.size() -> [%lu]\n",ch,ch,aux.size());
        #endif
        if(!(isalpha(ch)))continue;
        aux.push_back(ch);
        #ifdef DEBUG
        std::cout << "aux -> " << aux << std::endl;
        #endif
        if(aux.size()==2){
            to_change.push_back(aux);
            aux.clear();
        }
    }

    size_t pos_aux;

    while(fin.get(ch)){
        if(present_(ch,to_change,pos_aux)){
            fout << to_change[pos_aux][1];
        }
        else{
            fout << ch;
        }
    }

    fin.close();
    fout.close();
    fkeys.close();
}

bool present_(char c,std::vector<std::string>obj,size_t &ref){
    for(int i = 0; i < obj.size(); i++){
        if(obj[i][0] == c){
            ref = i;
            return true;
        }
    }
    ref = -1;
    return false;
}