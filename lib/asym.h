#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

void encryptRSA(const char *name, const int first_alp, const unsigned pq, const unsigned e);
unsigned findmod(const int,const int,const int);

typedef struct{
    int pq;
    int e;
    int first_alpha;
}param_;