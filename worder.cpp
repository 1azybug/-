#include<bits/stdc++.h>
using namespace std;
const string K[]={"__","int","void","break","float","while","do","struct","const","case","for","return","if","default","else","assign","var","declare"};
const string P[]={" ","-","/","(",")","==","<=","<","+","*",">","=",",",";","++","{","}"};
const int knum=17;
const int pnum=16;

//str 转10进制int 
int change(string ch)
{
	int si=ch.size();
	int x=0;
	for(int i=0;i<si;++i)
	x=x*10+ch[i]-48;
	return x; 
}

struct Token{


	string kind;//种属,I为标识符,K为关键字,P为界符,C1为整数常数(可16进制),C2为浮点型常数,CT为字符常数,ST为字符串常数; 
	int pos;//在各种表里的下标 
		
	int used;
	void pt()
	{
		cout<<'('<<kind<<' '<<pos<<')';
	}
	
	Token()
	{
		used=0;//默认标识符没用++ 
	}
};

struct Worder{
	
	//默认参数
	int ignore_tips;//忽略提示 
	int detail;//显示错误的详细信息 

	vector<string> I;
	vector<int> C1;
	vector<string>C2;
	vector<char> CT;
	vector<string>ST; 
	vector<Token>words;
	
	//缓冲区 
	string buf;
	int be;
	
	
	
	int getbuf()
	{
		string tmp;
		if(!(cin>>tmp))return 0;//读入失败 
		getline(cin,buf);
		buf=tmp+buf; 
		be=0;
		return 1;//读入成功;	
	} 
	
	Worder()
	{
		ignore_tips=1;//默认忽略tip 
//		ignore_tips=0;//默认显示tip 
		I.clear();
		C1.clear();
		C2.clear();
		CT.clear();
		ST.clear();
		words.clear();
		I.push_back("/0"); 
		C1.push_back(0); 
		C2.push_back("/0"); 
		CT.push_back(0); 
		ST.push_back("/0"); 
		
		buf="";
		be=0;
	}
	
	//可以把插入单独做一个函数,如果有返回位置,没有则插入后返回位置
	
	//插入C1
	int insC1(int x)
	{
		for(int i=1;i<C1.size();++i)
		{
			if(C1[i]==x)
			{
				return i;
			}
		}
		
		C1.push_back(x);
		return C1.size()-1;
	} 

	//插入C2
	int insC2(string x)
	{
		for(int i=1;i<C2.size();++i)
		{
			if(C2[i]==x)
			{
				return i;
			}
		}
		
		C2.push_back(x);
		return C2.size()-1;
	}
	 	
	//识别界符 
	int issym()
	{
		Token res;
		res.kind="P";
		
		//贪婪匹配,++ 要在+的前面 
		//界符匹配按照从左向右贪心匹配最长界符的策略 指:a+++++a 为 a++ ++ + a (离谱) 
		if(buf.substr(be,2)=="++")
		{
//			//++左右都为标识符则报错 
//			if((be+2<buf.size()&&isalpha(buf[be+2]))&&(words.size()>=1&&words.back().kind=="I"))
//			{
//				cout<<"!! word error: <++> left and right is [I]  !!\n ";
//				be++;
//				//错误处理:忽略0x和后面的字符 直到 读到界符和空格为止 	 
//				return 2;//虽然错误但仍可继续。 
//			}
//			
//			//但是++的左或右应为标识符 
//			if((be+2<buf.size()&&isalpha(buf[be+2])))
//			{
//				
//				res.pos=14;
//				words.push_back(res);
//				be+=2;
//				isname();
//				words.back().used=1;
//				return 1;//识别成功			
//			}
//
//			if((words.size()>=1&&words.back().kind=="I"&&words.back().used==0))
//			{
//				words.back().used=1;
//				res.pos=14;
//				words.push_back(res);
//				be+=2;
//				return 1;//识别成功			
//			}
			
			res.pos=14;
			words.push_back(res);
			be+=2;
			return 1;//识别成功					
			
		} 
		
		for(int i=0;i<=pnum;++i) 
		{
			if(buf.substr(be,P[i].size())==P[i])
			{
				res.pos=i;
				
				
				if(i)//即不是读到空格 
				words.push_back(res);
				
				be+=P[i].size();
				return 1;//识别成功	
			}
		}
		
		if(!ignore_tips)cout<<"\n**tip: isn't symbol!**\n";
		return 0;
	}
	
