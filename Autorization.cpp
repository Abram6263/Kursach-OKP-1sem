#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

const string file_prod = "FileWithProducts.txt";
const string file_users = "FileWithUsers.txt";
const int RESERVE_SIZE = 1;


struct Users // структура хранящая данные о пользователях
{
	string login;
	string pass;
	int role;
};

struct Products // структура хрянащая данные о продукции
{
	string name_products;
	string name_reg;
	string surname_reg;
	int amount;
	float price;
	int day, month;
};



bool isCheck(Users user); // определение пользователя или админа
bool isNumberNumeric(); // проверка на коректность вводимого числа
bool isNumberRangeCorrect(int number, int left_range, int right_range); // задаем диапазон ввода
int inputNumber(int left_range, int right_range); // проверка числа на коректность и заданный диапозон ввода
void changeProductsArray(Products *arr_of_products, int i); // изменение одного из описаний продукта
void showArrUsers(Users *rol, int &number_users);// вывод массива с пользователями на экран
void indTask(Products *arr_of_products, int &number_products); // индивидуальное задание
void searchNameProducts(Products *arr_of_products, int &number_products);  // поиск по названию продукта
void searchAmountProducts(Products *arr_of_products, int &number_products);  // поиск по кол-ву
void searchPriceProducts(Products *arr_of_products, int &number_products); // поиск по цене
void generateProductsArray(Products *arr_of_products, int &number_products); // создание изначального списка продуктов
void addProductsArray(Products *arr_of_products, int &number_products); // добавление продукта
void delProductsArray(Products *arr_of_products, int &number_products); // удаление продукта
void showProductsArray(Products *arr_of_products, int number_products); // вывод массива на экран
void showOneProductsArray(Products *arr_of_products, int i); // вывод одного эл-та массива на экран 
void writeFileProducts(Products *arr_of_products, int number_products); // перезапись файла с продуктами
void readFileProducts(Products *arr_of_products, int &number_products); // чтение файла с продуктами
void clearFileProducts(); // форматирование файла с продуктами
void writeNewFileUsers(Users *rol, int &number_users); // перезапись файла с пользователями
void writeEndFileUsers(Users user); // дозапись в файл с пользователями
void clearFileUsers(); // форматирование файла с пользователями 
void readFileUsers(Users *rol, int &number_users); // чтение файла с пользователями
void delFileUsers(Users *rol, int &number_users); // функция удаления учетной записи
void sortNameProducts(Products *arr_of_products, int &number_products); // сортировка по алфавиту
void sortPriceUpProducts(Products *arr_of_products, int &number_products);//сортировка по цене по возрастанию
void sortPriceDownProducts(Products *arr_of_products, int &number_products); //сортировка по цене по убыванию
void sortAmountDownProducts(Products *arr_of_products, int &number_products); //сортировка по кол-ву по убыванию
void sortAmountUpProducts(Products *arr_of_products, int &number_products); //сортировка по кол-ву по возрастанию
void enterUser(Products *arr_of_products, int &number_products); // меню юзера
void enterAdmin(Products *arr_of_products, int &number_products, Users *rol, int &number_users, Users user); // меню админа
void authorization(Products *arr_of_products, int &number_products, Users user, Users *rol); // авторизация
int number(int n); // проверка на коректность вводимых данных типа int
double number_double(double d);// проверка на коректность double

