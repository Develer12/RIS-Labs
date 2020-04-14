// ClientU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Winsock2.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <ctime>
#include <wchar.h>

#pragma comment(lib, "WS2_32.lib")

typedef HANDLE HDFS;

using namespace std;

string GetErrorMsgText (int code)
{
	string msgText;

	switch (code)
	{
		case WSAEINTR:				 msgText = "Работа функции прервана\n";						  break;
		case WSAEACCES:				 msgText = "Разрешение отвергнуто\n";						  break;
		case WSAEFAULT:				 msgText = "Ошибочный адрес\n";								  break;
		case WSAEINVAL:				 msgText = "Ошибка в аргументе\n";							  break;
		case WSAEMFILE:				 msgText = "Слишком много файлов открыто\n";				  break;
		case WSAEWOULDBLOCK:		 msgText = "Ресурс временно недоступен\n";					  break;
		case WSAEINPROGRESS:		 msgText = "Операция в процессе развития\n";				  break;
		case WSAEALREADY: 			 msgText = "Операция уже выполняется\n";					  break;
		case WSAENOTSOCK:   		 msgText = "Сокет задан неправильно\n";						  break;
		case WSAEDESTADDRREQ:		 msgText = "Требуется адрес расположения\n";				  break;
		case WSAEMSGSIZE:  			 msgText = "Сообщение слишком длинное\n";				      break;
		case WSAEPROTOTYPE:			 msgText = "Неправильный тип протокола для сокета\n";		  break;
		case WSAENOPROTOOPT:		 msgText = "Ошибка в опции протокола\n";					  break;
		case WSAEPROTONOSUPPORT:	 msgText = "Протокол не поддерживается\n";					  break;
		case WSAESOCKTNOSUPPORT:	 msgText = "Тип сокета не поддерживается\n";				  break;
		case WSAEOPNOTSUPP:			 msgText = "Операция не поддерживается\n";					  break;
		case WSAEPFNOSUPPORT:		 msgText = "Тип протоколов не поддерживается\n";			  break;
		case WSAEAFNOSUPPORT:		 msgText = "Тип адресов не поддерживается протоколом\n";	  break;
		case WSAEADDRINUSE:			 msgText = "Адрес уже используется\n";						  break;
		case WSAEADDRNOTAVAIL:		 msgText = "Запрошенный адрес не может быть использован\n";	  break;
		case WSAENETDOWN:			 msgText = "Сеть отключена\n";								  break;
		case WSAENETUNREACH:		 msgText = "Сеть не достижима\n";							  break;
		case WSAENETRESET:			 msgText = "Сеть разорвала соединение\n";					  break;
		case WSAECONNABORTED:		 msgText = "Программный отказ связи\n";						  break;
		case WSAECONNRESET:			 msgText = "Связь восстановлена\n";							  break;
		case WSAENOBUFS:			 msgText = "Не хватает памяти для буферов\n";				  break;
		case WSAEISCONN:			 msgText = "Сокет уже подключен\n";							  break;
		case WSAENOTCONN:			 msgText = "Сокет не подключен\n";							  break;
		case WSAESHUTDOWN:			 msgText = "Нельзя выполнить send: сокет завершил работу\n";  break;
		case WSAETIMEDOUT:			 msgText = "Закончился отведенный интервал  времени\n";		  break;
		case WSAECONNREFUSED:		 msgText = "Соединение отклонено\n";						  break;
		case WSAEHOSTDOWN:			 msgText = "Хост в неработоспособном состоянии\n";			  break;
		case WSAEHOSTUNREACH:		 msgText = "Нет маршрута для хоста\n";						  break;
		case WSAEPROCLIM:			 msgText = "Слишком много процессов\n";						  break;
		case WSASYSNOTREADY:		 msgText = "Сеть не доступна\n";							  break;
		case WSAVERNOTSUPPORTED:	 msgText = "Данная версия недоступна\n";					  break;
		case WSANOTINITIALISED:		 msgText = "Не выполнена инициализация WS2_32.DLL\n";		  break;
		case WSAEDISCON:			 msgText = "Выполняется отключение\n";						  break;
		case WSATYPE_NOT_FOUND:		 msgText = "Класс не найден\n";								  break;
		case WSAHOST_NOT_FOUND:		 msgText = "Хост не найден\n";								  break;
		case WSATRY_AGAIN:			 msgText = "Неавторизированный хост не найден\n";			  break;
		case WSANO_RECOVERY:		 msgText = "Неопределенная ошибка\n";						  break;
		case WSANO_DATA:			 msgText = "Нет записи запрошенного типа\n";				  break;
		case WSA_INVALID_HANDLE:	 msgText = "Указанный дескриптор события  с ошибкой\n";		  break;
		case WSA_INVALID_PARAMETER:	 msgText = "Один или более параметров с ошибкой\n";			  break;
		case WSA_IO_INCOMPLETE:		 msgText = "Объект ввода-вывода не в сигнальном состоянии\n"; break;
		case WSA_IO_PENDING:		 msgText = "Операция завершится позже\n";					  break;
		case WSA_NOT_ENOUGH_MEMORY:	 msgText = "Не достаточно памяти\n";						  break;
		case WSA_OPERATION_ABORTED:	 msgText = "Операция отвергнута\n";							  break;
		case WSAEINVALIDPROCTABLE:	 msgText = "Ошибочный сервис\n";							  break;
		case WSAEINVALIDPROVIDER:	 msgText = "Ошибка в версии сервиса\n";						  break;
		case WSAEPROVIDERFAILEDINIT: msgText = "Невозможно инициализировать сервис\n";			  break;
		case WSASYSCALLFAILURE:		 msgText = "Аварийное завершение системного вызова\n";		  break;
		default:					 msgText = "Error\n";										  break;
	};
	return msgText;
}

