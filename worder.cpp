#include<bits/stdc++.h>
using namespace std;
const string K[]={"__","int","void","break","float","while","do","struct","const","case","for","return","if","default","else","assign","var","declare"};
const string P[]={" ","-","/","(",")","==","<=","<","+","*",">","=",",",";","++","{","}"};
const int knum=17;
const int pnum=16;

//str ת10����int 
int change(string ch)
{
	int si=ch.size();
	int x=0;
	for(int i=0;i<si;++i)
	x=x*10+ch[i]-48;
	return x; 
}

struct Token{


	string kind;//����,IΪ��ʶ��,KΪ�ؼ���,PΪ���,C1Ϊ��������(��16����),C2Ϊ�����ͳ���,CTΪ�ַ�����,STΪ�ַ�������; 
	int pos;//�ڸ��ֱ�����±� 
		
	int used;
	void pt()
	{
		cout<<'('<<kind<<' '<<pos<<')';
	}
	
	Token()
	{
		used=0;//Ĭ�ϱ�ʶ��û��++ 
	}
};

struct Worder{
	
	//Ĭ�ϲ���
	int ignore_tips;//������ʾ 
	int detail;//��ʾ�������ϸ��Ϣ 

	vector<string> I;
	vector<int> C1;
	vector<string>C2;
	vector<char> CT;
	vector<string>ST; 
	vector<Token>words;
	
	//������ 
	string buf;
	int be;
	
	
	
	int getbuf()
	{
		string tmp;
		if(!(cin>>tmp))return 0;//����ʧ�� 
		getline(cin,buf);
		buf=tmp+buf; 
		be=0;
		return 1;//����ɹ�;	
	} 
	
	Worder()
	{
		ignore_tips=1;//Ĭ�Ϻ���tip 
//		ignore_tips=0;//Ĭ����ʾtip 
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
	
	//���԰Ѳ��뵥����һ������,����з���λ��,û�������󷵻�λ��
	
	//����C1
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

	//����C2
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
	 	
	//ʶ���� 
	int issym()
	{
		Token res;
		res.kind="P";
		
		//̰��ƥ��,++ Ҫ��+��ǰ�� 
		//���ƥ�䰴�մ�������̰��ƥ�������Ĳ��� ָ:a+++++a Ϊ a++ ++ + a (����) 
		if(buf.substr(be,2)=="++")
		{
//			//++���Ҷ�Ϊ��ʶ���򱨴� 
//			if((be+2<buf.size()&&isalpha(buf[be+2]))&&(words.size()>=1&&words.back().kind=="I"))
//			{
//				cout<<"!! word error: <++> left and right is [I]  !!\n ";
//				be++;
//				//������:����0x�ͺ�����ַ� ֱ�� ��������Ϳո�Ϊֹ 	 
//				return 2;//��Ȼ�����Կɼ����� 
//			}
//			
//			//����++�������ӦΪ��ʶ�� 
//			if((be+2<buf.size()&&isalpha(buf[be+2])))
//			{
//				
//				res.pos=14;
//				words.push_back(res);
//				be+=2;
//				isname();
//				words.back().used=1;
//				return 1;//ʶ��ɹ�			
//			}
//
//			if((words.size()>=1&&words.back().kind=="I"&&words.back().used==0))
//			{
//				words.back().used=1;
//				res.pos=14;
//				words.push_back(res);
//				be+=2;
//				return 1;//ʶ��ɹ�			
//			}
			
			res.pos=14;
			words.push_back(res);
			be+=2;
			return 1;//ʶ��ɹ�					
			
		} 
		
		for(int i=0;i<=pnum;++i) 
		{
			if(buf.substr(be,P[i].size())==P[i])
			{
				res.pos=i;
				
				
				if(i)//�����Ƕ����ո� 
				words.push_back(res);
				
				be+=P[i].size();
				return 1;//ʶ��ɹ�	
			}
		}
		
		if(!ignore_tips)cout<<"\n**tip: isn't symbol!**\n";
		return 0;
	}
	
	//ʶ��16����int
	int is16()
	{
		//���ùܸ���,��- �� ������  �ֱ���Ϊ���� ,-ΪһĿ�� 
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
//			//������:����0x�ͺ�����ַ� ֱ�� ��������Ϳո�Ϊֹ 	 
//			return 2;//��Ȼ�����Կɼ����� 
        
            cout<<"false";
            exit(0);
		}
		if(!(('0'<=buf[be]&&buf[be]<='9')||('a'<=buf[be]&&buf[be]<='f')||('A'<=buf[be]&&buf[be]<='F')))
		{
            cout<<"false";
            exit(0);
		}
		 
		int res=0;		
		//����������ǰ��0 && �����ִ�Сд 
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
 		
 		
// 		//������û����ͬ�ĳ���,ֱ����չ 
// 		C1.push_back(res);
//		Token tmp;
//		tmp.kind="C1";
//		tmp.pos=C1.size()-1;
//		words.push_back(tmp);
//		return 1;//ʶ��ɹ�; ��������������ĸ ,������������﷨�����ķ��� 


		Token tmp;
		tmp.kind="C1";
		//���ǿ�������ͬ�ĳ���
		for(int i=1;i<C1.size();++i)
		{
			if(C1[i]==res)
			{
				tmp.pos=i;
				words.push_back(tmp);
				return 1;
			}	
		}
		
 		//��չ 
 		C1.push_back(res);
		tmp.pos=C1.size()-1;
		words.push_back(tmp);
		return 1;//ʶ��ɹ�; ��������������ĸ ,������������﷨�����ķ���  
	}
	
