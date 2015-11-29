#pragma once

#define CYAN_NONE 51		//CYAN � ������� CYAN
#define CYAN_BLACK 48		//CYAN � ������ �������
#define DEFAULT 15			//������ ������� � ����� �������
#define BLUE_NONE 17		//����� � ����� �������
#define BLUE_WHITE 31		//����� � ����� �������
#define GRAY_NONE 119
#define GRAY_BLACK 112
#define GRAY_RED 124
#define GRAY_BLUE 121
#define WHITE_NONE 255
#define WHITE_BLACK 240
#define RED_WHITE 79

#include <Windows.h>
#include <iostream>

//�������� ������ �� ��������� ��������������
class ConsoleGraphics
{
public:

	//������������� ����� �������
	static void SetHandle(HANDLE handle);


	//��������� ������� � �������� �������
	static void drawSymbol(char symbol, COORD pos);

	//������ ������ � ������ ����
	static void drawSymbol(char symbol, int x, int y);


	//��������� ��������������
	static void drawRect(RECT rect, int attribute);
	static void drawRect(int left, int top, int right, int bottom, int attribute);

	//��������� ������������ ��������������
	static void fillRect(RECT rect, int attribute);
	static void fillRect(int left, int top, int right, int bottom, int attribute);

	//�������������� ����� ������
	static void drawText(const char* string, RECT rect, int attribute);
	static void drawText(const char* string, int left, int top, int right, int bottom, int attribute);

private:
	static HANDLE consoleHandle;

};