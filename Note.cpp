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

std::string Note::getNoteImportance() const{ //метод возвращает строку, соответствующую значению перечисления
	switch (noteImportance) {
	case LOW: return "Низкая";
		break;
	case REGULAR: return "Обычная";
		break;
	case HIGH: return "Высокая";
		break;
	default: return"";
		break;
	}
}

std::string Note::getNoteText() const {
	return noteText;
}

void Note::setTime(std::string time) { //Устанавливается поле time. Происходит проверка на правильность введенных данных
	int hours = -1, minutes = -1;
	char data[150];
	std::regex timeFormat("\\d{2}:\\d{2}"); //проверка осуществляется с помощью регулярного выражения (выражение означает - "два числа:два числа")
	if (std::regex_match(time, timeFormat)) {
		hours = std::stoi(time.substr(0, 2));
		minutes = std::stoi(time.substr(3, 2));
	}
	if (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || time.size()>5) {
		do {
			std::cout << std::endl << "Введите время заново, соответственно форме ЧЧ:ММ "<<std::endl;
			std::cin >> time;
			if (StreamChecker::isStreamFail(std::cin)) { continue; }
			if (!std::regex_match(time, timeFormat)) { continue; } //проверка
			hours = std::stoi(time.substr(0, 2));
			minutes = std::stoi(time.substr(3, 2));
		} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0||time.size()>5);
	}
	OemToCharA(time.c_str(), data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	this->time = data;
}

void Note::setNoteImportance(std::string importanceString) { //устанавливаем значение перечисления, согласно полученной строке
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

void Note::setNoteText(std::string text) { //устанавливает новое значение поля noteText
	char data[250];
	if (text.size() > 250) {
		std::cout << std::endl << "Размер текста заметки больше предела(>250)";
		return;
	}
	OemToCharA(text.c_str(), data);  ///перекодировка необходима, т.к. работаем с киррилицей.
	this->noteText = data;
}

void Note::print() const{  //метод для вывода информации об объекте на экран
	std::cout << "Время : " << time << std::endl;
	std::cout << "Важность : " << getNoteImportance() << std::endl;
	std::cout << "Текст заметки : "<<std::endl << noteText << std::endl;
	return;
}

void Note::create() { //метод для заполнения полей объекта, выполняется проверка на ввод данных в нужном формате, 
	char data[250];			//просиходит перекодировка строк(нужна для работы с киррилицей)
	int hours = -1, minutes = -1;
	std::regex timeFormat("\\d{2}:\\d{2}"); //используется регулярное выражение
	std::string newTime;
	do {
		std::cout << std::endl << "Введите время, соответственно форме ЧЧ:ММ "<<std::endl;
		std::cin >> newTime;
		if (StreamChecker::isStreamFail(std::cin)) { continue; }
		if (!std::regex_match(newTime, timeFormat)) { continue; }
		hours = std::stoi(newTime.substr(0, 2));
		minutes = std::stoi(newTime.substr(3, 2));
	} while (hours > 23 || hours < 0 || minutes>60 || minutes < 0 || newTime.size()>5); //проверка на корректный ввод данных
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

std::ostream& operator<< (std::ostream& out, const Note& note) { //перегрузка оператора <<, для вывода в поток(используется для записи в файл)
	out << note.time << std::endl;
	out << note.getNoteImportance() << std::endl; //из геттера возвращается строка соответствующая значению перечисления
	out << note.noteText << std::endl;
	return out;
}

std::istream& operator>> (std::istream& in, Note& note) { //перегрузка оператора >>, для ввода из потока.(используется для чтения из файла)
	std::string noteImp;
	std::getline(in, note.time);
	std::getline(in, noteImp);
	note.setNoteImportance(noteImp); //в сеттер передается строка, в соответствии с которой будет установлено значение перечисления
	std::getline(in, note.noteText);
	return in;
}