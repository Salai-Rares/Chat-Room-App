#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rectree.h"

rt *checkUsername(char *username,rt *root){
    rt *next=root;
    int idx,n=strlen(username);
    for(int i=0;i<n;i++){
        tolower(username[i]);
        idx=username[i]-'a';
        if(!next->alpha[idx]) return NULL;
        next=next->alpha[idx];
    }    
    if(!next->flag) return NULL;
    return next;
}

rt *usernameAviable(char *username,rt *root){
    rt *next=root;
    int idx,n=strlen(username);
    for(int i=0;i<n;i++){
        idx=username[i]-'a';
        if(!next->alpha[idx])
           next->alpha[idx]=ALLOC;
        next=next->alpha[idx];
    }    
    if(next->flag) return NULL;
    return next;
}