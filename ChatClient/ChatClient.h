#pragma once

/*
�������� �� ����� ������� � ��������
*/

#include <Windows.h>
#include "Packets.h"
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

class ChatClinet
{

public:

	ChatClinet(void(*incoming_message_callback)(std::string), void (*users_updated_callback)(std::vector<User>));
	bool ConnectToServer(const TCHAR* pipe_name);
	bool Login(std::string name, std::string password);
	bool Register(std::string name, std::string password);
	bool SendChatMessage(std::string message);
	bool LoadChat();
	bool GetUsers(std::vector<User>& users);
	void Disconnect();

	~ChatClinet();

private:
	HANDLE pipe;
	HANDLE my_pipe;
	User me;

	void(*incoming_message_callback)(std::string);
	void(*users_updated_callback)(std::vector<User>);

	bool send(char* buffer, int size, HANDLE pipe);		//���������� ������ � ������ ������
	int receive(char*& buffer, HANDLE pipe);			//��������� ������
	PacketTypes get_type(char* buffer);					//���������� ��� ���������
	bool create_pipe();									//������� ����� � ����� ��� �������� ����������� �����
	static DWORD WINAPI thread_func_wrapper(void*);		//�������
	void thread_func();									//����� ��������

	void decode_message(const char* buffer);			//����������� ���������
	void write_message(Message message);				//�������� ���������
	void write_users(char* buffer);						//���������� � �������� ������ �������������
};