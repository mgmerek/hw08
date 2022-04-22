/***********
 * File: appointment.h
 * Author: Mila Gmerek
 * Date: 4/18/2022
 * Brief: Appointment class
 ************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
class Appointment // appointment class
{
public:
    string title; // variables
    string date;
    int year;
    int month;
    int day;
    int time;
    int duration;

    void setTitle(string newTitle); // setter/mutator functions
    void setYear(int newYear);
    void setMonth(int newMonth);
    void setDay(int newDay);
    void setTime(int newTime);
    void setDuration(int newDuration);
    void setDate(int newYear, int newMonth, int newDay);

    string getTitle(); // getter/accessor functions
    int getYear();
    int getMonth();
    int getDay();
    int getTime(); // military time
    int getDuration();
    string getDate();
    string getStandardTime();

    Appointment();               // deafault constructor
    Appointment(string appData); // second constructor 

    string militaryToStandard(int time); // converts military time to standard time 
    int standardToMilitary(string time); // coverts standard time to military time 
    friend bool operator==(const Appointment &first, const Appointment &second); // compares each element of two appointments, returns true if they are the same
};