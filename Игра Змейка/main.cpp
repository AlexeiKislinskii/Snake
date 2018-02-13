#include "all.h"

using namespace std;

void main()
{
  SetConsoleCP( 1251 );
  SetConsoleOutputCP( 1251 );
	setlocale(LC_CTYPE,"Russian");
	system("cls");
	cout<<"Змейка версии 0.1"<<endl;
	
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<"                                Правила игры:                                "<<endl;
	cout<<"Игрок управляет длинным, тонким существом, напоминающим змею,"<<endl;
	cout<<"которое ползает по плоскости ограниченной стенками, собирая еду,"<<endl;
	cout<<"избегая столкновения с собственным хвостом и краями игрового поля."<<endl;
	cout<<"Каждый раз, когда змея съедает кусок пищи, она становится длиннее,"<<endl;
	cout<<"что постепенно усложняет игру."<<endl;
	cout<<"Игрок управляет направлением движения головы змеи."<<endl<<endl;
	cout<<"Игрок не может остановить движение змеи."<<endl;
	cout<<"В игре есть обучение, компьютер может показать Вам как играть"<<endl;
	cout<<"Скорость змеи увеличивается с каждым 10 яблочком."<<endl;
	cout<<"Приятной игры!"<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	

	while(1)
	{
		cout<<"Для начала игры нажмите Enter, для выхода Esc."<<endl;
		if(_getch()==13)game();
		if(_getch()==27)exit(0);
	}
}
char* CreateArray(int x)
{
	char* field = new char [x];
	return field;
}
void FreeArray(char* field)
{
	delete[] field;
}
void gotoXY(int line, int column)
{
  COORD coord;
  coord.Y = column;
  coord.X = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void game()
{
	system("cls");
	Field main;
	main.Input();
	main.Init();
	main.SnakeCreate();
	main.SnakePlaceOnField();
	main.GameEnd(main.SnakeMove());
	cout<<endl;
	exit(0);
}
