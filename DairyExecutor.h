#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Calendar.h"
#include "Note.h"
#include <vector>
#include <filesystem>
#include <cstdio>
#include "StreamChecker.h"

class DairyExecutor
{
private:
	static int daysInMonth(int month, int year);
	static std::string getDayFileNameWithPath();
	static std::vector<Note> readVectorOfNotes(std::string fileName); 
public:
	static void viewCalendar();
	static void makeNote();
	static void delNote();
	static void redactNote();
	static void viewNotesForSomeDay();
	static void viewNotesForToday();
};

