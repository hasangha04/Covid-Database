# Covid Database
This is a covid database built using data from the WHO and a hash table. The collision prevention technique used is separate chaining and the hash function is using
the division method. Separate chaining is managed by using a vector of a vector that stores data using a class that can hold the name of the country the latest date
for the data given and the total number of cases and deaths. The data is read from a CSV file using ifstream and is then put into the hash table. Alongside the 
original entries, the user can change an entry to a newer date with newer data as well as add in an entry that does not exist already in the hash table.
The other functions include a get function to retrieve an entry from the table and a remove function to remove an entry from the hash table. 
