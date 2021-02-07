#include "head.h"
#include "word_remember.h"
#include "login.h"
 
clock_t start,end;//������ʱ����������
char wordlist_filename[100];
char unknownlist_filename[100];
char userinfo_filename[100];

int load_file(struct Word wordlist[],int &n);
int save_file(struct Word wordlist[],int n);
void print(struct Word wordlist[],int n);
void Search(struct Word wordlist[],int n);
void search_EtoC(struct Word wordlist[],int n);
void search_CtoE(struct Word wordlist[],int n);
void search_EtoC_spe(struct Word wordlist[],int n);
void search_fast(struct Word wordlist[],int n);
void addnote(struct Word wordlist[],int n);
void addword(struct Word wordlist[],int &n);
void changeword(struct Word wordlist[],int n);
void deleteword(struct Word wordlist[],int &n);
void Test(struct Word wordlist[],int n);
void test_CtoE(struct Word wordlist[],int n);
void test_EtoC(struct Word wordlist[],int n);
void sort(struct Word wordlist[],int n);

int main(int argc, char** argv) 
{
	login();
	static struct Word wordlist[10000];
	int n=0;//������¼�ڴ��еĵ����� 
	int selection=0;
	while(1)
	{
		system("cls");
		cout<<"----------------------------------"<<endl;
		cout<<"         ������С����             "<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"         1.����ʿ�               "<<endl; 
		cout<<"         2.��ʾ�ʿ�               "<<endl;
		cout<<"         3.��������               "<<endl; 
		cout<<"         4.��ӵ��ʱʼ�           "<<endl;
		cout<<"         5.����µ���             "<<endl; 
		cout<<"         6.�޸ĵ�����Ϣ           "<<endl; 
		cout<<"         7.ɾ������               "<<endl; 
		cout<<"         8.���ʲ���               "<<endl; 
		cout<<"         9.������                 "<<endl;
		cout<<"         0.�˳�                   "<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"ѡ��0-9��:";
		cin>>selection;
		getchar();
		switch(selection)
		{
			case 1:	load_file(wordlist,n);
					break;
			case 2: sort(wordlist,n);
					print(wordlist,n);
					break;
			case 3: sort(wordlist,n);
					Search(wordlist,n);
					break;
			case 4: addnote(wordlist,n);
					break;
		    case 5: addword(wordlist,n);
		    		break;
		    case 6: changeword(wordlist,n);
		    		break;
		    case 7: deleteword(wordlist,n);	
		    		break;
		    case 8: Test(wordlist,n);
		    		break;
			case 9: sort(wordlist,n);
					rememberword(wordlist,n); 
					break;
			case 0: if(n==0)
		    		{
		    			break;
					}
					else
					{
						sort(wordlist,n);
		    			save_file(wordlist,n);
						break;
					} 
		} 
		if(selection==0)
		{
			break;
		}
	} 
	return 0;
}

int load_file(struct Word wordlist[],int &n)
{
	system("cls");
	Word newword;
	ifstream infile;
	cout<<"�����뵥���ļ���λ�ã�";
	cin>>wordlist_filename; 
	getchar();
	infile.open(wordlist_filename,ios::in);
	if(!infile)
	{
		cout<<endl<<"�������ļ� "<<wordlist_filename<<" !";
		Sleep(3000);
		n=0;
		return 0;
	}
	
	start=clock(); 
	while(!infile.eof())
	{
		infile>>newword.word>>newword.word_class>>newword.word_meaning;
		infile.getline(newword.word_note,50); 
		cout.setf(ios::left);
		if(infile)
		{
//			cout<<setw(20)<<newword.word<<newword.word_class<<newword.word_meaning<<newword.word_note<<endl;
			wordlist[n]=newword;
			n++;
		}
		else
		{
			break;
		}
	}
	end=clock();
	
	infile.close();
	cout<<endl<<"�ɹ�����"<<n<<"�����ʣ���ʱ";
	cout<<double(end-start)/CLOCKS_PER_SEC;
	cout<<"�롣\n\n��������ص����˵�......\n";
	getchar();
	return n;
}

