#include "header.h"

using namespace std;

class Zakaz
{
private:
	int zakazNumber;
	int serialNumberOfItem;
	int amount;
public:
	Zakaz()//конструктор по умолчанию
	{
		zakazNumber = 0;
		serialNumberOfItem = 0;
		amount = 0;
	}
	Zakaz(Zakaz& ob)//конструктор копирования
	{
		zakazNumber = ob.zakazNumber;
		serialNumberOfItem = ob.serialNumberOfItem;
		amount = ob.amount;
	}
	Zakaz(int serialNumberOfItem, int amount, int zakazNumber)
	{
		this->zakazNumber = zakazNumber;
		this->serialNumberOfItem = serialNumberOfItem;
		this->amount = amount;
	}
	void ParamsSet(int serialNumberOfItem, int amount, int zakazNumber)
	{
		this->zakazNumber = zakazNumber;
		this->serialNumberOfItem = serialNumberOfItem;
		this->amount = amount;
	}
	int serialNumberOfItemGet()
	{
		return serialNumberOfItem;
	}
	int amountGet()
	{
		return amount;
	}
	int zakazNumberGet()
	{
		return zakazNumber;
	}
	void zakazNumberDicrease()
	{
		zakazNumber--;
	}
	void Information()
	{
		cout << horizontalGap << "|        " << setw(7) << left << zakazNumber
			 << " |         " << setw(8) << left << serialNumberOfItem
			<< " |             " << setw(13) << left << amount << " | " << endl;
		cout << horizontalGap << "+----------------+------------------+---------------------------+" << endl;
	}
	void SaveToFile(string filename)
	{
		int zakazNumber = zakazNumberGet();
		int serialNumberOfItem = serialNumberOfItemGet();
		int amount = amountGet();
		ofstream outF(filename, ios::out | ios::app);
		if (!outF.is_open())
		{
			return;
		}
		outF.write((char*)&zakazNumber, sizeof(int));
		outF.write((char*)&serialNumberOfItem, sizeof(int));
		outF.write((char*)&amount, sizeof(int));
		outF.close();
	}
	bool ReadFromFile(string filename, int objectNumber)
	{
		int zakazNumber = 0;
		int serialNumberOfItem = 0;
		int amount = 0;
		bool pointerOutOfRange = false;
		ifstream inF(filename, ios::in | ios::binary);
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
			inF.read((char*)&zakazNumber, sizeof(int));
			inF.read((char*)&serialNumberOfItem, sizeof(int));
			inF.read((char*)&amount, sizeof(int));
			currentPos = inF.tellg();
		}
		if (currentPos <= fileEnd && i == objectNumber && currentPos != -1)
		{
			pointerOutOfRange = true;
		}
		inF.close();
		ParamsSet(serialNumberOfItem, amount, zakazNumber);
		return pointerOutOfRange;
	}
};

int ReturnUsersAmount()//получение количесва пользователей
{
	Client* client = new Client[1];
	int i = 1;
	while (client[0].ReadFromFile(i))
	{
		i++;
	}
	delete[]client;
	return i - 1;
}

int ReturnZakazsAmount(string userName)//получение количесва заказов пользователя
{
	Zakaz* zakaz = new Zakaz[1];
	int i = 1;
	while (zakaz[0].ReadFromFile(userName, i))
	{
		i++;
	}
	delete[]zakaz;
	return i - 1;
}

int ReadFromFileInMas(Client*& client)//чтение клиентов из файла
{
	int amount = ReturnUsersAmount();
	client = new Client[amount];
	for (int i = 1; i <= amount; i++)
	{
		client[i - 1].ReadFromFile(i);
	}
	return amount;
}

int ReadFromFileInMas(Zakaz*& zakaz, string userName)//чтение заказов из файла
{
	int amount = ReturnZakazsAmount(userName);
	zakaz = new Zakaz[amount];
	for (int i = 1; i <= amount; i++)
	{
		zakaz[i - 1].ReadFromFile(userName,i);
	}
	return amount;
}

void WriteInFileFromMas(Client* client, int amount)//запись клиентов в файл
{
	for (int i = 0; i < amount; i++)
	{
		client[i].SaveToFile();
	}
}

void WriteInFileFromMas(Zakaz*& zakaz, string userName, int amount)//запись заказов в файл
{
	for (int i = 0; i < amount; i++)
	{
		zakaz[i].SaveToFile(userName);
	}
}

