#include "StreamChecker.h"

bool StreamChecker::isStreamFail(std::istream& in) {
	if (in.fail()) // если предыдущее извлечение оказалось неудачным,
	{
		in.clear(); // то возвращаем cin в 'обычный' режим работы
		in.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		std::cout << std::endl << "Неправильно введены данные.\n";
		return true;
	}
	else {
		in.ignore(32767, '\n'); // удаляем лишние значения, на случай, если они есть
		return false;
	} 
}