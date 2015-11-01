#include "ChatClient.h"

//����������� � �������
bool ChatClinet::ConnectToServer(const TCHAR * pipe_name)
{
	//������������ � ������
	pipe = CreateFile(pipe_name, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (pipe == INVALID_HANDLE_VALUE)
		return false;

	DWORD mode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	SetNamedPipeHandleState(pipe, &mode, NULL, NULL);
	return true;
}

//����
bool ChatClinet::Login(QString name, QString password)
{
	char* buffer;
	User user;
	user.Name = name;
	user.Password = password;
	int size = PacketCoderDecoder::CodeRequestUserConnect(user, buffer);
	send(buffer, size, pipe);

	return false;
}

//�����������
bool ChatClinet::Register(QString name, QString password)
{
	//���������� ������
	char* buffer;
	User user;
	user.Name = name;
	user.Password = password;
	int size = PacketCoderDecoder::CodeRequestUserRegister(user, buffer);
	send(buffer, size, pipe);
	delete[] buffer;

	//���� ������
	receive(buffer, pipe);
	PacketTypes type = get_type(buffer);
	delete[] buffer;

	return  type != DATA_ERROR;
}

ChatClinet::~ChatClinet()
{
	CloseHandle(pipe);
}

//���������� ������ ������ � ������
bool ChatClinet::send(char * buffer, int size, HANDLE pipe)
{
	DWORD bw;
	WriteFile(pipe, &size, sizeof(size), &bw, NULL);
	WriteFile(pipe, buffer, size, &bw, NULL);
	return false;
}

int ChatClinet::receive(char*& buffer, HANDLE pipe)
{
	int size;
	DWORD br;

	//������ ������ ������
	ReadFile(pipe, &size, sizeof(int), &br, NULL);
	buffer = new char[size];

	//������ ������
	ReadFile(pipe, buffer, size, &br, NULL);

	return size;
}

PacketTypes ChatClinet::get_type(char * buffer)
{
	PacketTypes type;
	memcpy(&type, buffer, sizeof(PacketTypes));
	return type;
}
