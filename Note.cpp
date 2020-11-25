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

std::string Note::getNoteImportance() const{
	switch (noteImportance) {
	case LOW: return "Низкий";
		break;
	case REGULAR: return "Обычный";
		break;
	case HIGH: return "Высокий";
		break;
	default: return"";
		break;
	}
}

std::string Note::getNoteText() const {
	return noteText;
}

void Note::setTime(std::string time) { //проверку потом
	int hours, minutes;
	char data[150];
	hours = std::stoi(time.substr(0, 2));
	minutes = std::stoi(time.substr(3, 2));
	if (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || time.size()>5) {
		do {
			std::cout << std::endl << "Введите время заново, соответственно форме ЧЧ:ММ "<<std::endl;
			std::cin >> time;
			if (StreamChecker::isStreamFail(std::cin)) { return; }
			hours = std::stoi(time.substr(0, 2));
			minutes = std::stoi(time.substr(3, 2));
		} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0||time.size()>5);
	}
	OemToCharA(time.c_str(), data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	this->time = data;
}

void Note::setNoteImportance(std::string importanceString) {
	if (importanceString.size() != 0) {
		switch (importanceString.at(0)) {
		case 'Н': case 'н': noteImportance = Importance::LOW;
			break;
		case 'О':  case 'о': noteImportance = Importance::REGULAR;
			break;
		case 'В':  case 'в': noteImportance = Importance::HIGH;
			break;
		default: noteImportance = Importance::LOW;
			break;
		}
	}
}

void Note::setNoteText(std::string text) {
	char data[250];
	if (text.size() > 250) {
		std::cout << std::endl << "Размер текста заметки больше предела(>250)";
		return;
	}
	OemToCharA(text.c_str(), data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	this->noteText = data;
}

void Note::print() const{
	std::cout << "Время : " << time << std::endl;
	std::cout << "Важность : " << getNoteImportance() << std::endl;
	std::cout << "Текст заметки : "<<std::endl << noteText << std::endl;
	return;
}

void Note::create() { //Сделать проверки на ввод правильных данных
	char data[250];
	int hours = 0, minutes = 0;
	std::string newTime;
	do {
		std::cout << std::endl << "Введите время, соответственно форме ЧЧ:ММ "<<std::endl;
		std::cin >> newTime;
		if (StreamChecker::isStreamFail(std::cin)) { return; }
		hours = std::stoi(newTime.substr(0, 2));
		minutes = std::stoi(newTime.substr(3, 2));
	} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || time.size()>5);
	OemToCharA(newTime.c_str(), data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	time = data;
	std::cout << "Важность заметки(Высокая, Обычная, Низкая) : " << std::endl;
	std::cin.getline(data, 150);
	OemToCharA(data, data); ///перекодировка необходима, т.к. работаем с киррилицей.
	setNoteImportance(data);
	std::cout << "Текст заметки : (предел - 250 символов)" << std::endl;
	std::cin.getline(data, 250);
	OemToCharA(data, data);
	noteText = data;
}

std::ostream& operator<< (std::ostream& out, const Note& note) {
	out << note.time << std::endl;
	out << note.getNoteImportance() << std::endl;
	out << note.noteText << std::endl;
	return out;
}

std::istream& operator>> (std::istream& in, Note& note) {
	std::string noteImp;
	std::getline(in, note.time);
	std::getline(in, noteImp);
	note.setNoteImportance(noteImp);
	std::getline(in, note.noteText);
	return in;
}