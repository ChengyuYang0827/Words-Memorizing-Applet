#include "login.h"

void  login()
{
	
	int selection=0;
	int flag=0;//��¼�û�������û����������Ƿ�ƥ�� 
	while(1)
	{	int m=0;	//������¼�ڴ��е��û����� 
		struct User user_info[100];
		loadfile_enroll(user_info,m);
		system("cls");
		cout<<"---------------------"<<endl;
		cout<<"      ������1.0      "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"      1.��¼         "<<endl;
		cout<<"      2.ע��         "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"��ѡ��1-2����";
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
	infile.open("d:\\�û���Ϣ.txt",ios::in);
	if(!infile)
	{
		ofstream outfile("d:\\�û���Ϣ.txt");
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
	outfile.open("d:\\�û���Ϣ.txt",ios::out);
	if(!outfile)
	{
		cout<<"\n�޷������ݱ��浽�ļ� d:\\�û���Ϣ.txt !";
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
		cout<<"\n�����������û�����";
		cin>>temp_username;
		cout<<"\n�������������룺";
		int i=0;
		while(1)
		{
			char c=getch();//getch()�������ն˻����ַ�
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
	    	cout<<"\n�û���δע�ᣬ����ע�ᣡ\n";
	    	Sleep(3000);
	    	break;
		}
		else
		{
			if(strcmp(user_info[index].password,temp_password)!=0)
			{
				cout<<"\n�û��������벻ƥ�䣬���������룡\n";
				Sleep(3000);
				continue;
			}
			else
			{
				strcpy(userinfo_filename,temp_username);
				cout<<"\n��¼�ɹ���\n"; 
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
		cout<<"\n��������Ҫע����û���(��֧����ĸ������)��";
		cin>>temp_username;
		cout<<"\n����������(��֧����ĸ������)��";
		int i=0;
		while(1)
		{
			char c=getch();//getch()�������ն˻����ַ�
			if(c=='\r')
			{
				break;
			}
			printf("*");
			temp_password[i]=c;
			i++;
		}
		cout<<"\n\n��ȷ������(��֧����ĸ������)��";
		i=0;
		while(1)
		{
			char c=getch();//getch()�������ն˻����ַ�
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
				cout<<"\n����ע�ᣬ��ֱ�ӵ�¼��";
				Sleep(3000);
				goto out;
			}
		} 
		
		if(flag==0)
		{
			if(strcmp(temp_password,temp_repass)!=0)
			{
				cout<<"\n�������벻һ�£����������룡";
				Sleep(3000);
				continue; 
			}
			else
			{
//				struct User newuser;
//				strcpy(newuser.username,temp_username);
//				strcpy(newuser.username,temp_password);
//��ôд�Ǵ�ģ�user_info[m]=newuser;
				strcpy(user_info[m].username,temp_username);
				strcpy(user_info[m].password,temp_password);
				m++;
				cout<<"\nע��ɹ������¼��";
				Sleep(3000); 
				break;
			}
		}
	}
	out:
	savefile_enroll(user_info,m);
	return ;
}