	//ʶ���ַ�
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
		
//		//������û����ͬ�ĳ���,ֱ����չ
//		Token tmp;
//		tmp.kind="CT";
//		CT.push_back(buf[be+1]);
//		tmp.pos=CT.size()-1;
//		words.push_back(tmp);
//		be+=3;
//		return 1;

		Token tmp;
		tmp.kind="CT";
		//��������ͬ�ĳ���
		
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
	
	//ʶ���ַ���
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
		
		
//		//������û����ͬ�ĳ���,ֱ����չ
//		//��̰��ƥ��		
//		Token tmp;
//		tmp.kind="ST";
//		ST.push_back(buf.substr(be+1,ed-be-1));
//		tmp.pos=ST.size()-1;
//		words.push_back(tmp);
//		be=ed+1;
//		return 1;

		//��������ͬ�ĳ���
		//��̰��ƥ��		
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
		
		//��չST 
		ST.push_back(slice);
		tmp.pos=ST.size()-1;
		words.push_back(tmp);
		
		return 1;
	}
	
	//ʶ���ʶ�� �� �ؼ���
	
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
		
		//ʶ���Ƿ�Ϊ�ؼ��� 
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
		
		//ʶ���ʶ�� 
		tmp.kind="I";
		//�����Ƿ��ڱ��� 
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
		
		//��չI��
		I.push_back(slice);
		tmp.pos=I.size()-1;
		words.push_back(tmp);
		return 1; 
		
 	}
	 
	 
	//ʶ��10����int ��float 	,����ǰ��0 
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
		
		//e�����ִ�Сд 
		if(ed>=buf.size()||(buf[ed]!='.'&&buf[ed]!='e'&&buf[ed]!='E'))
		{
			//��10����int
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
			//����10. �ɿ���10.0������ ,������ѡ�񱨴� 
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
//		//������û����ͬ�ĳ���,ֱ����չ
//		Token tmp;
//		tmp.kind="C2";
//		C2.push_back(buf.substr(be,ed-be));
//		be=ed;
//		tmp.pos=C2.size()-1;
//		words.push_back(tmp);
//		return 1;//ʶ��ɹ�; ��������������ĸ ,������������﷨�����ķ���
		
		
		Token tmp;
		tmp.kind="C2";
		tmp.pos=insC2(buf.substr(be,ed-be));
		words.push_back(tmp);
		be=ed;
		return 1;//ʶ��ɹ�; ��������������ĸ ,������������﷨�����ķ��� 		 
		
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
		be++;//��Ȼ�����Կɼ�����			
	} 	
	
	
	void pt()//���Token���� 
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

//�����Ǵʷ�������Worder,���� ���� getword()�᷵����һ�����ʵ�token ,token��kind=="Finish"û����һ�������� 
//-----------------------------------------------------------------------------------------------------------------




int main()
{
	Worder ws;
	ws.run();
	ws.pt();
}

