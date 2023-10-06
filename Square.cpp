#include <iostream>
#include <vector>


using namespace std;


class Piece
{
	public:
		int type,colour,x,y;
		Piece(int t,int c,int i,int j)
		{
		type=t;
		colour=c;
		x=i;
		y=j;
	    }
		
		bool isInBoard()
	{
		if(x>=0 && x<=7 && y>=0 && y<=7)
		return true;
		return false;
	}		
};



class Square
{
	public:
	int colour;
	int x,y;
	Piece *piece;
	
	Square(int i,int j,Piece* p)
	{
		colour=0;
		x=i;
		y=j;
		piece=p;
		if((x%2==0 && y%2==0) || (x%2==1 && y%2==1))
		colour=1;
	
	}
	
	bool hasPiece()
	{
		if(this->piece==NULL)
		return false;
	
		
		return true;
	}
	
	bool isInBoard()
	{
		if(x>=0 && x<=7 && y>=0 && y<=7)
		return true;
		return false;
	}
	
	int getColour()
	{
		if(!this->isInBoard())
		return -1;
		
		if((x%2 ==0 && y%2==0)||(x%2==1 && y%2==1))
		return 1;
		
		return 0;
		
	}
	
	
};

class BoardState
{
	public:
	Square* squares[8][8];
	Piece* pieces[32];	
	BoardState()
	{
		//initialize white pieces
			squares[0][0]=new Square(0,0,new Piece(1,0,0,0));
			squares[1][0]=new Square(1,0,new Piece(2,0,1,0));
			squares[2][0]=new Square(2,0,new Piece(3,0,2,0));
			squares[3][0]=new Square(3,0,new Piece(5,0,3,0));
			squares[4][0]=new Square(4,0,new Piece(4,0,4,0));
			squares[5][0]=new Square(5,0,new Piece(3,0,5,0));
			squares[6][0]=new Square(6,0,new Piece(2,0,6,0));
			squares[7][0]=new Square(7,0,new Piece(1,0,7,0));
			
			
			
		//initialize black pieces	
			squares[0][7]=new Square(0,7,new Piece(1,1,0,7));
			squares[1][7]=new Square(1,7,new Piece(2,1,1,7));
			squares[2][7]=new Square(2,7,new Piece(3,1,2,7));
			squares[3][7]=new Square(3,7,new Piece(5,1,3,7));
			squares[4][7]=new Square(4,7,new Piece(4,1,4,7));
			squares[5][7]=new Square(5,7,new Piece(3,1,5,7));
			squares[6][7]=new Square(6,7,new Piece(2,1,6,7));
			squares[7][7]=new Square(7,7,new Piece(1,1,7,7));
			
			
		//initialize white Pawns
			for(int i=0;i<8;i++)
			squares[i][1]=new Square(i,1,new Piece(6,0,i,1));
			
		//initialize black Pawns
			for(int i=0;i<8;i++)
			squares[i][6]=new Square(i,6,new Piece(6,1,i,6));
			
		//initialize Piece of other 32 squares with nullptr
		for(int i=0;i<8;i++)
			for(int j=2;j<6;j++)		
			squares[i][j]=new Square(i,j,NULL);
		
		int k=0;
		int p[]={0,1,6,7};
		
		for(int j=0;j<4;j++)	
		for(int i=0;i<8;i++)
		pieces[k++]=squares[i][p[j]]->piece;
		//k=k+1;
		
		
		
		
	}
	
	
	void printBoardState()
	{
		cout<<endl;
		cout<<"Board State"<<endl;
		for(int i=0;i<32;i++)
		cout<<i<<"  :"<<"Piece :"<<pieces[i]->colour<<pieces[i]->type<<"  Position :"<<pieces[i]->x<<pieces[i]->y<<endl<<endl;
	}
	
	Square* getNorth(int i,int j)
	{
		if(j+1>7)
		return NULL;
		return squares[i][j+1];
	}
	
	Square* getSouth(int i,int j)
	{	if(j-1<0)
		return NULL;
		return squares[i][j-1];
	}
	
	Square* getEast(int i,int j)
	{
		if(i+1>7)
		return NULL;
		return squares[i+1][j];
	}
	
	Square* getWest(int i,int j)
	{	
		if(i-1<0)
		return NULL;
		return squares[i-1][j];
	}
	
	Square* getNorthEast(int i,int j)
	{
		if(i+1>7 || j+1>7)
		return NULL;
		return squares[i+1][j+1];
	}
	
