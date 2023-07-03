#include "lib/cifras.h"

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
            if(check_next(ch,shift_otm))shift_otm = toogle(shift_otm);
            //printf("ch: %c[%d]\t%c[%d]\t shift:[%d]\n",ch,ch,ch+shift_otm,ch+shift_otm,shift_otm);
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

void encryptVigenere(const char*name,const char*key){
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
    int shift;
    int pos=0;
    while((ch = getc(file_ptr)) != EOF){
        shift = key[(pos % strlen(key))];

        shift = charToShift(shift);

        if(isalpha(ch)){
            //printf("ch: %c[%d]\t%c[%d]\t shift:[%d]\n",ch,ch,ch+shift_otm,ch+shift_otm,shift_otm);
            if(check_next(ch,shift))shift = toogle(shift);
            ch += shift;
            pos++;
        }
        fprintf(encry_ptr,"%c",ch);
    }

    free(encry_name);
    fclose(encry_ptr);
    fclose(file_ptr);
}

int charToShift(char char_){
    if(isdigit(char_)){
        return char_;
    }
    else if(isalpha(char_)){
        return tolower(char_) - 97;
    }
    return 0;
}

int toogle(int shift){
    int res;
    res = shift>0?shift-26:shift+26;
    return res;
}

bool check_next(char ch, int shift){
    if(!(isalpha(ch+shift)))return true;
    
    bool check_pre = true;
    bool check_pos = true;

    if(islower(ch))check_pre = false;
    if(islower(ch+shift))check_pos = false;

    return check_pre^check_pos;

}