int save_file(struct Word wordlist[],int n)
{
	ofstream outfile;
	outfile.open(wordlist_filename,ios::out);
	if(!outfile)
	{
		cout<<"�޷������ݱ��浽�ļ� "<<wordlist_filename<<" !";
		Sleep(3000);
		return 0; 
	}	
	for(int i=0;i<n;i++)
	{
		outfile<<wordlist[i].word<<" "<<wordlist[i].word_class<<" "<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;	//getling����ʱnoteǰ��һ���ո��� 
	}	
	outfile.close();
	return 1;
}

void print(struct Word wordlist[],int n)
{
	system("cls");
	if(n==0)
	{
		cout<<endl<<"�ʿ����޵��ʣ��뵼��ʿ⣡\n"; 
	}
	else
	{
		cout.setf(ios::left);
		cout<<endl<<endl; 
		cout<<setw(20)<<"����"<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		
		start=clock();
		for(int i=0;i<n;i++)
		{
			cout<<setw(20)<<wordlist[i].word<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
		}
		end=clock();
		
		cout<<endl<<"������Ϣ����ʾ��ϣ�\n"; 
		cout<<endl<<"һ����ʾ"<<n<<"�����ʣ���ʱ" ;
		cout<<double(end-start)/CLOCKS_PER_SEC<<"�롣\n"; 
	}
	cout<<endl<<"��������������˵�......\n";
	getchar();
	return; 
}


void Search(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		int sel=0;
		cout<<endl;
		cout<<"---------------------"<<endl;
		cout<<"         ����        "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"    1.����Ӣ������   "<<endl;
		cout<<"    2.������������   "<<endl;
		cout<<"    3.Ӣ�ľ�ȷ����   "<<endl;
		cout<<"    4.��������       "<<endl; 
		cout<<"    5.�˳�����       "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"���������ѡ��1-5����";
		cin>>sel;
		getchar(); 
		switch(sel)
		{
			case 1: search_EtoC(wordlist,n);
					break;
			case 2: search_CtoE(wordlist,n);
					break;
			case 3: search_EtoC_spe(wordlist,n);
					break;
			case 4: search_fast(wordlist,n);
					break;
			case 5: break;
	    }
	    if(sel==5)
	    {
	    	break;
		}
	}
	return ;
}

void search_EtoC(struct Word wordlist[],int n)
{
	while(1)
	{	
		system("cls"); 
		int cnt=0;//��¼������� 
		char object[20];
		cout<<endl<<"����������Ҫ��ѯ�ĵ��ʣ����ִ�Сд�����س��������룩��";
		cin>>object; 
		
		start=clock();
		for(int i=0;i<n;i++)//���Ҳ���� 
		{
			if(strcmp(object,wordlist[i].word)==0)
			{
				if(cnt==0)
				{
					cout<<endl<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
					cout<<"---------------------------------------------------"<<endl;
					cout<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
					cnt++;
				}
				else
				{
					cout<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
					cnt++;
				}
			}	
		} 
		end=clock();
		
		if(cnt==0)
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ���Ҫ��ѯ�ĵ��ʡ�\n";
		}
		else
		{
			cout<<endl<<"���Ϲ�"<<cnt<<"�������������ʱ";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"�롣\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"����0���������˵�������1�������ң��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else if(_selection==1) 
		{
			continue;
		}
	}
	getchar();
	return;
} 

