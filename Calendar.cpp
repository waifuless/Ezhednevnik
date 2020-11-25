#include "Calendar.h"

void Calendar::printMonth(int monthNumber, int yearNumber) {
    time_t now;
    struct tm* timeinfo;

    int i, j;
    const char* month[] = { "Январь","Февраль", "Март","Апрель", "Май","Июнь",
        "Июль", "Август","Сентябрь","Октябрть", "Ноябрь","Декабрь" };


    time(&now); //get current timeinfo and modify it to the user's choice
    timeinfo = localtime(&now);
    timeinfo->tm_year = yearNumber - 1900; //годы нумеруются с 1900
    timeinfo->tm_mon = monthNumber - 1;

    std::cout<<std::endl<<std::endl;
    std::cout << "_______________________________" << std::endl
              << "  Пн  Вт  Ср  Чт  Пт  Сб  Вс" << std::setw(12)<<month[monthNumber - 1] << ", " << yearNumber << std::endl
              << "_______________________________"<<std::endl;


    for (i = 1; i < 32; i++) //year days with "overload"  
    {

        timeinfo->tm_mday = i;
        mktime(timeinfo);//call mktime: the whole timeinfo for the day will be set 

        if (timeinfo->tm_mon == monthNumber)
            break;

        if (i == 1)
        {
            if (timeinfo->tm_wday == 0) {  //нумерация дней недели начинается с 0. 0 - это воскресенье
                for (j = 0; j < 6; j++)
                    std::cout<<"    ";
            }
            else {
                for (j = 0; j < (timeinfo->tm_wday)-1; j++)
                    std::cout<<"    ";
            }
        }

        std::cout<<std::setw(4)<<timeinfo->tm_mday; //routine

        if (timeinfo->tm_wday == 0)
            std::cout<<std::endl;

    }
    return;
}


void Calendar::printYear(int yearNumber) {
    for (int i = 1; i < 13; i++) {
        printMonth(i, yearNumber);
    }
    return;
}