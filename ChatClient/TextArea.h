#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include "ConsoleGraphics.h"
#include "Locker.h"

//���������� ������� � ������ ������������� ��������������
class TextArea
{
public:

	TextArea();

	//������� ������
	TextArea(HANDLE consoleHandle, RECT rect, int attributes);

	//������������� ������ � ������� ��������� � ��������� ����
	void SetCursor();

	//��������� ��������� ������
	// ������������ �������� ����������, ��� �� ����������� �������
	// �� ��������� ��������
	bool AddSymbol(char symbol);

	//������ ���������� ����������
	void ScrollUp();
	void ScrollDown();

	//������� ����
	void Clear();

	//������� ����
	std::string GetText();

	//���������� ��������� �������
	COORD GetCursorPos();

	//��������������
	void Redraw();

private:
	COORD currentCursorPos;


	//��������� � ������ ��������, ���� ������� �����
	void get_bottom_page();
	
	//��������� � ������� ��������
	void get_upper_page();

	//������ ��������
	void draw_page(std::string str);

	//���������� ������� �������
	void draw_page_indicator();

	bool add_symbol(char symbol, bool add);

	//���������� ������������ ��������
	//int num_pages;
	int current_page;

	RECT Rect;					//�������������� �������������
	COORD CursorPos;			//��������� ������� � �����
	int Attributes;				//��������� ��� �������
	HANDLE consoleHandle;		//

	std::vector<std::string> pages;	//����� �������
};