bool isCheck(Users user)
{
	if (user.role == 2)
	{
		return true;
	}
	else if (user.role == 1)
	{
		return false;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Products arr_of_products[RESERVE_SIZE];
	int number_products = 0;
	Users user;
	Users rol[RESERVE_SIZE];
	authorization(arr_of_products, number_products, user, rol);
	

	_getch();
    return 0;
}





bool isNumberNumeric() // проверка на коректность вводимого числа
{
	if (cin.get() == '\n')
	{
		return true;
	}
	else
	{
		cin.clear();
		cin.ignore();
		return false;
	}
}
int number(int n)// проверка на коректность
{
	do
	{
		cin >> n;
		if (cin.good())
		{
			return n;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Ввод некоректный! Повторите ввод: ";
		}
	} while (true);
}

double number_double(double d)// проверка на коректность double
{
	do
	{
		cin >> d;
		if (cin.good())
		{
			return d;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Ввод некоректный! Повторите ввод: ";
		}
	} while (true);
}

bool isNumberRangeCorrect(int number, int left_range, int right_range) // задаем диапазон ввода
{
	if (number >= left_range && number <= right_range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int inputNumber(int left_range, int right_range) // проверка числа на коректность и заданный диапозон ввода
{
	int number;
	while (true)
	{
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range))
		{
			return number;
		}
		else
		{
			cout << "Некоректный ввод! Повторите ввод: ";
		}
	}
}

void generateProductsArray(Products *arr_of_products, int &number_products) // создание изначального списка продуктов
{
	
	number_products = 3;
	arr_of_products[0].name_products = "Бетон";
	arr_of_products[0].amount = 150;
	arr_of_products[0].price = 10.45;
	arr_of_products[0].day = 11;
	arr_of_products[0].month = 3;
	arr_of_products[0].name_reg = "admin";
	arr_of_products[0].surname_reg = "admin";

	arr_of_products[1].name_products = "Кирпич";
	arr_of_products[1].amount = 1250;
	arr_of_products[1].price = 0.20;
	arr_of_products[1].day = 6;
	arr_of_products[1].month = 4;
	arr_of_products[1].name_reg = "admin";
	arr_of_products[1].surname_reg = "admin";

	arr_of_products[2].name_products = "Гвозди";
	arr_of_products[2].amount = 5500;
	arr_of_products[2].price = 0.5;
	arr_of_products[2].day = 7;
	arr_of_products[2].month = 3;
	arr_of_products[2].name_reg = "admin";
	arr_of_products[2].surname_reg = "admin";
}

void addProductsArray(Products *arr_of_products, int &number_products)// добавление продукта
{
	if (number_products < RESERVE_SIZE)
	{
		number_products++;
	}
	else
	{
		cout << "Ошибка! Массив переполнен!" << endl;
		system("pause");
		exit(0);
	}
	cout << "имя продукта: ";
	cin.ignore();
	getline(cin, arr_of_products[number_products - 1].name_products);
	cout << "кол-во на складе: ";
	/*cin >> arr_of_products[number_products - 1].amount;*/
	arr_of_products[number_products - 1].amount = number(arr_of_products[number_products - 1].amount);
	cout << "цена за единицу: ";
	arr_of_products[number_products - 1].price = number_double(arr_of_products[number_products - 1].price);
	/*cin >> arr_of_products[number_products - 1].price;*/
	cout << "дата поставки на склад: день -  ";
	arr_of_products[number_products - 1].day = inputNumber(1, 30);
	cout << "\t\t\tмесяц - ";
	arr_of_products[number_products - 1].month = inputNumber(1, 12);
	cout << "Товар зарегистрировал - Имя: ";
	getline(cin, arr_of_products[number_products - 1].name_reg);
	cout << "\t\t\tФамилия: ";
	getline(cin, arr_of_products[number_products - 1].surname_reg);
}

void delProductsArray(Products *arr_of_products, int &number_products)// удаление продукта
{
	int k;
	cout << "введите номер продукта который хотите удалить: ";
	k = inputNumber(1, number_products);
		for (int i = k - 1; i < number_products; i++)
		{
			arr_of_products[i].name_products = arr_of_products[i + 1].name_products;
			arr_of_products[i].amount = arr_of_products[i + 1].amount;
			arr_of_products[i].price = arr_of_products[i + 1].price;
			arr_of_products[i].day = arr_of_products[i + 1].day;
			arr_of_products[i].month = arr_of_products[i + 1].month;
			arr_of_products[i].name_reg = arr_of_products[i + 1].name_reg;
			arr_of_products[i].surname_reg = arr_of_products[i + 1].surname_reg;
		}
		number_products--;
}


void showProductsArray(Products *arr_of_products, int number_products) // вывод массива на экран
{

	int y = 1;
	cout << "----------------------------------------------------------------" << endl;
	for (int i = 0; i < number_products; i++)
	{
		cout << "Продукт № " << y << "\nНаименование продукта - " << arr_of_products[i].name_products << "\nКол-во единиц товара - " << arr_of_products[i].amount << "\nЦена единицы товара - " << arr_of_products[i].price << "р." << "\nДата поступления товара на склад - " << arr_of_products[i].day << "." << arr_of_products[i].month << "\nФИО зарегистрировавшего товар - " << arr_of_products[i].name_reg << " " << arr_of_products[i].surname_reg << endl;
		cout << "----------------------------------------------------------------" << endl;
		y++;
	}
}

void showOneProductsArray(Products *arr_of_products, int i) // вывод одного эл-та массива на экран 
{
	cout << "----------------------------------------------------------------" << endl;
		cout <<"Продукт № "<< i+1 << "\nНаименование продукта - " << arr_of_products[i].name_products << "\nКол-во единиц товара - " << arr_of_products[i].amount << "\nЦена единицы товара - " << arr_of_products[i].price << "р." << "\nДата поступления товара на склад - " << arr_of_products[i].day << "." << arr_of_products[i].month << "\nФИО зарегистрировавшего товар - " << arr_of_products[i].name_reg << " " << arr_of_products[i].surname_reg << endl;
		
		
	
}

void writeFileProducts(Products *arr_of_products, int number_products)// перезапись файла с продуктами
{
	ofstream fout(file_prod, ios::out);
	for (int i = 0; i < number_products; i++)
	{
		fout << arr_of_products[i].name_products << " " << arr_of_products[i].amount << " " << arr_of_products[i].price << " " << arr_of_products[i].day << " " << arr_of_products[i].month << " " << arr_of_products[i].name_reg << " " << arr_of_products[i].surname_reg;
		if (i < number_products - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}

void clearFileProducts() // форматирование файла с продуктами
{
	ofstream fin(file_prod, ios::trunc);
	if (!fin.is_open())
	{
		cout << "Файл не найден!" << endl;
	}
	fin.close();
}

void readFileProducts(Products *arr_of_products, int &number_products)// чтение файла с продуктами
{
	ifstream fin(file_prod, ios::in);
	if (!fin.is_open())
	{
		cout << "Данный файл не найден!" << endl;
	}
	else
	{
		int i = 0;
		while (!fin.eof())
		{
			fin >> arr_of_products[i].name_products >> arr_of_products[i].amount >> arr_of_products[i].price >> arr_of_products[i].day >> arr_of_products[i].month >> arr_of_products[i].name_reg >> arr_of_products[i].surname_reg;
			i++;
		}
		number_products = i;
	}
	fin.close();
}

void writeNewFileUsers(Users *rol, int &number_users)// перезапись файла с пользователями
{
	ofstream fout(file_users, ios::out);
	
	for (int i = 0; i < number_users; i++)
	{
		rol[i].role = 2;
		fout << endl << rol[i].login << " " << rol[i].pass << " " << rol[i].role;
	}
	fout.close();
}

void writeEndFileUsers(Users user)// дозапись в файл с пользователями
{
	ofstream fout(file_users, ios::app);
	cout << "введите логин: ";
	cin >> user.login;
	cout << "введите пароль: ";
	cin >> user.pass;
	user.role = 2;
	fout << endl << user.login << " " << user.pass << " " << user.role;
	fout.close();
}

void readFileUsers(Users *rol, int &number_users) // чтение файла с пользователями
{
	ifstream fin_us(file_users, ios::in);
	if (!fin_us.is_open())
	{
		writeNewFileUsers(rol, number_users);
	}
		int i = 0;
		while (!fin_us.eof())
		{
			fin_us >> rol[i].login >> rol[i].pass >> rol[i].role;	
			i++;
		}
		number_users = i;
	
	fin_us.close();
}

void showArrUsers(Users *rol, int &number_users) // вывод массива с пользователями на экран
{
	for (int i = 0; i < number_users; i++)
	{
		cout << i + 1 << ". " << rol[i].login << " " << rol[i].pass << endl;
	}
}

void clearFileUsers()// форматирование файла с пользователями 
{
	ofstream fin_us(file_users, ios::trunc);
	if (!fin_us.is_open())
	{
		cout << "Данный файл не найден!" << endl;
	}
	fin_us.close();
}

void delFileUsers(Users *rol, int &number_users)// функция удаления учетной записи
{
	int k;
	cout << "введите номер учетной записи которую хотите удалить: ";
	do
	{
		cin >> k;
		if (cin.good())
		{
			for (int i = k - 1; i < number_users; i++)
			{
				rol[i].login = rol[i + 1].login;
				rol[i].pass = rol[i + 1].pass;
				rol[i].role = rol[i + 1].role;
			}
			number_users--;
			writeNewFileUsers(rol, number_users);
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Некоректный ввод! Потворите Ввод: ";
		}
	} while (true);
}

void sortPriceUpProducts(Products *arr_of_products, int &number_products)//сортировка по цене по возрастанию
{
	for (int i = 0; i < number_products; i++)
	{
		for (int j = 0; j < number_products - 1; j++)
		{
			if (arr_of_products[j + 1].price < arr_of_products[j].price)
			{
				swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
				swap(arr_of_products[j + 1].price, arr_of_products[j].price);
				swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
				swap(arr_of_products[j + 1].day, arr_of_products[j].day);
				swap(arr_of_products[j + 1].month, arr_of_products[j].month);
				swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
				swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
			}
		}
	}
}

void sortPriceDownProducts(Products *arr_of_products, int &number_products)//сортировка по цене по убыванию
{
	for (int i = 0; i < number_products; i++)
	{
		for (int j = 0; j < number_products - 1; j++)
		{
			if (arr_of_products[j + 1].price > arr_of_products[j].price)
			{
				swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
				swap(arr_of_products[j + 1].price, arr_of_products[j].price);
				swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
				swap(arr_of_products[j + 1].day, arr_of_products[j].day);
				swap(arr_of_products[j + 1].month, arr_of_products[j].month);
				swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
				swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
			}
		}
	}
}

void sortNameProducts(Products *arr_of_products, int &number_products) // сортировка по алфавиту
{
	for (int i = 0; i < number_products; i++)
	{
		for (int j = 0; j < number_products - 1; j++)
		{
			if (arr_of_products[j + 1].name_products.at(0) < arr_of_products[j].name_products.at(0))
			{
				swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
				swap(arr_of_products[j + 1].price, arr_of_products[j].price);
				swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
				swap(arr_of_products[j + 1].day, arr_of_products[j].day);
				swap(arr_of_products[j + 1].month, arr_of_products[j].month);
				swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
				swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
			}
			else if (arr_of_products[j + 1].name_products.at(0) == arr_of_products[j].name_products.at(0))
			{
				if (arr_of_products[j + 1].name_products.at(1) < arr_of_products[j].name_products.at(1))
				{
					swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
					swap(arr_of_products[j + 1].price, arr_of_products[j].price);
					swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
					swap(arr_of_products[j + 1].day, arr_of_products[j].day);
					swap(arr_of_products[j + 1].month, arr_of_products[j].month);
					swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
					swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
				}
			}
		}
	}
}

void sortAmountUpProducts(Products *arr_of_products, int &number_products)//сортировка по кол-ву по возрастанию
{
	for (int i = 0; i < number_products; i++)
	{
		for (int j = 0; j < number_products - 1; j++)
		{
			if (arr_of_products[j + 1].amount < arr_of_products[j].amount)
			{
				swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
				swap(arr_of_products[j + 1].price, arr_of_products[j].price);
				swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
				swap(arr_of_products[j + 1].day, arr_of_products[j].day);
				swap(arr_of_products[j + 1].month, arr_of_products[j].month);
				swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
				swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
			}
		}
	}
}

void sortAmountDownProducts(Products *arr_of_products, int &number_products)//сортировка по кол-ву по убыванию
{
	for (int i = 0; i < number_products; i++)
	{
		for (int j = 0; j < number_products - 1; j++)
		{
			if (arr_of_products[j + 1].amount > arr_of_products[j].amount)
			{
				swap(arr_of_products[j + 1].name_products, arr_of_products[j].name_products);
				swap(arr_of_products[j + 1].price, arr_of_products[j].price);
				swap(arr_of_products[j + 1].amount, arr_of_products[j].amount);
				swap(arr_of_products[j + 1].day, arr_of_products[j].day);
				swap(arr_of_products[j + 1].month, arr_of_products[j].month);
				swap(arr_of_products[j + 1].name_reg, arr_of_products[j].name_reg);
				swap(arr_of_products[j + 1].surname_reg, arr_of_products[j].surname_reg);
			}
		}
	}
}

void searchPriceProducts(Products *arr_of_products, int &number_products) // поиск по цене
{
	double begin = 0, end = 0;
	int z = 0;
	cout << "Введите диапозон поиска от: ";
	begin = number_double(begin);
	cout << "\t\t\tдо: ";
	end = number_double(end);
	for (int i = 0; i < number_products; i++)
	{
		if (arr_of_products[i].price >= begin && arr_of_products[i].price <= end)
		{

			showOneProductsArray(arr_of_products, i);
			cout << "----------------------------------------------------------------" << endl;
			z++;
		}
		
	}
	if (z == 0)
	{
		cout << "\n\t\t---------------------- ТАКИХ ПРОДУКТОВ НЕТ ----------------------" <<endl<< endl;
	}
}



void searchAmountProducts(Products *arr_of_products, int &number_products)  // поиск по кол-ву
{
	int begin, end;
	int z = 0;
	cout << "Введите диапозон поиска от: ";
	cin >> begin;
	cout << "\t\t\tдо: ";
	cin >> end;
	for (int i = 0; i < number_products; i++)
	{
		if (arr_of_products[i].amount >= begin && arr_of_products[i].amount <= end)
		{

			showOneProductsArray(arr_of_products, i);
			cout << "----------------------------------------------------------------" << endl;
			z++;
		}

	}
	if (z == 0)
	{
		cout << "\n\t\t---------------------- ТАКИХ ПРОДУКТОВ НЕТ ----------------------" << endl << endl;
	}
}

void searchNameProducts(Products *arr_of_products, int &number_products) // поиск по названию продукта
{
	string name;
	int z = 0;
	cout << "Введите название искомого продукта: ";
	cin >> name;
	for (int i = 0; i < number_products; i++)
	{
		if (arr_of_products[i].name_products == name)
		{

			showOneProductsArray(arr_of_products, i);
			cout << "----------------------------------------------------------------" << endl;
			z++;
		}

	}
	if (z == 0)
	{
		cout << "\n\t\t---------------------- ТАКИХ ПРОДУКТОВ НЕТ ----------------------" << endl << endl;
	}
}

void changeProductsArray(Products *arr_of_products, int i) // изменение одного из описаний продукта
{
	string nameproducts, nameReg, surnameReg;
	int num, price1, amount1, day1, month1;
	cout << "Изменить:\n1. Название\n2. Цену за единицу\n3. Колличество\n4. Дату поступления\n5. ФИО зарегистрировавшего товар\nВаш выбор: ";
	do
	{
		cin >> num;
		if (cin.good())
		{
			switch (num)
			{
			case 1:
				cout << "Введите новое название продукта: ";
				cin >> nameproducts;
				arr_of_products[i - 1].name_products = nameproducts;
				break;
			case 2:
				cout << "Введите новую цену за единицу продукта: ";
				cin >> price1;
				arr_of_products[i - 1].price = price1;
				break;
			case 3:
				cout << "Введите новое кол-во продукта: ";
				cin >> amount1;
				arr_of_products[i - 1].amount = amount1;
				break;
			case 4:
				cout << "Введите новую дату - день: ";
				day1 = inputNumber(1, 30);
				arr_of_products[i - 1].day = day1;
				cout << "\t\t\tмесяц: ";
				month1 = inputNumber(1, 12);
				arr_of_products[i - 1].month = month1;
				break;
			case 5:
				cout << "Введите новое имя: ";
				cin >> nameReg;
				arr_of_products[i - 1].name_reg = nameReg;
				cout << "\t\t\tФамилию: ";
				cin >> surnameReg;
				arr_of_products[i - 1].surname_reg = surnameReg;
				break;
			}
			cout << "----------------------------------------- ПРОДУКТ ИЗМЕНЁН -----------------------------------------" << endl;
			showOneProductsArray(arr_of_products, i - 1);
			break;
		}
		else
		{
			cin.clear();
			cin.ignore();
			cout << "Некоректный ввод! Повторите ввод: ";
		}
	} while (true);
	
}

void indTask(Products *arr_of_products, int &number_products) // индивидуальное задание
{
	sortNameProducts(arr_of_products, number_products);
	int x, today_day, today_month, today_amount_day, z = 0, amount_day_product;
	double y; // цена
	cout << "Введите сегодняшнее число - день: ";
	today_day = inputNumber(1, 30);
	cout << "\t\t\t   месяц:";
	today_month = inputNumber(1, 12);
	today_amount_day = today_month * 30 + today_day; // перевод в дни сегодняшней даты
	cout << "Введите кол-во месяцев: ";
	x = inputNumber(1, 12);
	x = x * 30; // перевод в дни введенных месяцев
	cout << "Введите стоимость: ";
	cin >> y;
	for (int i = 0; i < number_products; i++)
	{
		amount_day_product = arr_of_products[i].month * 30 + arr_of_products[i].day; // перевод в дни даты поступления продукта на склад
		if (today_amount_day - amount_day_product > x && arr_of_products[i].price > y)
		{
			showOneProductsArray(arr_of_products, i);
			z++;
		}
	}
	if (z == 0)
	{
		cout << "Продукты подходящие по данным критериям отсутствуют!" << endl;
	}
}

void enterUser(Products *arr_of_products, int &number_products)// меню юзера
{
	cout << "________________________________________| Вы вошли как пользователь |________________________________________" << endl;
	int choice, choice_0, choice_1, exit;
	do
	{
		exit = 0;
		readFileProducts(arr_of_products, number_products);
		while (true)
		{
			 
			cout << "Вам доступны следующие действия:\n1. Список продукции\n2. Сортировка\n3. Поиск\n4. Индивидуальное задание\n5. Выход из программы\nВаш выбор: ";
			cin >> choice;
			if (cin.good())
			{
				system("cls");
				break;
			}
			else
			{
				cin.clear();
				cin.ignore();
				system("cls");
				cout << "Ввод некоректный! Повторите ввод! " << endl;
			}
		}
		switch (choice)
		{
		case 1: // вывод списка продуктов на экран
			cout << "Список имеющихся продуктов:" << endl;
			showProductsArray(arr_of_products, number_products);
			break;
		case 2: // сортировка
			cout << "Выберете тип сортировки:\n1. По цене\n2. По количеству\n3. По алфавиту\n4. Выход в главное меню\nВаш выбор: ";
			cin >> choice_0;
			if (choice_0 != 1 && choice_0 != 2 && choice_0 != 3 && choice_0 != 4)
			{
				do
				{
					cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl << "Ваш выбор: ";
					cin >> choice_0;
				} while (choice_0 != 1 && choice_0 != 2 && choice_0 != 3 && choice_0 != 4);
			}
			switch (choice_0)
			{
			case 1: // сортировка по цене
				cout << "Выберете метод сортировки:\n1. По возрастанию\n2. По убыванию\nВаш выбор: ";
				cin >> choice_1;
				switch (choice_1)
				{
				case 1: // по возрастанию
					sortPriceUpProducts(arr_of_products, number_products);
					cout << "--------------------------------------- СПИСОК ОТСОРТИРОВАН ---------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				case 2: // по убыванию
					sortPriceDownProducts(arr_of_products, number_products);
					cout << "--------------------------------------- СПИСОК ОТСОРТИРОВАН ---------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				}
				break;
			case 2: // сортировка по кол-ву
				cout << "Выберете метод сортировки:\n1. По возрастанию\n2. По убыванию\nВаш выбор: ";
				cin >> choice_1;
				switch (choice_1)
				{
				case 1: // по возрастанию
					sortAmountUpProducts(arr_of_products, number_products);
					cout << "--------------------------------------- СПИСОК ОТСОРТИРОВАН ---------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				case 2: // по убыванию
					sortAmountDownProducts(arr_of_products, number_products);
					cout << "--------------------------------------- СПИСОК ОТСОРТИРОВАН ---------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				}
				break;

			case 3: // сортировка оп алфавиту
				sortNameProducts(arr_of_products, number_products);
				cout << "--------------------------------------- СПИСОК ОТСОРТИРОВАН ---------------------------------------" << endl;
				showProductsArray(arr_of_products, number_products);
				break;
			case 4:
				exit = 1;
				system("cls");
				break;
			}
			break;
		case 3:  // поиск
			cout << "Выберете тип поиска:\n1. По названию продукта\n2. По цене\n3. По количеству\n4.Выход в главное меню\nВаш выбор: ";
			choice_0 = inputNumber(1, 4);
			switch (choice_0)
			{
			case 1: // по названию
				searchNameProducts(arr_of_products, number_products);
				break;
			case 2:  // по цене
				searchPriceProducts(arr_of_products, number_products);
				break;
			case 3:  // по кол-ву
				searchAmountProducts(arr_of_products, number_products);
				break;
			case 4: // выход
				exit = 1;
				system("cls");
				break;
			}
			break;
		case 4:
			indTask(arr_of_products, number_products);
			break;
		case 5: // выход из программы
			exit = 2;
			break;
		}
		if (choice < 1 || choice > 5)
		{
			cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl;
			continue;
		}
			if (exit != 1 && exit != 2)
			{
				cout << "Нажмите 1 чтобы выйти в главное меню или нажмите 2 чтобы выйти из программы: ";
				cin >> exit;
				if (exit != 1 && exit != 2) // на случай некоректного ввода
				{
					do
					{
						system("cls");
						cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl;
						cout << "Нажмите 1 чтобы выйти в главное меню или нажмите 2 чтобы выйти из программы: ";
						cin >> exit;
					} while (exit != 1 && exit != 2);
				}
				system("cls");
			}
		
	} while (exit != 2);
}

void enterAdmin(Products *arr_of_products, int &number_products, Users *rol, int &number_users, Users user)// меню админа
{
	/*generateProductsArray(arr_of_products, number_products);
	writeFileProducts(arr_of_products, number_products);*/
	int choice, exit;
	int choice_0, choice_1;
	cout << "________________________________________| Вы вошли как Администратор |________________________________________" << endl << endl;
	do
	{
		exit = 0;
		
		
		cout << "Вам доступны следующие действия:\n1. Просмотр информации о продукции.\n2. Изменение информации о продукции\n3. Просмотр и изменение учетных записей пользователей.\n4. Выход из программы.\nВаш выбор: ";
		readFileProducts(arr_of_products, number_products);
		cin >> choice;
		switch (choice)// привязка действий к цифрам 1-4
		{
		case 1: // просмотр информации о продукции
			system("cls");
			showProductsArray(arr_of_products, number_products);
			break;
		case 2: // Изменение информации о продукции
			system("cls");
			do
			{
				
				cout << "Нажмите:\n1. Чтобы добавить новый продукт\n2. Чтобы удалить уже существующий\n3. Чтобы очистить список продукции\n4. Чтобы изменить одно из значений\n5. Чтобы выйти в главное меню\nВаш выбор: ";
				cin >> choice_0;
				switch (choice_0)
				{
				case 1:
					addProductsArray(arr_of_products, number_products);
					system("cls");
					cout << "--------------------------------------- ПРОДУКТ ДОБАВЛЕН ---------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				case 2:

					showProductsArray(arr_of_products, number_products);
					delProductsArray(arr_of_products, number_products);
					system("cls");
					cout << "----------------------------------------- ПРОДУКТ УДАЛЁН -----------------------------------------" << endl;
					showProductsArray(arr_of_products, number_products);
					break;
				case 3:
					clearFileProducts();
					break;
				case 4:
					system("cls");
					showProductsArray(arr_of_products, number_products);
					cout << "Выберете продукт (введите номер продукта): ";
					choice_1 = inputNumber(1, number_products);
					changeProductsArray(arr_of_products, choice_1);

					break;
				case 5:
					exit = 1;
					break;
				}
				if (choice_0 < 1 || choice_0>5)
				{
					system("cls");
					cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl;
				}
			} while (choice_0<1 || choice_0>5);
			break;
		case 3: //  Просмотр и изменение учетных записей пользователей
			system("cls");
			cout << "Все имеющиеся учетные записи:" << endl;
			readFileUsers(rol, number_users);
			showArrUsers(rol, number_users);
			cout << "----------------------------------------------------------------------------" << endl;
			cout << "Нажмите:\n1. Чтобы удалить из списка какую-либо учетную запись\n2. Чтобы очистить список\n3. Чтобы добавить нового пользователя\n4. Чтобы выйти в главное меню\nВаш выбор: ";
			choice_0 = inputNumber(1, 4);
			
			switch (choice_0)
			{
			case 1:
				delFileUsers(rol, number_users);
				system("cls");
				cout << "------------------------------------- УЧЁТНАЯ ЗАПИСЬ УДАЛЕНА -------------------------------------" << endl;
				readFileUsers(rol, number_users);
				break;
			case 2:
				clearFileUsers();
				cout << "--------------------------------------- СПИСОК ОЧИЩЕН ---------------------------------------" << endl;
				break;
			case 3:
				writeEndFileUsers(user);
				cout << "--------------------------------------- ПОЛЬЗОВАТЕЛЬ ДОБАВЛЕН ---------------------------------------" << endl;
				break;
			case 4:
				exit = 1;
				break;
			}
			break;
		case 4: // выход их программы
			exit = 2;
			break;
		}
		
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
		{
			system("cls");
			cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl;
			continue;
		}
		if (exit != 1 && exit != 2)
		{
			cout << "Нажмите 1 чтобы выйти в главное меню или нажмите 2 чтобы выйти из программы: ";
			cin >> exit;
			if (exit != 1 && exit != 2) // на случай некоректного ввода
			{
				do
				{
					system("cls");
					cout << "\t\t\t\t|ВЫ ВВЕЛИ НЕКОРЕКТНЫЕ ДАННЫЕ! ПОВТОРИТЕ ВВОД!|" << endl;
					cout << "Нажмите 1 чтобы выйти в главное меню или нажмите 2 чтобы выйти из программы: ";
					cin >> exit;
				} while (exit != 1 && exit != 2);
			}
			system("cls");
		}
		writeFileProducts(arr_of_products, number_products);
		system("cls");
	} while (exit != 2);
}

void authorization(Products *arr_of_products, int &number_products, Users user, Users *rol) // авторизация
{
	
	bool flag = false;
	int number_users = 0;
	
	int exxit;
	
	do
	{
		exxit = 0;
		system("cls");
		cout << "введите логин: ";
		cin >> user.login;
		cout << "введите пароль: ";
		cin >> user.pass;
		user.role = 0;
		if (user.login == "admin" || user.pass == "admin")
		{
			user.role = 1;
		}
		else
		{
			readFileUsers(rol, number_users);
			for (int i = 0; i < number_users; i++)
			{
				if (user.login == rol[i].login && user.pass == rol[i].pass)
				{
					user.role = 2;
				}
			}
			if (user.role != 2)
			{
				do
				{
					cout << "Вы ввели неверные данные! Нажмите 1 чтобы повторить ввод или 2 чтобы выйти из программы: ";
					cin >> exxit;
				} while (exxit != 2 && exxit != 1);
			}
		}
		
	} while (exxit == 1);
	if (exxit != 2)
	{
		flag = isCheck(user);
		system("cls");
		if (flag == true)
		{
			
			enterUser(arr_of_products, number_products);
		}
		else
		{
			enterAdmin(arr_of_products, number_products, rol, number_users, user);
		}
	}
}