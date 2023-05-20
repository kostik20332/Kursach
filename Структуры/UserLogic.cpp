#include "header.h"

using namespace std;

class Zakaz
{
private:
	int zakazNumber;
	int serialNumberOfItem;
	int amount;
public:
	Zakaz()//����������� �� ���������
	{
		zakazNumber = 0;
		serialNumberOfItem = 0;
		amount = 0;
	}
	Zakaz(Zakaz& ob)//����������� �����������
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
			cout << horizontalGap << "������ ��� �������� �����!" << endl;
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

int ReturnUsersAmount()//��������� ��������� �������������
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

int ReturnZakazsAmount(string userName)//��������� ��������� ������� ������������
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

int ReadFromFileInMas(Client*& client)//������ �������� �� �����
{
	int amount = ReturnUsersAmount();
	client = new Client[amount];
	for (int i = 1; i <= amount; i++)
	{
		client[i - 1].ReadFromFile(i);
	}
	return amount;
}

int ReadFromFileInMas(Zakaz*& zakaz, string userName)//������ ������� �� �����
{
	int amount = ReturnZakazsAmount(userName);
	zakaz = new Zakaz[amount];
	for (int i = 1; i <= amount; i++)
	{
		zakaz[i - 1].ReadFromFile(userName,i);
	}
	return amount;
}

void WriteInFileFromMas(Client* client, int amount)//������ �������� � ����
{
	for (int i = 0; i < amount; i++)
	{
		client[i].SaveToFile();
	}
}

void WriteInFileFromMas(Zakaz*& zakaz, string userName, int amount)//������ ������� � ����
{
	for (int i = 0; i < amount; i++)
	{
		zakaz[i].SaveToFile(userName);
	}
}

void DeleteUser(string userName)//�������� ������������
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
		cout << horizontalGap << "������������ �����!" << endl;
	}
	exitOnEnter();
	delete[]client;
}

void AddingUserOrder(string userName)//���������� ������ ������������
{
	int serialNumberOfItem, amount, zakazNumber;
	system("cls");
	cout << horizontalGap << "�������� ����� ������ �������! " << endl;
	cout << horizontalGap << "1 - ��������� ��������" << endl;
	cout << horizontalGap << "2 - �������� ���������� ������������" << endl;
	cout << horizontalGap << "3 - ���������" << endl;
	cout << horizontalGap << "4 - ���������" << endl;
	CursorSet(31, 5);
	cin >> serialNumberOfItem;
	if (serialNumberOfItem < 1 || serialNumberOfItem > 4)
	{
		cout << horizontalGap << "����� �������� ����� �������! " << endl;
		return;
	}
	cout << horizontalGap << "������� �������� ����������: ";
	cin >> amount;
	zakazNumber = ReturnZakazsAmount(userName) + 1;
	Zakaz zakaz(serialNumberOfItem, amount, zakazNumber);
	zakaz.SaveToFile(userName);
	cout << horizontalGap << "����� �������� �������!" << endl;
	exitOnEnter();
}

void DeleteZakazs(string userName)//�������� ���� ������� ������������
{
	ofstream outfile;
	outfile.open(userName, ofstream::out | ofstream::trunc);
	outfile.close();
}

void DeleteUserOrder(string userName, int zakazToDeleteNumber)//�������� ������ ������������
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
			//cout << horizontalGap << "����� �����!" << endl;
			AddProductWrite(zakaz[i].amountGet(), zakaz[i].serialNumberOfItemGet());
		}
		else
		{
			cout << horizontalGap << "�� ���������� ������ � ����� �������!" << endl;
		}
	}
	exitOnEnter();
	delete[]zakaz;
}

void QuickSort(string userName)// ���������� �������
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

void ViewUserOrders(string userName)//�������� ���� ������� ������������
{
	QuickSort(userName);
	Zakaz* zakaz = new Zakaz[1];
	int amount = ReadFromFileInMas(zakaz, userName);
	if (amount > 0)
	{
		system("cls");
		cout << horizontalGap << "                          ������" << endl;
		cout << horizontalGap << "+----------------+------------------+---------------------------+" << endl;
		cout << horizontalGap << "|  ����� ������  |  �������� �����  | ���������� ������ ������� |" << endl;
		cout << horizontalGap << "+----------------+------------------+---------------------------+" << endl;
		for (int i = 0; i < amount; i++)
		{
			zakaz[i].Information();
		}
	}
	else
	{
		cout << horizontalGap << "� ��� ��� ����������� �������!" << endl;
	}
	exitOnEnter();
	delete[]zakaz;
}

