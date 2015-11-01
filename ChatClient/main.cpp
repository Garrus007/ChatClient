
#include <QtCore/QCoreApplication>
#include <iostream>
#include "ChatClient.h"

using namespace std;

ChatClinet client;

//���������
int main_menu();
bool login();
bool sign_up();

int chat_menu();

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
		if (!sign_up())return 0;
	else if (answer == 2)
		if (!login())return 0;

	chat_menu();

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
	std::string name, password;
	cout << "             ����\n";
	cout << "���:    ";
	cin >> name;
	cout << "������: ";
	cin >> password;
	client.Login(QString(name.c_str()), QString(password.c_str()));
	return 0;
}

//�����������
bool sign_up()
{
	bool repeat = false;
	do
	{
		repeat = false;

		std::string name, password;
		cout << "          �����������\n";
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
			cout << "������. ����������� �����? (y\n) ";
			cin >> answer;
			if (answer == 'y')
				repeat = true;
			else return false;
		}
		

	} while (repeat);
}

//���� ����
int chat_menu()
{
	cout << "             ����\n";
	cout << "    1. �������� �����\n";
	cout << "    2. �������� �������������\n";
	cout << "    3. ������� ���\n";
	cout << "    4. �������������� � ����\n";
	cout << "> ";
	int answer;
	cin >> answer;
	return answer;
}