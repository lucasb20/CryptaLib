#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

void encryptCaesar(const char *name, const int shift);
int fix(int);
int toogle(int);
void encryptVigenere(const char*name,const char*key);
int charToShift(char);
bool check_next(char,int);