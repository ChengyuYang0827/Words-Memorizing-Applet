#ifndef _LOG_IN_
#define _LOG_IN_
#include "word_remember.h"
#include "head.h"
struct User
{
	char username[20];
	char password[20];
};

void  login();
int check_in(struct User user_info[],int m);
int loadfile_enroll(struct User user_info[],int &m);
int savefile_enroll(struct User user_info[],int m);
void enrollment(struct User user_info[],int &m);
#endif
