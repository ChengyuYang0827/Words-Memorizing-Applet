#ifndef _HEAD
#define _HEAD

#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
using namespace std; 

struct Word
{ 
	char word[50];           //单词拼写 
	char word_class[10];     //单词词性 
	char word_meaning[100];  //单词意思 
	char word_note[50];     //单词的笔记 
};

#endif
