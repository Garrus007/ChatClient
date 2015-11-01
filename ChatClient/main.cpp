
#include <QtCore/QCoreApplication>
#include <iostream>
#include "ChatClient.h"

using namespace std;

ChatClinet client;

//���������
int main_menu();
bool login();
bool sign_up();

void chat_help();
void chat();

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	cout << "-------------------------------------------------\n";
	cout << "|         ���������� ���, v0.1                  |\n";
	cout << "-------------------------------------------------\n";
	
	//������������ � �������
	if (!client.ConnectToServer(L"\\\\.\\pipe\\chat_server_pipe"))
	{
		cout << "�� ������� ������������ � �������";
		return 0;
	}

	//����� �������� ����
	int answer = main_menu();
	if (answer == 1)
	{
		if (!sign_up())return 0;
	}
	else if (answer == 2)
	{
		if (!login())return 0;
	}

	chat_help();
	chat();

	return 0;
}

//���������� ������� ����
int main_menu()
{
	cout << "          ������� ����\n";
	cout << "    1. ����������� �� �������\n";
	cout << "    2. ���� �� ������\n";
	cout << "> ";
	int answer;
	cin >> answer;
	return answer;
}

//���� �� ������
bool login()
{
	bool repeat = false;
	cout << "             ����\n";
	do
	{
		repeat = false;
		std::string name, password;
		cout << "���:    ";
		cin >> name;
		cout << "������: ";
		cin >> password;
		if (client.Login(QString(name.c_str()), QString(password.c_str())))
		{
			cout << "�������� ����\n";
			return true;
		}
		else
		{
			char answer;
			cout << "������. ����������� �����? (y\\n) ";
			cin >> answer;
			if (answer == 'y')
				repeat = true;
			else return false;
		}
	} while (repeat);
}

//�����������
bool sign_up()
{
	bool repeat = false;
	cout << "          �����������\n";
	do
	{
		repeat = false;
		std::string name, password;
		
		cout << "���:    ";
		cin >> name;
		cout << "������: ";
		cin >> password;
		if (client.Register(QString(name.c_str()), QString(password.c_str())))
		{
			cout << "�������� �����������\n";
			return true;
		}
		else
		{
			char answer;
			cout << "������. ����������� �����? (y\\n) ";
			cin >> answer;
			if (answer == 'y')
				repeat = true;
			else return false;
		}
		

	} while (repeat);
}

//���� ����
void chat_help()
{
	cout << "         �������\n";
	cout << "\\exit     �����\n";
	cout << "\\users    ������ �������������\n";
	cout << "\\help     �������� �������\n";
}

//���� ����
void chat()
{
	string answer;

	while (true)
	{
		//���� ���������\�������
		cout << "> ";
		cin >> answer;

		//��������� �������
		if (answer == "\\exit")return;
		else if (answer == "\\users")return;
		else if (answer == "\\help")
		{
			chat_help();
			continue;
		}

		//�������� ���������

	}
}