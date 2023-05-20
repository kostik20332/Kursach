#include <windows.h>
#include <iostream>
#include <conio.h>
#include "header.h"

using namespace std;

string NameEnter()
{
	string nameA;
	cout << horizontalGap << "������� ���� ���: ";
	cin >> nameA;
	while (!StringCheck(nameA))
	{
		cin >> nameA;
	}
	while (UserSearchWithoutEnter(nameA))
	{
		cout << horizontalGap << "������������ � ����� ������ ��� ����������!" << endl;
		cout << horizontalGap << "������� ������ ���: " << endl;
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
		cout << horizontalGap << "������������ � ����� ������ �� ����������!" << endl;
		nameA = "0";
		exitOnEnter();
	}
	return nameA;
}

string PhoneNumberEnter()
{
	string phoneNumber;
	cout << endl << horizontalGap << "������� ����� ��������: ";
	cin >> phoneNumber;
	while (phoneNumber.substr(0, 4) != "+375" || phoneNumber.length() != 13 || !PhoneNumberCheck(phoneNumber))
	{
		cout << horizontalGap << "����� �������� ����� ��������!" << endl;
		cout << horizontalGap << "������� ����� ��������: ";
		cin >> phoneNumber;
	}
	return phoneNumber;
}

int DataEnter() 
{
	int data;
	cout << horizontalGap << "������� ����� ������ : ";
	cin >> data;
	while (data < 0 || data > 31)
	{
		cout << horizontalGap << "����� ����������� ������ ����!" << endl;
		cout << horizontalGap << "������� ����� �� 1 �� 31 : ";
		cin >> data;
	}
	return data;
}

int MounthEnter()
{
	int data;
	cout << horizontalGap << "������� ����� ������ : ";
	cin >> data;
	while (data < 0 || data > 12)
	{
		cout << horizontalGap << "����� ����������� ����� ������!" << endl;
		cout << horizontalGap << "������� ����� �� 1 �� 12 : ";
		cin >> data;
	}
	return data;
}

int YearEnter()
{
	int data;
	cout << horizontalGap << "������� ��� : ";
	cin >> data;
	while (data < 2000 || data > 2100)
	{
		cout << horizontalGap << "����� ����������� ���!" << endl;
		cout << horizontalGap << "������� ����������� ��� : ";
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
		cout << horizontalGap << "������� ����� ����������� �����: ";
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
			cout << horizontalGap << "����� �������� ����� ����������� �����!" << endl;
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
		cout << horizontalGap << "������ �������� ��������!" << endl;
		cout << horizontalGap << "��������� �������: ";
	}
	return age;
}

int AgeEnter()
{
	int age;
	cout << horizontalGap << "������� �������: ";
	while (!(cin >> age) || age < 1 || age > 100)
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << horizontalGap << "����� �������� �������!" << endl;
		cout << horizontalGap << "������� ��� �������: ";
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
		if ((name[i] >= '�') && (name[i] <= '�')
			|| (name[i] >= 'a') && (name[i] <= 'z')
			|| (name[i] >= '�') && (name[i] <= '�')
			|| (name[i] >= 'A') && (name[i] <= 'Z'))
		{

		}
		else
		{
			cout << horizontalGap << "����� ������������ ������!" << endl;
			cout << horizontalGap << "������� ����� �� ����: ";
			return false;
		}
	}
	return true;
}

void exitOnEnter()
{
	char enter;
	cout << horizontalGap << "�������� Enter ��� ������ �����!" << endl;
	cin.get(enter);
	do
	{
		cin.get(enter);
	} while (enter != '\n');
}

void CursorSet(int x, int y) 
{
	COORD position = { x, y}; //������� x � y
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
	//cout << "������� ������: ";
	string pass;
	int ch = 0;// ���������� ��� �������.
	bool isPasswordStrength = true, aFound = false, Afound = false, numberFound = false;
	while (true)// �������� ������������ �����.
	{
		ch = _getch();// �������� ��� ������� ������� � ����������.
		if (ch == 13)// ��������� Enter �� ���������� �����.
		{
			break;// ���������� �����.
		}
		if (ch == 8)// ��������� Backspace �� �������� ��������.
		{
			cout << char(8) << ' ' << char(8);
			if (!pass.empty())
			{
				pass.erase(pass.length() - 1);//�������� ���������� ������� ������(������� ������� ������������ ��� ��������)
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
	//cout << "������� ������: ";
	string pass;
	int ch = 0;// ���������� ��� �������.
	bool isPasswordStrength = true, aFound = false, Afound = false, numberFound = false;
	while (true)// �������� ������������ �����.
	{
		ch = _getch();// �������� ��� ������� ������� � ����������.
		if (ch == 13)// ��������� Enter �� ���������� �����.
		{
			break;// ���������� �����.
		}
		if (ch == 8)// ��������� Backspace �� �������� ��������.
		{
			cout << char(8) << ' ' << char(8);
			if (!pass.empty())
			{
				pass.erase(pass.length() - 1);//�������� ���������� ������� ������(������� ������� ������������ ��� ��������)
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
			if ((pass[i] >= '�') && (pass[i] <= '�') || (pass[i] >= 'a') && (pass[i] <= 'z'))
			{
				aFound = true;
			}
			else if ((pass[i] >= '�') && (pass[i] <= '�')|| (pass[i] >= 'A') && (pass[i] <= 'Z'))
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
		cout << endl << horizontalGap << "��� ������ ������� ������!" << endl
			<< horizontalGap << "������������� �������� ��� �� ����� ������� � ������ ��������!";
	}
	return Incription(pass);
}