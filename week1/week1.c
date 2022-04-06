#include "library.h"
#include <ctype.h>

typedef struct {
    char word[40];
}list;
typedef list List;

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

void readFile(FILE *f, FILE *fp2, TreeType *root, int countL, List *stopwL){
    char *token, s[250], word[30];
    int line = 0;

    while(fgets(s,250,f) != NULL) {
        line ++;

        for(int i = 0; i< strlen(s); i++) {
            if(s[i] == '!' ||s[i] == '`' || s[i] == '-' ||s[i] == '"' || s[i] == '[' || s[i] == ']' || s[i] == '*' || s[i] == '_' || s[i] == ''||s[i] == '(' || s[i] == ')' || s[i] == '?') 
              s[i] = ' ';
        }
        if(s[strlen(s)-1] == '\n')  s[strlen(s) - 1] = '\0';

        char tmp[250];
        strcpy(tmp,s);
        
        token = strtok(s," ,;:");       
        while(token != NULL) {
            strcpy(word, token);

            if(isupper(word[0])) {
                for(int i = 0; i < strlen(tmp); i++) {
                    if(tmp[i] == word[0] && tmp[i-1] == ' ') {
                        strcpy(word," ");
                    }
                }
            }                
            for(int i = 0; i < strlen(word); i++) {
                if(isupper(word[i])) word[i] = tolower(word[i]);
            }
            while(word[strlen(word)-1] == '.' || word[strlen(word)-1] == '\'') word[strlen(word)-1] = '\0';

            int check = Check(stopwL, word, countL);
            char wordline[10];
            sprintf(wordline, "%d", line);

            if(strcmp(word, " ") != 0 && check == 0) {
                ElementType x;
                strcpy(x.line,"");
                strcpy(x.word, word);
                strcat(x.line, wordline);
                *(&root) = Insert(x, root, wordline);            
            }
            token = strtok(NULL," ,;:");
        }
    }
    inorderPrint(root, fp2);
}

void printFile(TreeType *root, FILE *fp2)
{
  if(root != NULL) 
  {
    printFile(root->left, fp2);
    fprintf(fp2,"%s   %d   %s\n", root->data.word, root->data.count, root->data.line);
    printFile(root->right, fp2);
  }
}

int main() {
    TreeType *root = NULL;
    FILE *fptr, *fptr1, *fptr2;
    char name[] = "vanban.txt", name1[] = "stopw.txt", name2[]= "result.txt";
    fptr = fopen(name,"r");
    fptr1 = fopen(name1,"r");
    fptr2 = fopen(name2, "w");

    int count_List = 0;
    List stopw_List[25];
    
    if(fptr == NULL || fptr1 == NULL) {
        printf("Can not open file!\n");
        return 0;
    }

    Stopw(fptr1, stopw_List, &count_List);
    readFile(fptr, fptr2, root, count_List, stopw_List);
    fclose(fptr);
    fclose(fptr1);
    fclose(fptr2);
} 