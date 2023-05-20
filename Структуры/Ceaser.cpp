#include <iostream>
#include<stdio.h>

using namespace std;

string Incription(string password)//шифрование паролей
{
	char ch;
	string incPassword = password;
	int i, key = 4;
	for (i = 0; i < password.length(); ++i)
	{
		ch = incPassword[i];
		if (ch >= 'a' && ch <= 'z')
		{
			ch = ch + key;
			if (ch > 'z')
			{
				ch = ch - 'z' + 'a' - 1;
			}
			incPassword[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch = ch + key;
			if (ch > 'Z')
			{
				ch = ch - 'Z' + 'A' - 1;
			}
			incPassword[i] = ch;
		}
		else if (ch >= '0' && ch <= '9')
		{
			ch = ch + key;
			if (ch > '9')
			{
				ch = ch - '9' + 1;
			}
			incPassword[i] = ch;
		}
	}
	//cout << "Encrypted message: %s" << incPassword;
	return incPassword;
}