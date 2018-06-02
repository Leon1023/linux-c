#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "BiTree.h"

void PreOrderTraverse( BiTree T )
{
    if(T==NULL){
       return;
    }
    printf("%c",T->data);
    PreOrderTraverse(T->LChild);
    PreOrderTraverse(T->RChild);
}



void InOrderTraverse( BiTree T )
{
    if(T == NULL){
        return;
    }
    InOrderTraverse(T->LChild);
    printf("%c",T->data);
    InOrderTraverse(T->RChild);
}



void PostOrderTraverse( BiTree T )
{
    if(T == NULL){
        //fprintf(stderr,"BitTree invalid:%s",strerror(errno));
       // exit(1);
       return;
    }
    InOrderTraverse(T->LChild);
    InOrderTraverse(T->RChild);
    printf("%c",T->data);
}


void CreatPreOrdBiTree(BiTree *T)
{
    TElemType ch;
    ch = getchar();
    if(ch=='#'){
        *T = NULL;
    }
    else{
        if((*T = (BiTree)malloc(sizeof(BiTNode)))==NULL){
           fprintf(stderr,"malloc false:%s",strerror(errno));
           exit(1);
       }
        (*T)->data = ch;
        CreatPreOrdBiTree(&((*T)->LChild));
        CreatPreOrdBiTree(&((*T)->RChild));
    }
}



void CreatInOrdBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    if(ch=='#'){
        *T = NULL;
    }
    else{
        if((*T = (BiTree)malloc(sizeof(BiTNode)))==NULL){
           fprintf(stderr,"malloc false:%s",strerror(errno));
           exit(1);
       }
        CreatPreOrdBiTree(&(*T)->LChild);
        (*T)->data = ch;
        CreatPreOrdBiTree(&(*T)->RChild);
    }
}



void CreatPostOrdBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    if(ch=='#'){
        *T = NULL;
    }
    else{
        if((*T = (BiTree)malloc(sizeof(BiTNode)))==NULL){
           fprintf(stderr,"malloc false:%s",strerror(errno));
           exit(1);
       }
        CreatPreOrdBiTree(&(*T)->LChild);
        CreatPreOrdBiTree(&(*T)->RChild);
        (*T)->data = ch;
    }
}



