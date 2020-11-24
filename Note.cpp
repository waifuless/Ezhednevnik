#include "Note.h"

Note::Note() {
	time = "00:00";
	noteImportance = Importance::LOW;
	noteText = "";
}

/*Note::Note(std::string time, Importance importance, std::string noteText) {
	this->time = time;
	this->noteImportance = importance;
	this->noteText = noteText;
}*/

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

void Note::setTime(std::string time) {
	this->time = time;
}

void Note::setNoteImportance(std::string importanceString) {
	switch (importanceString.at(0)) {
	case 'Н' : noteImportance = Importance::LOW;
		break;
	case 'О': noteImportance = Importance::REGULAR;
		break;
	case 'В': noteImportance = Importance::HIGH;
		break;
	default: noteImportance = Importance::LOW;
		break;
	}
}

void Note::setNoteText(std::string text) {
	this->noteText = text;
}

void Note::print() const{
	std::cout << "Время : " << time << std::endl;
	std::cout << "Важность : " << getNoteImportance() << std::endl;
	std::cout << "Текст заметки : "<<std::endl << noteText << std::endl;
	return;
}

void Note::create() { //Сделать проверки на ввод правильных данных
	char data[150];
	std::cout << "Время : " << std::endl;
	std::cin.getline(data, 150);
	OemToCharA(data, data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	time = data;
	std::cout << "Важность заметки(Высокая, Обычная, Низкая) : " << std::endl;
	std::cin.getline(data, 150);
	OemToCharA(data, data); ///перекодировка необходима, т.к. работаем с киррилицей.
	setNoteImportance(data);
	std::cout << "Текст заметки : " << std::endl;
	std::cin.getline(data, 150);
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