// ServerU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "string.h"
#include <locale>
#include "time.h"
#include "Winsock2.h"
#include <queue>

#pragma comment(lib, "WS2_32.lib")

using namespace std;

class Link
{
public:
	char* FileName;
	char command;
	bool UsingFile;
	SOCKADDR_IN Adr;
	HANDLE WaitEvent;
	HANDLE Thread;
}; 

#define MAX_FILE 10
Link *masthr[MAX_FILE];
SOCKET sS;
int lc;

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
	return  msgText + GetErrorMsgText (code);
};




DWORD WINAPI Dispath(LPVOID lp)
{
	queue<SOCKADDR_IN> *q = new queue<SOCKADDR_IN>();
	int index = (int)lp;
	while (true)
	{
		cout << "ssss1 " << (masthr[index]->Adr).sin_port << endl;

		WaitForSingleObject(masthr[index]->WaitEvent,INFINITE);
		cout << "ssss2 " << (masthr[index]->Adr).sin_port << endl;

		if (masthr[index]->command == 'e'){
			if (q->empty())
			{
				char buf[5];
				char b[1] = { 'e' };
				sendto(sS, (const char*)b, sizeof(b), NULL, (sockaddr*)&masthr[index]->Adr, lc);

				itoa((masthr[index]->Adr).sin_port, buf, 10);

				sendto(sS, buf, sizeof(buf), NULL, (sockaddr*)&masthr[index]->Adr, lc);

			}
			q->push(masthr[index]->Adr);
		}
		else if (masthr[index]->command == 'l'){
			q->pop();
			char b[1] = { 'l' };
			sendto(sS, (const char*)b, sizeof(b), NULL, (sockaddr*)&masthr[index]->Adr, lc);
			cout << "Leave " << (masthr[index]->Adr).sin_port << endl;

			if (!q->empty()){
				cout << "Leave empty" << (masthr[index]->Adr).sin_port << endl;

				SOCKADDR_IN sc = q->front();
				sendto(sS, (char*)(masthr[index]->Adr).sin_port, sizeof((char*)(masthr[index]->Adr).sin_port), NULL, (sockaddr*)&sc, lc);
			}
		}
		cout << "ssss3 " << (masthr[index]->Adr).sin_port << endl;

	}
}

int _tmain(int argc, _TCHAR* argv[])
{	setlocale(LC_ALL, "Russian");
	
	std::cout << "ServerU" << endl;
	try
	{
		for (int i = 0; i < MAX_FILE; i++)
		{	
			masthr[i] = NULL;
		}
		WSADATA wsaData;
			if (WSAStartup(MAKEWORD(2,0), &wsaData) != 0)
				throw SetErrorMsgText("Startup: ", WSAGetLastError());
			if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
				throw SetErrorMsgText("Socket: ", WSAGetLastError());
			SOCKADDR_IN serv;
			serv.sin_family = AF_INET;
			serv.sin_port = htons(2000);
			serv.sin_addr.s_addr = INADDR_ANY;
			
			if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
				throw SetErrorMsgText("Bind_Server: ", WSAGetLastError());
			
			while(true)
			{
				SOCKADDR_IN client;
				lc = sizeof(SOCKADDR_IN);
				char ibuf[50];
				ZeroMemory(ibuf, 50);
				if ((recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&client, &lc)) == SOCKET_ERROR)
					throw SetErrorMsgText("RecvFrom: ", WSAGetLastError());
				int port = client.sin_port;
				std::cout << "Client (" << inet_ntoa(client.sin_addr) << ":" << port << "): " << ibuf << endl;
				bool create = true;
				for (int i = 0; i < MAX_FILE; i++)
				{
					if (masthr[i] != NULL)
					{
						if (strcmp(ibuf + 5, masthr[i]->FileName) == 0)
						{
							std::cout << "Client (" << inet_ntoa(client.sin_addr) << ":" << port << "): " << "Create rout" << endl;

							create = false;
							masthr[i]->command = ibuf[0];
							masthr[i]->Adr = client;
							SetEvent(masthr[i]->WaitEvent);
							break;
						}
					}
				}
				if (create)
				{
					Link* a = new Link();
					int pos = -1;
					bool findplace = false;
					for (int i = 0; i < MAX_FILE; i++)
					{
						if (masthr[i] == 0) 
						{
							findplace = true;
							pos = i;
							masthr[i] = a;
							break;
						}
					}

					if (!findplace)
					{
						std::cout << "not create new thread" << endl;
						break;
					}
					char* filename = new char[strlen(ibuf)-5];
					strcpy(filename, ibuf + 5);

					a->FileName=filename;
					a->command = ibuf[0];
					a->Adr = client;
					a->UsingFile = false;
					a->WaitEvent = CreateEvent(NULL, false, true, NULL);
					a->Thread = CreateThread(NULL, NULL,&Dispath,(void*)pos, NULL, NULL);
					SetEvent(a->WaitEvent);
				}
			}
		
		if(closesocket(sS) == SOCKET_ERROR)
			throw SetErrorMsgText("close socket: ", WSAGetLastError());
		if(WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		std::cout << endl << errorMsgText;
	}
	system("pause");

	return 0;
}

