#pragma once
#include <iostream>
#include <Windows.h>
#include "TextArea.h"
#include "ConsoleGraphics.h"
#include "ConnectionCredentials.h"
#include "UsersList.h"
#include <conio.h>


class GUI
{
public:

	//�����������
	GUI();

	//������ ���������
	void DrawInterface();
		
	bool DrawMessage(std::string text);			//������� ���������
	char DrawMenu();							//������ ����
	ConnectionCredentials DrawLogin();			//������� ���� �����

	TextArea* inputArea;			//���� �����
	TextArea* chatArea;				//����
	UsersList* list;				//������ �������������

private:
	HANDLE consoleHandle;			//����� �������
	COORD  consoleSize;				//������ �������
	int    contactsWidth;			//������ ���� ���������
	int    headerHeight = 2;		//������ ���������
	int    inputHeight = 5;			//������ ���� �����

	//��������� ������� �������
	COORD getConsoleSize();

	void draw_interface();			//������ ���������
	void create_controls();			//������� ��������
	void redraw_interface();		//�������������� ���������

	RECT draw_popup_box();			//������ ���� ���������
};