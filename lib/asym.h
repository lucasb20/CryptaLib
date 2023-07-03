#include <gmpxx.h>

void encryptRSA(const char *name, const int first_alp, const unsigned pq, const unsigned e);
mpz_class findmod(const int,const int,const int);
void decryptRSA(const char *name, const unsigned p, const unsigned q, const unsigned e, const int first_alpha);
mpz_class search_val(const unsigned,mpz_class,const unsigned);
mpz_class search_mod(const unsigned,const unsigned,const unsigned);

typedef struct{
    int p;
    int q;
    int pq;
    int e;
    int first_alpha;
}param_;