#include "header.h"

class Product
{
private:
	int cehNumber;
	int amount;
	int datadata;
	int mounth;
	int year;
	string productName;
	string responsibleForCehName;
public:
	Product()//конструктор по умолчанию
	{
		datadata = 0;
		mounth = 0;
		year = 0;
		cehNumber = 0;
		amount = 0;
		productName = "0";
		responsibleForCehName = "0";
	}
	Product(int amount, int cehNumber, int datadata, int mounth, int year, string productName, string responsibleForCehName)//конструктор по умолчанию
	{
		this->datadata = datadata;
		this->mounth = mounth;
		this->year = year;
		this->cehNumber = cehNumber;
		this->amount = amount;
		this->productName = productName;
		this->responsibleForCehName = responsibleForCehName;
	}
	void ParamsSet(int amount, int cehNumber, int datadata, int mounth, int year, string productName, string responsibleForCehName)
	{
		this->datadata = datadata;
		this->mounth = mounth;
		this->year = year;
		this->cehNumber = cehNumber;
		this->amount = amount;
		this->productName = productName;
		this->responsibleForCehName = responsibleForCehName;
	}
	int amountGet()
	{
		return amount;
	}
	int cehNumberGet()
	{
		return cehNumber;
	}
	int dataGet()
	{
		return datadata;
	}
	int mounthGet()
	{
		return mounth;
	}
	int yearGet()
	{
		return year;
	}
	string productNameGet()
	{
		return productName;
	}
	string responsibleForCehNameGet()
	{
		return responsibleForCehName;
	}
	int serialNumberOfItemGet()
	{
		if (productName == "Карьерный самосвал")
		{
			return 1;
		}
		if (productName == "Самосвал пов. прох.")
		{
			return 2;
		}
		if (productName == "Погрузчик")
		{
			return 3;
		}
		if (productName == "Бульдозер")
		{
			return 4;
		}
		return 0;
	}
	void InformationShow()
	{
		if (mounth > 9) 
		{
			cout << horizontalGap << "| " << setw(2) << left << datadata << "." << mounth << "." << year;
		}
		else
		{
			cout << horizontalGap << "| " << setw(2) << left << datadata << "." << mounth << "." << year << " ";
		}
		//cout << horizontalGap << "| " << setw(2) << left << datadata << "." << mounth << "." << year;
		cout << " |      " << setw(7) << left << cehNumber
			<< " |         " << setw(21) << left << responsibleForCehName
			<< " |       " << setw(21) << left << productName
			<< " |        " << setw(7) << left << amount << " | " << endl;
		cout << horizontalGap << "+------------+--------------+-------------------------------+-----------------------------+----------------+" << endl;
	}
	void SaveToFile()
	{
		string productName = productNameGet();
		string responsibleForCehName = responsibleForCehNameGet();
		int datadata = dataGet();
		int mounth = mounthGet();
		int year = yearGet();
		int amount = amountGet();
		int cehNumber = cehNumberGet();
		ofstream outF("Productslist", ios::out | ios::app);
		if (!outF.is_open())
		{
			return;
		}
		int len = productName.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < productName.length(); i++)
		{
			outF.write((char*)&productName[i], sizeof(productName[i]));
		}
		len = responsibleForCehName.length();
		outF.write((char*)&len, sizeof(int));
		for (int i = 0; i < responsibleForCehName.length(); i++)
		{
			outF.write((char*)&responsibleForCehName[i], sizeof(responsibleForCehName[i]));
		}
		outF.write((char*)&datadata, sizeof(int));
		outF.write((char*)&mounth, sizeof(int));
		outF.write((char*)&year, sizeof(int));
		outF.write((char*)&amount, sizeof(int));
		outF.write((char*)&cehNumber, sizeof(int));
		outF.close();
	}
	bool ReadFromFile(int objectNumber)
	{
		int cehNumber = 0;
		int amount = 0;
		int datadata = 0;
		int mounth = 0;
		int year = 0;
		string productName = "";
		string responsibleForCehName = "";
		bool pointerOutOfRange = false;
		ifstream inF("Productslist", ios::in | ios::binary);
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
			productName = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				productName += c;
			}
			inF.read((char*)&len, sizeof(int));
			responsibleForCehName = "";
			for (int i = 0; i < len; i++)
			{
				inF.read((char*)&c, sizeof(c));
				responsibleForCehName += c;
			}
			inF.read((char*)&datadata, sizeof(int));
			inF.read((char*)&mounth, sizeof(int));
			inF.read((char*)&year, sizeof(int));
			inF.read((char*)&amount, sizeof(int));
			inF.read((char*)&cehNumber, sizeof(int));
			currentPos = inF.tellg();
		}
		if (currentPos <= fileEnd && i == objectNumber && currentPos != -1)
		{
			pointerOutOfRange = true;
		}
		inF.close();
		ParamsSet(amount, cehNumber, datadata, mounth, year, productName, responsibleForCehName);
		return pointerOutOfRange;
	}
};