	//识别16进制int
	int is16()
	{
		//不用管负数,将- 和 正常数  分别作为单词 ,-为一目符 
		/*
		int f=0;
		if(buf[be]=='-'&&be+1<buf.size())
		{
			f=1;
			be++;
		}
		*/
		if((buf.substr(be,2)!="0x"))
		{
			if(!ignore_tips)cout<<"\n**tip: isn't 16int!**\n";
			return 0;
		}
		
		be+=2;
		if(be>=buf.size())
		{
//			cout<<"!! word error: after 0x isn't [0-9a-fA-F]  !!\n ";
//			//错误处理:忽略0x和后面的字符 直到 读到界符和空格为止 	 
//			return 2;//虽然错误但仍可继续。 
        
            cout<<"false";
            exit(0);
		}
		if(!(('0'<=buf[be]&&buf[be]<='9')||('a'<=buf[be]&&buf[be]<='f')||('A'<=buf[be]&&buf[be]<='F')))
		{
            cout<<"false";
            exit(0);
		}
		 
		int res=0;		
		//这里允许有前导0 && 不区分大小写 
		while(be<buf.size()&&(('0'<=buf[be]&&buf[be]<='9')||('a'<=buf[be]&&buf[be]<='f')||('A'<=buf[be]&&buf[be]<='F')))
		{
			if('0'<=buf[be]&&buf[be]<='9')
			res=res*16+buf[be]-'0';
			
			if(('a'<=buf[be]&&buf[be]<='f'))
			res=res*16+buf[be]-'a'+10;

			if(('A'<=buf[be]&&buf[be]<='F'))
			res=res*16+buf[be]-'A'+10;
			
			be++;
		}
 		
 		
// 		//不管有没有相同的常数,直接扩展 
// 		C1.push_back(res);
//		Token tmp;
//		tmp.kind="C1";
//		tmp.pos=C1.size()-1;
//		words.push_back(tmp);
//		return 1;//识别成功; 允许后面接其他字母 ,后面出错属于语法分析的范畴 


		Token tmp;
		tmp.kind="C1";
		//考虑可能有相同的常数
		for(int i=1;i<C1.size();++i)
		{
			if(C1[i]==res)
			{
				tmp.pos=i;
				words.push_back(tmp);
				return 1;
			}	
		}
		
 		//扩展 
 		C1.push_back(res);
		tmp.pos=C1.size()-1;
		words.push_back(tmp);
		return 1;//识别成功; 允许后面接其他字母 ,后面出错属于语法分析的范畴  
	}
	
	//识别字符
	int ischar()
	{
		if(buf[be]!='\'')
		{
			if(!ignore_tips)cout<<"\n**tip: isn't char!**\n";
			return 0;			
		}
		
		int ed=be+1;
		while(ed<buf.size()&&buf[ed]!='\'')
		ed++;
		
		if(ed>=buf.size())
		{
            cout<<"false";
            exit(0);			
		}
		
		if(ed==be+1)
		{
            cout<<"false";
            exit(0);			
		}
		
		if(ed>be+2)
		{
            cout<<"false";
            exit(0);
		}
		
//		//不管有没有相同的常数,直接扩展
//		Token tmp;
//		tmp.kind="CT";
//		CT.push_back(buf[be+1]);
//		tmp.pos=CT.size()-1;
//		words.push_back(tmp);
//		be+=3;
//		return 1;

		Token tmp;
		tmp.kind="CT";
		//考虑有相同的常数
		
		for(int i=1;i<CT.size();++i)
		{
			if(CT[i]==buf[be+1])
			{
				tmp.pos=i;
				words.push_back(tmp); 
				be+=3;
				return 1;	
			}	
		} 
		
		
		CT.push_back(buf[be+1]);
		tmp.pos=CT.size()-1;
		words.push_back(tmp);
		be+=3;
		return 1;
	} 
	
	//识别字符串
	int isstr()
	{
		if(buf[be]!='\"')
		{
			if(!ignore_tips)cout<<"\n**tip: isn't str!**\n";
			return 0;			
		}
		
		int ed=be+1;
		while(ed<buf.size()&&buf[ed]!='\"')
		ed++;
		
		if(ed>=buf.size())
		{
            cout<<"false";
            exit(0); 			
		}
		
		
//		//不管有没有相同的常数,直接扩展
//		//非贪婪匹配		
//		Token tmp;
//		tmp.kind="ST";
//		ST.push_back(buf.substr(be+1,ed-be-1));
//		tmp.pos=ST.size()-1;
//		words.push_back(tmp);
//		be=ed+1;
//		return 1;

		//考虑有相同的常数
		//非贪婪匹配		
		Token tmp;
		tmp.kind="ST";
		
		string slice=buf.substr(be+1,ed-be-1);
		be=ed+1;
		
		for(int i=1;i<ST.size();++i)
		{
			if(ST[i]==slice)
			{
				tmp.pos=i;
				words.push_back(tmp);			
				return 1;				 
			}
		}
		
		//扩展ST 
		ST.push_back(slice);
		tmp.pos=ST.size()-1;
		words.push_back(tmp);
		
		return 1;
	}
	
