#include "all.h"

using namespace std;

void main()
{
  SetConsoleCP( 1251 );
  SetConsoleOutputCP( 1251 );
	setlocale(LC_CTYPE,"Russian");
	system("cls");
	cout<<"������ ������ 0.1"<<endl;
	
	cout<<"----------------------------------------------------------------------------"<<endl;
	cout<<"                                ������� ����:                                "<<endl;
	cout<<"����� ��������� �������, ������ ���������, ������������ ����,"<<endl;
	cout<<"������� ������� �� ��������� ������������ ��������, ������� ���,"<<endl;
	cout<<"������� ������������ � ����������� ������� � ������ �������� ����."<<endl;
	cout<<"������ ���, ����� ���� ������� ����� ����, ��� ���������� �������,"<<endl;
	cout<<"��� ���������� ��������� ����."<<endl;
	cout<<"����� ��������� ������������ �������� ������ ����."<<endl<<endl;
	cout<<"����� �� ����� ���������� �������� ����."<<endl;
	cout<<"� ���� ���� ��������, ��������� ����� �������� ��� ��� ������"<<endl;
	cout<<"�������� ���� ������������� � ������ 10 ��������."<<endl;
	cout<<"�������� ����!"<<endl;
	cout<<"----------------------------------------------------------------------------"<<endl;
	

	while(1)
	{
		cout<<"��� ������ ���� ������� Enter, ��� ������ Esc."<<endl;
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
