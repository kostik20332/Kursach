#include "Header.h"

using namespace std;

class Admin : public Person
{
public:
	using Person::Person;
	
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
		string fileName = "Adminslist";
		return fileName;
	}
	int ReturnSize() override
	{
		return sizeof(Admin);
	}
	bool PersonEnter(int& badEnterCounter) override
	{
		string adminPassword;
		cout << horizontalGap << "Введите пароль: ";
		adminPassword = PasswordEntering();
		cout << endl;
		if (this->passwordGet() == adminPassword)
		{
			system("cls");
			cout << endl << horizontalGap << "Вход выполнен успешно!" << endl;
			badEnterCounter = 0;
			return true;
		}
		else
		{
			cout << endl << horizontalGap << "Введён неверный пароль!" << endl;
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
		ofstream outF("Adminslist", ios::out | ios::app);
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
		ifstream inF("Adminslist", ios::in | ios::binary);
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

bool PersonSearch(Person* person, string personName)
{
	bool personEnter = false, personFound = false;
	int static badEnterCounter = 0;
	int& counter = badEnterCounter;
	int i = 1;
	while (person[0].ReadFromFile(i))
	{
		if (person[0].nameGet() == personName)
		{
			personFound = true;
			if (!person[0].ActivationGet())
			{
				cout << horizontalGap << "Пользователь не активирован!" << endl;
				break;
			}
			string adminPassword;
			cout << horizontalGap << "Введите пароль: ";
			adminPassword = PasswordEntering();
			cout << endl;
			if (person[0].passwordGet() == adminPassword)
			{
				system("cls");
				cout << endl << horizontalGap << "Вход выполнен успешно!" << endl;
				badEnterCounter = 0;
				personEnter = true;
			}
			else
			{
				cout << endl << horizontalGap << "Введён неверный пароль!" << endl;
				badEnterCounter++;
				if (badEnterCounter > 1)
				{
					cout << horizontalGap << "Вы превысили количество неправильных попыток!"
						<< endl << horizontalGap << "Подождите " << badEnterCounter * 5 << " секунд!" << endl;
					BlockInput(TRUE);
					Sleep(badEnterCounter * 5000);
					BlockInput(FALSE);
				}
				personEnter = false;
			}
			break;
		}
		i++;
	}
	if (!personFound)
	{
		cout << horizontalGap << "Записи с таким именем не существует!" << endl;
	}
	if (!personEnter)
	{
		exitOnEnter();
	}
	return personEnter;
}

void ViewForPerson(Person* person, string personName)
{
	system("cls");
	cout << horizontalGap << "       Информация: " << endl;
	int i = 1;
	while (person[0].ReadFromFile(i))
	{
		if (person[0].nameGet() == personName)
		{
			person[0].InformationShow();
			break;
		}
		i++;
	}
	exitOnEnter();
	system("cls");
}

int ReturnAdminsAmount()
{
	Admin* admin = new Admin[1];
	int i = 1;
	while (admin[0].ReadFromFile(i))
	{
		i++;
	}
	delete[] admin;
	return i - 1;
}

int ReadFromFileInMas(Admin*& admin)
{
	int amount = ReturnAdminsAmount();
	admin = new Admin[amount];
	for (int i = 1; i <= amount; i++)
	{
		admin[i - 1].ReadFromFile(i);
	}
	return amount;
}

void WriteInFileFromMas(Person* person, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		person[i].SaveToFile();
	}
}

void DeleteAdmins()//удаление пользователей для перезаписи
{
	ofstream outfile;
	outfile.open("Adminslist", ofstream::out | ofstream::trunc);
	outfile.close();
}

string CorrectAdminsInformation(string userName)
{
	Admin* admin;
	int i, variant, newAge;
	string newName, newPassword, newPhoneNumber, newEmail;
	string returnParam = "0";
	int amount = ReadFromFileInMas(admin);
	for (int i = 0; i < amount; i++)
	{
		if (admin[i].nameGet() == userName)
		{
			system("cls");
			cout << horizontalGap << "Выберите личные данные для редактирования:" << endl;
			cout << horizontalGap << "1 - Редактировать имя" << endl;
			cout << horizontalGap << "2 - Редактировать пароль" << endl;
			cout << horizontalGap << "3 - Редактировать номер телефона" << endl;
			cout << horizontalGap << "4 - Редактировать адрес электронной почты" << endl;
			cout << horizontalGap << "5 - Редактировать возраст" << endl;
			cout << horizontalGap << "Для выхода введите другую цифру или символ" << endl;
			CursorSet(31, 7);
			cin >> variant;
			system("cls");
			switch (variant)
			{
			case 1:
				newName = NameEnter();
				admin[i].nameSet(newName);
				cout << horizontalGap << "Имя администратора изменено!" << endl;
				returnParam = newName;
				exitOnEnter();
				break;
			case 2:
				newPassword = PasswordEntering();
				admin[i].passwordSet(newPassword);
				cout << horizontalGap << "Пароль администратора изменён!" << endl;
				exitOnEnter();
				break;
			case 3:
				newPhoneNumber = PhoneNumberEnter();
				admin[i].phoneNumberSet(newPhoneNumber);
				cout << horizontalGap << "Номер телефона администратора изменён!" << endl;
				exitOnEnter();
				break;
			case 4:
				cout << horizontalGap << "Введите новый адрес электронной почты: " << endl;
				newEmail = EmailEnter();
				admin[i].emailSet(newEmail);
				exitOnEnter();
				break;
			case 5:
				newAge = AgeEnter();
				admin[i].ageSet(newAge);
				cout << horizontalGap << "Возраст администратора изменён!" << endl;
				exitOnEnter();
				break;
			default:
				
				break;
			}
			//exitOnEnter();
			break;
		}
	}
	DeleteAdmins();
	WriteInFileFromMas(admin, amount);
	delete[] admin;
	return returnParam;
}

void AddPerson(Person* person)
{
	string nameA, password, phoneNumber, email;
	int age;
	system("cls");
	nameA = NameEnter();
	cout << horizontalGap << "Введите пароль: ";
	password = PasswordEnteringForRegistration();
	phoneNumber = PhoneNumberEnter();
	email = EmailEnter();
	age = AgeEnter();
	person[0].PersonCreate(nameA, password, phoneNumber, email, age);
	person[0].SaveToFile();
	cout << horizontalGap << "Регистрация прошла успешно!" << endl;
	exitOnEnter();
}

bool AdminEnter()
{
	Admin* admin = new Admin[1];
	string adminName,userName,newName;
	int variant, zakazToDeleteNumber;
	system("cls");
	cout << horizontalGap << "        Вход\n";
	cout << horizontalGap << "Введите имя администратора: ";
	cin >> adminName;
	while (!StringCheck(adminName))
	{
		cin >> adminName;
	}

	if (PersonSearch(admin, adminName))
	{
		while (true)
		{
			system("cls");
			cout << horizontalGap << "        Личный кабинет" << endl;
			cout << horizontalGap << "1 - Просмотр личных данных" << endl;
			cout << horizontalGap << "2 - Редактирование личных данных" << endl;
			cout << horizontalGap << "3 - Редактирование данных пользователя" << endl;
			cout << horizontalGap << "4 - Регистрация нового пользователя" << endl;
			cout << horizontalGap << "5 - Активация пользователя" << endl;
			cout << horizontalGap << "6 - Блокировка пользователя" << endl;
			cout << horizontalGap << "7 - Вывод информации о всех пользователях" << endl;
			cout << horizontalGap << "8 - Вывод информации о конкретном пользователе" << endl;
			cout << horizontalGap << "9 - Удалить информацию о всех пользователях" << endl;
			cout << horizontalGap << "10 - Удалить информацию о конкретном пользователе" << endl;
			cout << horizontalGap << "11 - Удалить выполненный заказ пользователя" << endl;
			cout << horizontalGap << "12 - Просмотреть все выполненные заказы" << endl;
			cout << horizontalGap << "13 - Просмотреть заказы, выполненные конкретным цехом" << endl;
			cout << horizontalGap << "Для выхода из личного кабинета введите другую цифру или символ" << endl;
			CursorSet(31, 15);
			cin >> variant;
			switch (variant)
			{
			case 1:
			{
				delete[] admin;
				admin = new Admin[1];
				ViewForPerson(admin, adminName);
				break;
			}
			case 2:
				delete[] admin;
				admin = new Admin[1];
				newName = CorrectAdminsInformation(adminName);
				if (newName != "0")
				{
					adminName = newName;
				}
				break;
			case 3:
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для редактирования данных: ";
				userName = NameEnterForEdit();
				if (userName != "0")
				{
					CorrectUsersInformation(userName);
				}
				break;
			case 4:
			{
				Client* client = new Client[1];
				client[0].Activation();
				AddPerson(client);
				delete[] client;
				break;
			}
			case 5:
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для активации: ";
				userName = NameEnterForEdit();
				if(userName != "0")
				{
					UserStatusChanging(userName, true);
				}
				break;
			case 6:
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для блокировки: ";
				userName = NameEnterForEdit();
				if (userName != "0")
				{
					UserStatusChanging(userName, false);
				}
				break;
			case 7:
				AllUsersView();
				break;
			case 8:
			{
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для просмотра данных: ";
				userName = NameEnterForEdit();
				if (userName != "0")
				{
					Client* client = new Client[1];
					ViewForPerson(client, userName);
					delete[] client;
				}
				break;
			}
			case 9:
				DeleteUsersWithZakazs();
				cout << horizontalGap << "Все пользователи удалены!" << endl;
				exitOnEnter();
				break;
			case 10:
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для удаления: ";
				userName = NameEnterForEdit();
				if (userName != "0")
				{
					DeleteUser(userName);
				}
				break;
			case 11:
				system("cls");
				cout << horizontalGap << "Введите имя пользователя для удаления завершённого заказа: ";
				userName = NameEnterForEdit();
				if (userName != "0")
				{
					cout << horizontalGap << "Введите номер заказа для удаления: ";
					cin >> zakazToDeleteNumber;
					DeleteUserOrder(userName, zakazToDeleteNumber);
				}
				break;
			case 12:
				ViewAllProducts();
				break;
			case 13:
				IndividualTask();
				break;
			default:
				
				return 0;
			}
		}
	}
	delete[] admin;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string password;
	string text_in;
	string text_out;
	int variant, verticalGap = 0;
	while (true)
	{
		for (int i = 0; i < verticalGap; i++)
		{
			cout << endl;
		}
		system("cls");
		cout << horizontalGap << "          Меню" << endl;
		cout << horizontalGap << "1 - Вход пользователя" << endl;
		cout << horizontalGap << "2 - Вход администратора" << endl;
		cout << horizontalGap << "3 - Регистрация пользователя" << endl;
		cout << horizontalGap << "4 - Регистрация администратора" << endl;
		cout << horizontalGap << "Для выхода из программы введите другую цифру или символ" << endl;
		CursorSet(31, 6);
		cin >> variant;
		switch (variant)
		{
		case 1:
			UserEnter();
			break;
		case 2:
			AdminEnter();
			break;
		case 3:
		{
			Client* client = new Client[1];
			client[0].Disactivation();
			AddPerson(client);
			delete[] client;
			break;
		}
		case 4:
			system("cls");
			cout << horizontalGap << "Введите секретный код: ";
			password = PasswordEntering();
			cout << endl;
			if (password == "56789")
			{
				Admin* admin = new Admin[1];
				AddPerson(admin);
				delete[] admin;
			}
			else
			{
				cout << horizontalGap << "Введён неверный код!" << endl;
				exitOnEnter();
			}
			break;
		case 5:

			break;
		default:
			cout << horizontalGap << "Выход!";
			return 0;
		}
	}
}
