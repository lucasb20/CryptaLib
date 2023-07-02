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
    
    while((ch = getc(file_ptr)) != EOF){
        printf("ch: %c[%d]\tis: %d\tnew_ch: %c[%d]\tnum: %d\n",ch,ch,isalpha(ch),ch+shift,ch+(shift % 26),shift % 26);
        if(isalpha(ch))ch += (shift+26) % 26;
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