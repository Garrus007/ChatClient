#include "TextArea.h"

TextArea::TextArea()
{
	consoleHandle = INVALID_HANDLE_VALUE;
}

//������� ������
TextArea::TextArea(HANDLE consoleHandle, RECT rect, int attributes)
{
	this->consoleHandle = consoleHandle;
	Rect = rect;
	CursorPos.X = Rect.left;
	CursorPos.Y = Rect.top;
	currentCursorPos.X = CursorPos.X - 1;
	currentCursorPos.Y = CursorPos.Y;
	Attributes = attributes;

	//����������� ��������
	current_page = 0;
	pages.push_back(std::string());

	draw_page_indicator();
}

//������������� ������ � ������� ��������� � ��������� ����
void TextArea::SetCursor()
{
	SetConsoleCursorPosition(consoleHandle, currentCursorPos);
}

//��������� ��������� ������
bool TextArea::AddSymbol(char symbol)
{
	return add_symbol(symbol, true);
}


//��������� ����� �� 1 ��������
void TextArea::ScrollUp()
{
	get_upper_page();
}


//��������� ���� �� 1 ��������
void TextArea::ScrollDown()
{
	if (current_page < pages.size() - 1)
		get_bottom_page();
}

//������� ����
void TextArea::Clear()
{
	pages.clear();
	pages.push_back(std::string());
	draw_page(pages[0]);
	current_page = 0;
}

//���������� ����
std::string TextArea::GetText()
{
	std::string str;
	for (int i = 0; i < pages.size(); i++)
		str += pages[i] + "\n";

	return str;
}

//���������� �������� �������
COORD TextArea::GetCursorPos()
{
	return currentCursorPos;
}

//��������������
void TextArea::Redraw()
{
	draw_page(pages[current_page]);
}

///////////////////////////////////////////////////////////////////////////

//��������� ������, �� ����� ������� - �������� � ��������� � ����
//��� ������ ��������
bool TextArea::add_symbol(char symbol, bool add)
{
	//������ ������ ��������� ������
	SetConsoleTextAttribute(consoleHandle, Attributes);

	if (symbol == '\b')
	{
		//�������� �������
		if (currentCursorPos.X == Rect.left - 1)return false;

		ConsoleGraphics::drawSymbol(' ', currentCursorPos);

		currentCursorPos.X--;

		//������� �� ������� ������
		if (currentCursorPos.X < Rect.left)
		{
			if (currentCursorPos.Y > Rect.top)
			{
				currentCursorPos.X = Rect.right;
				currentCursorPos.Y--;
			}
		}

		//����� ��������� �������
		if ((currentCursorPos.X >= Rect.left) && (currentCursorPos.Y >= Rect.top))
			SetCursor();

		//�������� ���������� �������
		if (add)
			pages[current_page] = pages[current_page].substr(0, pages[current_page].length() - 1);

	}
	else if (symbol == '\n')
	{
		//������� ������
		if (currentCursorPos.Y < Rect.bottom)
		{
			currentCursorPos.Y++;
			currentCursorPos.X = Rect.left - 1;
			SetCursor();


			if (add)
				pages[current_page] += symbol;
		}
		else
			get_bottom_page();
	}
	else if (symbol == -115)
	{
		//�����
		get_upper_page();
	}
	else if (symbol == -111)
	{
		//����
		if (current_page < pages.size() - 1)
			get_bottom_page();
	}
	else
	{
		//���������� �������
		currentCursorPos.X++;

		//������� ��� ���������� ������
		if (currentCursorPos.X > Rect.right)
		{
			//�������� ������ ���� ���� �����
			if (currentCursorPos.Y < Rect.bottom)
			{
				currentCursorPos.Y++;
				currentCursorPos.X = Rect.left;
			}
			else
				get_bottom_page();
		}

		if ((currentCursorPos.X <= Rect.right) && (currentCursorPos.Y <= Rect.bottom))
		{
			if (add)
				pages[current_page] += symbol;

			ConsoleGraphics::drawSymbol(symbol, currentCursorPos);
		}
		else
			currentCursorPos.X--;

		SetCursor();
	}

	return false;
}

//������� � ������ ��������
void TextArea::get_bottom_page()
{
	current_page++;
	if (current_page >= pages.size())
	{
		//�������� ����� ��������
		pages.push_back(std::string());
	}

	draw_page(pages[current_page]);
}

//������� � ������� ��������
void TextArea::get_upper_page()
{
	if (current_page > 0)
	{
		current_page--;
		draw_page(pages[current_page]);
	}
}

//��������� ��������
void TextArea::draw_page(std::string str)
{
	//������� ������� ���� ����
	ConsoleGraphics::fillRect(Rect, Attributes);
	currentCursorPos.X = CursorPos.X - 1;
	currentCursorPos.Y = CursorPos.Y;

	//������ �����
	int i = 0;
	while ((i < str.length()) && !add_symbol(str[i], false))
		i++;

	draw_page_indicator();
}

//���������� ���������
void TextArea::draw_page_indicator()
{
	COORD c;
	c.X = Rect.left + 1;
	c.Y = Rect.top - 1;
	SetConsoleTextAttribute(consoleHandle, Attributes);
	SetConsoleCursorPosition(consoleHandle, c);
	std::cout << "[" << current_page + 1 << "/" << pages.size() << "]";
	SetCursor();
}

