
#include <QtCore/QCoreApplication>
//#include <QString>
#include <iostream>

using namespace std;

int main_menu();
bool login();
bool sign_up();


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	cout << "-------------------------------------------------\n";
	cout << "|         ���������� ���, v0.1                  |\n";
	cout << "-------------------------------------------------\n";
	
	int answer = main_menu();
	if (answer == 1)
		sign_up();
	else if (answer == 2)
		login();

	return 0;
}

//���������� ������� ����
int main_menu()
{
	cout << "          ������� ����\n";
	cout << "    1. ����������� �� �������\n";
	cout << "    2. ���� �� ������\n";
	cout << "> ";
	int answer;
	cin >> answer;
	return answer;
}

//���� �� ������
bool login()
{
	std::string name, password;
	cout << "             ����\n";
	cout << "���:    ";
	cin >> name;
	cout << "������: ";
	cin >> password;
	return 0;
}

//�����������
bool sign_up()
{
	std::string name, password;
	cout << "          �����������\n";
	cout << "���:    ";
	cin >> name;
	cout << "������: ";
	cin >> password;
	return 0;
}