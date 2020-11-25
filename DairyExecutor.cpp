#include "DairyExecutor.h"

void DairyExecutor::viewCalendar() { //������� ��� ��������� ���������
	int year = 0, month = 0, choice = 0;
	std::cout << std::endl << "1)������� ��������� �� ���"
			  << std::endl << "2)������� ��������� �� �����"<<std::endl;
	std::cin >> choice;
	if (StreamChecker::isStreamFail(std::cin)) {return;} //��������, �� ������� ��� ���������� ������
	do {
		std::cout << std::endl << "������� ��� (1970-2200): ";
		std::cin >> year;
		if (StreamChecker::isStreamFail(std::cin)) { return; }
	} while (year < 1970||year>2200);
	if (choice == 2) {
		do {
			std::cout << std::endl << "������� ����� : ";
			std::cin >> month;
			if (StreamChecker::isStreamFail(std::cin)) {return;}
		} while (month > 12 || month < 1);
		Calendar::printMonth(month, year);  //���������� ������� ������ ������ ������
	}
	else {
		Calendar::printYear(year); // ���� ����, �� ������ ������������
	}
}

int DairyExecutor::daysInMonth(int month, int year) { //������� ���������� ���������� ���� � ���������� ������
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
		break;
	case 2: 
		if (year % 400 == 0) { //��������, ���������� �� ���
			return 29;
	}
		if (year % 100==0) {
			return 28;
	}
		if(year %4 ==0){
			return 29;
	}
		return 28;
		break;
	default: return 30;
		break;
	}
}

std::string DairyExecutor::getDayFileNameWithPath() { //������� � ������� ������������ ������ ���� ��� �������
	int year = 0, month = 0, day = 0;					//������� ���������� ���� � ����� � ����� �����
	std::cout << std::endl << "������� ����";
	do {
		std::cout << std::endl << "��� : ";
		std::cin >> year;
	}
	while (StreamChecker::isStreamFail(std::cin));
	do {
		std::cout << std::endl << "����� : ";
		std::cin >> month;
		if (StreamChecker::isStreamFail(std::cin)) { continue; }
	} while (month > 12 || month < 1);
	do {
		std::cout << std::endl << "���� : ";
		std::cin >> day;
		if (StreamChecker::isStreamFail(std::cin)) { continue; }
	} while (day > DairyExecutor::daysInMonth(month, year) || day < 1);
	return "Notes\\" + std::to_string(year) + "\\" + std::to_string(month) + "\\" + std::to_string(day) + ".txt";
}

void DairyExecutor::makeNote() { //������� ������� ������� � ���������� �� � ����
	int year=0, month=0, day=0;
	Note newNote;
	std::string fileName = DairyExecutor::getDayFileNameWithPath(); //�������� ���� � �����
	std::filesystem::create_directories(fileName.substr(0, fileName.find_last_of('\\'))); //������� ����� ��� �������� ������ �� ����������� ����
	std::ofstream out(fileName, std::ios::app);
	newNote.create();
	if (out.is_open()) {
		out << newNote;  //���������� ������� � ����
	}
	out.close();
}

void DairyExecutor::delNote() { //������� ������� ���� �������, ���� ���, �� ����� ������������
	int choice = 0;
	std::vector<Note> notes;
	std::ofstream out;
	std::string fileName = DairyExecutor::getDayFileNameWithPath();
	std::cout << std::endl << "�������� �������� :"
		<< std::endl << "1 - ������� ���� ������"
		<< std::endl << "2 - ������� ��� ������" << std::endl;
	std::cin >> choice;
	if (StreamChecker::isStreamFail(std::cin)) { return; }
	switch (choice) {
	case 1:
		notes = DairyExecutor::readVectorOfNotes(fileName);
		if (notes.size() == 0) {
			std::cout << std::endl << "������� �� ����������";
			return;
		}
		for (int i = 0; i < notes.size(); i++) {
			std::cout << i + 1 << ')';
			notes[i].print();
		}
		std::cout << "������� ����� ������ ";
		std::cin >> choice;
		if (StreamChecker::isStreamFail(std::cin)) { return; }
		out.open(fileName);
		for (int i = 0; i < notes.size(); i++) {  //����� ���������� �������� �� ����� �� ���������� ������� ���, ���� ����, ������� 
			if (i != choice - 1) {  //������������ ������� �������
				out << notes[i];
			}
		}
		out.close();
		break;
	case 2:
		remove(fileName.c_str()); //������� ����
		std::cout << std::endl << "��� ������ �������";
		break;
	default: std::cout << std::endl << "������ �������� �� ����������";
		return;
		break;
	}
}