void DeleteUser(string userName)//удаление пользователя
{
	Client* client = new Client[1];
	int amount = ReadFromFileInMas(client);
	if (amount > 0)
	{
		for (int i = 0; i < amount; i++)
		{
			if (client[i].nameGet() == userName)
			{
				for (int j = i; j < amount - 1; j++)
				{
					client[j] = client[j + 1];
				}
				break;
			}
		}
		DeleteUsers();
		WriteInFileFromMas(client, amount - 1);
		cout << horizontalGap << "Пользователь удалён!" << endl;
	}
	exitOnEnter();
	delete[]client;
}

void AddingUserOrder(string userName)//добавление заказа пользователя
{
	int serialNumberOfItem, amount, zakazNumber;
	system("cls");
	cout << horizontalGap << "Выберите номер нужной техники! " << endl;
	cout << horizontalGap << "1 - Карьерный самосвал" << endl;
	cout << horizontalGap << "2 - Самосвал повышенной проходимости" << endl;
	cout << horizontalGap << "3 - Погрузчик" << endl;
	cout << horizontalGap << "4 - Бульдозер" << endl;
	CursorSet(31, 5);
	cin >> serialNumberOfItem;
	if (serialNumberOfItem < 1 || serialNumberOfItem > 4)
	{
		cout << horizontalGap << "Введён неверный номер техники! " << endl;
		return;
	}
	cout << horizontalGap << "Введите желаемое количество: ";
	cin >> amount;
	zakazNumber = ReturnZakazsAmount(userName) + 1;
	Zakaz zakaz(serialNumberOfItem, amount, zakazNumber);
	zakaz.SaveToFile(userName);
	cout << horizontalGap << "Заказ оформлен успешно!" << endl;
	exitOnEnter();
}

void DeleteZakazs(string userName)//удаление всех заказов пользователя
{
	ofstream outfile;
	outfile.open(userName, ofstream::out | ofstream::trunc);
	outfile.close();
}

void DeleteUserOrder(string userName, int zakazToDeleteNumber)//удаление заказа пользователя
{
	Zakaz* zakaz = new Zakaz[1];
	Zakaz temp;
	bool zakazFound = false;
	int amount = ReadFromFileInMas(zakaz, userName);
	int i = 0;
	if (amount > 0)
	{
		for (i = 0; i < amount; i++)
		{
			if (zakaz[i].zakazNumberGet() == zakazToDeleteNumber)
			{
				zakazFound = true;
				for (int j = i; j < amount - 1; j++)
				{
					zakaz[j] = zakaz[j + 1];
					zakaz[j].zakazNumberDicrease();
				}
				break;
			}
		}
		DeleteZakazs(userName);
		WriteInFileFromMas(zakaz, userName, amount - 1);
		if(zakazFound)
		{
			//cout << horizontalGap << "Заказ удалён!" << endl;
			AddProductWrite(zakaz[i].amountGet(), zakaz[i].serialNumberOfItemGet());
		}
		else
		{
			cout << horizontalGap << "Не существует заказа с таким номером!" << endl;
		}
	}
	exitOnEnter();
	delete[]zakaz;
}

void QuickSort(string userName)// сортировка заказов
{
	Zakaz* zakaz = new Zakaz[1];
	Zakaz temp;
	int amount = ReadFromFileInMas(zakaz, userName);
	if(amount > 0)
	{
		int measure1[100], measure2[100], ind = 0;
		measure1[ind] = 0;
		measure2[ind] = amount - 1;
		int i = 0, j = amount - 1, left, right;
		int x = zakaz[amount / 2].zakazNumberGet();
		while (ind != -1)
		{
			left = measure1[ind];
			right = measure2[ind];
			ind--;
			while (left < right)
			{
				i = left;
				j = right;
				x = zakaz[(left + right) / 2].zakazNumberGet();
				while (i <= j)
				{
					while (zakaz[i].zakazNumberGet() < x) i++;
					while (zakaz[j].zakazNumberGet() > x) j--;
					if (i <= j)
					{
						temp = zakaz[i];
						zakaz[i] = zakaz[j];
						zakaz[j] = temp;
						i++;
						j--;
					}
					if ((j - left) < (right - i))
					{
						if (i < right)
						{
							ind++;
							measure1[ind] = i;
							measure2[ind] = right;
						}
						right = j;
					}
					else
					{
						if (left < j)
						{
							ind++;
							measure1[ind] = left;
							measure2[ind] = j;
						}
						left = i;
					}
				}
			}
		}
		DeleteZakazs(userName);
		WriteInFileFromMas(zakaz, userName, amount);
	}
	delete[]zakaz;
}

