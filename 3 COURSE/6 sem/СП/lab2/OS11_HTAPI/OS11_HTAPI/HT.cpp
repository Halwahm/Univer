#include "pch.h"

#include "HT.h"
#include <Windows.h>
#include <time.h>
#include "HTSupport.h"
#include <stdio.h>
#include <stdlib.h>

char commonErrorDescription[2048] = "";

const char fileMappingName[] = "Local\\HTFMAP";

// ��������� ������������� ������� � ��������� ������� ����������
HANDLE hMutex = NULL;
const char hMutexName[] = "Local\\HTFMAP_MUTEX";

extern "C" __declspec(dllexport) HTHANDLE* Create(
	int	  Capacity,					   // ������� ���������
	int   SecSnapshotInterval,		   // ������������� ���������� � ���.
	int   MaxKeyLength,                // ������������ ������ �����
	int   MaxPayloadLength,            // ������������ ������ ������
	const char  FileName[512]          // ��� ����� 
)
{
	HTHANDLE* ht = NULL;

	try
	{
		// 

		if (hMutex == NULL) hMutex = CreateMutex(NULL, false, hMutexName); 

		//

		ht = new HTHANDLE(Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, FileName);

		InitializeCriticalSection(&ht->csection);

		ht->File = CreateFile(FileName,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (ht->File == INVALID_HANDLE_VALUE)
		{
			strcpy(ht->LastErrorMessage, "������ �������� ��� �������� �����");
			throw "������ �������� ��� �������� �����";
		}

		// ������������� ������ ��� ����� ���������
		DWORD HTMaximumSize = sizeof(HTControl) + Capacity * (MaxKeyLength + MaxPayloadLength);

		// ������� ��� ��������� ����������� ��� ���������� ������ ������������� � ������ (�������������) ����� ��� ��������� �����.
		ht->FileMapping = CreateFileMapping(ht->File,
			NULL,
			PAGE_READWRITE,
			0,
			HTMaximumSize,
			fileMappingName
		);
		if (ht->FileMapping == NULL)
		{
			strcpy(ht->LastErrorMessage, "������ �������� ����������� ����� � ������");
			throw "������ �������� ����������� ����� � ������";
		}

		// MapViewOfFile ���������� ������������� ������������� ����� � �������� ������������ ����������� ��������

		ht->Addr = MapViewOfFile(ht->FileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		// ������������ ������ (����), ������ � ��������� ������-������, ������� ����� ��������, �������, ����� ������������ ������ (0 - ���� ����)

		if (ht->Addr == NULL)
		{
			strcpy(ht->LastErrorMessage, "������ ������������� ������������� ����� � �������� ������������� ��������");
			throw "������ ������������� ������������� ����� � �������� ������������� ��������";
		}

		time(&(ht->lastsnaptime)); 		// time() ���������� ������� ����� ������� ��� �������� time_t

		// �������� � ������ ������ (�����) ������ ����� ����������� ���������

		memcpy(ht->Addr, (const void*)(&(ht->htc)), sizeof(HTControl));

		// 

		ht->snap_stop_Event = CreateEvent(NULL, // �� ����������� ��������� ����������
			false, // auto-reset event
			false,
			NULL);

		// ������ snap-��������� ��� ���������� ���������
		// CreateThread() ���������� ������, ��������� ������ �����, ������� ������, �������� ������, ����� ��������, ������������� ������

		ht->snapthread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&SnapThread, (LPVOID)ht, NULL, NULL);

	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "����� - ���������� � Create(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

		delete[] ht;
		ht = NULL;
	}

	return ht;
}

extern "C" __declspec(dllexport) BOOL Close(const HTHANDLE* hthandle, char* resultInfo)
{
	bool retval = true;

	try
	{
		if (hthandle == NULL)
		{
			strcpy(resultInfo, "������� �������� ��������������� �������");
			throw "������� �������� ��������������� �������";
		}

		Snap(hthandle);

		if (hthandle->Addr != NULL)
			if (!UnmapViewOfFile(hthandle->Addr)) throw "������ �������� ����������� ����� � ������";

		if (hthandle->FileMapping != NULL)
			if (!CloseHandle(hthandle->FileMapping)) throw "������ �������� ����������� ����������� ����� � ������";

		if (hthandle->File != NULL)
			if (!CloseHandle(hthandle->File)) throw "������ �������� ����������� �����";

		// ������� �������� ������ snap
		if (hthandle->snap_stop_Event != NULL)
			SetEvent(hthandle->snap_stop_Event); // ��������� ������� � ���������� ���������

		if (hthandle->snapthread != NULL)
		{ 
			DWORD wres = WaitForSingleObject(hthandle->snapthread, 3000); // 3 ������� ���� ���������� ������ ������ snap
			if (wres == WAIT_TIMEOUT) TerminateThread(hthandle->snapthread, -1); // �� ��������� ���������������� ���������� ������� ����� ������ - ������������� ��������� �����
			if (!CloseHandle(hthandle->snapthread)) throw "������ �������� ����������� ������";
		}

		DeleteCriticalSection((LPCRITICAL_SECTION)&(hthandle->csection));

		if (hthandle->snap_stop_Event != NULL)
			if (!CloseHandle(hthandle->snap_stop_Event)) throw "������ �������� ����������� �������";

		// �������� ������� ������������� ������� � ���������
		if (hMutex != NULL)
			if (!CloseHandle(hMutex)) throw "������ �������� ������� ������������� ������� � ���������";

	}
	catch (const char* em)
	{
		retval = false;
		strcpy(commonErrorDescription, "����� - ���������� � Close(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	return retval;
}

// ������������ �������� ���������
extern "C" __declspec(dllexport) BOOL Insert(const HTHANDLE* hthandle, const Element*  element)
{
	bool result = true;

	try
	{
		// ������������� ����������������� ������� � ���������
		WaitForSingleObject(hMutex, INFINITE); // ���� ������������ ������� � ���������
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // ���������� ���������� �����������

		// �������� �� ����������� ������������ ����������� ����� � �������� ������

		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� ������������ ����������� �����");
			throw "��������� ������������ ����������� �����";
		}

		if (element->payloadlength > hthandle->htc.MaxPayloadLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� ������������ ����������� �������� ������");
			throw "��������� ������������ ����������� �������� ������";
		}

		// ��������� �� ����� ������� ��������� � ���������

		if (Get(hthandle, new Element(element->key, element->keylength)) != NULL)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� �������� ����� � ��������� - ����� ���������� ��������");
			throw "��������� �������� ����� � ��������� - ����� ���������� ��������";
		}

		char* memfile = (char*)hthandle->Addr;

		// ����� ��� �� �������� �����
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		// ���� hash ������ ���������� ������ � ���������, �� �������� ��������� � 1�� �����
		idx = (idx <= hthandle->htc.Capacity ? idx : 1); // ����� �������� �����	

		if (*(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)) == '\0') { // ���� �� �����

			memcpy(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), element->key, element->keylength);
			memcpy(memfile + sizeof(HTControl) + (idx - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, element->payload, element->payloadlength);

		}

		else { // ���� ����� - ���� ������ ��������� ���� ������� � �������

			int slotcounter = 0; // ������� ������������� ������

			int k = idx;
			while (*(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)) != '\0') {

				if (++k > hthandle->htc.Capacity) k = 1; // ��� ���������� ���������� ����� - ��������� � ������

				if (++slotcounter >= hthandle->htc.Capacity)
				{
					// ��������� �����������

					strcpy((char*)(hthandle->LastErrorMessage), "���������� �������� ������� � ��������� - ��������� ���������");
					throw "���������� �������� ������� � ��������� - ��������� ���������";

				}
			}

			// ������ k ������ ����� ������� ������� �����
			memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), element->key, element->keylength);
			memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, element->payload, element->payloadlength);

		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

		result = false;
		strcpy(commonErrorDescription, "����� - ���������� � Insert(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

	return result;
}

