#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rectree.h"
#include "database.h"

typedef struct record{
    unsigned int ways;
    char flag;
    char password[30];
}record;

record node2db(rt *node){
   record r;
   r.ways=0;
   for(int i=0;i<26;i++)
       if(node->alpha[i])
          r.ways = r.ways | (1<<i);
   r.flag=node->flag;
   strcpy(r.password,node->password);
   return r;
}   

rt* db2node(record r){
   rt *node=ALLOC;
   for(int i=0;i<26;i++){
       if(r.ways & (1<<i))
         node->alpha[i]=ALLOC;
   }
   node->flag=r.flag;
   strcpy(node->password,r.password);
   return node;
}

void wf(FILE *f,rt *node){
     record temp=node2db(node);
     fwrite(&temp,sizeof(record),1,f);
     for(int i=0;i<26;i++){
         if(node->alpha[i])
           wf(f,node->alpha[i]);
     }
}

void dbStore(char *path,rt *root){
    if(!root) return;
    FILE *file=fopen(path,"wb");
    wf(file,root);
    fclose(file);
}

rt* rf(FILE *f){
    rt *node;
    record temp;
    fread(&temp,sizeof(record),1,f);
    node=db2node(temp);
    for(int i=0;i<26;i++){
        if(node->alpha[i])
           node->alpha[i]=rf(f);
    }
    return node;
}

rt* dbLoad(char *path){
    FILE *file=fopen(path,"rb");
    if(feof(file)) return NULL;
    rt *root;
    root=rf(file);
    fclose(file);
    return root;   
}