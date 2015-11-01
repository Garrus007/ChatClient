#pragma once

/*
�������� �� ����� ������� � ��������
*/

#include <Windows.h>
#include <qstring.h>
#include "Packets.h"

class ChatClinet
{
public:

	bool ConnectToServer(const TCHAR* pipe_name);
	bool Login(QString name, QString password);
	bool Register(QString name, QString password);
	bool SendChatMessage(QString message);
	bool LoadChat(Chat& chat);
	bool GetUsers(QList<User>& users);
	void Disconnect();

	~ChatClinet();

private:
	HANDLE pipe;
	User me;

	//���������� ������ � ������ ������
	bool send(char* buffer, int size, HANDLE pipe);

	//��������� ������
	int receive(char*& buffer, HANDLE pipe);

	//���������� ��� ���������
	PacketTypes get_type(char* buffer);
};