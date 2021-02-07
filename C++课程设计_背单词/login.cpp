#include "login.h"

void  login()
{
	
	int selection=0;
	int flag=0;//记录用户输入的用户名和密码是否匹配 
	while(1)
	{	int m=0;	//用来记录内存中的用户数量 
		struct User user_info[100];
		loadfile_enroll(user_info,m);
		system("cls");
		cout<<"---------------------"<<endl;
		cout<<"      背单词1.0      "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"      1.登录         "<<endl;
		cout<<"      2.注册         "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"请选择（1-2）：";
		cin>>selection;
		switch(selection)
		{
			case 1:flag=check_in(user_info,m);
				   break;
			case 2:enrollment(user_info,m);
				   break;
		}
		if(flag==1)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	return;
}

int loadfile_enroll(struct User user_info[],int &m)
{
	User newuser;
	ifstream infile;
	infile.open("d:\\用户信息.txt",ios::in);
	if(!infile)
	{
		ofstream outfile("d:\\用户信息.txt");
		outfile.close();
		m=0;
		return 0;
	}
	while(!infile.eof())
	{
		infile>>newuser.username>>newuser.password;
		if(infile)
		{
			user_info[m]=newuser;
			m++;
		}
		else
		{
			break;
		}
	}
	infile.close();	
	return m;
}

int savefile_enroll(struct User user_info[],int m)
{
	ofstream outfile;
	outfile.open("d:\\用户信息.txt",ios::out);
	if(!outfile)
	{
		cout<<"\n无法将数据保存到文件 d:\\用户信息.txt !";
		Sleep(3000);
		return 0; 
	}	
	for(int i=0;i<m;i++)
	{
		outfile<<user_info[i].username<<" "<<user_info[i].password<<endl;
	}	
	outfile.close();
	return 1;
}

int check_in(struct User user_info[],int m)
{
	while(1)
	{
		system("cls");
		char temp_username[20]={0};
		char temp_password[20]={0}; 
		int index=-1;
		cout<<"\n请输入您的用户名：";
		cin>>temp_username;
		cout<<"\n请输入您的密码：";
		int i=0;
		while(1)
		{
			char c=getch();//getch()不会向终端回显字符
			if(c=='\r')
			{
				break;
			}
			printf("*");
			temp_password[i]=c;
			i++;
		}
		cout<<endl;
		for(int i=0;i<m;i++)
		{
			if(strcmp(user_info[i].username,temp_username)==0)
			{
				index=i;
				break;
			}	
	    } 
	    if(index==-1)
	    {
	    	cout<<"\n用户名未注册，请先注册！\n";
	    	Sleep(3000);
	    	break;
		}
		else
		{
			if(strcmp(user_info[index].password,temp_password)!=0)
			{
				cout<<"\n用户名和密码不匹配，请重新输入！\n";
				Sleep(3000);
				continue;
			}
			else
			{
				strcpy(userinfo_filename,temp_username);
				cout<<"\n登录成功！\n"; 
				Sleep(3000); 
				return 1;
			}
		}
	}
	return 0;
}

void enrollment(struct User user_info[],int &m)
{
	while(1)
	{
		system("cls");
		int flag=0;
		char temp_username[20];
		char temp_password[20]={0};
		char temp_repass[20]={0};
		cout<<"\n请输入您要注册的用户名(仅支持字母和数字)：";
		cin>>temp_username;
		cout<<"\n请输入密码(仅支持字母和数字)：";
		int i=0;
		while(1)
		{
			char c=getch();//getch()不会向终端回显字符
			if(c=='\r')
			{
				break;
			}
			printf("*");
			temp_password[i]=c;
			i++;
		}
		cout<<"\n\n请确认密码(仅支持字母和数字)：";
		i=0;
		while(1)
		{
			char c=getch();//getch()不会向终端回显字符
			if(c=='\r')
			{
				break;
			}	
			printf("*");
			temp_repass[i]=c;
			i++;
		}
		cout<<endl;
		for(int i=0;i<m;i++)
		{
			if(strcmp(temp_username,user_info[i].username)==0)
			{
				flag=1;
				cout<<"\n您已注册，请直接登录！";
				Sleep(3000);
				goto out;
			}
		} 
		
		if(flag==0)
		{
			if(strcmp(temp_password,temp_repass)!=0)
			{
				cout<<"\n两次密码不一致，请重新输入！";
				Sleep(3000);
				continue; 
			}
			else
			{
//				struct User newuser;
//				strcpy(newuser.username,temp_username);
//				strcpy(newuser.username,temp_password);
//这么写是错的？user_info[m]=newuser;
				strcpy(user_info[m].username,temp_username);
				strcpy(user_info[m].password,temp_password);
				m++;
				cout<<"\n注册成功，请登录！";
				Sleep(3000); 
				break;
			}
		}
	}
	out:
	savefile_enroll(user_info,m);
	return ;
}

