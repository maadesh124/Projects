#include <graphics.h>
#include <iostream>
#include "square.cpp"
#include <sstream>
#include <string>

using namespace std;

class BoardUI
{
	
	public:
	BoardState *b;
	string path;
	
	BoardUI(BoardState *bs,string p)
	{
		b=bs;
		path=p;
	}
	
	string toString(int n)
	{
		stringstream ss;
		ss<<n;
		return ss.str();
	}
	
	void drawCurrentBoardState()
	{
		initwindow(584,584, "My Graphics Window", false, true);
		for(int y=0;y<8;y++)
		for(int x=0;x<8;x++)
		{
			string fp;
			Square* s=b->squares[x][y];
			
			
			//string path="D:\\CPP\\gui\\Images\\Images bmp\\";
			
			
			if(!s->hasPiece())
			fp=path+toString(s->colour)+".bmp";  //********************
			else
			fp=path+toString(s->colour)+toString(s->piece->colour)+toString(s->piece->type)+".bmp";  //********************
			//cout<<fp<<" ("<<x<<","<<y<<")"<<endl;
				
			readimagefile(&fp[0],x*73,(7-y)*73,(x+1)*73,(8-y)*73);
		}
		
	//	getch();
	//	closegraph();
	}
	
	void movePiece(int x1,int y1,int x2,int y2)
	{
		Square* src=b->squares[x1][y1];
		Square* dst=b->squares[x2][y2];
		

	//	cout<<x1<<y1<<endl;
		string dstfp=path+toString(dst->colour)+toString(src->piece->colour)+toString(src->piece->type)+".bmp"; // ****************************
		int x=dst->x;
		int y=dst->y;
		readimagefile(&dstfp[0],x*73,(7-y)*73,(x+1)*73,(8-y)*73);
		
		string srcfp=path+toString(src->colour)+".bmp";            //*****************************************
		x=src->x;
		y=src->y;
		readimagefile(&srcfp[0],x*73,(7-y)*73,(x+1)*73,(8-y)*73);
		
		
	}
	
	
};

string replace(string st,char tar, char rep)
{
	int n=st.size();
	string ans="";
	for(int i=0;i<n;i++)
	{
		if(st[i]=='\\')
		ans=ans+"\\\\";
		else
		ans=ans+st[i];
	}
	return ans;
}

int main() {

	BoardState* b=new BoardState();
	string pa;
	cout<<"Move the extracted folder to Local Disk D or E or some other , Do not keep the folder in Local Disk C.\nEnter path of Folder which contains images, Path should not contain any spaces .\nDo not rename any image file.\n Example :D:\\CPP\\gui\\Images\\ImagesBmp\n Here ImagesBmp contains images."<<endl;
	//string pa="D:\\CPP\\gui\\Images\\ImagesBmp\\";
	cin>>pa;
	replace(pa,'\\','\\\\');
	
	
	if(pa[0]=='C')
	{
	cout<<"Extracted Folder is still In LocalDisk C"<<endl;
	return 0;
	}
	
	pa=pa+"\\";
	cout<<pa<<"\n"<<endl;
	BoardUI* bu=new BoardUI(b,pa);
	bu->drawCurrentBoardState();
	
	cout<<"To move a piece from one square to another, please enter the coordinates of the source square as 'x1y1' and the destination square as 'x2y2'."<<endl;
	cout<<"Keep in mind that positions are indexed starting from the bottom-left corner, with both 'x' and 'y' values starting from 0."<<endl;
	cout<<"For example, if you want to move a piece from square 41 to square 43, you would enter 'src=41' and 'dst=43'.\n\n"<<endl;
	
	int src,dst;
	int i=0,k;
	while(true)
	{
		k=(i%2)+1;
		cout<<"Player "<<k<<"'s chance"<<endl;
		cout<<"src="<<endl;
		cin>>src;
		if(src==-1)
		break;
		cout<<"dst="<<endl;
		cin>>dst;
		
		Square* ssrc=b->squares[src/10][src%10];
		Square* sdst=b->squares[dst/10][dst%10];
		
		if(!ssrc->hasPiece())
		continue;
		
		if(ssrc->piece->colour!=k-1)
		{
			cout<<"Wrong Play"<<endl;
			continue;
		}
		
		if(b->isIllegalMove(ssrc,sdst))
		{
		cout<<"illegal Move"<<endl;
		continue;
		}
		
	
		if(b->isValidMove(ssrc,sdst))
		{
		
	/*	vector<Square*>* v=b->getSquaresInPath(ssrc,sdst);
		if(v!=NULL)
		{
		int n=v->size();
		for(int i=0;i<n;i++)
		cout<<v->at(i)->x<<v->at(i)->y<<endl;
		}
		
		*/
		
		
		
		bu->movePiece(src/10,src%10,dst/10,dst%10);
		bu->b->move(src/10,src%10,dst/10,dst%10);
		//bu->b->printBoardState();
		
	
		
		if(b->isCheckMate(!(k-1),ssrc,sdst))
		{
		cout<<"***********Game Over*************"<<endl;
		cout<<"Player "<<k<<" won the match."<<endl;
		break;
		}
		
		//if(b->isADestination(sdst,!(k-1)))
		//cout<<"IS a destination"<<endl;
		
		
		
		}
		else
		{
		cout<<"Invalid Move"<<endl;
		continue;
		}
		i++;
	}
    
    getch();
    return 0;
}

