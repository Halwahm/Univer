#pragma once
#include <string>
#include <Windows.h>
struct stringNode {
	stringNode* next = NULL;
	std::string ip;
	int count = 0;
	double avgCorrection = 0;
};
class stringList
{
public:
	stringList();
	~stringList();
	void push(stringNode* element) {
		if (head == NULL) {
			head = element;
			head->next = NULL;
			_size++;
		}
		else {
			element->next = head;
			head = element;
			_size++;
		}
	}
	int size() {
		return _size;
	}
	void push_back(stringNode* element) {
		if (head == NULL) {
			head = element;
			head->next = NULL;
			_size++;
		}
		else {
			stringNode* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = element;
			temp->next->next = NULL;
			_size++;
		}
	}
	stringNode* get(DWORD i) {
		if (i >= 0 && i < _size) {
			if (i == 0) {
				stringNode* node = new stringNode();
				node->avgCorrection = head->avgCorrection;
				node->ip = head->ip;
				node->count = head->count;
				return node;
			}
			else {
				int t = 0;
				stringNode* temp = head;
				while (t < i) {
					temp = temp->next;
					t++;
				}
				stringNode* node = new stringNode();
				node->avgCorrection = temp->avgCorrection;
				node->ip = temp->ip;
				node->count = temp->count;
				return node;
			}
		}
		return nullptr;
	}
	stringNode* get(std::string ip) {
		stringNode* temp = head;
		while (temp != NULL) {
			if (temp->ip == ip)return temp;
			temp = temp->next;
		}
		return nullptr;
	}
	BOOL contain(std::string ip) {
		stringNode* temp = head;
		while (temp != NULL) {
			if (temp->ip == ip)return TRUE;
			temp = temp->next;
		}
		return FALSE;
	}
	int indexOf(std::string ip) {
		stringNode* temp = head;
		int i = 0;
		while (temp != NULL) {
			if (temp->ip == ip)return i;
			i++;
			temp = temp->next;
		}
		return -1;
	}
	BOOL remove(DWORD i, stringNode* ip) {
		if (i > 0) {
			int t = 0;
			stringNode* temp = head;
			while (t < i - 1) {
				if (temp == NULL)return FALSE;
				temp = temp->next;
				t++;
			}
			if (temp->next == NULL)return FALSE;
			if (ip != NULL) {
				ip = temp->next;
				ip->next = NULL;
			}
			temp->next = temp->next->next;
			_size--;
			return TRUE;
		}
		if (i == 0) {
			if (ip != NULL) {
				ip = head;
			}
			head = head->next;
			if (ip != NULL) {
				ip->next = NULL;
			}
			_size--;
			return TRUE;
		}
		return FALSE;
	}
	std::string toConcatedString(std::string separator) {
		std::string result = "";
		stringNode* temp = head;
		if (head == NULL)return result;
		result += temp->ip;
		temp = temp->next;
		while (temp != NULL) {
			result += separator;
			result += temp->ip;
			temp = temp->next;
		}
		return result;
	}
private:
	stringNode* head;
	int _size = 0;
	
};

stringList::stringList()
{
	head = NULL;
	_size = 0;
}

stringList::~stringList()
{
}
