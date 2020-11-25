#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "StreamChecker.h"
#include <regex>

class Note
{
private:
	enum Importance {  //черечисление для степени важности заметок
		LOW,
		REGULAR,
		HIGH
	};
	std::string time;
	Importance noteImportance;
	std::string noteText;
public:
	Note();
	Note(std::string time, Importance noteImportance, std::string noteText);
	std::string getTime () const;
	std::string getNoteImportance() const;
	std::string getNoteText() const;
	void setTime(std::string time);
	void setNoteImportance(std::string importanceStirng);
	void setNoteText(std::string noteText);
	void print() const;
	void create();
	friend std::ostream& operator<< (std::ostream& out, const Note& note);
	friend std::istream& operator>> (std::istream& in, Note& note);
};