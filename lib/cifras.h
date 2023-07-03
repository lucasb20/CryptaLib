

void encryptCaesar(const char *name, const int shift);
int fix(int);
int toogle(int);
void encryptVigenere(const char*name,const char*key);
int charToShift(char);
bool check_next(char,int);

typedef union{
    int shift;
    char *key;
} key;