#include "Note.h"

Note::Note() {
	time = "00:00";
	noteImportance = Importance::LOW;
	noteText = "";
}

Note::Note(std::string time, Importance importance, std::string noteText) {
	this->time = time;
	this->noteImportance = importance;
	this->noteText = noteText;
}

std::string Note::getTime() const{
	return time;
}

std::string Note::getNoteImportance() const{ //����� ���������� ������, ��������������� �������� ������������
	switch (noteImportance) {
	case LOW: return "������";
		break;
	case REGULAR: return "�������";
		break;
	case HIGH: return "�������";
		break;
	default: return"";
		break;
	}
}

std::string Note::getNoteText() const {
	return noteText;
}

void Note::setTime(std::string time) { //��������������� ���� time. ���������� �������� �� ������������ ��������� ������
	int hours = -1, minutes = -1;
	char data[150];
	std::regex timeFormat("\\d{2}:\\d{2}"); //�������� �������������� � ������� ����������� ��������� (��������� �������� - "��� �����:��� �����")
	if (std::regex_match(time, timeFormat)) {
		hours = std::stoi(time.substr(0, 2));
		minutes = std::stoi(time.substr(3, 2));
	}
	if (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || time.size()>5) {
		do {
			std::cout << std::endl << "������� ����� ������, �������������� ����� ��:�� "<<std::endl;
			std::cin >> time;
			if (StreamChecker::isStreamFail(std::cin)) { continue; }
			if (!std::regex_match(time, timeFormat)) { continue; } //��������
			hours = std::stoi(time.substr(0, 2));
			minutes = std::stoi(time.substr(3, 2));
		} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0||time.size()>5);
	}
	OemToCharA(time.c_str(), data);  ///������������� ����������, �.�. �������� � ����������.
	this->time = data;
}

void Note::setNoteImportance(std::string importanceString) { //������������� �������� ������������, �������� ���������� ������
	if (importanceString.size() != 0) {
		switch (importanceString.at(0)) {
		case '�': case '�': noteImportance = Importance::LOW;
			break;
		case '�':  case '�': noteImportance = Importance::REGULAR;
			break;
		case '�':  case '�': noteImportance = Importance::HIGH;
			break;
		default: noteImportance = Importance::LOW;
			break;
		}
	}
}

void Note::setNoteText(std::string text) { //������������� ����� �������� ���� noteText
	char data[250];
	if (text.size() > 250) {
		std::cout << std::endl << "������ ������ ������� ������ �������(>250)";
		return;
	}
	OemToCharA(text.c_str(), data);  ///������������� ����������, �.�. �������� � ����������.
	this->noteText = data;
}

void Note::print() const{  //����� ��� ������ ���������� �� ������� �� �����
	std::cout << "����� : " << time << std::endl;
	std::cout << "�������� : " << getNoteImportance() << std::endl;
	std::cout << "����� ������� : "<<std::endl << noteText << std::endl;
	return;
}

void Note::create() { //����� ��� ���������� ����� �������, ����������� �������� �� ���� ������ � ������ �������, 
	char data[250];			//���������� ������������� �����(����� ��� ������ � ����������)
	int hours = -1, minutes = -1;
	std::regex timeFormat("\\d{2}:\\d{2}"); //������������ ���������� ���������
	std::string newTime;
	do {
		std::cout << std::endl << "������� �����, �������������� ����� ��:�� "<<std::endl;
		std::cin >> newTime;
		if (StreamChecker::isStreamFail(std::cin)) { continue; }
		if (!std::regex_match(newTime, timeFormat)) { continue; }
		hours = std::stoi(newTime.substr(0, 2));
		minutes = std::stoi(newTime.substr(3, 2));
	} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || newTime.size()>5); //�������� �� ���������� ���� ������
	OemToCharA(newTime.c_str(), data);  ///������������� ����������, �.�. �������� � ����������.
	time = data;
	std::cout << "�������� �������(�������, �������, ������) : " << std::endl;
	std::cin.getline(data, 150);
	OemToCharA(data, data); ///������������� ����������, �.�. �������� � ����������.
	setNoteImportance(data);
	std::cout << "����� ������� : (������ - 250 ��������)" << std::endl;
	std::cin.getline(data, 250);
	OemToCharA(data, data);
	noteText = data;
}

std::ostream& operator<< (std::ostream& out, const Note& note) { //���������� ��������� <<, ��� ������ � �����(������������ ��� ������ � ����)
	out << note.time << std::endl;
	out << note.getNoteImportance() << std::endl; //�� ������� ������������ ������ ��������������� �������� ������������
	out << note.noteText << std::endl;
	return out;
}

std::istream& operator>> (std::istream& in, Note& note) { //���������� ��������� >>, ��� ����� �� ������.(������������ ��� ������ �� �����)
	std::string noteImp;
	std::getline(in, note.time);
	std::getline(in, noteImp);
	note.setNoteImportance(noteImp); //� ������ ���������� ������, � ������������ � ������� ����� ����������� �������� ������������
	std::getline(in, note.noteText);
	return in;
}