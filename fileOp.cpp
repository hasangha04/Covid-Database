#include "database.h"

CovidDB::CovidDB(int m) 
{
    v = vector<vector<cvsdata>>(m);
    this->m = m;
}

int CovidDB::hash(string country)
{
    int sum = 0;
    for (int i = 0; i < country.length(); i++)
    {
        char c = int(country.at(i));
        sum += (i * c); //c is the ASCII code for char.
    }
    return sum % 17;
}

bool CovidDB::add(cvsdata entry)
{
    bool result;
    bool check = true;

    int index = hash(entry.getCountry());

    vector<string> date = split(entry.getDate(), '/');
    int month = stoi(date[0]);
    int day = stoi(date[1]);
    int year = stoi(date[2]);

    for (int j = 0; j < v[index].size(); j++)
    {
        if (v[index][j].getCountry() == entry.getCountry())
        {
            vector<string> checkerDate = split(v[index][j].getDate(), '/');
            int monthChecker = stoi(checkerDate[0]);
            int dayChecker = stoi(checkerDate[1]);
            int yearChecker = stoi(checkerDate[2]);
            if (check != false)
            {
                if (year > yearChecker)
                {
                    v[index][j].setDate(entry.getDate());
                    v[index][j].setCases(entry.getCases());
                    v[index][j].setDeaths(entry.getDeaths());
                    result = true;
                    return result;
                }
                else if (year == yearChecker && month > monthChecker)
                {
                    v[index][j].setDate(entry.getDate());
                    v[index][j].setCases(entry.getCases());
                    v[index][j].setDeaths(entry.getDeaths());
                    result = true;
                    return result;
                }
                else if (year == yearChecker)
                {
                    if (month >= monthChecker)
                    {
                        if (day > dayChecker)
                        {
                            v[index][j].setDate(entry.getDate());
                            v[index][j].setCases(entry.getCases());
                            v[index][j].setDeaths(entry.getDeaths());
                            result = true;
                            return result;
                        }
                    }
                }
                check = false;
                return check;
            }
        }
    }
    int hashIndex = hash(entry.getCountry());
    v[hashIndex].push_back(entry);
    result = true;
    return result;
}

cvsdata CovidDB::get(string country)
{
    int i = hash(country);

    // Scan for the element to be found
    for (int j = 0; j < v[i].size(); j++) 
    {
        if (v[i][j].getCountry() == country) 
        {
            return v[i][j];
        }
    }
    return cvsdata("0", "0", 0, 0);
}

void  CovidDB::remove(string country) 
{
    // get index first
    int i = hash(country);                          
    // traverse ith list(vector) to search 
    for (int j = 0; j < v[i].size(); j++) 
    {
        // if found, delete
        if (v[i][j].getCountry() == country)
        {
            v[i].erase(v[i].begin() + j);
            cout << country << " is deleted!" << endl;
            return;
        }
    }
    cout << "No Entry: " << country << " in hash table!";
}

// Display the contents
void  CovidDB::display()
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << " -> " << v[i][j].toString();
            cout << endl;
        }
    }
}

void CovidDB::readFile()
{
    vector<cvsdata> recordList;

    // Open the file
    ifstream file("WHO-COVID-Data.csv");

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            // split the content in each line
            vector<string> result = split(line, ',');

            // wrap up all the data in the string to a cvsdata type and push it to the vector
            cvsdata oneEntry = cvsdata(result[0], result[1], stoi(result[2]), stoi(result[3]));

            recordList.push_back(oneEntry);
        }
    }
    vector<cvsdata> allEntries;
    combine(recordList, allEntries);
    for (int i = 0; i < allEntries.size(); i++)
    {
        v[hash(allEntries[i].getCountry())].push_back(allEntries[i]);
    }
}

void CovidDB::combine(vector<cvsdata> & recordList, vector<cvsdata> & allEntries) 
{
    int sumCases = 0;
    int sumDeaths = 0;

    for (int i = 0; i < recordList.size(); i++)
    {
        if (i != recordList.size()-1)
        {
            sumCases += recordList[i].getCases();
            sumDeaths += recordList[i].getDeaths();

            string name = recordList[i].getCountry();
            string nameCheck = recordList[i + 1].getCountry();

            if (name != nameCheck)
            {
                string latestDate = recordList[i].getDate();
                cvsdata dataEntry("", "", 0, 0);
                dataEntry.setDate(latestDate);
                dataEntry.setCountry(name);
                dataEntry.setCases(sumCases);
                dataEntry.setDeaths(sumDeaths);
                allEntries.push_back(dataEntry);
                sumCases = 0;
                sumDeaths = 0;
            }
        }
        else
        {
            sumCases += recordList[i].getCases();
            sumDeaths += recordList[i].getDeaths();
            string name = recordList[i].getCountry();
            string latestDate = recordList[i].getDate();
            cvsdata dataEntry("", "", 0, 0);
            dataEntry.setDate(latestDate);
            dataEntry.setCountry(name);
            dataEntry.setCases(sumCases);
            dataEntry.setDeaths(sumDeaths);
            allEntries.push_back(dataEntry);
        }
    }
}

vector<string> CovidDB::split(string str, char del)
{
    vector<string> result;
    // declaring temp string to store the curr "word" upto del
    string temp = "";
    for (int i = 0; i < (int)str.size(); i++)
    {
        // If current char is not ',', then append it to the "word", otherwise you have completed the word, 
        // and start the next word
        if (str[i] != del)
        {
            temp += str[i];
        }
        else
        {
            result.push_back(temp);
            temp = "";
        }
    }
    // push the last substring after the last ',' to the result
    result.push_back(temp);
    return result;
}

cvsdata::cvsdata(string date, string country, int cases, int deaths)
{
    this->date = date;
    this->country = country;
    this->cases = cases;
    this->deaths = deaths;
}

string cvsdata::getDate()
{
    return date;
}

string cvsdata::getCountry()
{
    return country;
}

int cvsdata::getCases()
{
    return cases;
}

int cvsdata::getDeaths()
{
    return deaths;
}

string cvsdata::toString()
{
    return date + " " + country + " " + to_string(cases) + " " + to_string(deaths);
}

void cvsdata::setDate(string date)
{
    this->date = date;
}

void cvsdata::setCountry(string country)
{
    this->country = country;
}

void cvsdata::setCases(int newCases)
{
    this->cases += newCases;
}

void cvsdata::setDeaths(int newDeaths)
{
    this->deaths += newDeaths;
}