#include <windows.h>
#include <iostream>
#include <conio.h>
#include "header.h"

using namespace std;

string NameEnter()
{
	string nameA;
	cout << horizontalGap << "Введите ваше имя: ";
	cin >> nameA;
	while (!StringCheck(nameA))
	{
		cin >> nameA;
	}
	while (UserSearchWithoutEnter(nameA))
	{
		cout << horizontalGap << "Пользователь с таким именем уже существует!" << endl;
		cout << horizontalGap << "Введите другое имя: " << endl;
		cin >> nameA;
		while (!StringCheck(nameA))
		{
			cin >> nameA;
		}
	}
	return nameA;
}

string NameEnterForEdit()
{
	string nameA;
	cin >> nameA;
	while (!StringCheck(nameA))
	{
		cin >> nameA;
	}
	if (!UserSearchWithoutEnter(nameA))
	{
		cout << horizontalGap << "Пользователя с таким именем не существует!" << endl;
		nameA = "0";
		exitOnEnter();
	}
	return nameA;
}

string PhoneNumberEnter()
{
	string phoneNumber;
	cout << endl << horizontalGap << "Введите номер телефона: ";
	cin >> phoneNumber;
	while (phoneNumber.substr(0, 4) != "+375" || phoneNumber.length() != 13 || !PhoneNumberCheck(phoneNumber))
	{
		cout << horizontalGap << "Введён неверный номер телефона!" << endl;
		cout << horizontalGap << "Введите номер телефона: ";
		cin >> phoneNumber;
	}
	return phoneNumber;
}

int DataEnter() 
{
	int data;
	cout << horizontalGap << "Введите число месяца : ";
	cin >> data;
	while (data < 0 || data > 31)
	{
		cout << horizontalGap << "Введён некоректный формат даты!" << endl;
		cout << horizontalGap << "Введите число от 1 до 31 : ";
		cin >> data;
	}
	return data;
}

int MounthEnter()
{
	int data;
	cout << horizontalGap << "Введите номер месяца : ";
	cin >> data;
	while (data < 0 || data > 12)
	{
		cout << horizontalGap << "Введён некоректный номер месяца!" << endl;
		cout << horizontalGap << "Введите число от 1 до 12 : ";
		cin >> data;
	}
	return data;
}

int YearEnter()
{
	int data;
	cout << horizontalGap << "Введите год : ";
	cin >> data;
	while (data < 2000 || data > 2100)
	{
		cout << horizontalGap << "Введён некоректный год!" << endl;
		cout << horizontalGap << "Введите сегодняшний год : ";
		cin >> data;
	}
	return data;
}

string EmailEnter()
{
	string email;
	bool dogFound = false, dotFound = false, firstLetterFound = false, middleLetterFound = false, lastLetterFound = false;
	while (!dogFound || !dotFound || !firstLetterFound || !middleLetterFound || !lastLetterFound)
	{
		dogFound = dotFound = firstLetterFound = middleLetterFound = lastLetterFound = false;
		cout << horizontalGap << "Введите адрес электронной почты: ";
		cin >> email;
		for (int i = 0; i < email.length(); i++)
		{
			if (email[i] == '@')
			{
				dogFound = true;
			}
			else if (email[i] == '.' && dogFound)
			{
				dotFound = true;
			}
			else if (((email[i] >= 'a') && (email[i] <= 'z') || (email[i] >= 'A') && (email[i] <= 'Z')) && (!firstLetterFound))
			{
				firstLetterFound = true;
			}
			else if (((email[i] >= 'a') && (email[i] <= 'z') || (email[i] >= 'A') && (email[i] <= 'Z')) && (dogFound) && (!dotFound))
			{
				middleLetterFound = true;
			}
			else if (((email[i] >= 'a') && (email[i] <= 'z') || (email[i] >= 'A') && (email[i] <= 'Z')) && (dogFound) && (dotFound))
			{
				lastLetterFound = true;
				break;
			}
		}
		if (!dogFound || !dotFound || !firstLetterFound || !middleLetterFound || !lastLetterFound)
		{
			cout << horizontalGap << "Введён неверный адрес электронной почты!" << endl;
		}
	}
	return email;
}

int IntEnter(string vvodRequest)
{
	int age;
	cout << horizontalGap << vvodRequest;
	while (!(cin >> age) || age < 1 || age > 100)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << horizontalGap << "Введёно неверное значение!" << endl;
		cout << horizontalGap << "Повторите попытку: ";
	}
	return age;
}

