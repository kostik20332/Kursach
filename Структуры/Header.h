#define _CRT_SECURE_NO_WARNINGS
#define horizontalGap "                               "
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <io.h>
#include <fstream>

using namespace std;

class Person
{
private:
	string name;
	string password;
	string phoneNumber;
	string email;
	int age;
public:
	Person()//конструктор по умолчанию
	{
		age = 0;
		name = "0";
		password = "0";
		phoneNumber = "0";
		email = "0";
	}
	Person(string name, string password, string phoneNumber, string email, int age)
	{
		this->age = age;
		this->name = name;
		this->password = password;
		this->phoneNumber = phoneNumber;
		this->email = email;
	}
	virtual void PersonCreate(string nameA, string password, string phoneNumber, string email, int age) {}
	//Метод записи в файл объекта класса
	virtual void SaveToFile() {}
	//Метод чтения из файла в объект класса
	virtual bool ReadFromFile(int objectNumber) { return false; }
	virtual bool PersonEnter(int& badEnterCounter) { return false; }
	virtual bool ActivationGet() { return true; }
	virtual string PersonFileNameGet() { return " "; }
	virtual int ReturnSize() { return 1; }
	void Сopy(Person& ob)//конструктор копирования
	{
		age = ob.ageGet();
		name = ob.nameGet();
		password = ob.passwordGet();
		phoneNumber = ob.phoneNumberGet();
		email = ob.emailGet();
	}
	int ageGet()
	{
		return age;
	}
	void ageSet(int age)
	{
		this->age = age;
	}
	string nameGet()
	{
		return name;
	}
	void nameSet(string newName)
	{
		this->name = newName;
	}
	string emailGet()
	{
		return email;
	}
	void emailSet(string email)
	{
		this->email = email;
	}
	string phoneNumberGet()
	{
		return phoneNumber;
	}
	void phoneNumberSet(string phoneNumber)
	{
		this->phoneNumber = phoneNumber;
	}
	string passwordGet()
	{
		return password;
	}
	void passwordSet(string password)
	{
		this->password = password;
	}
	void InformationShow()
	{
		cout << horizontalGap << "Имя: " << name << endl
			<< horizontalGap << "Номер телефона: " << phoneNumber << endl
			<< horizontalGap << "Адрес электронной почты: " << email << endl
			<< horizontalGap << "Возраст: " << age << endl;
	}
};

string CorrectUsersInformation(string userName);
string PasswordEntering();
string PasswordEntering();
string NameEnter();
string PhoneNumberEnter();
string EmailEnter();
string NameEnterForEdit();
string Incription(string password);
string StringEnter();
string PasswordEnteringForRegistration();

void UserEnter();
void UserStatusChanging(string userName, bool activateUser);
void AllUsersView();
void DeleteUsers();
void DeleteUser(string userName);
void DeleteUserOrder(string userName, int zakazToDeleteNumber);
void exitOnEnter();
void CursorSet(int x, int y);
void ViewForPerson(Person* person, string name);
void DeleteUsersWithZakazs();
void AddProductWrite(int kolvo, int serialNumber);
void ViewAllProducts();
void IndividualTask();

bool StringCheck(string name);
bool PhoneNumberCheck(string phoneNumber);
bool StringCheck(string name);
bool PhoneNumberCheck(string phoneNumber);
bool UserSearchWithoutEnter(string userName);
bool PersonSearch(Person* person, string personName);

int AgeEnter();
int IntEnter(string vvodRequest);
int DataEnter();
int MounthEnter();
int YearEnter();

