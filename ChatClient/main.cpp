
#include <QtCore/QCoreApplication>
#include <qdebug.h>
#include <iostream>
#include <iomanip>

#include "ChatClient.h"
#include "User.h"

using namespace std;

ChatClinet client;

//���������
char main_menu();
bool login();
bool sign_up();

void chat_help();
void chat();
void show_users(QList<User> users);
string online_to_string(bool);

QString q_tab(QString str, int width);

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
	char answer = main_menu();
	if (answer == '1')
	{
		if (!sign_up())return 0;
	}
	else if (answer == '2')
	{
		if (!login())return 0;
	}
	else
		return 0;

	chat_help();
	chat();
	client.Disconnect();

	return 0;
}

//���������� ������� ����
char main_menu()
{
	cout << "-------------------------------------------------\n";
	cout << "|              ������� ����                     |\n";
	cout << "-------------------------------------------------\n";
	cout << "|   1. ����������� �� �������                   |\n";
	cout << "|   2. ���� �� ������                           |\n";
	cout << "|> ";
	char answer;
	cin >> answer;
	cout << "-------------------------------------------------\n";
	return answer;
}

//���� �� ������
bool login()
{
	bool repeat = false;
	cout << "-------------------------------------------------\n";
	cout << "|                   ����                        |\n";
	cout << "-------------------------------------------------\n";
	do
	{
		repeat = false;
		std::string name, password;
		cout << "|   ���:    ";
		cin >> name;
		cout << "|   ������: ";
		cin >> password;
		if (client.Login(name, password))
		{
			cout << "|   �������� ����                               |\n";;
			cout << "-------------------------------------------------\n";
			return true;
		}
		else
		{
			char answer;
			cout << "|   ������. ����������� ����� (y\\n)?           |\n";
			cin >> answer;
			if (answer == 'y')
				repeat = true;
			else
			{
				cout << "-------------------------------------------------\n";
				return false;
			}
		}
	} while (repeat);
}

//�����������
bool sign_up()
{
	bool repeat = false;
	cout << "-------------------------------------------------\n";
	cout << "|              �����������                      |\n";
	cout << "-------------------------------------------------\n";
	do
	{
		repeat = false;
		std::string name, password;
		
		cout << "|   ���:    ";
		cin >> name;
		cout << "|   ������: ";
		cin >> password;
		if (client.Register(name,password))
		{
			cout << "|   �������� �����������                        |\n";;
			cout << "-------------------------------------------------\n";
			return true;
		}
		else
		{
			char answer;
			cout << "|   ������. ����������� ����� (y\\n)?           |\n";
			cin >> answer;
			if (answer == 'y')
				repeat = true;
			else
			{
				cout << "-------------------------------------------------\n";
				return false;
			}
		}
		

	} while (repeat);
}

//���� ����
void chat_help()
{
	cout << "-------------------------------------------------\n";
	cout << "|                 �������                       |\n";
	cout << "-------------------------------------------------\n";
	cout << "|   \\exit     �����                            |\n";
	cout << "|   \\users    ������ �������������             |\n";
	cout << "|   \\help     �������� �������                 |\n";
	cout << "-------------------------------------------------\n";
}

//���� ����
void chat()
{
	//��������� ������ �������
	cout << "> ";
	if (!client.LoadChat())
		cout << "�� ������� ��������� ���\n";


	char input[1024];
	cin.get();	//����� ������ ������ �����

	while (true)
	{
		//���� ���������\�������
		cin.getline(input, 1024);

		//��������� �������
		if (strcmp(input,"\\exit")==0)return;
		else if (strcmp(input,"\\users")==0)
		{
			QList<User> users;
			if (client.GetUsers(users))
				show_users(users);
			else
				cout << "�� ������� ��������� ������ �������������\n";
			continue;
		}
		else if (strcmp(input,"\\help")==0)
		{
			chat_help();
			continue;
		}

		//�������� ���������
		if (!client.SendChatMessage(input))
			cout << "�� ������� ��������� ���������\n";
		cout << "> ";
	}
}

//������� ���� �������������
void show_users(QList<User> users)
{
	cout << "\n�������� ����:\n";
	cout << "|-------------------------|----------|\n";
	cout << "| ���                     | ������   |\n";
	cout << "|-------------------------|----------|\n";
	for (int i = 0; i < users.size(); i++)
	{
		cout << "|"<<setw(25)<<std::left<<users[i].Name << "|" <<setw(10) <<std::left<< online_to_string(users[i].IsOnline) << "|\n";
	}

	cout << "|-------------------------|----------|\n";
}

//��������� ������� ������ � ����
string online_to_string(bool status)
{
	if (status)
		return "online";
	else
		return "offline";
}