	//识别标识符 和 关键字
	
	int isname()
	{
		if(!isalpha(buf[be]))
		{
			if(!ignore_tips)cout<<"\n**tip: isn't keyword or identifier!**\n";
			return 0;				
		}
		
		int ed=be+1;
		while(ed<buf.size()&&(isalpha(buf[ed])||(isdigit(buf[ed]))))
		ed++;
		
		//buf[be,ed)
		string 	slice=buf.substr(be,ed-be);
		be=ed;
		
		Token tmp;
		
		//识别是否为关键字 
		tmp.kind="K";		
		for(int i=1;i<=knum;++i)
		{
			if(slice==K[i])
			{
				tmp.pos=i;
				words.push_back(tmp);
				return 1;
			}
		}
		
		//识别标识符 
		tmp.kind="I";
		//查找是否在表中 
		int si=I.size();
		for(int i=1;i<si;++i) 
		{
			//zai
			if(slice==I[i])
			{
				tmp.pos=i;
				words.push_back(tmp);
				return 1;
			}
		}
		
		//扩展I表
		I.push_back(slice);
		tmp.pos=I.size()-1;
		words.push_back(tmp);
		return 1; 
		
 	}
	 
	 
	//识别10进制int 和float 	,允许前导0 
	int isnum()
	{
		if(!isdigit(buf[be]))
		{
			if(!ignore_tips)cout<<"\n**tip: isn't number!**\n";
			return 0;			
		}
		
		int ed=be+1;
		while(ed<buf.size()&&isdigit(buf[ed]))
		{
			ed++;
		}
		
		//e不区分大小写 
		if(ed>=buf.size()||(buf[ed]!='.'&&buf[ed]!='e'&&buf[ed]!='E'))
		{
			//是10进制int
			string slice=buf.substr(be,ed-be);
			int x=change(slice);
			Token tmp;
			tmp.kind="C1";
//			C1.push_back(x);
//			tmp.pos=C1.size()-1;
			tmp.pos=insC1(x);//
			words.push_back(tmp);
			be=ed;
			return 1;
		}
		
		if(buf[ed]=='.')
		{
			ed++;
			//类似10. 可看作10.0浮点数 ,但这里选择报错 
			if(ed>=buf.size())
			{
                cout<<"false";
                exit(0); 				
			}
			
			if(!isdigit(buf[ed]))
			{
                cout<<"false";
                exit(0);			
			}
			
			while(ed<buf.size()&&isdigit(buf[ed]))
			{
				ed++;
			}
			 
		}
		
		if(buf[ed]=='e'||buf[ed]=='E')
		{
			if(ed+1<buf.size())
			{
				if(buf[ed+1]=='+'||buf[ed+1]=='-')ed++;
			}
			
			ed++;
			if(ed>=buf.size())
			{
                cout<<"false";
                exit(0); 	 				
			}
			
			if(!isdigit(buf[ed]))
			{
                cout<<"false";
                exit(0); 				
			}
			
			while(ed<buf.size()&&isdigit(buf[ed]))
			{
				ed++;
			}			
		}
//		//不管有没有相同的常数,直接扩展
//		Token tmp;
//		tmp.kind="C2";
//		C2.push_back(buf.substr(be,ed-be));
//		be=ed;
//		tmp.pos=C2.size()-1;
//		words.push_back(tmp);
//		return 1;//识别成功; 允许后面接其他字母 ,后面出错属于语法分析的范畴
		
		
		Token tmp;
		tmp.kind="C2";
		tmp.pos=insC2(buf.substr(be,ed-be));
		words.push_back(tmp);
		be=ed;
		return 1;//识别成功; 允许后面接其他字母 ,后面出错属于语法分析的范畴 		 
		
	}
	
	int run()
	{
		while(1)
		{
			if(be>=buf.size())
			{
				if(!getbuf())
				{
					if(!ignore_tips)cout<<"\n**tip:nfile words was read all**\n";
					return 1;
				}
			}
			
			if(issym())continue;
			if(is16())continue;
			if(ischar())continue;
			if(isstr())continue;
			if(isname())continue;
			if(isnum())continue;
			
            cout<<"false";
            exit(0); 	
						
		}
	
	}
	
