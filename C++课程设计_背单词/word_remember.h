#ifndef _WORD_REMEMBER_
#define _WORD_REMEMBER_ 

#include "head.h"
#include "login.h"

extern clock_t start,end;
extern char unknownlist_filename[100];
extern char wordlist_filename[100];
extern char userinfo_filename[100];

void revise_mode(struct Word unknown[],int &cnt);
void rememberword(struct Word wordlist[],int n);
int loadfile_bdc(struct Word unknown[],int &cnt);
int savefile_bdc(struct Word unknown[],int cnt);
void deleteword_bdc(struct Word unknown[],int &cnt,int i); 
void addword_bdc(struct Word unknown[],int &cnt,struct Word toadd);
void inorder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt);
void outoforder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt);
#endif
