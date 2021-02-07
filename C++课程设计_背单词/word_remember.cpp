
#include "word_remember.h"



void rememberword(struct Word wordlist[],int n)
{
	while(1)
	{
		int cnt=0;//������¼�ڴ��е�������
		struct Word unknown[1000];
		loadfile_bdc(unknown,cnt);
		int selection=0;
	 
		system("cls");
		cout<<"-------------------"<<endl;
		cout<<"    ������ģʽ     "<<endl;
		cout<<"-------------------"<<endl;
		cout<<"    1.��ϰ����     "<<endl;
		cout<<"    2.˳�����     "<<endl;
		cout<<"    3.�������     "<<endl;
		cout<<"    4.�˳�         "<<endl;
		cout<<"-------------------"<<endl;
		cout<<"ѡ��0-4��:";
		cin>>selection;
		getchar();
		switch(selection)
		{
			case 1: revise_mode(unknown,cnt);
			        break;
			case 2: inorder_mode(wordlist,n,unknown,cnt);
					break;
			case 3: outoforder_mode(wordlist,n,unknown,cnt);
			 		break;
			case 4: break;	
		}
		if(selection==4)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	return ;
}

int loadfile_bdc(struct Word unknown[],int &cnt)
{
	Word newword;
	ifstream infile;
	char temp[100]="d:\\";
	strcat(temp,userinfo_filename);
	strcat(temp,"������.txt");
	strcpy(unknownlist_filename,temp);
	infile.open(unknownlist_filename,ios::in);
	if(!infile)
	{
		ofstream outfile(unknownlist_filename);
		outfile.close();
		cnt=0;
		return 0;
	}
	
	while(!infile.eof())
	{
		infile>>newword.word>>newword.word_class>>newword.word_meaning;
		infile.getline(newword.word_note,50); 
		if(infile)
		{
			unknown[cnt]=newword;
			cnt++;
		}
		else
		{
			break;
		}
	}
	infile.close();	
	
	return cnt;	
}

int savefile_bdc(struct Word unknown[],int cnt)
{
	ofstream outfile;
	outfile.open(unknownlist_filename,ios::out);
	if(!outfile)
	{
		cout<<"�޷������ݱ��浽�ļ� "<<unknownlist_filename<<" !";
		Sleep(3000);
		return 0; 
	}	
	for(int i=0;i<cnt;i++)
	{
		outfile<<unknown[i].word<<" "<<unknown[i].word_class<<" "<<unknown[i].word_meaning<<unknown[i].word_note<<endl;	//getling����ʱnoteǰ��һ���ո��� 
	}	
	outfile.close();
	return 1;
}

void deleteword_bdc(struct Word unknown[],int &cnt,int i)//iΪҪɾ���ĵ��ʵ��±�
{
	//ԭ�����±��0��cnt-1;
	for(int j=i;j<=cnt-2;j++)
	{
		unknown[j]=unknown[j+1];
	}
	cnt--;
	return ;
} 

void addword_bdc(struct Word unknown[],int &cnt,struct Word toadd)
{
	unknown[cnt]=toadd;
	cnt++;
}

int find_word(struct Word wordlist[],int n,char _word[],char _class[])//�ҵ������±꣬��Ȼ����-1 
{
	int flag=0;
	int i=0; 
	for(i=0;i<n;i++)
	{
		if(strcmp(wordlist[i].word,_word)==0&&strcmp(wordlist[i].word_class,_class)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		i=-1;
	}
	return i;
} 

void revise_mode(struct Word unknown[],int &cnt)
{
	system("cls");
	int d[1000]={0}; 
	if(cnt==0)
	{
		cout<<endl<<"��û�п��Ը�ϰ�ĵ���Ŷ��"<<endl; 
	}
	else
	{
		cout<<"\n-------------------------------��ϰģʽ-----------------------------------"<<endl;
		cout<<endl<<endl;
		
		start=clock();
		for(int i=0;i<cnt;i++)
		{
			cout<<setw(20)<<"����"<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
			cout<<"--------------------------------------------------------------------------"<<endl;
			cout<<setw(20)<<unknown[i].word<<setw(10)<<unknown[i].word_class<<setw(30)<<unknown[i].word_meaning<<unknown[i].word_note<<endl;
			cout<<"--------------------------------------------------------------------------"<<endl; 
			cout<<endl<<"A.������     B.���������ʿ�      C.�˳���ϰģʽ"<<endl;
			cout<<"\n���������ѡ��";
			char sel=0;
			cin>>sel;
			switch(sel)
			{
				case 'a':
				case 'A': cout<<"\n���������\n\n\n";
					      d[i]=1;
					      break;
				case 'b': 
				case 'B': cout<<"\n�������ͣ�\n\n\n";
						  break;
				case 'c':
				case 'C': goto out;
			} 
			cout<<endl;
	 	}
	 	end=clock();
	 	getchar();
		cout<<"��ϲ���Ѹ�ϰ�����е�����,��ʱ"<<double(end-start)/CLOCKS_PER_SEC<<"�롣";
		goto out;	
	}
	out:
	int cnt_0=cnt;
	for(int i=0;i<cnt_0;i++)
	{
		if(d[i]==1)
		{
			deleteword_bdc(unknown,cnt,i);
		}
	}//ɾ���Ѿ���ס�ĵ��� 
	savefile_bdc(unknown,cnt);
	cout<<"\n\n����������ر�����ģʽ�˵�...";
	getchar();
	return;
}

void inorder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt)
{ 
	while(1)
	{
		system("cls");
		cout<<"\n-------------------------------˳�����ģʽ---------------------------------"<<endl;
		cout<<endl;
		char _word[20];
		char _class[10];
		cout<<"����������Ҫ��ʼ�ĵ��ʣ����س��������룩��";
		cin>>_word;
		cout<<"������õ��ʵĴ��ԣ����س��������룩��" ;
		cin>>_class;
		int dofind=find_word(wordlist,n,_word,_class);
		if(dofind==-1)
		{
			cout<<endl<<"��Ǹû���ҵ��õ��ʣ��밴������������롣\n";
			getchar(); 
			getchar();
			continue;
		}
		else
		{
			cout<<endl<<endl;
			start=clock();
			for(int i=dofind;i<n;i++)
			{
				cout<<setw(20)<<"����"<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<setw(20)<<wordlist[i].word<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<endl<<"A.������     B.��������ʿ�      C.�˳�˳�����ģʽ"<<endl;
				cout<<"\n���������ѡ��";
				char sel=0;
				cin>>sel;
				switch(sel)
				{
					case 'a':
					case 'A': cout<<"\n���������\n\n\n";
						      break;
					case 'b': 
					case 'B': cout<<"\n�������ͣ�\n\n\n";
							  addword_bdc(unknown,cnt,wordlist[i]);
							  break;
					case 'c':
					case 'C': goto out;
				} 
				cout<<endl;
	 	    }
			end=clock();
			getchar();
			cout<<"��ϲ���ѱ����ʿ�,��ʱ"<<double(end-start)/CLOCKS_PER_SEC<<"�롣";
			goto out;		
		}
	}
	out:
	savefile_bdc(unknown,cnt);
	cout<<"\n\n����������ر�����ģʽ�˵�...";
	getchar();
	return;		
}

void outoforder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt)
{
	system("cls");
	srand(time(0));
	cout<<"\n-------------------------------�������ģʽ---------------------------------"<<endl;
	cout<<endl<<endl;
	while(1)
	{
		int rad=rand()%n;
		cout<<setw(20)<<"����"<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<setw(20)<<wordlist[rad].word<<setw(10)<<wordlist[rad].word_class<<setw(30)<<wordlist[rad].word_meaning<<wordlist[rad].word_note<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<endl<<"A.������     B.��������ʿ�      C.�˳�˳�����ģʽ"<<endl;
		cout<<"\n���������ѡ��";
		char sel=0;
		cin>>sel;
		getchar();
		switch(sel)
		{
			case 'a':
			case 'A': cout<<"\n���������\n\n\n";
				      break;
			case 'b': 
			case 'B': cout<<"\n�������ͣ�\n\n\n";
					  addword_bdc(unknown,cnt,wordlist[rad]);
					  break;
			case 'c':
			case 'C': goto out;
		} 
		cout<<endl;
	}
	out:
	savefile_bdc(unknown,cnt);
	cout<<"\n\n����������ر�����ģʽ�˵�...";
	getchar();
	return;		
	
}
