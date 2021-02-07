
#include "word_remember.h"



void rememberword(struct Word wordlist[],int n)
{
	while(1)
	{
		int cnt=0;//用来记录内存中的生词数
		struct Word unknown[1000];
		loadfile_bdc(unknown,cnt);
		int selection=0;
	 
		system("cls");
		cout<<"-------------------"<<endl;
		cout<<"    背单词模式     "<<endl;
		cout<<"-------------------"<<endl;
		cout<<"    1.复习生词     "<<endl;
		cout<<"    2.顺序记忆     "<<endl;
		cout<<"    3.乱序记忆     "<<endl;
		cout<<"    4.退出         "<<endl;
		cout<<"-------------------"<<endl;
		cout<<"选择（0-4）:";
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
	strcat(temp,"的生词.txt");
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
		cout<<"无法将数据保存到文件 "<<unknownlist_filename<<" !";
		Sleep(3000);
		return 0; 
	}	
	for(int i=0;i<cnt;i++)
	{
		outfile<<unknown[i].word<<" "<<unknown[i].word_class<<" "<<unknown[i].word_meaning<<unknown[i].word_note<<endl;	//getling读入时note前有一个空格了 
	}	
	outfile.close();
	return 1;
}

void deleteword_bdc(struct Word unknown[],int &cnt,int i)//i为要删除的单词的下标
{
	//原数组下标从0到cnt-1;
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

int find_word(struct Word wordlist[],int n,char _word[],char _class[])//找到返回下标，不然返回-1 
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
		cout<<endl<<"您没有可以复习的单词哦！"<<endl; 
	}
	else
	{
		cout<<"\n-------------------------------复习模式-----------------------------------"<<endl;
		cout<<endl<<endl;
		
		start=clock();
		for(int i=0;i<cnt;i++)
		{
			cout<<setw(20)<<"单词"<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
			cout<<"--------------------------------------------------------------------------"<<endl;
			cout<<setw(20)<<unknown[i].word<<setw(10)<<unknown[i].word_class<<setw(30)<<unknown[i].word_meaning<<unknown[i].word_note<<endl;
			cout<<"--------------------------------------------------------------------------"<<endl; 
			cout<<endl<<"A.已掌握     B.保留在生词库      C.退出复习模式"<<endl;
			cout<<"\n请输入你的选择：";
			char sel=0;
			cin>>sel;
			switch(sel)
			{
				case 'a':
				case 'A': cout<<"\n你真聪明！\n\n\n";
					      d[i]=1;
					      break;
				case 'b': 
				case 'B': cout<<"\n继续加油！\n\n\n";
						  break;
				case 'c':
				case 'C': goto out;
			} 
			cout<<endl;
	 	}
	 	end=clock();
	 	getchar();
		cout<<"恭喜您已复习完所有的生词,用时"<<double(end-start)/CLOCKS_PER_SEC<<"秒。";
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
	}//删除已经记住的单词 
	savefile_bdc(unknown,cnt);
	cout<<"\n\n按任意键返回背单词模式菜单...";
	getchar();
	return;
}

void inorder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt)
{ 
	while(1)
	{
		system("cls");
		cout<<"\n-------------------------------顺序记忆模式---------------------------------"<<endl;
		cout<<endl;
		char _word[20];
		char _class[10];
		cout<<"请输入你想要开始的单词（按回车结束输入）：";
		cin>>_word;
		cout<<"请输入该单词的词性（按回车结束输入）：" ;
		cin>>_class;
		int dofind=find_word(wordlist,n,_word,_class);
		if(dofind==-1)
		{
			cout<<endl<<"抱歉没有找到该单词，请按任意键重新输入。\n";
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
				cout<<setw(20)<<"单词"<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<setw(20)<<wordlist[i].word<<setw(10)<<wordlist[i].word_class<<setw(30)<<wordlist[i].word_meaning<<wordlist[i].word_note<<endl;
				cout<<"--------------------------------------------------------------------------"<<endl;
				cout<<endl<<"A.已掌握     B.添加入生词库      C.退出顺序记忆模式"<<endl;
				cout<<"\n请输入你的选择：";
				char sel=0;
				cin>>sel;
				switch(sel)
				{
					case 'a':
					case 'A': cout<<"\n你真聪明！\n\n\n";
						      break;
					case 'b': 
					case 'B': cout<<"\n继续加油！\n\n\n";
							  addword_bdc(unknown,cnt,wordlist[i]);
							  break;
					case 'c':
					case 'C': goto out;
				} 
				cout<<endl;
	 	    }
			end=clock();
			getchar();
			cout<<"恭喜您已背穿词库,用时"<<double(end-start)/CLOCKS_PER_SEC<<"秒。";
			goto out;		
		}
	}
	out:
	savefile_bdc(unknown,cnt);
	cout<<"\n\n按任意键返回背单词模式菜单...";
	getchar();
	return;		
}

void outoforder_mode(struct Word wordlist[],int n,struct Word unknown[],int &cnt)
{
	system("cls");
	srand(time(0));
	cout<<"\n-------------------------------乱序记忆模式---------------------------------"<<endl;
	cout<<endl<<endl;
	while(1)
	{
		int rad=rand()%n;
		cout<<setw(20)<<"单词"<<setw(10)<<"词性"<<setw(31)<<"中文意思"<<"笔记"<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<setw(20)<<wordlist[rad].word<<setw(10)<<wordlist[rad].word_class<<setw(30)<<wordlist[rad].word_meaning<<wordlist[rad].word_note<<endl;
		cout<<"--------------------------------------------------------------------------"<<endl;
		cout<<endl<<"A.已掌握     B.添加入生词库      C.退出顺序记忆模式"<<endl;
		cout<<"\n请输入你的选择：";
		char sel=0;
		cin>>sel;
		getchar();
		switch(sel)
		{
			case 'a':
			case 'A': cout<<"\n你真聪明！\n\n\n";
				      break;
			case 'b': 
			case 'B': cout<<"\n继续加油！\n\n\n";
					  addword_bdc(unknown,cnt,wordlist[rad]);
					  break;
			case 'c':
			case 'C': goto out;
		} 
		cout<<endl;
	}
	out:
	savefile_bdc(unknown,cnt);
	cout<<"\n\n按任意键返回背单词模式菜单...";
	getchar();
	return;		
	
}
