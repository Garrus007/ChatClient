#pragma once

//��� ����������� ��� ������������� �������� � ���� ������������� �������
//��� ����� ��� ����, ����� ������������� ������� ����� ���� ������������
//�� ������ � �������� ������, ������� ����� ������� memcpy, �� � �� ��������,
//���������� ������������
//��� �� ����� ��������� ���� ������������� �������

#include "User.h"
#include "Chat.h"
#include "Message.h"

class Serializers
{

public:

	//QString
	static int Sizeof(const QString& string);
	static int Serialize(const QString& string, char* data);
	static int Deserialize(QString& string, const char* data);

	//QList
	//���������� ������ ������ ��� �������� ���������������� ������
	template <class T>
	static int Sizeof(const QList<T>& list)
	{
		return get_list_buffer_size<QList<T>, T>((QList<T>)list);
	}

	//����������� ������
	template <class T>
	static int Serialize(const QList<T>& list, char* data)
	{
		return serialize_list<QList<T>, T>(list, data);
	}

	//������������� ������
	//��������������, ��� ������� ������ ������ �����
	template <class T>
	static int Deserialize(QList<T>& list, const char* data)
	{
		return deserialize_list<QList<T>, T>(list, data);
	}

	//QLinkedList
	//���������� ������ ������ ��� �������� ���������� ������
	template <class T>
	static int Sizeof(const QLinkedList<T>& list)
	{
		return get_list_buffer_size<QLinkedList<T>, T>(list);
	}

	//����������� ��������� ������
	template <class T>
	static int Serialize(const QLinkedList<T>& list, char* data)
	{
		return serialize_list<QLinkedList<T>, T>(list, data);
	}

	//������������� ��������� ������
	//��������������, ��� ������� ������ ������ �����
	template <class T>
	static int Deserialize(QLinkedList<T>& list, const char* data)
	{
		return deserialize_list<QLinkedList<T>, T>(list, data);
	}
	
	//������� ����*, ������� ����� �������������
	//����� memcpy
	//������ ��������� ��� ��������� ������
	template <class T>
	static int Sizeof(const T val)
	{
		return sizeof(val);
	}

	template <class T>
	static int Serialize(const T val, char* buffer)
	{
		memcpy(buffer, &val, sizeof(val));
		return sizeof(val);
	}

	template <class T>
	static int Deserialize(T& val, const char* buffer)
	{
		memcpy(&val, buffer, sizeof(val));
		return sizeof(val);
	}

	//User
	static int Sizeof(const User& val);
	static int Serialize(const User& val, char* buffer);
	static int Deserialize(User& val, const char* buffer);

	//Message
	static int Sizeof(const Message& val);
	static int Serialize(const Message& val, char* buffer);
	static int Deserialize(Message& val, const char* buffer);

	//Chat
	static int Sizeof(const Chat& val);
	static int Serialize(const Chat& val, char* buffer);
	static int Deserialize(Chat& val, const char* buffer);

	//ChatOnlyInfo
	static int Sizeof(const ChatOnlyInfo& val);
	static int Serialize(const ChatOnlyInfo& val, char* buffer);
	static int Deserialize(ChatOnlyInfo& val, const char* buffer);

private:
	//���������� ������, ����������� ��� �������� ������
	template <class LIST, class T>
	static int get_list_buffer_size(const LIST &list)
	{
		int size = sizeof(int);
		for (auto i = list.begin(); i != list.end(); ++i)
			size += Sizeof(*i);
		return size;
	}

	//������������� ������-������
	template <class LIST, class T>
	static int deserialize_list(LIST& list, const char* data)
	{
		//���������� ������ ������
		int size;
		memcpy(&size, data, sizeof(int));
		data += sizeof(int); //�������� ���������

		//������ ��������
		T element;
		for (int i = 0; i < size; i++)
		{
			data += Deserialize(element, data);
			list.append(element);
		}

		return list.count()*sizeof(T);
	}

	//����������� ������-������
	template <class LIST, class T>
	static int serialize_list(const LIST list, char* data)
	{
		//���������� ������
		int size = list.count();
		memcpy(data, &size, sizeof(int));
		data += sizeof(int);  //�������� ���������

		//���������� ��������
		for (auto i = list.begin(); i != list.end(); ++i)
			data += Serialize(*i, data);
		

		return sizeof(int) + list.count()*sizeof(T);
	}
};