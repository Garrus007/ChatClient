#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "User.h"
#include "ConsoleGraphics.h"
#include "Locker.h"

//���������� ������ �������������
class UsersList
{
public:
	//������� ������
	UsersList(HANDLE consoleHandle, RECT rect, int attributes);

	//�������� ������ �������������
	void DrawUsers(std::vector<User> users);

private:
	HANDLE consoleHandle;		//����� �������
	RECT rect;					//������ � ��������� ������� 
	int attributes;				//��������� ������


	char online_to_char(bool is_online);

};