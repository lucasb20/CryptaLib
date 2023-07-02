#include "lib/algs.h"

void encryptCaesar(const char *name, const int shift){
    FILE *file_ptr;
    if(!(file_ptr = fopen(name,"r"))){
        std::cout << "Erro ao abrir o arquivo.\n";
        exit(1);
    }

    char *encry_name = (char*) malloc(strlen(name) + 6);
    sprintf(encry_name,"encry_%s",name);

    FILE *encry_ptr;
    if(!(encry_ptr = fopen(encry_name,"w"))){
        std::cout << "Erro.\n";
        exit(1);
    }

    char ch;
    int shift_otm = fix(shift);
    while((ch = getc(file_ptr)) != EOF){
        if(isalpha(ch)){
            if(!(isalpha(ch+shift_otm)))shift_otm = toogle(shift_otm);
            ch += shift_otm;
        }
        fprintf(encry_ptr,"%c",ch);
    }

    free(encry_name);
    fclose(encry_ptr);
    fclose(file_ptr);
}

int fix(int num){
    int num_fix = num;
    bool isneg = (num_fix<0)?true:false;
    if(isneg)num_fix*=-1;

    while(num_fix>=26){
        num_fix-=26;
    }

    if(isneg)num_fix = num_fix*(-1);

    return num_fix;
}

int toogle(int shift){
    int res;
    res = shift>0?shift-26:shift+26;
    return res;
}