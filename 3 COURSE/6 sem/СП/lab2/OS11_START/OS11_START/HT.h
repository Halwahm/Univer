#pragma once
#include <Windows.h>

// API HT - ����������� ��������� ��� ������� � ��-��������� 
//          ��-��������� ������������� ��� �������� ������ � �� � ������� ����/��������
//          ���������������� (�����������) ������ �������������� � ������� snapshot-���������� 
//          Create - �������  � ������� HT-��������� ��� �������������   
//          Open   - ������� HT-��������� ��� �������������
//          Insert - ������� ������� ������
//          Delete - ������� ������� ������    
//          Get    - ������  ������� ������
//          Update - �������� ������� ������
//          Snap   - �������� snapshot
//          Close  - ��������� Snap � ������� HT-��������� ��� �������������
//          GetLastError - �������� ��������� � ��������� ������

#pragma pack(push, 1)
struct HTControl
{
	// ��������� �������� ����������� �������������

	HTControl()
	{
		this->Capacity = 5000;
		this->SecSnapshotInterval = 10; // ������
		this->MaxKeyLength = 4;
		this->MaxPayloadLength = 10;
	}

	HTControl(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength)
	{
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
	}

	int Capacity;               // ������� ��������� � ���������� ��������� 
	int SecSnapshotInterval;    // ������������� ���������� � ���. 
	int MaxKeyLength;           // ������������ ����� �����
	int MaxPayloadLength;       // ������������ ����� ������
};
#pragma pack(pop)


#pragma pack(push, 1)
struct HTHANDLE    // ���� ���������� HT
{
	HTHANDLE()
	{
		this->htc.Capacity = 5000;
		this->htc.SecSnapshotInterval = 10; // ������
		this->htc.MaxKeyLength = 4;
		this->htc.MaxPayloadLength = 10;
		strcpy(this->FileName, ".\\temp\\HTspace.dat");
	}
	HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const char FileName[512])
	{
		this->htc.Capacity = Capacity;
		this->htc.SecSnapshotInterval = SecSnapshotInterval;
		this->htc.MaxKeyLength = MaxKeyLength;
		this->htc.MaxPayloadLength = MaxPayloadLength;
		strcpy(this->FileName, FileName);
	}
	HTControl htc; // ��������� �������� ����������� �������������

	char    FileName[512];          // ��� ����� 
	HANDLE  File = NULL;                   // File HANDLE != 0, ���� ���� ������
	HANDLE  FileMapping = NULL;            // Mapping File HANDLE != 0, ���� mapping ������  
	LPVOID  Addr;                   // Addr != NULL, ���� mapview ��������  
	char    LastErrorMessage[512];  // ��������� �� ��������� ������ ��� 0x00  
	time_t  lastsnaptime;           // ���� ���������� snap'a (time()) 

	CRITICAL_SECTION csection; // ����������� ������ ������� � snapshot-�����������
	HANDLE snapthread = NULL; // ���������� ������ snapshot-���������
	HANDLE snap_stop_Event = NULL; // ���������� ������� ���������� ��������� snapshot-���������
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Element   // ������� 
{
	Element()
	{

	}
	Element(const void* key, int keylength) // for Get                                          
	{
		this->key = key;
		this->keylength = keylength;
		this->payload = NULL;
		this->payloadlength = 0;
	}
	Element(const void* key, int keylength, const void* payload, int payloadlength) // for Insert
	{
		this->key = key;
		this->keylength = keylength;
		this->payload = payload;
		this->payloadlength = payloadlength;
	}
	Element(Element* oldelement, const void* newpayload, int newpayloadlength) // for update
	{
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = newpayload;
		this->payloadlength = newpayloadlength;
	}
	const void*     key;                 // �������� ����� 
	int             keylength;           // ������ �����
	const void*     payload;             // ������ 
	int             payloadlength;       // ������ ������
};
#pragma pack(pop)

extern "C" __declspec(dllimport) HTHANDLE*  Create   //  ������� HT             
(
	int	  Capacity,					   // ������� ���������
	int   SecSnapshotInterval,		   // ������������� ���������� � ���.
	int   MaxKeyLength,                // ������������ ������ �����
	int   MaxPayloadLength,            // ������������ ������ ������
	const char  FileName[512]          // ��� ����� 
); 	// != NULL �������� ����������  

extern "C" __declspec(dllimport) HTHANDLE*   Open     //  ������� HT - ����� OpenFileMapping()
(
	const char FileName[512],
	char* resultInfo
); 	// != NULL �������� ���������� 

extern "C" __declspec(dllimport) BOOL Snap         // ��������� Snapshot
(
	const HTHANDLE*    hthandle           // ���������� HT (File, FileMapping)
);


extern "C" __declspec(dllimport) BOOL Close        // Snap � ������� HT  �  �������� HTHANDLE
(
	const HTHANDLE*    hthandle, // ���������� HT (File, FileMapping)
	char* resultInfo 
);	//  == TRUE �������� ����������   


extern "C" __declspec(dllimport) BOOL Insert      // �������� ������� � ���������
(
	const HTHANDLE* hthandle,            // ���������� HT
	const Element*  element              // �������
);	//  == TRUE �������� ���������� 


extern "C" __declspec(dllimport) BOOL Delete      // ������� ������� � ���������
(
	const HTHANDLE* hthandle,            // ���������� HT (����)
	const Element*  element              // ������� 
);	//  == TRUE �������� ���������� 

extern "C" __declspec(dllimport) Element* Get     //  ������ ������� � ���������
(
	const HTHANDLE* hthandle,            // ���������� HT
	const Element*  element              // ������� 
); 	//  != NULL �������� ���������� 


extern "C" __declspec(dllimport) BOOL Update     //  ������� ������� � ���������
(
	const HTHANDLE* hthandle,            // ���������� HT
	Element*  oldelement,          // ������ ������� (����, ������ �����)
	const void*     newpayload,          // ����� ������  
	int             newpayloadlength     // ������ ����� ������
); 	//  != NULL �������� ���������� 

char* GetLastError  // �������� ��������� � ��������� ������
(
	HTHANDLE* ht                         // ���������� HT
);

extern "C" __declspec(dllimport) void print                               // ����������� ������� 
(
	const Element*  element              // ������� 
);

//extern "C" __declspec(dllimport) 
void SnapThread
(
	void* pAddr
);