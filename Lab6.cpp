#include <iostream>
#include <fstream>
using namespace std;

struct AutoInfo
{
	string name;
	int price;
	string color;
	double rating;
	void Out();
};

struct Tree
{
	AutoInfo data;
	Tree* left;
	Tree* right;
};

int GetTreeSize(Tree* T)//Размер дерева
{
	if (!T)
	{
		return 0;
	}
	if (!T->left && !T->right)
	{
		return 1;
	}
	int left = 0, right = 0;
	if (T->left)
	{
		left = GetTreeSize(T->left);
	}
	if (T->right)
	{
		right = GetTreeSize(T->right);
	}
	return left + right + 1;
}

void Add(Tree*& T, AutoInfo data, int type)
{
	if (!T)
	{
		T = new Tree;
		T->data = data;
		T->left = NULL;
		T->right = NULL;
		return;
	}
	if (type == 0)
	{
		if (data.name < T->data.name)
		{
			Add(T->left, data, 0);
		}
		else
		{
			Add(T->right, data, 0);
		}
	}
	else if (type == 1)
	{
		if (data.price < T->data.price)
		{
			Add(T->left, data, 1);
		}
		else
		{
			Add(T->right, data, 1);
		}
	}
}

void PrintLRR(Tree* T, ofstream& SF)//Вывод информации 
{
	if (!T)
	{
		return;
	}
	PrintLRR(T->left, SF);
	T->data.Out();
	SF << T->data.name << " " << T->data.price << " " << T->data.color << " " << T->data.rating << endl;
	PrintLRR(T->right, SF);
}

void SelectionPrintLRR(Tree* T, AutoInfo Info, int type)
{
	if (!T)
	{
		return;
	}
	SelectionPrintLRR(T->left, Info, type);
	if (type == 0)
	{
		if (T->data.name[0] == Info.name[0])
		{
			T->data.Out();
		}
	}
	else if (type == 1)
	{
		if (T->data.price < Info.price)
		{
			T->data.Out();
		}
	}
	SelectionPrintLRR(T->right, Info, type);
}


void Delete(Tree*& T)
{
	if (T)
	{
		if (T->left)
		{
			Delete(T->left);
		}
		if (T->right)
		{
			Delete(T->right);
		}
		delete T;
		T = NULL;
	}
	else
	{
		cout << "Дерево пустое" << endl << endl;
	}
}

void AutoInfo::Out()
{
	cout << "Автомобиль: " << name << "\t\t" << "Цена: " << price << "\t" << "Цвет: " << color << "\t" << "Рейтинг: " << rating << endl << endl;
}

bool FileAdd(Tree*&, int);

int main()
{
	setlocale(LC_ALL, "RUS");
	ofstream SF;
	Tree* T = NULL;
	AutoInfo Info;
	char symbol = '0';
	int key = 0;
	do
	{
		cout << "1) Упорядочить данные об объектах по строковому полю" << endl
			<< "2) Упорядочить данные об объектах по числовому полю" << endl
			<< "3) Информация с заданным числвым значением" << endl
			<< "4) Информация с заданным символом" << endl
			<< "0) Выход" << endl;
		cout << endl << "Выбирите действие: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			SF.open("SortAuto.txt");
			FileAdd(T, 0);
			PrintLRR(T, SF);
			cout << "Размер дерева = " << GetTreeSize(T) << endl << endl;
			Delete(T);
			SF.close();
			break;
		case 2:
			SF.open("SortAuto.txt");
			FileAdd(T, 1);
			PrintLRR(T, SF);
			cout << "Размер дерева = " << GetTreeSize(T) << endl << endl;
			Delete(T);
			SF.close();
			break;
		case 3:
			cout << "Введите цену авто: ";
			cin >> Info.price;
			cout << endl;
			FileAdd(T, 1);
			SelectionPrintLRR(T, Info, 1);
			Delete(T);
			break;
		case 4:
			cout << "Введите первый символ: ";
			cin >> Info.name;
			cout << endl;
			FileAdd(T, 0);
			SelectionPrintLRR(T, Info, 0);
			Delete(T);
			break;
		default:
			if (key != 0)
			{
				cout << "Такого действия нет !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
	Delete(T);
}

bool FileAdd(Tree*& T, int type)//Работа с файлом
{
	AutoInfo Info;
	ifstream F("Auto.txt");
	if (!F)
	{
		cout << "Файл не обнаружен" << endl;
		return false;
	}
	while (F >> Info.name >> Info.price >> Info.color >> Info.rating)
	{
		Add(T, Info, type);
	}
	F.close();
}