void search_CtoE(struct Word wordlist[],int n)
{
	while(1)
	{	
		system("cls");
		int cnt=0;//��¼������� 
		char object[20];
		cout<<endl<<"����������Ҫ��ѯ�ĵ��ʵ�������˼��";
		cin>>object; 
		
		start=clock();
		for(int i=0;i<n;i++)//���Ҳ���� 
		{
			if(strcmp(object,wordlist[i].word_meaning)==0)
			{
				if(cnt==0)
				{
					cout<<endl<<setw(10)<<"����"<<setw(21)<<"Ӣ�ĵ���"<<"�ʼ�"<<endl;
					cout<<"--------------------------------------------"<<endl;
					cout<<setw(10)<<wordlist[i].word_class<<setw(20)<<wordlist[i].word<<wordlist[i].word_note<<endl;
					cnt++;
				}
				else
				{
					cout<<setw(10)<<wordlist[i].word_class<<setw(20)<<wordlist[i].word<<wordlist[i].word_note<<endl;
					cnt++;
				}
			}	
		} 
		end=clock();
		
		if(cnt==0)
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ���Ҫ��ѯ�ĵ��ʡ�\n";
		}
		else
		{
			cout<<endl<<"���Ϲ�"<<cnt<<"�������������ʱ";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"�롣\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"����0���������˵�������1�������ң��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	getchar();
	return;
} 

void search_EtoC_spe(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		int cnt=0;//��¼�������
		char object_word[20];
		char object_word_class[10];
		cout<<endl<<"����������Ҫ��ѯ�ĵ��ʣ����ִ�Сд�����س��������룩��";
		cin>>object_word;
		cout<<"������õ��ʵĴ��ԣ�Сд�����س����������룩��";
		cin>>object_word_class;
		
		start=clock();
		for(int i=0;i<n;i++)
		{
			if(strcmp(object_word,wordlist[i].word)==0&&strcmp(object_word_class,wordlist[i].word_class)==0)
			{
				cout<<endl<<setw(31)<<"������˼"<<"�ʼ�";
				cout<<endl<<"---------------------------------------";
				cout<<endl<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note;
				cout<<endl; 
				cnt++;
			}
		}
		end=clock();
		
		if(cnt==1)
		{
			cout<<endl<<"����������ʱ"<<double(end-start)/CLOCKS_PER_SEC<<"�롣\n"; 
		}
		else
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ���Ҫ��ѯ�ĵ��ʡ�\n";
		}
		
		int _selection=0;
		cout<<endl<<"����0���������˵�������1�������ң��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else
		{
			continue;
		}
	}
	getchar();
	return;
}

void search_fast(struct Word wordlist[],int n)
{
	while(1)
	{	
		system("cls"); 
		int cnt=0;//��¼������� 
		char object[20];
		cout<<endl<<"����������Ҫ��ѯ�ĵ��ʣ����ִ�Сд�����س��������룩��";
		cin>>object; 
		
		int left=0;
		int right=n-1;
		int center=(left+right)/2;
		start=clock();
		while(left<=right)
		{
			if(strcmp(wordlist[center].word,object)==0)
			{
				break;
			}
			else if(strcmp(wordlist[center].word,object)<0)
			{
				left=center+1;
				center=(left+right)/2;
			}
			else
			{
				right=center-1;
				center=(left+right)/2;
			}
		}
		end=clock();
		
		if(left>right)
		{
			cnt=0; 
		} 
		else
		{
			cout<<endl<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
			cout<<"---------------------------------------------------"<<endl;
			cout<<setw(10)<<wordlist[center].word_class<<setw(30)<<wordlist[center].word_meaning<<wordlist[center].word_note<<endl;
			cnt++;
		}
		
		if(cnt==0)
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ���Ҫ��ѯ�ĵ��ʡ�\n";
		}
		else
		{
			cout<<endl<<"���Ϲ�"<<cnt<<"�������������ʱ";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"�롣\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"����0���������˵�������1�������ң��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else if(_selection==1) 
		{
			continue;
		}
	}
	getchar();
	return;
} 	

void addnote(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		int cnt=0;//���������û���ҵ� 
		int temp=0;//������¼�ҵ��ĵ��ʵ��±� 
		char input[50];
		char object_word[20];
		char object_word_class[10];
		cout<<endl<<"����������Ҫ��ӱʼǵĵ��ʣ����ִ�Сд�����س��������룩��";
		cin>>object_word;
		cout<<endl<<"������õ��ʵĴ��ԣ�Сд�����س����������룩��";
		cin>>object_word_class;
		getchar();
		
		start=clock();
		for(int i=0;i<n;i++)
		{
			if(strcmp(object_word,wordlist[i].word)==0&&strcmp(object_word_class,wordlist[i].word_class)==0)
			{
				cnt++;
				temp=i;
			}
		}
		end=clock();
		
		if(cnt==1)
		{
			strcpy(wordlist[temp].word_note," ");//ԭ����" ����" 
			cout<<endl<<"���ҵ��õ��ʡ���������Ҫ��ӵıʼǣ�";
			cin.getline(input,50);
			cout<<endl<<"��ӳɹ���"<<endl; 
			strcat(wordlist[temp].word_note,input);
		}
		else
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ�������ĵ��ʡ�"<<endl; 
		}
		
		cout<<endl<<"����0�������˵�������1������ӣ��밴�س����������룩��"; 
		int _selection=0;
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else if(_selection==1)
		{
			continue;
		}
	}
	return ; 
}

