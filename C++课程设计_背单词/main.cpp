#include "head.h"
#include "word_remember.h"
#include "login.h"
 
clock_t start,end;//用来计时的两个变量
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
	int n=0;//用来记录内存中的单词数 
	int selection=0;
	while(1)
	{
		system("cls");
		cout<<"----------------------------------"<<endl;
		cout<<"         背单词小程序             "<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"         1.导入词库               "<<endl; 
		cout<<"         2.显示词库               "<<endl;
		cout<<"         3.单词搜索               "<<endl; 
		cout<<"         4.添加单词笔记           "<<endl;
		cout<<"         5.添加新单词             "<<endl; 
		cout<<"         6.修改单词信息           "<<endl; 
		cout<<"         7.删除单词               "<<endl; 
		cout<<"         8.单词测试               "<<endl; 
		cout<<"         9.背单词                 "<<endl;
		cout<<"         0.退出                   "<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"选择（0-9）:";
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
	cout<<"请输入单词文件的位置：";
	cin>>wordlist_filename; 
	getchar();
	infile.open(wordlist_filename,ios::in);
	if(!infile)
	{
		cout<<endl<<"无数据文件 "<<wordlist_filename<<" !";
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
	cout<<endl<<"成功导入"<<n<<"个单词，用时";
	cout<<double(end-start)/CLOCKS_PER_SEC;
	cout<<"秒。\n\n按任意键回到主菜单......\n";
	getchar();
	return n;
}

int save_file(struct Word wordlist[],int n)
{
	ofstream outfile;
	outfile.open(wordlist_filename,ios::out);
	if(!outfile)
	{
		cout<<"无法将数据保存到文件 "<<wordlist_filename<<" !";
		Sleep(3000);
		return 0; 
	}	
	for(int i=0;i<n;i++)
	{
		outfile<<wordlist[i].word<<" "<<wordlist[i].word_class<<" "<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;	//getling读入时note前有一个空格了 
	}	
	outfile.close();
	return 1;
}

void print(struct Word wordlist[],int n)
{
	system("cls");
	if(n==0)
	{
		cout<<endl<<"词库中无单词，请导入词库！\n"; 
	}
	else
	{
		cout.setf(ios::left);
		cout<<endl<<endl; 
		cout<<setw(20)<<"单词"<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		
		start=clock();
		for(int i=0;i<n;i++)
		{
			cout<<setw(20)<<wordlist[i].word<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
		}
		end=clock();
		
		cout<<endl<<"单词信息已显示完毕！\n"; 
		cout<<endl<<"一共显示"<<n<<"个单词，用时" ;
		cout<<double(end-start)/CLOCKS_PER_SEC<<"秒。\n"; 
	}
	cout<<endl<<"按任意键返回主菜单......\n";
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
		cout<<"         搜索        "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"    1.输入英文搜索   "<<endl;
		cout<<"    2.输入中文搜索   "<<endl;
		cout<<"    3.英文精确搜索   "<<endl;
		cout<<"    4.快速搜索       "<<endl; 
		cout<<"    5.退出搜索       "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"请输入你的选择（1-5）：";
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
		int cnt=0;//记录结果个数 
		char object[20];
		cout<<endl<<"请输入你想要查询的单词（区分大小写并按回车结束输入）：";
		cin>>object; 
		
		start=clock();
		for(int i=0;i<n;i++)//查找并输出 
		{
			if(strcmp(object,wordlist[i].word)==0)
			{
				if(cnt==0)
				{
					cout<<endl<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
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
			cout<<endl<<"很抱歉没有找到您要查询的单词。\n";
		}
		else
		{
			cout<<endl<<"以上共"<<cnt<<"条搜索结果，用时";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"秒。\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"输入0返回搜索菜单，输入1继续查找（请按回车键结束输入）：";
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
		int cnt=0;//记录结果个数 
		char object[20];
		cout<<endl<<"请输入你想要查询的单词的中文意思：";
		cin>>object; 
		
		start=clock();
		for(int i=0;i<n;i++)//查找并输出 
		{
			if(strcmp(object,wordlist[i].word_meaning)==0)
			{
				if(cnt==0)
				{
					cout<<endl<<setw(10)<<"词性"<<setw(21)<<"英文单词"<<"笔记"<<endl;
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
			cout<<endl<<"很抱歉没有找到您要查询的单词。\n";
		}
		else
		{
			cout<<endl<<"以上共"<<cnt<<"条搜索结果，用时";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"秒。\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"输入0返回搜索菜单，输入1继续查找（请按回车键结束输入）：";
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
		int cnt=0;//记录结果个数
		char object_word[20];
		char object_word_class[10];
		cout<<endl<<"请输入你想要查询的单词（区分大小写并按回车结束输入）：";
		cin>>object_word;
		cout<<"请输入该单词的词性（小写并按回车键结束输入）：";
		cin>>object_word_class;
		
		start=clock();
		for(int i=0;i<n;i++)
		{
			if(strcmp(object_word,wordlist[i].word)==0&&strcmp(object_word_class,wordlist[i].word_class)==0)
			{
				cout<<endl<<setw(31)<<"中文意思"<<"笔记";
				cout<<endl<<"---------------------------------------";
				cout<<endl<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note;
				cout<<endl; 
				cnt++;
			}
		}
		end=clock();
		
		if(cnt==1)
		{
			cout<<endl<<"本次搜索用时"<<double(end-start)/CLOCKS_PER_SEC<<"秒。\n"; 
		}
		else
		{
			cout<<endl<<"很抱歉没有找到您要查询的单词。\n";
		}
		
		int _selection=0;
		cout<<endl<<"输入0返回搜索菜单，输入1继续查找（请按回车键结束输入）：";
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
		int cnt=0;//记录结果个数 
		char object[20];
		cout<<endl<<"请输入你想要查询的单词（区分大小写并按回车结束输入）：";
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
			cout<<endl<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
			cout<<"---------------------------------------------------"<<endl;
			cout<<setw(10)<<wordlist[center].word_class<<setw(30)<<wordlist[center].word_meaning<<wordlist[center].word_note<<endl;
			cnt++;
		}
		
		if(cnt==0)
		{
			cout<<endl<<"很抱歉没有找到您要查询的单词。\n";
		}
		else
		{
			cout<<endl<<"以上共"<<cnt<<"条搜索结果，用时";
			cout<<double(end-start)/CLOCKS_PER_SEC<<"秒。\n" ;
		} 
		
		int _selection=0;
		cout<<endl<<"输入0返回搜索菜单，输入1继续查找（请按回车键结束输入）：";
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
		int cnt=0;//用来标记有没有找到 
		int temp=0;//用来记录找到的单词的下标 
		char input[50];
		char object_word[20];
		char object_word_class[10];
		cout<<endl<<"请输入你想要添加笔记的单词（区分大小写并按回车结束输入）：";
		cin>>object_word;
		cout<<endl<<"请输入该单词的词性（小写并按回车键结束输入）：";
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
			strcpy(wordlist[temp].word_note," ");//原来是" 暂无" 
			cout<<endl<<"已找到该单词。请输入您要添加的笔记：";
			cin.getline(input,50);
			cout<<endl<<"添加成功！"<<endl; 
			strcat(wordlist[temp].word_note,input);
		}
		else
		{
			cout<<endl<<"很抱歉没有找到您输入的单词。"<<endl; 
		}
		
		cout<<endl<<"输入0返回主菜单，输入1继续添加（请按回车键结束输入）："; 
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
		cout<<endl<<"请输入您要添加的单词（按回车键结束输入）："; 
		cin>>input_word;
		cout<<endl<<"请输入该单词的词性（按回车键结束输入）：";
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
			cout<<endl<<"词库里已经有您要添加的单词了哦！\n"; 
		}
		else
		{
			cout<<endl<<"请输入该单词的中文意思（按回车键结束输入）：";
			cin>>input_word_meaning;
			getchar();
			cout<<endl<<"请输入该单词的笔记（按回车键结束输入）：";
			cin.getline(input_word_note,50);
			strcpy(wordlist[n].word,input_word);
			strcpy(wordlist[n].word_class,input_word_class);
			strcpy(wordlist[n].word_meaning,input_word_meaning);
			strcpy(wordlist[n].word_note," ");
			strcat(wordlist[n].word_note,input_word_note);
			n++;
			cout<<endl<<"添加成功！\n";
		}
		
		cout<<endl<<"输入0返回主菜单，输入1继续添加（请按回车键结束输入）：";
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
		cout<<endl<<"请输入您要修改的单词（按回车键结束输入）："; 
		cin>>input_word;
		cout<<endl<<"请输入该单词的词性（按回车键结束输入）：";
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
			cout<<endl<<"很抱歉没有找到您输入的单词。\n";	
	    }
	    else
		{
			while(1)
			{
				system("cls");
				int sel=0;	
				cout<<endl<<"您要修改的单词：\n";
				cout<<endl;
				cout<<setw(20)<<"单词"<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<setw(20)<<wordlist[temp].word<<setw(10)<<wordlist[temp].word_class<<setw(30)<<wordlist[temp].word_meaning<<wordlist[temp].word_note<<endl;
				cout<<endl;
				cout<<endl;
				cout<<"------------\n"; 
				cout<<"    修改    \n";
				cout<<"------------\n";
				cout<<" 1.单词拼写 \n";
				cout<<" 2.单词词性 \n";
				cout<<" 3.单词意思 \n";
				cout<<" 4.单词笔记 \n";
				cout<<" 5.修改完毕 \n"; 
				cout<<"------------\n";
				cout<<"请输入要修改的选项（1-5）：" ;
				cin>>sel;
				
				switch(sel)
				{
					case 1: cout<<endl<<"请输入修改后的单词拼写：";
					        cin>>input_word;
					        strcpy(wordlist[temp].word,input_word);
					        cout<<"拼写修改成功！\n"; 
					        Sleep(3000); 
					        break;
					case 2: cout<<endl<<"请输入修改后的词性：";
							cin>>input_word_class;
							strcpy(wordlist[temp].word_class,input_word_class);
							cout<<"词性修改成功！\n"; 
							Sleep(3000); 
							break;
					case 3: cout<<endl<<"请输入修改后的中文意思：";
					        cin>>input_word_meaning;
							strcpy(wordlist[temp].word_meaning,input_word_meaning);
							cout<<"中文意思修改成功！\n"; 
							Sleep(3000); 
							break;
					case 4: getchar();
							cout<<endl<<"请输入修改后的笔记：";
					        cin.getline(input_word_note,50);
							strcpy(wordlist[temp].word_note," ");
							strcat(wordlist[temp].word_note,input_word_note);
							cout<<"笔记修改成功！\n"; 
							Sleep(3000); 
							break;
					case 5: break;
				}
			
				if(sel==5)
				{
					break;
				}
			}	 
			cout<<endl<<"该单词信息修改成功！\n"; 	
		}
	  	
		cout<<endl<<"输入0返回主菜单，输入1继续修改其它单词（请按回车键结束输入）：";
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
		cout<<endl<<"请输入您要删除的单词（按回车键结束输入）："; 
		cin>>input_word;
		cout<<endl<<"请输入该单词的词性（按回车键结束输入）：";
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
			cout<<endl<<"很抱歉没有找到您输入的单词。\n";
		}
		else
		{
			for(int j=temp;j<=n-2;j++)
			{
				wordlist[j]=wordlist[j+1];
			}
			n--;
			cout<<endl<<"已找到您输入的单词，删除成功！\n"; 
			cout<<endl<<"词库中还有"<<n<<"个单词。\n"; 
		}
		
		cout<<endl<<"输入0返回主菜单，输入1继续删除（请按回车键结束输入）：";
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
		cout<<"         测试        "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"    1.中译英测试     "<<endl;
		cout<<"    2.英译中测试     "<<endl;
		cout<<"    3.退出测试       "<<endl;
		cout<<"---------------------"<<endl;
		cout<<"请输入你的选择（1-3）：";
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
		cout<<endl<<"请根据给出的中文意思及词性写出相应的英文单词（共十题,每题十分）：\n";
	
		start=clock(); 
		srand(time(NULL));
		for(int i=0;i<10;i++)
		{
			int rad=rand()%n;//产生0-n-1的随机数
			cout<<endl<<"第"<<i+1<<"题： " <<wordlist[rad].word_meaning<<" "<<wordlist[rad].word_class<<endl;
			cout<<"请输入你的答案：";
			cin>>input;
			if(strcmp(wordlist[rad].word,input)==0)
			{
				cnt++;
				cout<<"恭喜你，答对了！\n"; 
			}
			else
			{
				wrongans[i]=rad;
				cout<<"很遗憾，答错了！\n";
			}
		} 
		end=clock();
		
		cout<<endl; 
		switch(cnt)
		{
			case 10: 
			case  9: cout<<"太厉害了，";
					 break;
			case  8: 
			case  7: cout<<"还不错哟，";
			 		 break;
			case  6: 
			case  5:
			case  4:
			case  3:
			case  2:
			case  1:
			case  0: cout<<"要加油啦，"; 
		} 
		cout<<"你本次测试用时"<<double(end-start)/CLOCKS_PER_SEC<<"秒，正确率" <<cnt*10<<"%。"<<endl;
		if(cnt!=10)
		{
			cout<<"\n以下为正确答案："<<endl;
			for(int i=0;i<10;i++)
			{
				if(wrongans[i]!=-1)
				{
					cout<<endl<<"第"<<i+1<<"题的正确答案为: "<<wordlist[wrongans[i]].word<<endl;
				}
			}
		}
		
		int _selection=0;
		cout<<endl<<"输入0返回测试菜单，输入1继续测试（请按回车键结束输入）：";
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
		cout<<endl<<"请根据给出的英文单词及词性选择相应的中文意思（共十题,每题十分）：\n";
		
		start=clock();
		for(int k=0;k<10;k++)
		{
			char content_word[4][50];
			char content_class[4][10];
			char content_meaning[4][50];
			int rad[4];
			for(int i=0;i<4;i++)//随机产生四个单词的下标,不重复 
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
			
			int right_ans=rand()%4;//随机产生正确答案; 
			char ans;
			cout<<endl<<"第"<<k+1<<"题： "<<content_word[right_ans]<<"  "<<content_class[right_ans]<<endl;
			cout<<"A."<<content_meaning[0]<<"\nB."<<content_meaning[1]<<"\nC."<<content_meaning[2]<<"\nD."<<content_meaning[3]<<endl;
			cout<<"请输入你的选择：";
			cin>>ans;
			if(ans-'a'==right_ans||ans-'A'==right_ans)
			{
				cout<<"恭喜你，答对啦！\n"; 
				cnt++;
			}
			else
			{
				cout<<"很遗憾，答错了。\n"; 
				wrongans[k]=right_ans;
			}
			
		} 
		end=clock();
		
		cout<<endl; 
		switch(cnt)
		{
			case 10: 
			case  9: cout<<"太厉害了，";
					 break;
			case  8: 
			case  7: cout<<"还不错哟，";
			 		 break;
			case  6: 
			case  5:
			case  4:
			case  3:
			case  2:
			case  1:
			case  0: cout<<"要加油啦，"; 
		} 
		cout<<"你本次测试用时"<<double(end-start)/CLOCKS_PER_SEC<<"秒，正确率" <<cnt*10<<"%。"<<endl;
		if(cnt!=10)
		{
			cout<<"\n以下为正确答案："<<endl;
			for(int i=0;i<10;i++)
			{
				if(wrongans[i]!=-1)
				{
					cout<<endl<<"第"<<i+1<<"题的正确答案为: "<<(char)(wrongans[i]+'A')<<endl;
				}
			}
		}
		int _selection=0;
		cout<<endl<<"输入0返回测试菜单，输入1继续测试（请按回车键结束输入）：";
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
	//冒泡排序算法；进行n-1次比较 
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
 