void AddProductWrite(int kolvo, int serialNumber)
{
	int amount;
	int cehNumber;
	int datadata, mounth, year;
	string productName;
	string responsibleForCehName;
	cout << horizontalGap << "Введите информацию о выполненном заказе!" << endl;
	//amount = IntEnter("Введите количество техники: ");
	amount = kolvo;
	cehNumber = IntEnter("Введите номер цеха: ");
	datadata = DataEnter();
	mounth = MounthEnter();
	year = YearEnter();
	/*cout << horizontalGap << "Введите имя продукта: ";
	productName = ProductNameEnter();*/
	switch (serialNumber)
	{
	case 1:
		productName = "Карьерный самосвал";
		break;
	case 2:
		productName = "Самосвал пов. прох.";
		break;
	case 3:
		productName = "Погрузчик";
		break;
	case 4:
		productName = "Бульдозер";
		break;
	}
	cout << horizontalGap << "Введите имя ответственного за цех: ";
	responsibleForCehName = StringEnter();
	Product *product = new Product[1];
	//Product product(amount, cehNumber, data, productName, responsibleForCehName);
	product[0].ParamsSet(amount, cehNumber, datadata, mounth, year, productName, responsibleForCehName);
	product[0].SaveToFile();
	cout << horizontalGap << "Запись прошла успешно!" << endl;
	//exitOnEnter();
}

void ViewAllProducts()
{
	Product* product = new Product[1];
	system("cls");
	if(product[0].ReadFromFile(1))
	{
		cout << horizontalGap << "                          ВЫПОЛНЕННЫЕ ЗАКАЗЫ" << endl;
		cout << horizontalGap << "+------------+--------------+-------------------------------+-----------------------------+----------------+" << endl;
		cout << horizontalGap << "|    Дата    |  Номер цеха  |     Ответственный по цеху     |    Наименование продукта    | Количество шт. |" << endl;
		cout << horizontalGap << "+------------+--------------+-------------------------------+-----------------------------+----------------+" << endl;
		int i = 1;
		while (product[0].ReadFromFile(i))
		{
			product[0].InformationShow();
			i++;
		}
	}
	else
	{
		cout << horizontalGap << "Нет выполненных заказов!" << endl;
	}
	exitOnEnter();
	//system("cls");
	delete[] product;
}

int ReturnProductsAmount()
{
	Product* product = new Product[1];
	int i = 1;
	while (product[0].ReadFromFile(i))
	{
		i++;
	}
	delete[] product;
	return i - 1;
}

int GetProductsWithCehNumber(Product*& productsWithCeh, int cehNumber, int cehProducts)
{
	Product* product = new Product[1];
	productsWithCeh = new Product[cehProducts];
	int i = 1, k = 0;
	while (product[0].ReadFromFile(i))
	{
		if (product[0].cehNumberGet() == cehNumber)
		{
			productsWithCeh[k++] = product[0];
		}
		i++;
	}
	delete[] product;
	return k;
}

bool DataComparing(int datadata[], int mounth[], int year[], Product product)
{
	int productYear = product.yearGet();
	int productMounth = product.mounthGet();
	int productDate = product.dataGet();
	if (productYear > year[0] && productYear < year[1])
	{
		return true;
	}
	else if (productMounth > mounth[0] && productMounth < mounth[1] && (productYear == year[0] || productYear == year[1]))
	{
		return true;
	}
	else if (productDate >= datadata[0] && productDate <= datadata[1] && (productMounth == mounth[0] || productMounth == mounth[1]) && (productYear == year[0] || productYear == year[1]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void IndividualTask()
{
	Product* productsWithCeh;
	int cehNumber = IntEnter("Введите номер цеха: ");
	int datadata[2], mounth[2], year[2];
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:
			cout << horizontalGap << "Введите временной промежуток!" << endl;
			cout << horizontalGap << "Введите дату, начиная с которой отобразить данные!" << endl;
			break;
		case 1:
			cout << horizontalGap << "Введите дату, до которой отобразить данные!" << endl;
			break;
		}
		datadata[i] = DataEnter();
		mounth[i] = MounthEnter();
		year[i] = YearEnter();
	}
	int i = 1, k = 0, cehProducts = ReturnProductsAmount();
	int karCamosval = 0, camPovProh = 0, pogruzcich = 0, buldozer = 0;
	k = GetProductsWithCehNumber(productsWithCeh, cehNumber, cehProducts);
	for (int i = 0; i < k; i++)
	{
		if(DataComparing(datadata, mounth, year, productsWithCeh[i]))
		{
			switch (productsWithCeh[i].serialNumberOfItemGet())
			{
			case 1:
				karCamosval++;
				break;
			case 2:
				camPovProh++;
				break;
			case 3:
				pogruzcich++;
				break;
			case 4:
				buldozer++;
				break;
			}
		}
	}
	if(karCamosval != 0 || camPovProh != 0 || pogruzcich != 0 || buldozer != 0)
	{
		system("cls");
		cout << horizontalGap << "Цех с номером " << cehNumber << " в период времени с "
			<< datadata[0] << "." << mounth[0] << "." << year[0] << " по "
			<< datadata[1] << "." << mounth[1] << "." << year[1] << " выпустил:" << endl;
		cout << horizontalGap << "+--------------------+---------------------+-----------+-----------+" << endl;
		cout << horizontalGap << "| Карьерный самосвал | Самосвал пов. прох. | Погрузчик | Бульдозер |" << endl;
		cout << horizontalGap << "+--------------------+---------------------+-----------+-----------+" << endl;
		cout << horizontalGap << " |      " << setw(12) << left << karCamosval
			<< " |         " << setw(12) << left << camPovProh
			<< " |       " << setw(8) << left << pogruzcich
			<< " |        " << setw(7) << left << buldozer << " | " << endl;
		cout << horizontalGap << "+--------------------+---------------------+-----------+-----------+" << endl;
		delete[] productsWithCeh;
		exitOnEnter();
	}
	else
	{
		cout << horizontalGap << "Цех с номером " << cehNumber << " в период времени с "
			<< datadata[0] << "." << mounth[0] << "." << year[0] << " по "
			<< datadata[1] << "." << mounth[1] << "." << year[1] << " не выпустил ни одной единицы техники!" << endl;
		exitOnEnter();
	}
}