void addword(struct Word wordlist[],int &n)
{
	while(1)
	{	
		system("cls");
		char input_word[50];
		char input_word_class[10];
		char input_word_meaning[100];
		char input_word_note[50];
		int cnt=0;
		cout<<endl<<"��������Ҫ��ӵĵ��ʣ����س����������룩��"; 
		cin>>input_word;
		cout<<endl<<"������õ��ʵĴ��ԣ����س����������룩��";
		cin>>input_word_class;
		
		for(int i=0;i<n;i++)
		{
			if(strcmp(wordlist[i].word,input_word)==0&&strcmp(wordlist[i].word_class,input_word_class)==0)
			{
				cnt++;
			}
		}
		
		if(cnt==1)
		{
			cout<<endl<<"�ʿ����Ѿ�����Ҫ��ӵĵ�����Ŷ��\n"; 
		}
		else
		{
			cout<<endl<<"������õ��ʵ�������˼�����س����������룩��";
			cin>>input_word_meaning;
			getchar();
			cout<<endl<<"������õ��ʵıʼǣ����س����������룩��";
			cin.getline(input_word_note,50);
			strcpy(wordlist[n].word,input_word);
			strcpy(wordlist[n].word_class,input_word_class);
			strcpy(wordlist[n].word_meaning,input_word_meaning);
			strcpy(wordlist[n].word_note," ");
			strcat(wordlist[n].word_note,input_word_note);
			n++;
			cout<<endl<<"��ӳɹ���\n";
		}
		
		cout<<endl<<"����0�������˵�������1������ӣ��밴�س����������룩��";
		int _selection=0;
		cin>>_selection;
		if(_selection==0)
		{
			break;
		} 
		else if(_selection==1)
		{
			continue;
		}
	}	
	return ;
}

void changeword(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		char input_word[50];
		char input_word_class[10];
		char input_word_meaning[100];
		char input_word_note[50];
		int cnt=0;
		int temp=0;
		cout<<endl<<"��������Ҫ�޸ĵĵ��ʣ����س����������룩��"; 
		cin>>input_word;
		cout<<endl<<"������õ��ʵĴ��ԣ����س����������룩��";
		cin>>input_word_class;
		
		for(int i=0;i<n;i++)
		{
			if(strcmp(wordlist[i].word,input_word)==0&&strcmp(wordlist[i].word_class,input_word_class)==0)
			{
				cnt++;
				temp=i;
			}
		}
		
		if(cnt==0)
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ�������ĵ��ʡ�\n";	
	    }
	    else
		{
			while(1)
			{
				system("cls");
				int sel=0;	
				cout<<endl<<"��Ҫ�޸ĵĵ��ʣ�\n";
				cout<<endl;
				cout<<setw(20)<<"����"<<setw(10)<<"����"<<setw(31)<<"������˼"<<"�ʼ�"<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<setw(20)<<wordlist[temp].word<<setw(10)<<wordlist[temp].word_class<<setw(30)<<wordlist[temp].word_meaning<<wordlist[temp].word_note<<endl;
				cout<<endl;
				cout<<endl;
				cout<<"------------\n"; 
				cout<<"    �޸�    \n";
				cout<<"------------\n";
				cout<<" 1.����ƴд \n";
				cout<<" 2.���ʴ��� \n";
				cout<<" 3.������˼ \n";
				cout<<" 4.���ʱʼ� \n";
				cout<<" 5.�޸���� \n"; 
				cout<<"------------\n";
				cout<<"������Ҫ�޸ĵ�ѡ�1-5����" ;
				cin>>sel;
				
				switch(sel)
				{
					case 1: cout<<endl<<"�������޸ĺ�ĵ���ƴд��";
					        cin>>input_word;
					        strcpy(wordlist[temp].word,input_word);
					        cout<<"ƴд�޸ĳɹ���\n"; 
					        Sleep(3000); 
					        break;
					case 2: cout<<endl<<"�������޸ĺ�Ĵ��ԣ�";
							cin>>input_word_class;
							strcpy(wordlist[temp].word_class,input_word_class);
							cout<<"�����޸ĳɹ���\n"; 
							Sleep(3000); 
							break;
					case 3: cout<<endl<<"�������޸ĺ��������˼��";
					        cin>>input_word_meaning;
							strcpy(wordlist[temp].word_meaning,input_word_meaning);
							cout<<"������˼�޸ĳɹ���\n"; 
							Sleep(3000); 
							break;
					case 4: getchar();
							cout<<endl<<"�������޸ĺ�ıʼǣ�";
					        cin.getline(input_word_note,50);
							strcpy(wordlist[temp].word_note," ");
							strcat(wordlist[temp].word_note,input_word_note);
							cout<<"�ʼ��޸ĳɹ���\n"; 
							Sleep(3000); 
							break;
					case 5: break;
				}
			
				if(sel==5)
				{
					break;
				}
			}	 
			cout<<endl<<"�õ�����Ϣ�޸ĳɹ���\n"; 	
		}
	  	
		cout<<endl<<"����0�������˵�������1�����޸��������ʣ��밴�س����������룩��";
		int _selection;
		cin>>_selection;
		if(_selection==0)
		{
			break;	
	    }
	    else if(_selection==1)
	    {
	    	continue;
		}
	}	
}