extern "C" __declspec(dllexport) Element* Get(const HTHANDLE* hthandle, const Element* element)
{
	Element* newelem = NULL;

	try
	{
		// ������������� ����������������� ������� � ���������
		// WaitForSingleObject(hMutex, INFINITE); // ���� ������������ ������� � ���������
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // ���������� ���������� �����������

		// �������� �� ����������� ������������ ����������� �����

		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� ������������ ����������� �����");
			throw "��������� ������������ ����������� �����";
		}

		// ����� ��� �� �������� �����
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		//
		// ���� hash ������ ���������� ������ � ���������, �� �������� ��������� � 1�� �����
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // ����� �������� �����	
		int slotcheck = 0; // ���-�� ������������� ������

		do {

			// �� ��� ���� �������� ����� � ����� �� �������� � ��������� ���� �� ����� ����������� ��� �����

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)element->key) == 0) { // ������ ������� �� �����

				newelem = new Element(element->key, element->keylength);

				newelem->payload = new char[hthandle->htc.MaxPayloadLength];
				ZeroMemory((void *)(newelem->payload), hthandle->htc.MaxPayloadLength);
				memcpy((void *)(newelem->payload), memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, hthandle->htc.MaxPayloadLength);
				newelem->payloadlength = strlen((char *)(newelem->payload)) + 1; // ������� ���� (������ ����� ������) ����� ����� �������� ������

				break;

			}

			if (++k > hthandle->htc.Capacity) k = 1; // ��� ���������� ���������� ����� - ��������� � ������

		} while (++slotcheck != hthandle->htc.Capacity);

		if (newelem == NULL)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "������� �� ������");
			throw "������� �� ������";
		}
	}
	catch (const char* em)
	{
		newelem = NULL;
		
		strcpy(commonErrorDescription, "����� - ���������� � Get(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}


	return newelem;
}

extern "C" __declspec(dllexport) BOOL Update(const HTHANDLE* hthandle, Element* oldelement, const void* newpayload, int newpayloadlength)
{
	bool result = false;

	Element* newelem = new Element(oldelement, newpayload, newpayloadlength);

	try
	{
		// ������������� ����������������� ������� � ���������
		WaitForSingleObject(hMutex, INFINITE); // ���� ������������ ������� � ���������
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // ���������� ���������� �����������

		// �������� �� ����������� ������������ ����������� �������� ������

		if (newelem->payloadlength > hthandle->htc.MaxPayloadLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� ������������ ����������� �������� ������");
			throw "��������� ������������ ����������� �������� ������";
		}

		// ����� ��� �� �������� �����
		int idx = BuildHash(newelem->key, strlen((const char*)(newelem->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		// ���� ��������� ���� �� �������� �����

		// ���� hash ������ ���������� ������ � ���������, �� �������� ��������� � 1�� �����
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // ����� �������� �����		

		int slotcheck = 0; // ���-�� ������������� ������

		do {

			// �� ��� ���� �������� ����� � ����� �� �������� � ��������� ���� �� ����� ����������� ��� �����

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)oldelement->key) == 0) { // ������ ������� �� �����

				memcpy(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength) + hthandle->htc.MaxKeyLength, newelem->payload, newelem->payloadlength);

				result = true; // ������� ������ � ��������

				break; // while

			} // ������ ������� �� �����

			if (++k > hthandle->htc.Capacity) k = 1; // ��� ���������� ���������� ����� - ��������� � ������

		} while (++slotcheck != hthandle->htc.Capacity);

		if (!result) // ������� ��� ���������� �� ������
		{
			strcpy((char*)(hthandle->LastErrorMessage), "������� ���������� ��������������� ��������");
			throw "������� ���������� ��������������� ��������";
		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

		result = false;

		strcpy(commonErrorDescription, "����� - ���������� � Update(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

	return result;
}

extern "C" __declspec(dllexport) BOOL Delete(const HTHANDLE* hthandle, const Element*  element)
{
	bool result = false;

	try
	{
		// ������������� ����������������� ������� � ���������
		WaitForSingleObject(hMutex, INFINITE); // ���� ������������ ������� � ���������
		//

		strcpy((char*)(hthandle->LastErrorMessage), ""); // ���������� ���������� �����������

		// �������� �� ����������� ������������ ����������� �����
		if (element->keylength > hthandle->htc.MaxKeyLength)
		{
			strcpy((char*)(hthandle->LastErrorMessage), "��������� ������������ ����������� �����");
			throw "��������� ������������ ����������� �����";
		}

		// ����� ��� �� �������� �����
		int idx = BuildHash(element->key, strlen((const char*)(element->key)) + 1);

		char* memfile = (char*)hthandle->Addr;

		//

		// ���� ��������� ���� �� �������� �����

		// ���� hash ������ ���������� ������ � ���������, �� �������� ��������� � 1�� �����
		int k = (idx <= hthandle->htc.Capacity ? idx : 1); // ����� �������� �����	

		int slotcheck = 0; // ���-�� ������������� ������

		do {

			// �� ��� ���� �������� ����� � ����� �� �������� � ��������� ���� �� ����� ����������� ��� �����

			char* slotkey = new char[hthandle->htc.MaxKeyLength];
			ZeroMemory(slotkey, hthandle->htc.MaxKeyLength);

			memcpy(slotkey, memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), hthandle->htc.MaxKeyLength);

			if (strcmp(slotkey, (const char *)element->key) == 0) { // ������ ������� �� �����

				ZeroMemory(memfile + sizeof(HTControl) + (k - 1)*(hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength), (hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength));

				result = true; // ������� ������ � ������

				break; // while

			} // // ������ ������� �� �����

			if (++k > hthandle->htc.Capacity) k = 1; // ��� ���������� ���������� ����� - ��������� � ������

		} while (++slotcheck != hthandle->htc.Capacity);

		if (!result) // ������� ��� �������� �� ������
		{
			strcpy((char*)(hthandle->LastErrorMessage), "������� �������� ��������������� ��������");
			throw "������� �������� ��������������� ��������";
		}

	}
	catch (const char* em)
	{
		if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

		result = false;

		strcpy(commonErrorDescription, "����� - ���������� � Delete(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	if (hMutex != NULL) ReleaseMutex(hMutex); // ����������� ������ � ���������

	return result;
}

extern "C" __declspec(dllexport) HTHANDLE* Open(const char FileName[512], char* resultInfo)
{
	HTHANDLE* ht = NULL;

	try
	{
		//

		if (hMutex == NULL) hMutex = OpenMutex(SYNCHRONIZE, false, hMutexName);

		//

		HANDLE f = CreateFile(FileName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (f == INVALID_HANDLE_VALUE)
		{
			strcpy(resultInfo, "������ �������� ����� ��������� ��� ������");
			throw "������ �������� ����� ��������� ��� ������";
		}

		char buffparams[sizeof(HTControl)] = "";

		// ��������� � ����� ��������� ���������
		DWORD numberOfBytesRead = 0;

		if (!ReadFile(f, buffparams, sizeof(buffparams), &numberOfBytesRead, NULL))
		{
			strcpy(resultInfo, "������ ������ �����");
			throw "������ ������ �����";
		}
		// ��������� ���������� �����
		//CloseHandle(f);

		// �������� ��������� �������� ����������� ������������� �� ������������ ������
		HTControl htc = *((HTControl *)buffparams);

		ht = new HTHANDLE(htc.Capacity, htc.SecSnapshotInterval, htc.MaxKeyLength, htc.MaxPayloadLength, FileName);

		InitializeCriticalSection(&ht->csection);
		ht->File = f;

		// ��������� ������������ File Mapping
		ht->FileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS, TRUE, fileMappingName);

		if (ht->FileMapping == NULL)
		{
			strcpy(ht->LastErrorMessage, "������ �������� ����������� ����� � ������");
			throw "������ �������� ����������� ����� � ������";
		}

		ht->Addr = MapViewOfFile(ht->FileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);

		if (ht->Addr == NULL)
		{
			strcpy(ht->LastErrorMessage, "������ ������������� ������������� ����� � �������� ������������� ��������");
			throw "������ ������������� ������������� ����� � �������� ������������� ��������";
		}

		time(&(ht->lastsnaptime)); 		// time() ���������� ������� ����� ������� ��� �������� time_t

		ht->snap_stop_Event = CreateEvent(NULL, // �������� ������
			false, // auto-reset event
			false, // � ������������ ���������
			NULL); // ���

		// ht->snapthread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&SnapThread, (LPVOID)ht, NULL, NULL);

	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "����� - ���������� � Open(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}
	}

	return ht;
}

extern "C" __declspec(dllexport) BOOL Snap(const HTHANDLE* hthandle)
{
	// ������������� ����������������� ������� � ���������
	// WaitForSingleObject(hMutex, INFINITE); // ���� ������������ ������� � ���������
	//

	EnterCriticalSection((LPCRITICAL_SECTION)(&hthandle->csection));

	bool retval = true;
	try
	{
		// ���������� ������ �� ���� ��������� ���� � �������������� ������������� �����

		if (!FlushViewOfFile(hthandle->Addr, sizeof(HTControl) + hthandle->htc.Capacity * (hthandle->htc.MaxKeyLength + hthandle->htc.MaxPayloadLength)))
		{
			throw "������ ������ FlushViewOfFile()";
		}

		// ������� ��� �������� ������ ����� ��������� � ����

		if (!FlushFileBuffers(hthandle->File))
		{
			throw "������ ������ FlushFileBuffers()";
		}

		// ������� ����� snapshot

		time((time_t*)(&(hthandle->lastsnaptime))); 		// time() ���������� ������� ����� ������� ��� �������� time_t
		printf("\nspanshot � %s", ctime(&(hthandle->lastsnaptime)));
	}
	catch (const char* em)
	{
		strcpy(commonErrorDescription, "����� - ���������� � Snap(): ");
		strcat(commonErrorDescription, em);
		if (GetLastError() != 0)
		{
			strcat(commonErrorDescription, "\r\n��� ������: ");
			strcat(commonErrorDescription, _ultoa(GetLastError(), commonErrorDescription + strlen(commonErrorDescription), 10));
		}

		strcpy(((HTHANDLE*)hthandle)->LastErrorMessage, "����� ��� ���������� snapshot ���������");
	}

	LeaveCriticalSection((LPCRITICAL_SECTION)(&hthandle->csection));

	// ReleaseMutex(hMutex); // ����������� ������ � ���������

	return retval;
}

extern "C" __declspec(dllexport) void print(const Element* element)
{
	printf("����: %s ��������: %s", element->key, element->payload);
}
 
// extern "C" __declspec(dllexport) 
void SnapThread(void* paramAddr)
{
	// ��������� ��������� (����������� � ������ ���������� ������) - snap-��������� ��� ���������� ���������

	while (true)
	{
		Snap((HTHANDLE*)paramAddr);

		if (WaitForSingleObject(((HTHANDLE*)paramAddr)->snap_stop_Event, 100) == WAIT_OBJECT_0)
		{
			// ��������� ������� � ����������� ������ ������, ������� �� �����
			break;
		}

		Sleep(((HTHANDLE*)paramAddr)->htc.SecSnapshotInterval * 1000); // ����
	}

}

__declspec(dllexport) char* GetLastError(HTHANDLE* ht)
{
	return ht->LastErrorMessage;
}

__declspec(dllexport) char* GetLastError(HTHANDLE* ht, int htlen)
{
	return ht->LastErrorMessage;
}