class Client : public Person
{
private:
	bool activation = false;
public:
	using Person::Person;
	Client()//конструктор по умолчанию
	{
		activation = false;
	}
	Client(Client& ob)//конструктор копирования
	{
		activation = ob.activation;
	}
	Client(string name, string password, string phoneNumber, string email, int age, bool activation)
	{
		this->activation = activation;
	}
	void Сopy(Client& ob)//конструктор копирования
	{
		activation = ob.ActivationGet();
	}
	bool ActivationGet() override
	{
		return activation;
	}
	void activationSet(bool activation)
	{
		this->activation = activation;
	}
	void Activation()
	{
		activation = true;
	}
	void Disactivation()
	{
		activation = false;
	}
	void PersonCreate(string nameA, string password, string phoneNumber, string email, int age) override
	{
		this->ageSet(age);
		this->nameSet(nameA);
		this->passwordSet(password);
		this->phoneNumberSet(phoneNumber);
		this->emailSet(email);
	}
	string PersonFileNameGet() override
	{
		string fileName = "Userslist";
		return fileName;
	}
	int ReturnSize() override
	{
		return sizeof(Client);
	}
	bool PersonEnter(int& badEnterCounter) override
	{
		if (!activation)
		{
			cout << horizontalGap << "Пользователь не активирован администратором!" << endl;
			return false;
		}
		string userPassword;
		cout << horizontalGap << "Введите пароль: ";
		userPassword = PasswordEntering();
		cout << endl;
		if (this->passwordGet() == userPassword)
		{
			system("cls");
			cout << horizontalGap << "Вход выполнен успешно!" << endl;
			badEnterCounter = 0;
			return true;
		}
		else
		{
			cout << horizontalGap << "Введён неверный пароль!" << endl;
			badEnterCounter++;
			if (badEnterCounter > 1)
			{
				cout << horizontalGap << "Вы превысили количество неправильных попыток!"
					<< endl << horizontalGap << "Подождите " << badEnterCounter * 5 << " секунд!" << endl;
				BlockInput(TRUE);
				Sleep(badEnterCounter * 5000);
				BlockInput(FALSE);
			}
			return false;
		}
	}
	void SaveToFile() override
	{
		string name = nameGet();
		string password = passwordGet();
		string phoneNumber = phoneNumberGet();
		string email = emailGet();
		int age = ageGet();
		ofstream outF("Userslist", ios::out | ios::app);
		if (!outF.is_open())
		{
			return;
		}
		int len = name.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < name.length(); i++)
		{
			outF.write((char*)&name[i], sizeof(name[i]));
		}
		len = password.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < password.length(); i++)
		{
			outF.write((char*)&password[i], sizeof(password[i]));
		}
		len = phoneNumber.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < phoneNumber.length(); i++)
		{
			outF.write((char*)&phoneNumber[i], sizeof(phoneNumber[i]));
		}
		len = email.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < email.length(); i++)
		{
			outF.write((char*)&email[i], sizeof(email[i]));
		}
		outF.write((char*)&age, sizeof(int));
		outF.write((char*)&activation, sizeof(bool));
		outF.close();
	}
	bool ReadFromFile(int objectNumber) override
	{
		string name = "";
		string password = "";
		string phoneNumber = "";
		string email = "";
		int age = 0;
		bool pointerOutOfRange = false;
		ifstream inF("Userslist", ios::in | ios::binary);
		if (!inF.is_open())
		{
			cout << horizontalGap << "Ошибка при открытии файла!" << endl;
			return false;
		}
		inF.seekg(0, ios::end);
		int fileEnd = inF.tellg();
		inF.seekg(0, ios::beg);
		int len, currentPos = 4;
		int i = 0;
		for (i = 0; i < objectNumber && currentPos < fileEnd; i++)
		{
			inF.read((char*)&len, sizeof(int));
			char c;
			name = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				name += c;
			}
			inF.read((char*)&len, sizeof(int));
			password = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				password += c;
			}
			inF.read((char*)&len, sizeof(int));
			phoneNumber = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				phoneNumber += c;
			}
			inF.read((char*)&len, sizeof(int));
			email = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				email += c;
			}
			inF.read((char*)&age, sizeof(int));
			inF.read((char*)&activation, sizeof(bool));
			currentPos = inF.tellg();
		}
		if (currentPos <= fileEnd && i == objectNumber && currentPos != -1)
		{
			pointerOutOfRange = true;
		}
		inF.close();
		this->ageSet(age);
		this->nameSet(name);
		this->passwordSet(password);
		this->phoneNumberSet(phoneNumber);
		this->emailSet(email);
		return pointerOutOfRange;
	}
};