int AgeEnter()
{
	int age;
	cout << horizontalGap << "Введите возраст: ";
	while (!(cin >> age) || age < 1 || age > 100)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << horizontalGap << "Введён неверный возраст!" << endl;
		cout << horizontalGap << "Введите ваш возраст: ";
	}
	return age;
}

string StringEnter()
{
	string nameA;
	cin >> nameA;
	while (!StringCheck(nameA))
	{
		cin >> nameA;
	}
	return nameA;
}

bool StringCheck(string name)
{
	for (int i = 0; i < name.size(); i++)
	{
		if ((name[i] >= 'а') && (name[i] <= 'я')
			|| (name[i] >= 'a') && (name[i] <= 'z')
			|| (name[i] >= 'А') && (name[i] <= 'Я')
			|| (name[i] >= 'A') && (name[i] <= 'Z'))
		{

		}
		else
		{
			cout << horizontalGap << "Введён недопустимый символ!" << endl;
			cout << horizontalGap << "Введите слово из букв: ";
			return false;
		}
	}
	return true;
}

void exitOnEnter()
{
	char enter;
	cout << horizontalGap << "Нажимите Enter для выхода назад!" << endl;
	cin.get(enter);
	do
	{
		cin.get(enter);
	} while (enter != '\n');
}

void CursorSet(int x, int y) 
{
	COORD position = { x, y}; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}

bool PhoneNumberCheck(string phoneNumber)
{
	for (size_t i = 1; i < phoneNumber.length(); i++)
	{
		if (!isdigit(phoneNumber[i]))
		{
			return false;
		}
	}
	return true;
}

string PasswordEntering()
{
	//cout << "Введите пароль: ";
	string pass;
	int ch = 0;// Переменная для символа.
	bool isPasswordStrength = true, aFound = false, Afound = false, numberFound = false;
	while (true)// Создание бесконечного цикла.
	{
		ch = _getch();// Помещаем код нажатой клавиши в переменную.
		if (ch == 13)// Установка Enter на прерывание цикла.
		{
			break;// Прерывание цикла.
		}
		if (ch == 8)// Установка Backspace на удаление символов.
		{
			cout << char(8) << ' ' << char(8);
			if (!pass.empty())
			{
				pass.erase(pass.length() - 1);//удаление последнего символа строки(символа который записывается при удалении)
			}
		}
		else
		{
			cout << '*';
			pass += (char)ch;
		}
	}
	return Incription(pass);
}

string PasswordEnteringForRegistration()
{
	//cout << "Введите пароль: ";
	string pass;
	int ch = 0;// Переменная для символа.
	bool isPasswordStrength = true, aFound = false, Afound = false, numberFound = false;
	while (true)// Создание бесконечного цикла.
	{
		ch = _getch();// Помещаем код нажатой клавиши в переменную.
		if (ch == 13)// Установка Enter на прерывание цикла.
		{
			break;// Прерывание цикла.
		}
		if (ch == 8)// Установка Backspace на удаление символов.
		{
			cout << char(8) << ' ' << char(8);
			if (!pass.empty())
			{
				pass.erase(pass.length() - 1);//удаление последнего символа строки(символа который записывается при удалении)
			}
		}
		else
		{
			cout << '*';
			pass += (char)ch;
		}
	}
	if (pass.length() < 8) 
	{
		isPasswordStrength = false;
	}
	else
	{
		for (int i = 0; i < pass.length(); i++)
		{
			if ((pass[i] >= 'а') && (pass[i] <= 'я') || (pass[i] >= 'a') && (pass[i] <= 'z'))
			{
				aFound = true;
			}
			else if ((pass[i] >= 'А') && (pass[i] <= 'Я')|| (pass[i] >= 'A') && (pass[i] <= 'Z'))
			{
				Afound = true;
			}
			else if (pass[i] >= 0 && pass[i] <= 9)
			{
				numberFound = true;
			}
		}
		if (!numberFound || !Afound || !aFound)
		{
			isPasswordStrength = false;
		}
	}
	if (!isPasswordStrength)
	{
		cout << endl << horizontalGap << "Ваш пароль слишком слабый!" << endl
			<< horizontalGap << "Рекомендуется изменить его на более сложный в личном кабинете!";
	}
	return Incription(pass);
}