	Square* getNorthWest(int i,int j)
	{
		if(i-1<0 || j+1>7)
		return NULL;
		return squares[i-1][j+1];
	}
	
	Square* getSouthEast(int i,int j)
	{	
		if(i+1>7 || j-1 <0)
		return NULL;
		return squares[i+1][j-1];
	}
	
	Square* getSouthWest(int i,int j)
	{
		if(i-1<0 || j-1<0)
		return NULL;
		return squares[i-1][j-1];
	}
	
	bool isInBoard(int x,int y)
	{
		if(x>=0 && x<=7 && y>=0 && y<=7)
		return true;
		return false;
	}
	
	
	bool isValidRookMove(Square *src,Square* dst)
	{
		int found=0;
		Square* current=getNorth(src->x,src->y);

		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getNorth(current->x,current->y);
		}
		
		current=getSouth(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getSouth(current->x,current->y);
		}
		
		current=getEast(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getEast(current->x,current->y);
		}
		
		
		current=getWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getWest(current->x,current->y);
		}
		
		
		if(found==1)
		return true;
		return false;
	}
	

	bool isValidKnightMove(Square* src, Square* dst)
	{
		int x=src->x;
		int y=src->y;
		if((isInBoard(x-1,y+2) && dst==squares[x-1][y+2]) || (isInBoard(x+1,y+2) && dst==squares[x+1][y+2]) ||
		   (isInBoard(x+2,y+1) && dst==squares[x+2][y+1]) || (isInBoard(x-2,y+1) && dst==squares[x-2][y+1]) || 
		   (isInBoard(x+2,y-1) && dst==squares[x+2][y-1]) || (isInBoard(x-2,y-1) && dst==squares[x-2][y-1]) || 
		   (isInBoard(x+1,y-2) && dst==squares[x+1][y-2]) || (isInBoard(x-1,y-2) && dst==squares[x-1][y-2]) )
		   return true;
	}
	
	bool isValidBishopMove(Square *src,Square *dst)
	{
		int found=0;
		Square* current=getNorthEast(src->x,src->y);

		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getNorthEast(current->x,current->y);
		}
		
		current=getSouthEast(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getSouthEast(current->x,current->y);
		}
		
		current=getNorthWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getNorthWest(current->x,current->y);
		}
		
		
		current=getSouthWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			current=getSouthWest(current->x,current->y);
		}
		
		
		if(found==1)
		return true;
		return false;	
	}
	
	bool isValidQueenMove(Square* src, Square* dst )
	{
		
		
		if(isValidRookMove(src,dst) || isValidBishopMove(src,dst))
		return true;
		return false;
	}
	
	bool isValidPawnMove(Square* src,Square* dst)
	{
		int c=src->piece->colour;
		
	
		
		if(c==0)
		{	
			if(getNorth(src->x,src->y)!=NULL)
			if(!getNorth(src->x,src->y)->hasPiece() && getNorth(src->x,src->y)==dst)
			return true;
			
			if(getNorthEast(src->x,src->y)!=NULL)
			if(getNorthEast(src->x,src->y)->hasPiece())
			if(getNorthEast(src->x,src->y)->piece->colour==1 && getNorthEast(src->x,src->y)==dst)
			return true;
		
			
			if(getNorthWest(src->x,src->y)!=NULL)
			if(getNorthWest(src->x,src->y)->hasPiece())
			if(getNorthWest(src->x,src->y)->piece->colour==1 && getNorthWest(src->x,src->y)==dst)
			return true;
			
			
			if(src->y==1 && dst->y==3 && src->x==dst->x && dst->piece==NULL)
			return true;
		}
		
		
		
		
		if(c==1)
		{
			if(getSouth(src->x,src->y)!=NULL)
			if(!getSouth(src->x,src->y)->hasPiece() && getSouth(src->x,src->y)==dst )
			return true;
			
			if(getSouthEast(src->x,src->y)!=NULL)
			{
			if(getSouthEast(src->x,src->y)->hasPiece())
			{
			if(getSouthEast(src->x,src->y)->piece->colour==0 && getSouthEast(src->x,src->y)==dst)
			return true;
			}
			}
			
					
			
			if(getSouthWest(src->x,src->y)!=NULL)
			if(getSouthWest(src->x,src->y)->hasPiece())
			if(getSouthWest(src->x,src->y)->piece->colour==0 && getSouthWest(src->x,src->y)==dst )
			return true;
						
			if(src->y==6 && dst->y==4 && src->x==dst->x && dst->piece==NULL)
			return true;
		}
		

		
		return false;
	}
	
	bool isAdjacentSquare(Square* src,Square* dst)
	{
		if(!dst->isInBoard() || !src->isInBoard()) 
		return false;
		
		
		
		Square* d=getNorth(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;
		
		d=getNorthEast(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;
		
	    d=getEast(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;
		
		d=getSouthEast(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;
		
		d=getSouth(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;		
		
		d=getSouthWest(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;

		d=getWest(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;
		
		
		d=getNorthWest(src->x,src->y);
		if(d!=NULL && d==dst)
		return true;		
		
		return false;
	}
	
	bool isValidPawnMove1(Square* src,Square* dst)
	{
		
		
		if(!src->isInBoard() || !dst->isInBoard() )
		return false;
		if(!src->hasPiece())
		return false;
		if(dst->hasPiece() && dst->piece->colour==src->piece->colour)
		return false; 
		
		
		
		if(src->piece->colour==0)
		{
			
			if((getNorthEast(src->x,src->y)!=NULL && dst==getNorthEast(src->x,src->y)) ||
			 (getNorthWest(src->x,src->y)!=NULL && dst==getNorthWest(src->x,src->y)))
			 return true;
		}
		
		if(src->piece->colour==1)
		{
			if((getSouthEast(src->x,src->y)!=NULL && dst==getSouthEast(src->x,src->y)) ||
			 (getSouthWest(src->x,src->y)!=NULL && dst==getSouthWest(src->x,src->y)))
			 return true;
		}

		return false;
	}
	
	bool isValidKingMove(Square* src,Square* dst)
	{
		int start=(src->piece->colour==0) ? 16:0;
		int end=start+16;
		
		
	int indexOfDstPiece;
		for(int i=0;i<32;i++)
		if(pieces[i]==dst->piece)
		indexOfDstPiece=i;
		bool isValid;
		
		// check if any coin of opp. colour can move to dst , if yes king cannot move to dst hence return false
		for(int i=start;i<end;i++)
		{
					
			if(isInBoard(pieces[i]->x,pieces[i]->y) && i!=4 && i!=28 && pieces[i]->type!=6)
			{
				// if dst has piece
				if(dst->hasPiece() && dst->piece->colour==pieces[i]->colour && pieces[i]!=dst->piece)
				{	
	
					dst->piece->x=-1;dst->piece->y=-1;
					dst->piece=NULL;
					
					
					isValid=isValidMove(squares[pieces[i]->x][pieces[i]->y],dst);
		
					
					dst->piece=pieces[indexOfDstPiece];
					dst->piece->x=dst->x;dst->piece->y=dst->y;

					if(isValid)
					return false;
					
				}
				
				//if dst does not have piece
				else if(!dst->hasPiece() && isValidMove(squares[pieces[i]->x][pieces[i]->y],dst))
				{	
				return false;
				}
			}
			else if((i==4 || i==28))
			{
				if(isAdjacentSquare(squares[pieces[i]->x][pieces[i]->y],dst))
				return false;
			}
			else if(isInBoard(pieces[i]->x,pieces[i]->y) && pieces[i]->type==6)
			{
				if(isValidPawnMove1(squares[pieces[i]->x][pieces[i]->y],dst))
				return false;
			}

		}
		
		int x=src->x;
		int y=src->y;
		


		
		
		
		if((getNorth(x,y)!=NULL && dst==getNorth(x,y)) || (getEast(x,y)!=NULL && dst==getEast(x,y)) ||
		(getSouth(x,y)!=NULL && dst==getSouth(x,y)) || (getWest(x,y)!=NULL && dst==getWest(x,y)) ||
		(getNorthEast(x,y)!=NULL && dst==getNorthEast(x,y)) || (getNorthWest(x,y)!=NULL && dst==getNorthWest(x,y)) ||
		(getSouthEast(x,y)!=NULL && dst==getSouthEast(x,y)) || (getSouthWest(x,y)!=NULL && dst==getSouthWest(x,y))  )
		return true;

		return false;
	}
	
	bool isValidMove(Square *src,Square* dst )
	{
		

		if(!src->isInBoard() || !dst->isInBoard())
		return false;

		if(!src->hasPiece())
		return false;	

		if(src==dst)
		return false;
		
	
		if(dst->hasPiece())
			if(src->piece->colour==dst->piece->colour )
			return false;
		

		
		if(src->piece->type==1)
		return isValidRookMove(src,dst);
		
		if(src->piece->type==2)
		return isValidKnightMove(src,dst);
		
		if(src->piece->type==3)
		return isValidBishopMove(src,dst);
		

		
		if(src->piece->type==4)
		return isValidKingMove(src,dst);
		
		
		
		
		
		if(src->piece->type==5)
		return isValidQueenMove(src,dst);
		
			
		
		
		if(src->piece->type==6)
		return isValidPawnMove(src,dst);
		
	
		
		
		return false;
		
		
	}
	
	bool isValidMove1(Square *src,Square* dst )
	{
		// calls validPawnMove1 if type ==6

		if(!src->isInBoard() || !dst->isInBoard())
		return false;

		if(!src->hasPiece())
		return false;	

		if(src==dst)
		return false;
		
	
		if(dst->hasPiece())
			if(src->piece->colour==dst->piece->colour )
			return false;
		

		
		if(src->piece->type==1)
		return isValidRookMove(src,dst);
		
		if(src->piece->type==2)
		return isValidKnightMove(src,dst);
		
		if(src->piece->type==3)
		return isValidBishopMove(src,dst);
		

		
		if(src->piece->type==4)
		return isValidKingMove(src,dst);
		
	
		if(src->piece->type==5)
		return isValidQueenMove(src,dst);
		
		
		if(src->piece->type==6)
		return isValidPawnMove1(src,dst);

		
		return false;
		
		
	}
	
	bool move(int x1,int y1,int x2,int y2)
	{
		if(!isInBoard(x1,y1) || !isInBoard(x2,y2))
		return false;
		
		Square* src=squares[x1][y1];
		Square* dst=squares[x2][y2];
		

			src->piece->x=dst->x;
			src->piece->y=dst->y;
			
			if(dst->hasPiece())
			{          
			dst->piece->x=-1;
			dst->piece->y=-1;
			}

			dst->piece=src->piece;
			src->piece=NULL;
		
		
		
		
	}
	
	
	Piece* isCheck(bool c)
	{
		//call after moving piece
	 
		Piece* king=(c==1)?pieces[28]:pieces[4];
		Square* kingSquare=squares[king->x][king->y];
		
		king->x=-1;king->y=-1;
		kingSquare->piece=NULL;
		
		//cout<<"reached "<<kingSquare->x<<kingSquare->y<<endl;
		
		Piece* p=isADestination1(kingSquare,!c);
		
		king->x=kingSquare->x;king->y=kingSquare->y;
		kingSquare->piece=king;
		
		return p;
		 
	}
	
	
	bool isKingTrapped(bool c)
	{
		
		Piece* king=(c==1)?pieces[28]:pieces[4];
		Square* kingSquare=squares[king->x][king->y];

	//	cout<<kingSquare->x<<kingSquare->y<<endl;

		Square* d=getNorth(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;

		d=getNorthEast(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		d=getEast(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		d=getSouthEast(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		d=getSouth(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		
		
		d=getSouthWest(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		d=getWest(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		d=getNorthWest(kingSquare->x,kingSquare->y);
		if(d!=NULL && isValidMove(kingSquare,d))
		return false;
		
		return true;
	}
	
	vector<Square*>* getSquaresInPathForRook(Square* src,Square* dst)
	{
		int found=0;
		vector<Square*>* v=new vector<Square*>();
		Square* current=getNorth(src->x,src->y);
		
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getNorth(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getSouth(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getSouth(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getEast(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getEast(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getWest(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		
		return v;
		
	}
	
	vector<Square*>* getSquaresInPathForBishop(Square* src,Square* dst)
	{
		int found=0;
		vector<Square*>* v=new vector<Square*>();
		Square* current=getNorthEast(src->x,src->y);
		
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getNorthEast(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getSouthEast(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getSouthEast(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getSouthWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getSouthWest(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		current=getNorthWest(src->x,src->y);
		while(found==0 && current!=NULL)
		{
			if(current==dst)
			{
			found=1;
			break;
			}
			if(current->hasPiece())
			break;
			v->push_back(current);
			current=getNorthWest(current->x,current->y);
		}
		if(found==0)
		v->clear();
		
		
		return v;
	}
	
	vector<Square*>* getSquaresInPathForQueen(Square* src,Square* dst)
	{
		if(isValidRookMove(src,dst))
		return getSquaresInPathForRook(src,dst);
		if(isValidBishopMove(src,dst))
		return getSquaresInPathForBishop(src,dst);
	}
	
	vector<Square*>* getSquaresInPath(Square* src,Square* dst)
	{
		vector<Square*>* v=new vector<Square*>();
		
	//	cout<<"hi "<<isValidMove(src,dst)<<endl;
		if(!isValidMove(src,dst))
		return NULL;
		
		
		if(src->piece->type==1)
		{
			return getSquaresInPathForRook(src,dst);
		}
		else if(src->piece->type==3)
		{
			return getSquaresInPathForBishop(src,dst);
		}
		else if(src->piece->type==5)
		{
		return getSquaresInPathForQueen(src,dst);
		}
		
		return NULL;
	}
	
	Piece* isADestination(Square* s,int c)
	{
		int start = (c==0)?0:16;
		int end=start+16;
		for(int i=start;i<end;i++)
		{
			if(pieces[i]->type==4 || !pieces[i]->isInBoard())
			continue;
			
			if(isValidMove(squares[pieces[i]->x][pieces[i]->y],s))
			return pieces[i];
			//else
			//cout<<pieces[i]->colour<<pieces[i]->type<<" Not a Valid Move"<<endl;
		}
		
		return NULL;
	}
	
		Piece* isADestination1(Square* s,int c)
	{
		int start = (c==0)?0:16;
		int end=start+16;
		for(int i=start;i<end;i++)
		{
			if(pieces[i]->type==4 || !pieces[i]->isInBoard())
			continue;
			
			if(pieces[i]->type==6 && isValidPawnMove1(squares[pieces[i]->x][pieces[i]->y],s))
			return pieces[i];
			
			if(pieces[i]->type!=6 && isValidMove(squares[pieces[i]->x][pieces[i]->y],s)  )
			return pieces[i];
			
		}
		
		return NULL;
	}
	
	bool isIllegalMove(Square* src,Square* dst)
	{
		if(!src->isInBoard() || !dst->isInBoard())
		return false;

		if(!src->hasPiece())
		return false;	

		if(src==dst)
		return false;
		
	
		if(dst->hasPiece())
			if(src->piece->colour==dst->piece->colour )
			return false;
		
		
		int c=src->piece->colour;
		//Piece* chi=isCheck(c);
		Piece* oldDst;
		int k=0;
		if(dst->hasPiece())
		{
		oldDst=dst->piece;
		k=1;
		}
		
		move(src->x,src->y,dst->x,dst->y);//
		Piece* chf=isCheck(c);
		move(dst->x,dst->y,src->x,src->y);
		
		if(k==1)
		{

		dst->piece=oldDst;
		dst->piece->x=dst->x;dst->piece->y=dst->y;
		
		}
		
		if( chf!=NULL)
		return true;
		
		return false;
	}
	
	Piece* canAttackHost(Square* hs)
	{
		int start=(hs->piece->colour==0)?16:0;
		int end=start+16;
		
		for(int i=start;i<end;i++)
		{	
			
			if(pieces[i]->isInBoard())
			{
				
			if(isValidMove1(squares[pieces[i]->x][pieces[i]->y] , hs) && !isIllegalMove(squares[pieces[i]->x][pieces[i]->y],hs))
			return pieces[i];
			
			}
			
		}
		
		
		return NULL;
	}
	
	bool isCheckMate(int n,Square* src, Square* dst)
	{

	
		
			                        
		Piece* king=(n==0)?pieces[4]:pieces[28];
		Square* kingSquare=squares[king->x][king->y];
		
		Piece* host=isCheck(n);
		Square* hostSquare;
		if(host!=NULL)
		hostSquare=squares[host->x][host->y];
		
		
		
		if(host==NULL)
		return false;
		
		
		if(!isKingTrapped(n))
		return false;
		
	//	cout<<" Checked trap"<<endl;
		
		
		Piece* a=canAttackHost(hostSquare);
		cout<<a<<endl;
		
		
		if(a!=NULL)
		return false;
	
		
	//	cout<<"checked host attack"<<endl;
		
		int l;
		
		vector<Square*>* v=getSquaresInPath(hostSquare,kingSquare);
		if(v!=NULL)
		l=v->size();
		
	//	cout<<"Obtained path"<<endl;
		
				
			
		if(host->type!=2 && host->type!=4 && host->type!=6 && v!=NULL)
		{
						
		for(int i=0;i<l;i++)
		{
			if(isADestination(v->at(i),n)!=NULL)
			return false;
		}
		}	
		

		
	//	cout<<"Returned true"<<endl;
		return true;
	}
	
	

};


