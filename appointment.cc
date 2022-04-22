/***********
 * File: appointment.cc
 * Author: Mila Gmerek
 * Date: 4/18/2022
 * Brief: Function definitions
 ************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "appointment.h"

using namespace std;

Appointment::Appointment() // default constructor 
{
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0; // Military
    duration = 1;
}

Appointment::Appointment(string appData) // second constructor 
{
    title = "N/A"; // default values
    day = 1;
    month = 1;
    year = 1;
    time = 0; // military time
    duration = 1;
    int size = appData.size(); // size of string with appointment data 
    for (int i = 0; i < size; i++)
    {
        if (appData.at(0) == ' ') // erases whitespace at the beginning 
        {
            appData.erase(0, 1);
        }
    }

    Appointment a; // puts appointment data in the correct format 
    string title;
    int location = appData.find("|");
    title = appData.at(location);
    a.setTitle(title);

    int location2 = appData.find("|", location);
    year = appData.at(location2);
    string y = to_string(year);
    a.setYear(year);

    int location3 = appData.find("|", location2);
    month = appData.at(location3);
    string m = to_string(month);
    a.setMonth(month);

    int location4 = appData.find("|", location3);
    day = appData.at(location4);
    string d = to_string(day);
    a.setDay(day);

    int location5 = appData.find("|", location4);
    time = appData.at(location5);
    string t = to_string(time);
    a.setTime(time);

    int location6 = appData.find("|", location5);
    duration = appData.at(location6);
    string dur = to_string(duration);
    a.setDuration(duration);
}

void Appointment::setTitle(string newTitle) // setter functions 
{
    if (newTitle != "N/A")
    {
        title = newTitle;
    }
}

void Appointment::setYear(int newYear)
{
    if (newYear != 1)
    {
        year = newYear;
    }
}

void Appointment::setMonth(int newMonth)
{
    if (newMonth != 1)
    {
        month = newMonth;
    }
}

void Appointment::setDay(int newDay)
{
    if (newDay != 1)
    {
        day = newDay;
    }
}

void Appointment::setTime(int newTime)
{
    if (newTime != 0)
    {
        time = newTime;
    }
}

void Appointment::setDuration(int newDuration)
{
    if (newDuration != 0)
    {
        duration = newDuration;
    }
}

void Appointment::setDate(int newYear, int newMonth, int newDay)
{
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}

string Appointment::getTitle() // getter functions 
{
    return title;
}

int Appointment::getYear()
{
    return year;
}

int Appointment::getMonth()
{
    return month;
}

int Appointment::getDay()
{
    return day;
}

int Appointment::getTime()
{
    return time;
} 

int Appointment::getDuration()
{
    return duration;
}

string Appointment::getDate() // formats date 
{
    getMonth();
    getDay();
    getYear();
    string m = to_string(month);
    string d = to_string(day);
    string y = to_string(year);
    date = m + d + y;
    date.insert(2, "/");
    date.insert(5, "/");
    return date;
}

string Appointment::getStandardTime() // takes military time and returns standard time 
{
    return militaryToStandard(time);
}

string Appointment::militaryToStandard(int time) // takes military time and returns standard time 
{
    string standardTime;
    string timeOfDay;
    if (time < 1200)
    {
        timeOfDay = "aM";
    }
    if (time > 1200 || time == 1200)
    {
        timeOfDay = "pM";
    }
    if (time == 0)
    {
        timeOfDay = "aM";
        time += 1200;
    }
    if (time > 1200)
    {
        time -= 1200;
    }
    if (time < 1200)
    {
        standardTime = time;
    }

    standardTime = to_string(time);

    if (standardTime.length() == 4)
    {
        standardTime.insert(2, ":");
        standardTime.insert(5, timeOfDay);
    }
    if (standardTime.length() == 3)
    {
        standardTime.insert(1, ":");
        standardTime.insert(4, timeOfDay);
    }
    return standardTime;
}

int Appointment::standardToMilitary(string time)  // military time to standard time 
{
    int militaryTime;
    militaryTime = atoi(time.c_str());
    if (militaryTime < 1200)
    {
        militaryTime += 1200;
    }
    return militaryTime;
}

bool operator==(const Appointment &first, const Appointment &second) // comapares all elements of two appointments 
{
    int num = 1;
    if (first.title == second.title)
    {
        num++;
    }
    if (first.year == second.year)
    {
        num++;
    }
    if (first.month == second.month)
    {
        num++;
    }
    if (first.day == second.day)
    {
        num++;
    }
    if (first.time == second.time)
    {
        num++;
    }
    if (first.duration == second.duration)
    {
        num++;
    }
    if (num == 7)
    {
        return true;
    }
    return false;
}