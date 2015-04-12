#include "all.h"

using namespace std;

SnakeList::SnakeList():Head(NULL),Tail(NULL){};
SnakeList::~SnakeList()
{
	while(Head->next!=NULL)
	{
		SnakeElement *temp = Head->next;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		delete temp;
	}
	delete Head;
};
void SnakeList::Add(int x,char pixel)
 {
   SnakeElement *temp=new SnakeElement; 
   temp->next=NULL; 
   temp->x=x;
   temp->pixel=pixel;

   if (Head!=NULL)
   {
	   Tail->next=temp;
	   Tail=temp;
   }
   else 
   {
	   Head=Tail=temp; 
   }
 }
void SnakeList::DeleteHead()
{
	SnakeElement *temp=Head->next;
	delete Head;
	Head=temp;
}
Field::Field(){x=y=12;};
Field::Field(int x_init,int y_init):x(x_init+2),y(y_init+2){};
Field::~Field(){FreeArray(map);};
void Field::Init()
{
	unsigned int size =x*y;
	map = CreateArray(size);
	for(unsigned int i = 0;i<size;++i)map[i]=' ';
	for(unsigned int i = 0;i<x;++i)map[i]='*';
	for(unsigned int i = size;i>=size-x;--i)map[i]='*';
	for(unsigned int i = x;i<size-x;i=i+x)map[i]=map[i+x-1]='*';		
};
void Field::Print(int init_x)
{
	int size = x*y;
	int iterr=0;
	if(init_x==0)
	{
		gotoXY(0,0);
		for(int i = 0;i<size;++i)
		{
			if(iterr%x==0&&i!=0)cout<<endl;
			cout<<map[i];
			++iterr;
		}
	}
	else
	{
		gotoXY(init_x%x,(int)init_x/x);
		cout<<map[init_x];
	}
}
void Field::Input()
{
	system("cls");
	cout<<"Введите размеры поля(рекомендуемый размер 10 на 10)"<<endl;
	cin>>x>>y;
	while(x>77||y>22||x<10||y<10)
	{
		system("cls");
		cout<<"Максимальный размер поля 77 на 22"<<endl;
		cout<<"Минимальный размер поля 10 на 10"<<endl;
		cin>>x>>y;
	}
	x=x+2;
	y=y+2;
	system("cls");
	cout<<"Нажмите Enter для обучающей игры, для продолжения любую другую"<<endl;
	if(_getch()==13)player=false;
	system("cls");
}
void Field::SnakeCreate()
{
	snake.Add((int)(y/2*x)+(x/2)+x,'^');
	snake.Add((int)(y/2*x)+(x/2),'^');
	Direction=1;
	lenth = 2;
}
void Field::SnakePlaceOnField()
{
	map[snake.getHeadX()]=snake.getHeadPixel();
	map[snake.getTailX()]=snake.getTailPixel();
}
int Field::SnakeMove()
{
	int result = 0;
	int TailX = 0;
	int KeyStroke;
	int DeltaPoint;
	int food;
	char Pixel= '^';
	bool realplayer=player;
	Algorithm=false;
	score = 0;

	food=Food();
	Print(0);
	cout<<endl<<"Для начала игры нажмите любую клавишу";
	_getch();
	system("cls");
	Print(0);
	while(1)
	{
		if(_kbhit()&&realplayer)
		{
			KeyStroke = _getch();
			if (KeyStroke == 224)
			{   
				KeyStroke = _getch();
				if(KeyStroke==72&&Direction!=1&&Direction!=3){Direction=1;Pixel='^';}
				else if(KeyStroke==80&&Direction!=1&&Direction!=3){Direction=3;Pixel='V';}
				else if(KeyStroke==75&&Direction!=2&&Direction!=4){Direction=4;Pixel='<';}
				else if(KeyStroke==77&&Direction!=2&&Direction!=4){Direction=2;Pixel='>';}
			}
		}
		else if(!realplayer)
		{
			result=PerfectPlayer(snake.getTailX(),food);
			if(result==5)result=1;
			if(result==0)result=4;
			if(result==1){Direction=1;Pixel='^';}
			else if(result==3){Direction=3;Pixel='V';}
			else if(result==4){Direction=4;Pixel='<';}
			else if(result==2){Direction=2;Pixel='>';}
		}
		TailX = snake.getTailX();
		result = Scan(Direction,TailX);
		if(result!=3&&result!=4)
		{
			if(result==2)
			{
				if(Direction==1)TailX=TailX-x;
				else if(Direction==3)TailX=TailX+x;
				else if(Direction==2)TailX++;
				else if(Direction==4)TailX--;
				snake.Add(TailX,Pixel);
				lenth++;
				if(lenth==x*y&&realplayer)return 1;
				else if(lenth==x*y&&!realplayer)return 41;
				SnakePlaceOnField();
				food=Food();
				score++;
				PrintScore();
			}
			else
			{
				map[snake.getHeadX()]=' ';
				DeltaPoint = snake.getHeadX();
				snake.DeleteHead();
				if(Direction==1)TailX=TailX-x;
				else if(Direction==3)TailX=TailX+x;
				else if(Direction==2)TailX++;
				else if(Direction==4)TailX--;
				snake.Add(TailX,Pixel);
				SnakePlaceOnField();
			}
			Print(DeltaPoint);
			Print(snake.getTailX());
			Print(snake.getHeadX());
			setSpeed();
			
		}	
		else if(realplayer) return 0;
		else return 40;
	}
}
int Field::Scan(int Direction,int input)
{
	if(Direction==0)Direction=4;
	if(Direction==5)Direction=1;
	if(Direction==1)
	{
		if(map[input-x]==' ')return 1;//free space
		else if(map[input-x]=='A')return 2;//food
		else if(map[input-x]=='*')return 3;//border
		else return 4;//snake
	}
	else if(Direction==3)
	{
		if(map[input+x]==' ')return 1;//free space
		else if(map[input+x]=='A')return 2;//food
		else if(map[input+x]=='*')return 3;//border
		else return 4;//snake
	}
	else if(Direction==2)
	{
		if(map[input+1]==' ')return 1;//free space
		else if(map[input+1]=='A')return 2;//food
		else if(map[input+1]=='*')return 3;//border
		else return 4;//snake
	}
	else if(Direction==4)
	{
		if(map[input-1]==' ')return 1;//free space
		else if(map[input-1]=='A')return 2;//food
		else if(map[input-1]=='*')return 3;//border
		else return 4;//snake
	}
	return 40;//error
}
int Field::Food()
{
	unsigned int FoodIndex, size;
	size = x*y;
	srand(time(0));
	FoodIndex=rand()%size;
	while(map[FoodIndex]!=' ')
	{
		srand(time(0)*FoodIndex);
		FoodIndex=rand()%size;
	}
	map[FoodIndex]='A';
	Print(FoodIndex);
	return FoodIndex;
}
int Field::PerfectPlayer(int Tail,int Food)
{
	Coord tail=IndexToXY(Tail);
	Coord food=IndexToXY(Food);
	int temp = Direction;
	double bestDist = Distance(tail,food);
	while(1)
	{
		if((tail.x==food.x&&tail.y<food.y&&Direction==1)||
			(tail.x==food.x&&tail.y>food.y&&Direction==3)||
			(tail.y==food.y&&tail.x>food.x&&Direction==2)||
			(tail.y==food.y&&tail.x<food.x&&Direction==4))
		{
			if(Scan(1,Tail)==1)return 1;
			else if(Scan(2,Tail)==1)return 2;
			else if(Scan(3,Tail)==1)return 3;
			else if(Scan(4,Tail)==1)return 4;
			else return 40;
		}
		switch(temp)
		{
		case 1:
			if(Distance(Tail+1,Food)<bestDist){bestDist=Distance(Tail+1,Food);temp=2;}
			if(Distance(Tail-1,Food)<bestDist){bestDist=Distance(Tail-1,Food);temp=4;}
			break;
		case 2:
			if(Distance(Tail+x,Food)<bestDist){bestDist=Distance(Tail+x,Food);temp=3;}
			if(Distance(Tail-x,Food)<bestDist){bestDist=Distance(Tail-x,Food);temp=1;}
			break;
		case 3:
			if(Distance(Tail+1,Food)<bestDist){bestDist=Distance(Tail+1,Food);temp=2;}
			if(Distance(Tail-1,Food)<bestDist){bestDist=Distance(Tail-1,Food);temp=4;}
			break;
		case 4:
			if(Distance(Tail-x,Food)<bestDist){bestDist=Distance(Tail-x,Food);temp=1;}
			if(Distance(Tail+x,Food)<bestDist){bestDist=Distance(Tail+x,Food);temp=3;}
			break;
		}
		if(Scan(temp,Tail)!=4){Direction = temp;return Direction;}
		else Algorithm=true;
		
		while(Algorithm)
		{
			////нужен весовой алгоритм поиска пути
				//if(Scan(Direction+1,Tail)<3){TimeToLeftOrRightHandAlgorithm=false;return Direction+1;}
				//else if(Scan(Direction-1,Tail)<3){TimeToLeftOrRightHandAlgorithm=false;return Direction-1;}
				//else return 40;//gameover
			int temp1=0;
			int temp2=0;
			int Out;
			if(Scan(Direction,Tail)==1)return Direction;
			if(Direction==1||Direction==3)
			{
				for(unsigned int i = tail.x;i<x;i++)
				{
					if(Scan(Direction+1,XYToIndex(i,tail.y))==4||i==x)i=x;
					temp1++;
				}
				for(int i = tail.x;i>0;i--)
				{
					if(Scan(Direction-1,XYToIndex(i,tail.y))==4||i==0)i=0;
					temp2++;
				}
				if(temp1>temp2)Out=Direction+1;
				else if(temp1<temp2)Out=Direction-1;
				else Out=Direction+1;
			}
			if(Direction==2||Direction==4)
			{
				for(unsigned int i = tail.y;i<y;i++)
				{
					if(Scan(Direction+1,XYToIndex(tail.x,i))==4||i==y)i=y;
					temp1++;
				}
				for(int i = tail.y;i>0;i--)
				{
					if(Scan(Direction-1,XYToIndex(tail.x,i))==4||i==0)i=0;
					temp2++;
				}
				if(temp1>temp2)Out=Direction+1;
				else if(temp1<temp2)Out=Direction-1;
				else Out=Direction+1;
			}
			Algorithm=false;
			return Out;
		}
	}
};
Coord Field::IndexToXY(int index)
{
	Coord point;
	point.y=(int)(index/x)+1;
	point.x=index%x;
	return point;
};
int Field::XYToIndex(int x_init,int y_init)
{
	int vihod = 0;
	vihod = (y_init-1)*x+x_init;
	return vihod;
};
void Field::PrintScore()
{
	gotoXY(6,y);
	cout<<"                                    ";
	gotoXY(0,y);
	cout<<"Счет: "<<score;
};
void Field::GameEnd(int result)
{
	gotoXY(0,y+1);
	if(result==0)cout<<"Вы проиграли!"<<endl;
	else if(result==1)cout<<"Вы выиграли!"<<endl;
	else if(result==40)cout<<"Компьютер проиграл О_о"<<endl;
	else if(result==41)cout<<"Обучение окончено."<<endl;

	while(1)
	{
		gotoXY(0,y+2);
		cout<<"Для повтора игры нажмите Enter, для выхода Esc.";
		if(_getch()==13)game();
		if(_getch()==27)exit(0);
	}
};
void Field::setSpeed()
{
	if(lenth<10)_sleep((165-15*0.6));
	else if(lenth>=10&&lenth<20)_sleep((165-15*1.2));
	else if(lenth>=20&&lenth<30)_sleep((165-15*1.8));
	else if(lenth>=30&&lenth<40)_sleep((165-15*2.4));
	else if(lenth>=40&&lenth<50)_sleep((165-15*3));
	else if(lenth>=50&&lenth<60)_sleep((165-15*3.6));
	else if(lenth>=60&&lenth<70)_sleep((165-15*4.2));
	else if(lenth>=70&&lenth<80)_sleep((165-15*4.8));
	else if(lenth>=80&&lenth<90)_sleep((165-15*5.4));
	else if(lenth>=90)_sleep((165-15*6));
};
double Field::Distance(Coord point1,Coord point2)
{
	double temp=0;
	temp=sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2));
	return temp;
};
double Field::Distance(int index1,int index2)
{
	double temp=0;
	Coord point1=IndexToXY(index1);
	Coord point2=IndexToXY(index2);
	temp=sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2));
	return temp;
};