void ViewUserOrders(string userName)//просмотр всех заказов пользователя
{
	QuickSort(userName);
	Zakaz* zakaz = new Zakaz[1];
	int amount = ReadFromFileInMas(zakaz, userName);
	if (amount > 0)
	{
		system("cls");
		cout << horizontalGap << "                          ЗАКАЗЫ" << endl;
		cout << horizontalGap << "+----------------+------------------+---------------------------+" << endl;
		cout << horizontalGap << "|  Номер заказа  |  Серийный номер  | количество единиц техники |" << endl;
		cout << horizontalGap << "+----------------+------------------+---------------------------+" << endl;
		for (int i = 0; i < amount; i++)
		{
			zakaz[i].Information();
		}
	}
	else
	{
		cout << horizontalGap << "У вас нет действующих заказов!" << endl;
	}
	exitOnEnter();
	delete[]zakaz;
}

void DeleteUsers()//удаление пользователей для перезаписи
{
	ofstream outfile;
	outfile.open("Userslist", ofstream::out | ofstream::trunc);
	outfile.close();
}

void DeleteUsersWithZakazs()//удаление всех заказов при удалении пользователей
{
	Client* client = new Client[1];
	int i = 1;
	while (client[0].ReadFromFile(i))
	{
		DeleteZakazs(client[0].nameGet());
		i++;
	}
	DeleteUsers();
	delete[]client;
}

bool UserSearchWithoutEnter(string userName)//проверка на существование пользователя
{
	Client* client = new Client[1];
	bool userFound = false;
	int i = 1;
	while (client[0].ReadFromFile(i))
	{
		if (client[0].nameGet() == userName)
		{
			userFound = true;
			break;
		}
		i++;
	}
	delete[]client;
	return userFound;
}

void UserStatusChanging(string userName, bool activateUser)//активация или блокировка пользователя
{
	Client* client = new Client[1];
	int amount = ReadFromFileInMas(client);
	bool userFound = false;
	for (int i = 0; i < amount; i++)
	{
		if (client[i].nameGet() == userName)
		{
			userFound = true;
			if (activateUser)
			{
				client[i].Activation();
				cout << horizontalGap << "Пользователь активирован!" << endl;
			}
			else
			{
				client[i].Disactivation();
				cout << horizontalGap << "Пользователь заблокирован!" << endl;
			}
			break;
		}
	}
	if (!userFound)
	{
		cout << horizontalGap << "Пользователя с таким именем не существует!" << endl;
	}
	else
	{
		DeleteUsers();
		WriteInFileFromMas(client, amount);
	}
	exitOnEnter();
	delete[]client;
}

string CorrectUsersInformation(string userName)//редактирование личной информации
{
	int variant, newAge;
	string newName, newPassword, newPhoneNumber, newEmail, returnParam = "0";
	Client* client = new Client[1];
	int amount = ReadFromFileInMas(client);
	for (int i = 0; i < amount; i++)
	{
		if (client[i].nameGet() == userName)
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
				client[i].nameSet(newName);
				cout << horizontalGap << "Имя пользователя изменено!" << endl;
				returnParam = newName;
				exitOnEnter();
				break;
			case 2://проверить корректность вывода мб чтото съехало
				newPassword = PasswordEntering();
				client[i].passwordSet(newPassword);
				cout << horizontalGap << "Пароль пользователя изменён!" << endl;
				exitOnEnter();
				break;
			case 3:
				newPhoneNumber = PhoneNumberEnter();
				client[i].phoneNumberSet(newPhoneNumber);
				cout << horizontalGap << "Номер телефона пользователя изменён!" << endl;
				exitOnEnter();
				break;
			case 4:
				newEmail = EmailEnter();
				client[i].emailSet(newEmail);
				cout << horizontalGap << "Адрес электронной почты пользователя изменён!" << endl;
				exitOnEnter();
				break;
			case 5:
				newAge = AgeEnter();
				client[i].ageSet(newAge);
				cout << horizontalGap << "Возраст пользователя изменён!" << endl;
				exitOnEnter();
				break;
			default:
				
				break;
			}
			break;
		}
	}
	DeleteUsers();
	WriteInFileFromMas(client, amount);
	delete[]client;
	return returnParam;
}

