#include "ConsoleGraphics.h"
HANDLE ConsoleGraphics::consoleHandle;

void ConsoleGraphics::SetHandle(HANDLE handle)
{
	consoleHandle = handle;
}

//��������� ������� � �������� �������
void ConsoleGraphics::drawSymbol(char symbol, COORD pos)
{
	SetConsoleCursorPosition(consoleHandle, pos);
	std::cout << symbol;
}

//������ ������ � ������ ����
void ConsoleGraphics::drawSymbol(char symbol, int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	drawSymbol(symbol, pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��������� ��������������
void ConsoleGraphics::drawRect(RECT rect, int attribute)
{
	COORD pos;
	SetConsoleTextAttribute(consoleHandle, attribute);

	for (int x = rect.left + 1; x < rect.right; x++)
	{
		drawSymbol('\xCD\xA0', x, rect.top);
		drawSymbol('\xCD\xA0', x, rect.bottom);
	}

	for (int y = rect.top + 1; y < rect.bottom; y++)
	{
		drawSymbol('\xBA\xB1', rect.left, y);
		drawSymbol('\xBA\xB1', rect.right, y);
	}

	//������ ����
	drawSymbol('\xC9\xA5', rect.left, rect.top);
	drawSymbol('\xBB\xA8', rect.right, rect.top);
	drawSymbol('\xBC\xAE', rect.right, rect.bottom);
	drawSymbol('\xC8\xAB', rect.left, rect.bottom);
}

void ConsoleGraphics::drawRect(int left, int top, int right, int bottom, int attribute)
{
	RECT rect;
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;
	drawRect(rect, attribute);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��������� ������������ ��������������
void ConsoleGraphics::fillRect(RECT rect, int attribute)
{
	COORD pos;
	for (int x = rect.left; x <= rect.right; x++)
	{
		pos.X = x;
		for (int y = rect.top; y <= rect.bottom; y++)
		{
			pos.Y = y;
			SetConsoleCursorPosition(consoleHandle, pos);
			SetConsoleTextAttribute(consoleHandle, attribute);
			std::cout << ' ';
		}
	}

	pos.X = rect.left;
	pos.Y = rect.top;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void ConsoleGraphics::fillRect(int left, int top, int right, int bottom, int attribute)
{
	RECT rect;
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;
	fillRect(rect, attribute);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�������������� ����� ������
void ConsoleGraphics::drawText(const char* string, RECT rect, int attribute)
{
	COORD pos;
	int len = strlen(string);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	pos.X = rect.left + width / 2 - len / 2;
	pos.Y = rect.top + height / 2;
	SetConsoleCursorPosition(consoleHandle, pos);
	SetConsoleTextAttribute(consoleHandle, attribute);
	std::cout << string;
}

void ConsoleGraphics::drawText(const char* string, int left, int top, int right, int bottom, int attribute)
{
	RECT rect;
	rect.left = left;
	rect.right = right;
	rect.top = top;
	rect.bottom = bottom;
	drawText(string, rect, attribute);
}
