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
bool ChatClinet::Login(std::string name, std::string password)
{
	//���������� ������
	char* buffer;
	User user;
	user.Name = name;
	user.Password = password;
	int size = PacketCoderDecoder::CodeRequestUserConnect(user, buffer);
	send(buffer, size, pipe);
	delete[] buffer;

	//���� ������

	receive(buffer, pipe);
	PacketTypes type = get_type(buffer);

	if (type == DATA_USER)
	{
		PacketCoderDecoder::DecodeDataUser(me, buffer);
		delete[] buffer;
		return create_pipe();
	}
	delete[] buffer;
	return false;
}

//�����������
bool ChatClinet::Register(std::string name, std::string password)
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
	

	if (type == DATA_USER)
	{
		PacketCoderDecoder::DecodeDataUser(me, buffer);
		delete[] buffer;
		return create_pipe();
	}

	delete[] buffer;
	return false;
}

//���������� ���������
bool ChatClinet::SendChatMessage(std::string message)
{
	char* buffer;
	Message msg;
	msg.Text = message;
	msg.Author = me;

	int size = PacketCoderDecoder::CodeDataMessage(msg, buffer);
	send(buffer, size, pipe);
	delete[] buffer;
	return true;
}

//��������� ��� - ���������� ������� ���������
bool ChatClinet::LoadChat(Chat & chat)
{
	return false;
}

//�������� ������ �������������
bool ChatClinet::GetUsers(QList<User>& users)
{
	//���������� ������
	char* buffer;
	int size = PacketCoderDecoder::CodeRequestUsersList(buffer);
	send(buffer, size, pipe);
	delete[] buffer;

	//���� ������
	int a = receive(buffer, pipe);
	PacketTypes type = get_type(buffer);
	if (type == DATA_USERS_LIST)
		PacketCoderDecoder::DecodeDataUsersList(users, buffer);
	delete[] buffer;

	return  type == DATA_USERS_LIST;
}

//����������  ������, ��� ������ ��������
void ChatClinet::Disconnect()
{
	char* buffer;
	int size = PacketCoderDecoder::CodeRequestClose(me.Id, buffer);
	send(buffer, size, pipe);
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

//������� ����� � ����� ��� �������� ����������� �����
bool ChatClinet::create_pipe()
{
	char pipe_name[255];
	sprintf(pipe_name, "\\\\.\\pipe\\%d", me.Id);

	my_pipe = CreateNamedPipeA(pipe_name,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES,
		1024, 1024, 10000, NULL);
	if (my_pipe == INVALID_HANDLE_VALUE)
		return false;

	CreateThread(NULL, 0, thread_func_wrapper, (LPVOID)this, NULL, NULL);

	return true;
}

//������� ��� �������� ������
DWORD ChatClinet::thread_func_wrapper(void * param)
{
	ChatClinet* context = static_cast<ChatClinet*>(param);
	context->thread_func();
	return 0;
}

//������� ������
void ChatClinet::thread_func()
{
	char* buffer;
	Message message;

	while (true)
	{
		//������� ����������� � ������ � ������
		ConnectNamedPipe(my_pipe, NULL);
		int size = receive(buffer, my_pipe);

		//��������� ���������
		PacketCoderDecoder::DecodeDataMessage(message, buffer);
		if (message.Author.Id != me.Id)
		{
			std::cout << std::setw(10) << std::left << message.Author.Name << message.Text << "\n";	
			std::cout << "> ";
		}
			
		DisconnectNamedPipe(my_pipe);

	}
}