void UserEnter()//вход пользователя в личный кабинет
{
	Client* client = new Client[1];
	string userName, newName;
	int variant;
	system("cls");
	cout << horizontalGap << "        Вход\n";
	cout << horizontalGap << "Введите имя пользователя: ";
	cin >> userName;
	while (!StringCheck(userName))
	{
		cin >> userName;
	}
	if (PersonSearch(client, userName))
	{
		while (true)
		{
			system("cls");
			cout << horizontalGap << "        Личный кабинет" << endl;
			cout << horizontalGap << "1 - Просмотр личных данных" << endl;
			cout << horizontalGap << "2 - Редактирование личных данных" << endl;
			cout << horizontalGap << "3 - Оформление нового заказа" << endl;
			cout << horizontalGap << "4 - Просмотр действующих заказов" << endl;
			cout << horizontalGap << "Для выхода из личного кабинета введите другую цифру или символ" << endl;
			CursorSet(31, 6);
			cin >> variant;
			switch (variant)
			{
			case 1:
			{
				delete[] client;
				client = new Client[1];
				ViewForPerson(client, userName);
				break;
			}
			case 2:
				delete[] client;
				client = new Client[1];
				cout << "1" << endl;
				newName = CorrectUsersInformation(userName);
				cout << "3" << endl;
				if (newName != "0")
				{
					userName = newName;
				}
				break;
			case 3:
				AddingUserOrder(userName);
				break;
			case 4:
				ViewUserOrders(userName);
				break;
			default:

				return;
			}
		}
	}
	delete[]client;
}

void QuickSortForUsers()//сортировка пользователей
{
	Client temp;
	Client* client = new Client[1];
	int amount = ReadFromFileInMas(client);
	if (amount > 0)
	{
		int measure1[100], measure2[100], ind = 0;
		measure1[ind] = 0;
		measure2[ind] = amount - 1;
		int i = 0, j = amount - 1, left, right;
		string x = client[amount / 2].nameGet();
		while (ind != -1)
		{
			left = measure1[ind];
			right = measure2[ind];
			ind--;
			while (left < right)
			{
				i = left;
				j = right;
				x = client[(left + right) / 2].nameGet();
				while (i <= j)
				{
					while (client[i].nameGet().compare(x) > 0) i++;
					while (client[j].nameGet().compare(x) < 0) j--;
					if (i <= j)
					{
						temp = client[i];
						client[i] = client[j];
						client[j] = temp;
						i++;
						j--;
					}
					if ((j - left) < (right - i))
					{
						if (i < right)
						{
							ind++;
							measure1[ind] = i;
							measure2[ind] = right;
						}
						right = j;
					}
					else
					{
						if (left < j)
						{
							ind++;
							measure1[ind] = left;
							measure2[ind] = j;
						}
						left = i;
					}
				}
			}
		}
		DeleteUsers();
		WriteInFileFromMas(client, amount);
	}
	delete[]client;
}

void AllUsersView()//вывод всех пользователей
{
	QuickSortForUsers();
	Client* client = new Client[1];
	system("cls");
	if (client[0].ReadFromFile(1))
	{
		cout << horizontalGap << "                                      ПОЛЬЗОВАТЕЛИ" << endl;
		cout << horizontalGap << "+----------------------+---------------+-----------------------------------+---------+" << endl;
		cout << horizontalGap << "|          Имя         |   номер тел.  |      адрес электронной почты      | возраст |" << endl;
		cout << horizontalGap << "+----------------------+---------------+-----------------------------------+---------+" << endl;
	}
	else
	{
		cout << horizontalGap << "Нет пользователей для отображения!" << endl;
	}
	int i = 1;
	while (client[0].ReadFromFile(i))
	{
		cout << horizontalGap << "| " << setw(20) << left << client[0].nameGet()
			<< " | " << setw(12) << left << client[0].phoneNumberGet()
			<< " | " << setw(33) << left << client[0].emailGet()
			<< " | " << setw(7) << left << client[0].ageGet() << " | " << endl;
		cout << horizontalGap << "+----------------------+---------------+-----------------------------------+---------+" << endl;
		i++;
	}
	exitOnEnter();
	delete[]client;
}