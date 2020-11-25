#include <iostream>
#include "DairyExecutor.h"
#include <clocale>
#include "StreamChecker.h"

int menu();

int main() {
	setlocale(LC_ALL, "rus");
	while (1) {   //��������� ��������, ���� ������������ �� ������� "�����"
		switch (menu()) {  //�������� ����
		case 1: DairyExecutor::viewCalendar();
			break;
		case 2: DairyExecutor::makeNote();
			break;
		case 3: DairyExecutor::delNote();
			break;
		case 4: DairyExecutor::redactNote();
			break;
		case 5: DairyExecutor::viewNotesForToday();
			break;
		case 6: DairyExecutor::viewNotesForSomeDay();
			break;
		case 7: return 0;
			break;
		default: std::cout << std::endl << "�������� ��� ����� ������� �� ���������";
			continue;
			break;
		}
	}
}

int menu() {  //��� ��� ������ ��������
	int choice = 0;
	std::cout << std::endl << "�������� �������� : "
		<< std::endl << "1)���������� ���������"
		<< std::endl << "2)�������� �������"
		<< std::endl << "3)������� �������"
		<< std::endl << "4)������������� �������"
		<< std::endl << "5)���������� ������� �� �������"
		<< std::endl << "6)���������� ������� �� ������ ����"
		<< std::endl << "7)�����"<<std::endl;
	std::cin >> choice;
	if (StreamChecker::isStreamFail(std::cin)) {
		return 0;
	}
	return choice;
}