	Token getword()
	{
		if(be>=buf.size())
		{
			if(!getbuf())
			{
				if(!ignore_tips)cout<<"\n**tip:nfile words was read all**\n";
				Token tmp;
				tmp.kind="Finish";
				tmp.pos=0;
				return tmp;
			}
		}
		
		if(issym())
		{
			return words.back();	
		}
		if(is16())
		{
			return words.back();	
		}		
		if(ischar())
		{
			return words.back();	
		}
		if(isstr())
		{
			return words.back();	
		}
		if(isname())
		{
			return words.back();	
		}
		if(isnum())
		{
			return words.back();	
		}
		
		cout<<"!! word error: invalid char:<"<<buf[be]<<"> !!\n "; 
		be++;//虽然错误但仍可继续。			
	} 	
	
	
	void pt()//输出Token序列 
	{
		cout<<"Token :";
		for(int i=0;i<words.size();++i)
		{
			Token tmp=words[i];
			tmp.pt();
		}
		cout<<endl;
		
		cout<<"I :";
		for(int i=1;i<I.size();++i)
		{
			if(i<I.size()-1)cout<<I[i]<<' ';
			else cout<<I[i];		
		}	
		cout<<endl;	
		
		cout<<"C1 :";
		for(int i=1;i<C1.size();++i)
		{
			if(i<C1.size()-1)cout<<C1[i]<<' ';
			else cout<<C1[i];
		}
		cout<<endl;

		cout<<"C2 :";
		for(int i=1;i<C2.size();++i)
		{
			if(i<C2.size()-1)cout<<C2[i]<<' ';
			else cout<<C2[i];
		}
		cout<<endl;
		
		cout<<"CT :";
		for(int i=1;i<CT.size();++i)
		{
			if(i<CT.size()-1)cout<<CT[i]<<' ';
			else cout<<CT[i];
		}		
		cout<<endl;

		cout<<"ST :";
		for(int i=1;i<ST.size();++i)
		{
			if(i<ST.size()-1)cout<<ST[i]<<' ';
			else cout<<ST[i];
		}		
		cout<<endl;
	}

};

//以上是词法分析器Worder,调用 方法 getword()会返回下一个单词的token ,token的kind=="Finish"没有下一个单词了 
//-----------------------------------------------------------------------------------------------------------------

struct  SYNB
{
	string kname;			//名字 
	int ktype;			//类型 
	string kcat;			//种类 
	int isact;				//活跃信息，0不活跃；1活跃 
	int addr;				//指向相关信息 
};
vector<SYNB> synbl;//符号表/主表 

struct VAL
{
	int be;//开始 
	int ed;//结束 
	string kname;//名字 
};
vector<VAL> vall;//活动记录 

struct QT
{
	string oper;			//算符 
	string object1;			//对象1 
	string object2;			//对象2 
	string ans;				//结果 
};
vector<QT> qtl;				//四元式表 

struct E
{
	string kname;
	int ed;
};

struct F
{
	string kname;
	int ed;
};

struct T
{
	string kname;
	int ed;
};

struct TYPE//类型
{
	string ktval;			 
	
	int kainf;			//数组表 
	int krinf;			//结构表 
}; 
vector<TYPE> typel;

struct AINF//数组 
{
	int kbegin;
	int kend;
	int ktype;
	
	int size;
};
vector<AINF> ainfl;

struct RINF//结构 
{
	string kname;
	int kbegin;
	string kcat;
};
vector<RINF> rinfl;

struct PFINF//函数 
{
	string klevel;
	int numvariate;
	int kpara;
};
vector<PFINF> pfinfl;

struct PARA//参数
{
	string kname;
	int ktype;
	string kcat;
	int addr;
};
vector<PARA> paral;

struct CONS//常量 
{
	int kcons;
};
vector<CONS> consl;

struct LEN//长度 
{
	int klen;
};
vector<LEN> lenl;

int tnum=0;
string newt()		//返回一个新的临时变量 
{
	int i;
	tnum++;i=tnum;
	char a;
	string x="t",tmp="";
	while(1)
	{
		a=tnum%10+'0';
		tmp+=a;
		i=i/10;
		if(i==0){x+=tmp;return x;}
	}
}


int main()
{
	Worder ws;
	ws.run();
	ws.pt();
	
}