void deleteword(struct Word wordlist[],int &n)
{
	
	while(1)
	{
		system("cls");
		char input_word[50];
		char input_word_class[10];
		int cnt=0;
		int temp=0;
		cout<<endl<<"��������Ҫɾ���ĵ��ʣ����س����������룩��"; 
		cin>>input_word;
		cout<<endl<<"������õ��ʵĴ��ԣ����س����������룩��";
		cin>>input_word_class;
		
		for(int i=0;i<n;i++)
		{
			if(strcmp(wordlist[i].word,input_word)==0&&strcmp(wordlist[i].word_class,input_word_class)==0)
			{
				cnt++;
				temp=i;
			}
		}
		
		if(cnt==0)
		{
			cout<<endl<<"�ܱ�Ǹû���ҵ�������ĵ��ʡ�\n";
		}
		else
		{
			for(int j=temp;j<=n-2;j++)
			{
				wordlist[j]=wordlist[j+1];
			}
			n--;
			cout<<endl<<"���ҵ�������ĵ��ʣ�ɾ���ɹ���\n"; 
			cout<<endl<<"�ʿ��л���"<<n<<"�����ʡ�\n"; 
		}
		
		cout<<endl<<"����0�������˵�������1����ɾ�����밴�س����������룩��";
		int _selection;
		cin>>_selection;
		if(_selection==0)
		{
			break;	
	    }
	    else if(_selection==1)
	    {
	    	continue;
		}	
	} 	
}


void Test(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		int sel=0;
		cout<<endl;
		cout<<"---------------------"<<endl;
		cout<<"         ����        "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"    1.����Ӣ����     "<<endl;
		cout<<"    2.Ӣ���в���     "<<endl;
		cout<<"    3.�˳�����       "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"���������ѡ��1-3����";
		cin>>sel;
		getchar(); 
		switch(sel)
		{
			case 1: test_CtoE(wordlist,n);
					break;
			case 2: test_EtoC(wordlist,n);
					break;
			case 3: break;
	    }
	    if(sel==3)
	    {
	    	break;
		}
	}
	return ;
}

void test_CtoE(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		int cnt=0;
		int wrongans[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; 
		char input[50];
		cout<<endl<<"����ݸ�����������˼������д����Ӧ��Ӣ�ĵ��ʣ���ʮ��,ÿ��ʮ�֣���\n";
	
		start=clock(); 
		srand(time(NULL));
		for(int i=0;i<10;i++)
		{
			int rad=rand()%n;//����0-n-1�������
			cout<<endl<<"��"<<i+1<<"�⣺ " <<wordlist[rad].word_meaning<<" "<<wordlist[rad].word_class<<endl;
			cout<<"��������Ĵ𰸣�";
			cin>>input;
			if(strcmp(wordlist[rad].word,input)==0)
			{
				cnt++;
				cout<<"��ϲ�㣬����ˣ�\n"; 
			}
			else
			{
				wrongans[i]=rad;
				cout<<"���ź�������ˣ�\n";
			}
		} 
		end=clock();
		
		cout<<endl; 
		switch(cnt)
		{
			case 10: 
			case  9: cout<<"̫�����ˣ�";
					 break;
			case  8: 
			case  7: cout<<"������Ӵ��";
			 		 break;
			case  6: 
			case  5:
			case  4:
			case  3:
			case  2:
			case  1:
			case  0: cout<<"Ҫ��������"; 
		} 
		cout<<"�㱾�β�����ʱ"<<double(end-start)/CLOCKS_PER_SEC<<"�룬��ȷ��" <<cnt*10<<"%��"<<endl;
		if(cnt!=10)
		{
			cout<<"\n����Ϊ��ȷ�𰸣�"<<endl;
			for(int i=0;i<10;i++)
			{
				if(wrongans[i]!=-1)
				{
					cout<<endl<<"��"<<i+1<<"�����ȷ��Ϊ: "<<wordlist[wrongans[i]].word<<endl;
				}
			}
		}
		
		int _selection=0;
		cout<<endl<<"����0���ز��Բ˵�������1�������ԣ��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else if(_selection==1) 
		{
			continue;
		}
	} 
	return ;
}