void DeleteUsers()//�������� ������������� ��� ����������
{
	ofstream outfile;
	outfile.open("Userslist", ofstream::out | ofstream::trunc);
	outfile.close();
}

void DeleteUsersWithZakazs()//�������� ���� ������� ��� �������� �������������
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

bool UserSearchWithoutEnter(string userName)//�������� �� ������������� ������������
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

void UserStatusChanging(string userName, bool activateUser)//��������� ��� ���������� ������������
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
				cout << horizontalGap << "������������ �����������!" << endl;
			}
			else
			{
				client[i].Disactivation();
				cout << horizontalGap << "������������ ������������!" << endl;
			}
			break;
		}
	}
	if (!userFound)
	{
		cout << horizontalGap << "������������ � ����� ������ �� ����������!" << endl;
	}
	else
	{
		DeleteUsers();
		WriteInFileFromMas(client, amount);
	}
	exitOnEnter();
	delete[]client;
}

string CorrectUsersInformation(string userName)//�������������� ������ ����������
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
			cout << horizontalGap << "�������� ������ ������ ��� ��������������:" << endl;
			cout << horizontalGap << "1 - ������������� ���" << endl;
			cout << horizontalGap << "2 - ������������� ������" << endl;
			cout << horizontalGap << "3 - ������������� ����� ��������" << endl;
			cout << horizontalGap << "4 - ������������� ����� ����������� �����" << endl;
			cout << horizontalGap << "5 - ������������� �������" << endl;
			cout << horizontalGap << "��� ������ ������� ������ ����� ��� ������" << endl;
			CursorSet(31, 7);
			cin >> variant;
			system("cls");
			switch (variant)
			{
			case 1:
				newName = NameEnter();
				client[i].nameSet(newName);
				cout << horizontalGap << "��� ������������ ��������!" << endl;
				returnParam = newName;
				exitOnEnter();
				break;
			case 2://��������� ������������ ������ �� ����� �������
				newPassword = PasswordEntering();
				client[i].passwordSet(newPassword);
				cout << horizontalGap << "������ ������������ ������!" << endl;
				exitOnEnter();
				break;
			case 3:
				newPhoneNumber = PhoneNumberEnter();
				client[i].phoneNumberSet(newPhoneNumber);
				cout << horizontalGap << "����� �������� ������������ ������!" << endl;
				exitOnEnter();
				break;
			case 4:
				newEmail = EmailEnter();
				client[i].emailSet(newEmail);
				cout << horizontalGap << "����� ����������� ����� ������������ ������!" << endl;
				exitOnEnter();
				break;
			case 5:
				newAge = AgeEnter();
				client[i].ageSet(newAge);
				cout << horizontalGap << "������� ������������ ������!" << endl;
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

void UserEnter()//���� ������������ � ������ �������
{
	Client* client = new Client[1];
	string userName, newName;
	int variant;
	system("cls");
	cout << horizontalGap << "        ����\n";
	cout << horizontalGap << "������� ��� ������������: ";
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
			cout << horizontalGap << "        ������ �������" << endl;
			cout << horizontalGap << "1 - �������� ������ ������" << endl;
			cout << horizontalGap << "2 - �������������� ������ ������" << endl;
			cout << horizontalGap << "3 - ���������� ������ ������" << endl;
			cout << horizontalGap << "4 - �������� ����������� �������" << endl;
			cout << horizontalGap << "��� ������ �� ������� �������� ������� ������ ����� ��� ������" << endl;
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

void QuickSortForUsers()//���������� �������������
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

void AllUsersView()//����� ���� �������������
{
	QuickSortForUsers();
	Client* client = new Client[1];
	system("cls");
	if (client[0].ReadFromFile(1))
	{
		cout << horizontalGap << "                                      ������������" << endl;
		cout << horizontalGap << "+----------------------+---------------+-----------------------------------+---------+" << endl;
		cout << horizontalGap << "|          ���         |   ����� ���.  |      ����� ����������� �����      | ������� |" << endl;
		cout << horizontalGap << "+----------------------+---------------+-----------------------------------+---------+" << endl;
	}
	else
	{
		cout << horizontalGap << "��� ������������� ��� �����������!" << endl;
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