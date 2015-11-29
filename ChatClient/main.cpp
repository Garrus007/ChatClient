#include <iostream>
#include <iomanip>

#include "ChatClient.h"
#include "User.h"

#include "GUI.h"

using namespace std;

string online_to_string(bool);		//��������� ������� ������ � �����
bool menu();						//���������� ����
bool login();						//���������� ���� �����
bool registration();				//���������� ���� �����������
void chat();						//���

void print_message(string text);	//�������� ��������� ���������
void update_clients();

ChatClinet client(print_message, update_clients);
GUI gui;

int main(int argc, char *argv[])
{
	gui.DrawInterface();

	//������������ � �������
	if (!client.ConnectToServer(L"\\\\.\\pipe\\chat_server_pipe"))
	{
		gui.DrawMessage("Can't connect to server");
		return 0;
	}

	//����� ����
	if (!menu())return 0;

	//������ ����
	chat();
	client.Disconnect();

	return 0;
}

//����
bool menu()
{
	char c;
	do
	{
		c = gui.DrawMenu();
		if (tolower(c) == 'l')
		{
			//����
			bool flag = true;
			do
			{
				if (!login())
					flag = gui.DrawMessage("Error, can't login. Try again?");
				else return true;
			} while (flag);

		}
		else if (tolower(c) == 'r')
		{
			//�����������		
			bool flag = false;
			do
			{
				if (!registration())
					flag = gui.DrawMessage("Error, can't register. Try again?");
				else return true;
			} while (flag);
		}
		
	} while ((tolower(c)!='l') || (tolower(c)!='r'));


	return false;
}

//����
bool login()
{
	auto cc = gui.DrawLogin();
	return client.Login(cc.Name, cc.Password);
}

//�����������
bool registration()
{
	auto cc = gui.DrawLogin();
	return client.Register(cc.Name, cc.Password);
}

void chat()
{
	//��������� �������
	if (!client.LoadChat())
	{
		gui.DrawMessage("Error while loading chat history");
		return;
	}


	string text;
	bool ctr_mode = false;

	while (text!="\exit")
	{
		char c = getch();

		//�������� ���������
		if (c == '\r')
		{
			//���������� ���������
			if (!client.SendChatMessage(gui.inputArea->GetText()))
			{
				gui.DrawMessage("Error while sending message");
				return;
			}

			//����������
			print_message("me:\n" + gui.inputArea->GetText());
			gui.inputArea->Clear();
			continue;
		}

		//����� ���. ������
		if (c == -32)
		{
			ctr_mode = true;
			continue;
		}

		if (ctr_mode)
		{
			//������ ������� ���������
			if (c == 80)
			{
				gui.chatArea->ScrollDown();
				continue;
			}
			else if (c == 72)
			{
				gui.chatArea->ScrollUp();
				continue;
			}

			ctr_mode = false;
		}

		gui.inputArea->AddSymbol(c);
	}
}

//��������� ������� ������ � ����
string online_to_string(bool status)
{
	if (status)
		return "online";
	else
		return "offline";
}

//�������� ���������
void print_message(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		gui.chatArea->AddSymbol(text[i]);
	}
}

//��������� ������ �������������
void update_clients()
{

}