void DairyExecutor::redactNote() { //����� ����������� ��������� ������������� �������
	int choiceOfNote = 0, choiceOfField = 0;
	char buffData[150];
	std::string newData;
	std::vector<Note> notes;
	std::string fileName = DairyExecutor::getDayFileNameWithPath();
	notes = readVectorOfNotes(fileName);  //������ ������ � ���������
	if (notes.size() == 0) {
		std::cout << std::endl << "������� �� ����������";
		return;
	}
	for (int i = 0; i < notes.size(); i++) {
		std::cout << i + 1 << ')';
		notes[i].print();
	}
	std::cout << "������� ����� ������ ";
	std::cin >> choiceOfNote;
	if (StreamChecker::isStreamFail(std::cin)) { return; }
	if (choiceOfNote > notes.size() || choiceOfNote < 0) {
		std::cout << std::endl << "������ ��� ����� ������� �����������";
		return;
	}
	std::cout << std:: endl << "����� ���� ���������� ��������?"
		<< std::endl << "1) �����"
		<< std::endl << "2) ��������"
		<< std::endl << "3) ����� �������" << std::endl;
	std::cin >> choiceOfField;
	if (StreamChecker::isStreamFail(std::cin)) { return; }
	std::cout << "������� ����� ������: " << std::endl;
	getline(std::cin, newData);
	switch (choiceOfField) {
	case 1: notes[choiceOfNote - 1].setTime(newData);   //���������� ����� ������ � ����, �� ����� ������������
		break;
	case 2: 
		OemToCharA(newData.c_str(), buffData);
		newData = buffData;
		notes[choiceOfNote - 1].setNoteImportance(newData);
		break;
	case 3: notes[choiceOfNote - 1].setNoteText(newData);
		break;
	default: std::cout << std::endl << "������ ���� �� ����������";
		return;
		break;
	}
	std::ofstream out(fileName);
	for (int i = 0; i < notes.size(); i++) { //���������� ������� ���������� �������
		out << notes[i];
	}
	out.close();
}

void DairyExecutor::viewNotesForToday() { //����� ������� ��� ������ ��� ����, ������� ����� � �������.
	std::vector<Note> notes;
	time_t seconds = time(NULL);
	tm* timeinf = localtime(&seconds);
	std::string fileName = "Notes\\" + std::to_string(timeinf->tm_year + 1900) + "\\" + std::to_string(timeinf->tm_mon+1) + 
		"\\" + std::to_string(timeinf->tm_mday) + ".txt"; //+1900, �.�. ������ ������� ���� � 1900 ����
	notes = DairyExecutor::readVectorOfNotes(fileName);
	std::cout << std::endl;
	if (notes.size() == 0) {
		std::cout << std::endl << "������� �� �������";
	}
	for (int i = 0; i < notes.size(); i++) {
		std::cout << i + 1 << ')';
		notes[i].print();
	}
}

std::vector<Note> DairyExecutor::readVectorOfNotes(std::string fileName) {  
	int year = 0, month = 0, day = 0;
	Note readNote;
	std::vector<Note> notes;
	std::ifstream in(fileName);
	if (in.is_open()) {
		while (!in.eof()) {
			in >> readNote; //����� ������ ������� �� �����,
			if (!in.eof()) {
				notes.push_back(readNote); //��������� ������ � ������
			}
		}
		in.close();
	}
	else {
		std::cout<<std::endl << "���� � ��������� �� ������";
	}
	return notes;  //���������� ������
}

void DairyExecutor::viewNotesForSomeDay() {  //����� ������� ������� ��� ���, ���������� �������������
	std::vector<Note> notes;
	std::string fileName = DairyExecutor::getDayFileNameWithPath();
	notes = DairyExecutor::readVectorOfNotes(fileName);  //������� ������, ������ �����
	std::cout << std::endl;
	if (notes.size() == 0) {
		std::cout << std::endl << "������� �� �������";
	}
	for (int i = 0; i < notes.size(); i++) {
		std::cout << i + 1 << ')';
		notes[i].print();  //������ �� �����
	}
}