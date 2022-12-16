#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class cvsdata
{
    string date;
    string country;
    int cases;
    int deaths;

public:
    cvsdata(string date, string country, int cases, int deaths);

    string getDate();

    string getCountry();

    int getCases();

    int getDeaths();

    void setDate(string date);

    void setCountry(string country);

    void setCases(int newCases);

    void setDeaths(int newDeaths);

    string toString();
};

class CovidDB
{
private:
    int m; 
    vector<vector<cvsdata>> v;

public:
    CovidDB(int m);

    int hash(string country);

    bool add(cvsdata entry);

    cvsdata get(string country);
    
    void remove(string country);

    void display();

    vector<string> split(string str, char del);

    void readFile();

    void combine(vector<cvsdata> & recordList, vector<cvsdata> & allEntries);
};