void test_EtoC(struct Word wordlist[],int n)
{
	while(1)
	{
		system("cls");
		srand(time(0));
		int cnt=0;
		int wrongans[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; 
		cout<<endl<<"����ݸ�����Ӣ�ĵ��ʼ�����ѡ����Ӧ��������˼����ʮ��,ÿ��ʮ�֣���\n";
		
		start=clock();
		for(int k=0;k<10;k++)
		{
			char content_word[4][50];
			char content_class[4][10];
			char content_meaning[4][50];
			int rad[4];
			for(int i=0;i<4;i++)//��������ĸ����ʵ��±�,���ظ� 
			{
				rad[i]=rand()%n;
				int flag=1;
				while(1)
				{
					for(int j=0;j<i;j++)
					{
						if(rad[j]==rad[i])
						{
							flag=0;
							break;
						}
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
			}
			
			for(int i=0;i<4;i++)
			{
				strcpy(content_word[i],wordlist[rad[i]].word);
				strcpy(content_class[i],wordlist[rad[i]].word_class);
				strcpy(content_meaning[i],wordlist[rad[i]].word_meaning);
			}
			
			int right_ans=rand()%4;//���������ȷ��; 
			char ans;
			cout<<endl<<"��"<<k+1<<"�⣺ "<<content_word[right_ans]<<"  "<<content_class[right_ans]<<endl;
			cout<<"A."<<content_meaning[0]<<"\nB."<<content_meaning[1]<<"\nC."<<content_meaning[2]<<"\nD."<<content_meaning[3]<<endl;
			cout<<"���������ѡ��";
			cin>>ans;
			if(ans-'a'==right_ans||ans-'A'==right_ans)
			{
				cout<<"��ϲ�㣬�������\n"; 
				cnt++;
			}
			else
			{
				cout<<"���ź�������ˡ�\n"; 
				wrongans[k]=right_ans;
			}
			
		} 
		end=clock();
		
		cout<<endl; 
		switch(cnt)
		{
			case 10: 
			case  9: cout<<"̫�����ˣ�";
					 break;
			case  8: 
			case  7: cout<<"������Ӵ��";
			 		 break;
			case  6: 
			case  5:
			case  4:
			case  3:
			case  2:
			case  1:
			case  0: cout<<"Ҫ��������"; 
		} 
		cout<<"�㱾�β�����ʱ"<<double(end-start)/CLOCKS_PER_SEC<<"�룬��ȷ��" <<cnt*10<<"%��"<<endl;
		if(cnt!=10)
		{
			cout<<"\n����Ϊ��ȷ�𰸣�"<<endl;
			for(int i=0;i<10;i++)
			{
				if(wrongans[i]!=-1)
				{
					cout<<endl<<"��"<<i+1<<"�����ȷ��Ϊ: "<<(char)(wrongans[i]+'A')<<endl;
				}
			}
		}
		int _selection=0;
		cout<<endl<<"����0���ز��Բ˵�������1�������ԣ��밴�س����������룩��";
		cin>>_selection;
		if(_selection==0)
		{
			break;
		}
		else if(_selection==1) 
		{
			continue;
		}
	}
	return ;	
}

void sort(struct Word wordlist[],int n)
{
	struct Word temp;
	//ð�������㷨������n-1�αȽ� 
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1-i;j++)
		{
			if(strcmp(wordlist[j].word,wordlist[j+1].word)>0)
			{
				temp=wordlist[j];
				wordlist[j]=wordlist[j+1];
				wordlist[j+1]=temp;
			}	
		}
	}
	return ;
}
 
