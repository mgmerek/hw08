/***********
 * File: appointment_main.cc
 * Author: Mila Gmerek
 * Date: 4/18/2022
 * Brief: Main program for appointment class
 ************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "appointment.h"

using namespace std;

void input(ifstream &inStream, vector<Appointment> &agenda, vector<string> stringInputs);
void output(ofstream &outStream, vector<Appointment> agenda, vector<string> stringInputs);
void deleteTime(string timeString, vector<Appointment> agenda, vector<string> &stringInputs);
void deleteTitle(vector<Appointment> agenda, vector<string> &stringInputs);
void addAppt(string appData, vector<string> &stringInputs);
void sameTimes(vector<Appointment> &agenda, int time);
int indexOfMinTime(vector<int> appointmentTimes);
void displayAppointments(vector<Appointment> &agenda, vector<int> &appointmentTimes);

int main(int argc, char const *argv[])
{
    vector<string> stringInputs;  // vector that contains each appointment as a string
    vector<Appointment> agenda;   // vector with all appointments
    vector<int> appointmentTimes; // vector with all appointment times
    ifstream inStream;
    ofstream outStream;
    string arg1; // string that represents user input
    string arg2;
    arg1 = argv[1];
    arg2 = argv[2];

    if (argc == 2) // calls function based off of user input
    {
        if (arg1 == "-ps")
        {
            input(inStream, agenda, stringInputs);
            displayAppointments(agenda, appointmentTimes);
        }
    }
    else if (argc == 3) // calls function based off of user input
    {
        if (arg1 == "-p")
        {
            input(inStream, agenda, stringInputs);
            sameTimes(agenda, stol(arg2));
        }
        else if (arg1 == "-a")
        {
            input(inStream, agenda, stringInputs);
            addAppt(arg2, stringInputs);
            output(outStream, agenda, stringInputs);
        }
        else if (arg1 == "-dt")
        {
            input(inStream, agenda, stringInputs);
            if (agenda.size() != 0)
            {
                deleteTitle(agenda, stringInputs);
                output(outStream, agenda, stringInputs);
            }
        }
        else if (arg1 == "-dm")
        {
            input(inStream, agenda, stringInputs);
            deleteTime(arg2, agenda, stringInputs);
            output(outStream, agenda, stringInputs);
        }
    }
    else // if user does not enter a valid option
    {
        cout << "Error: invalid commands" << endl;
    }

    return 0;
}

void inputData(ifstream &inStream, vector<Appointment> &agenda, vector<string> stringInputs) // loads vector
{
    string line;
    inStream.open("agenda.txt");
    if (inStream.fail())
    {
        cout << "Error: file failed to open" << endl;
        exit(0);
    }
    while (!inStream.eof())
    {
        getline(inStream >> ws, line);
        agenda.push_back(line);
        stringInputs.push_back(line);
        Appointment a(line);
    }
    inStream.close();
}

void deleteTime(string timeString, vector<Appointment> agenda, vector<string> &inputStrings) // deletes all appointments at a certain time
{
    int targetTime = stol(timeString);
    for (unsigned int i = 0; i < agenda.size(); i++)
    {
        if (agenda.at(i).getTime() == targetTime)
        {
            inputStrings.erase(inputStrings.begin() + i - agenda.size());
        }
    }
}

void addAppt(string appData, vector<string> &inputStrings) // adds an appointment to vector
{
    inputStrings.push_back(appData);
}

void displayAppointments(vector<Appointment> &agenda, vector<int> &appointmentTimes) // displays appointments in order from earliest to latest
{
    int min;
    for (unsigned int i = 0; i < agenda.size(); i++)
    {
        appointmentTimes.push_back(agenda.at(i).getTime());
    }
    for (unsigned int i = 0; i < appointmentTimes.size() - 1; i++)
    {
        min = indexOfMinTime(appointmentTimes);
        swap(agenda.at(i), agenda.at(min));
        swap(appointmentTimes.at(i), appointmentTimes.at(min));
    }
}

void delApptTitle(vector<Appointment> agenda, vector<string> &inputStrings) // deletes appointments with a certain title
{
    string s = " ";
    for (unsigned int i = 0; i < agenda.size(); i++)
    {
        for (unsigned int j = 0; j < agenda.at(i).getTitle().length(); j++)
        {
            s += toupper(agenda.at(i).getTitle().at(j));
        }
        s = " ";
    }
}

void outputData(ofstream &outStream, vector<Appointment> agenda, vector<string> inputStrings) // outputs contents of vector
{
    outStream.open("agenda.txt");
    for (size_t i = 0; i < inputStrings.size(); i++)
    {
        outStream << inputStrings.at(i);
        outStream << endl;
    }
    outStream.close();
}

void sameTimes(vector<Appointment> &agenda, int time) // outputs appointments at the same times
{
    for (size_t i = 0; i < agenda.size(); i++)
    {
        if (agenda.at(i).getTime() == time)
        {
            cout << setw(35) << left << agenda.at(i).getTitle() << setw(10) << agenda.at(i).getYear();
            cout << setw(10) << agenda.at(i).getMonth() << setw(10) << agenda.at(i).getDay();
            cout << setw(10) << agenda.at(i).getStandardTime() << setw(10) << agenda.at(i).getDuration() << endl;
        }
    }
}

int indexOfMinTime(vector<int> appointmentTimes) // finds index of earliest appointment and the index will be used to put appointments in order
{
    int min;
    int indexOfSmallest;
    min = appointmentTimes.at(0);
    indexOfSmallest = min;
    for (unsigned int i = min; i < appointmentTimes.size() - 1; i++)
    {
        if (appointmentTimes.at(i) < min)
        {
            min = appointmentTimes.at(i);
            indexOfSmallest = i;
        }
    }
    return indexOfSmallest;
}
