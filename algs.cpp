#include "lib/algs.h"

void encryptCaesar(const char *name){
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

    //

    free(encry_name);
    fclose(encry_ptr);
    fclose(file_ptr);
}

void decryptCaesar(const char *name){
    FILE *file_ptr;
    if(!(file_ptr = fopen(name,"r"))){
        std::cout << "Erro ao abrir o arquivo.\n";
        exit(1);
    }

    char *decry_name = (char*) malloc(strlen(name) + 6);
    sprintf(decry_name,"decry_%s",name);

    FILE *decry_ptr;    
    if(!(decry_ptr = fopen(decry_name,"w"))){
        std::cout << "Erro.\n";
        exit(1);
    }

    //

    free(decry_name);
    fclose(decry_ptr);
    fclose(file_ptr);
}