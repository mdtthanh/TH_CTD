#include "library.h"
#include <ctype.h>


typedef struct List {
    char word[40];
};

int Check(List *stopwL, char *word, int countL) {
    for(int i = 0; i < countL; i++) {
        if(strcmp(stopwL[i].word, word) == 0) return 1;
    }
    return 0;
}

void Stopw(FILE *fp1, List *stopwL, int *countL) {
    char name[3];
    while(fgets(name,3,fp1) != NULL) {
        name[strlen(name) - 1] = '\0';
        strcpy(stopwL[*countL].word,name);
        *countL = *countL + 1;
    }
}

void readFile(FILE *f1, FILE *f2, TreeType *root, int countL, List *stopwL) {
    char *token, s[250], word[30];
    int line = 0; 
    
    while (fgets(s, 250, f1) != NULL) 
    {
        line++; // cứ hết 1 dòng thì line cộng thêm 1
                for(int i = 0; i< strlen(s); i++) {
            if(s[i] == '!' ||s[i] == '`' || s[i] == '-' ||s[i] == '"' || s[i] == '[' || s[i] == ']' || s[i] == '*' || s[i] == '_' || s[i] == ''||s[i] == '(' || s[i] == ')' || s[i] == '?') 
              s[i] = ' ';
        }
        if (s[strlen(s) - 1] == '\n') 
        {
            s[strlen(s) - 1] = '\0';
        }
        char tmp[250];
        strcpy(tmp, s);
        token = strtok(s, " ,;:"); // khi gặp dấu cách , ; : thì cắt chuỗi
        while (token != NULL){
            strcpy(word, token);
            if (isupper(word[0])){
                for(int i = 0; i < strlen(tmp); i++){
                    if(tmp[i] == word[0] && tmp[i-1] == ' '){
                        strcpy(word, " ");
                    }
                }
            }
            for(int i = 0; i < strlen(word); i++){
                if(isupper(word[i])){
                    word[i] = tolower(word[i]);
                }
            }
            while(word[strlen(word) - 1] == '.' || word[strlen(word) - 1] == '\'') word[strlen(word) - 1] = '\0';

            int check = Check(stopwL, word, countL);
    
        }

        
    }
    
}
