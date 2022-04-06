#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    char word[40];
    char line[30000];
}element;
  
typedef element ElementType;

struct node{
     ElementType data;
     struct node *left,*right;
};

typedef struct node TreeType;

TreeType *newNode(ElementType x)
{
  TreeType *tmp = (TreeType*)malloc(sizeof(TreeType));

  if(tmp != NULL)
    {
      tmp->left = NULL;
      tmp->right = NULL;
      tmp->data.count = 1;
      strcpy(tmp->data.word, x.word); 
      strcpy(tmp->data.line, x.line);
    }
  return tmp;
}

TreeType *Search(ElementType x, TreeType *root, char *wordline)
{
  if(root == NULL) return NULL;
  
  else if(strcmp(x.word,root->data.word) == 0){
      if(strlen(root->data.line) >= 1){
        strcat(root->data.line, ",");
      }
      strcat(root->data.line, wordline);
      root->data.count++;
      return root;
  }
    
  else if(strcmp(x.word,root->data.word) > 0)
    return Search(x,root->right, wordline);
  
  else
    return Search(x,root->left, wordline);
}

TreeType *Insert(ElementType x, TreeType *root, char *wordline)
{
  if(root == NULL)
  {
    root = newNode(x);
    return root;
  }
  if(Search(x, root, wordline) != NULL) return root;

  if(strcmp(x.word, root->data.word) < 0)
    root->left = Insert(x, root->left, wordline); 

  if(strcmp(x.word, root->data.word) > 0)
    root->right = Insert(x, root->right, wordline);
  
  return root;
}

void inorderPrint(TreeType *root, FILE *fptr)
{
  if(root != NULL) 
  {
    inorderPrint(root->left, fptr);
    printf("%s   %d   %s\n",root->data.word, root->data.count, root->data.line);
    fprintf(fptr,"%s   %d   %s\n", root->data.word, root->data.count, root->data.line);
    inorderPrint(root->right, fptr);
  }
}

void freeTree(TreeType *root)
{
  if(root == NULL) return;
  freeTree(root->left);
  freeTree(root->right);
  free(root);
  return;
}