string SetErrorMsgText (string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
};

SOCKET cS;
SOCKADDR_IN serv;
int len;
char inBuf[30];
bool EnterCA(char* FileName)
{
	string str("enter");
	str.append(FileName);

	int c=sendto(cS, str.c_str(), str.length(), NULL, (sockaddr*)&serv, len);

	if (recvfrom(cS, inBuf, sizeof(inBuf), NULL, (sockaddr*)&serv, &len))
	{
		if ((const char*)inBuf[0] == (const char*)'e')
		{
			cout << "client enter in the flow" << endl;
		}
		else if ((const char*)inBuf[0] == (const char*)'l')
		{
			cout << "client leave the flow" << endl;
		}

		recvfrom(cS, inBuf, sizeof(inBuf), NULL, (sockaddr*)&serv, &len);
		cout << inBuf << endl;

		if (inBuf)
		{
			return true;
		}
		return false;

	}
	else
		return false;
}

bool LeaveCA(char* FileName)
{
	string str("leave");
	str.append(FileName);
	sendto(cS, str.c_str(), str.length(), NULL, (sockaddr*)&serv, len);
	return true;
}

HDFS OpenDFSFile(char* FileName, char* FileWay)
{
	if (EnterCA(FileName))
	{
		HANDLE ptrFile = CreateFileA(FileWay, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (ptrFile != NULL)
		{
			return ptrFile;
		}
		return 0;
	}
	return 0;
}

int ReadDFSFile(HDFS hdfs, void* buf, int bufsize)
{
	int s;
	if (ReadFile(hdfs, buf, bufsize, (LPDWORD)&s, NULL))
	{
		return 1;
	}
	else return -1;
}

int WriteDFSFile(HDFS hdfs, void* buf, int bufsize)
{
	int s;
	SetFilePointer(hdfs, NULL, NULL, FILE_END);
	if (WriteFile(hdfs, buf, bufsize, (LPDWORD)&s, NULL))
	{
		FlushFileBuffers(hdfs);//сбросить буфер
		return s;
	}
	else return -1;
}

void CloseDFSFile(HDFS hdfs, char* FileName)
{
	CloseHandle(hdfs);
	LeaveCA(FileName);
}

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_CTYPE, "Russian");
	
	string IP = "127.0.0.1";	
	time_t rawtime;
	struct tm * timeinfo;


	char buffer[80];                                // строка, в которой будет храниться текущее время
	cout << "ClientU" << endl;

	try
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		if ((cS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());
		serv.sin_family  = AF_INET;
		serv.sin_port = htons(2000);
		serv.sin_addr.s_addr = inet_addr(IP.c_str());
		len = sizeof(serv);

		char buf[200];

		while (true)
		{
			char start;
			cin >> start;

			if (start)
			{
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				ZeroMemory(buffer, 80);
				ZeroMemory(buf, 200);
				strftime(buffer, 80, "%c", timeinfo);

				HDFS h;
				h = OpenDFSFile("111", "111.txt");
				if (h)
				{
					cout << "OpenDFSFile" << endl;
					if (ReadDFSFile(h, buf, 10) > 0)
					{
						cout << "ReadDFSFile" << endl;
						cout << buf << endl;

						strcat(buffer, " ");

						strcat(buffer, inBuf);
						for (int i = 0; i < 10; i++)
						{
							cout << "111: " << buffer << endl;

							WriteDFSFile(h, buffer, strlen(buffer));
							WriteDFSFile(h, "\r\n", strlen("\r\n"));
						}
						cout << "TEXT WRITED" << endl;

						ZeroMemory(buffer, 80);
						Sleep(5000);
						CloseDFSFile(h, "111");
					}
				}
				else
				{
					cout << "Another client use file, try again" << endl;
				}
			}
		}


		if (closesocket(cS) == SOCKET_ERROR)
			throw SetErrorMsgText("Closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)         
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}
	cout << endl;
	system("pause");
return 0;
}