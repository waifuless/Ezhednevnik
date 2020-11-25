#include <iostream>
#include "DairyExecutor.h"
#include <clocale>
#include "StreamChecker.h"

int menu();

int main() {
	setlocale(LC_ALL, "rus");
	while (1) {   //программа работает, пока пользователь не выберет "выход"
		switch (menu()) {  //вызываем меню
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
		default: std::cout << std::endl << "Действия под таким номером не существет";
			continue;
			break;
		}
	}
}

int menu() {  //для для выбора действия
	int choice = 0;
	std::cout << std::endl << "Выберите действие : "
		<< std::endl << "1)Посмотреть календарь"
		<< std::endl << "2)Добавить заметку"
		<< std::endl << "3)Удалить заметку"
		<< std::endl << "4)Редактировать заметку"
		<< std::endl << "5)Посмотреть заметки на сегодня"
		<< std::endl << "6)Посмотреть заметки на другой день"
		<< std::endl << "7)Выход"<<std::endl;
	std::cin >> choice;
	if (StreamChecker::isStreamFail(std::cin)) {
		return 0;
	}
	return choice;
}