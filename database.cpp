#include"database.h"

int main()
{
	CovidDB table(17);
	bool end = true;
	int input;
	string country;
	string date;
	int cases; 
	int deaths;
	while (end != false)
	{
		cout << endl;
		cout << "Covid Tracker" << endl;
		cout << "Please choose the operation you want: " << endl;
		cout << "1. Create the initial hash table" << endl;
		cout << "2. Add a new data entry" << endl;
		cout << "3. Get a data entry" << endl;
		cout << "4. Remove a data entry" << endl;
		cout << "5. Display hash table" << endl;
		cout << "0. Quit the system" << endl;
		cout << "Your Choice: ";

		cin >> input;
		switch (input)
		{
			case 1: 
				table.readFile();
				break;
			case 2:
			{
				cout << "What country would you like to add (Capitalize the first character): ";
				cin >> country;
				cout << "What is the date for this entry (in form MM/DD/YYYY): ";
				cin >> date;
				cout << "What are the number of cases: ";
				cin >> cases;
				cout << "What are the number of deaths: ";
				cin >> deaths;
				cvsdata entry(date, country, cases, deaths);
				cout << endl;
				if (table.add(entry) == true)
				{
					cout << "Entry added" << endl;
					cout << table.get(country).toString() << endl;
				}
				else
				{
					cout << "Entry couldn't be added" << endl;
				}
				break;
			}
			case 3:
				cout << "What countries data would you like (put a _ for space): ";
				cin >> country;
				cout << endl;
				if (table.get(country).toString() == "0 0 0 0")
				{
					cout << "This entry does not exist";
				}
				else 
				{
					cout << table.get(country).toString();
				}
				cout << endl;
				break;
			case 4:
				cout << "What country would you like to remove: ";
				cin >> country;
				cout << endl;
				table.remove(country);
				cout << endl;
				break;
			case 5:
				table.display();
				break;
			case 0:
				cout << "Thank you for using the program" << endl;
				end = false;
				break;
			default:
				cout << "Not a vaild option try again" << endl;
				break;
		}
	}
}