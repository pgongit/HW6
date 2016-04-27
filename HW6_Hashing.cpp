/*
Hash Table implementation
*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

const int TABLE_SIZE = 65000;




class HashEntry {

private:
	int key;
	int value;

public:

	HashEntry(int key, int value) {
		this->key = key;
		this->value = value;
	}

	int getKey() {return key;} // return the key

	int getValue() { return value; } // return the value
};

class HashTable {

private:

	HashEntry **table;

public:

	/*Constructor to initialize a hash table*/
	HashTable() {
		table = new HashEntry*[TABLE_SIZE];

		for (int i = 0; i < TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
	}


	/*
	Function to write Hash table content to a file
	*/
	void WriteToFile(string fileName)
	{
		ofstream outFile;
		outFile.open(fileName);
		if (outFile.is_open() == true)
		{
			bool first = true;
			for (int i = 0; i < TABLE_SIZE; i++)
			{
				if (table[i] != NULL)
				{
					try
					{	//write index, key, and value to file				
						if (first == false)
						{
							outFile << ",";
						}
						outFile << table[i]->getValue();
						first = false;
					}
					catch (int e)
					{
					}
				}
			}
		}
		outFile.close();
		outFile.clear();
	}



	/*
	Function to insert the value at the position specified by 
	the Hash function or Quadratic Probing function in case of collision.
	*/
	void Insert(int key, int value, int probeKey) {
		//get a hash value
		int hash = Hash(key);

		if (table[hash] == NULL)
		{
			table[hash] = new HashEntry(key, value);
		}
		else
		{
			int index = QuadraticProbing(key,probeKey);//get new position using quadratic probing
			if (index > -1)
			{
				table[index] = new HashEntry(key, value);//insert a value
			}
		}
	}

	/*
	Hash function that extract the third, fifth, seventh and eighth digits 
	and returns a new value composed of these numbers;
	*/
	int Hash(int val)
	{
		string n = to_string(val);
		string key = "";
		for (int i = 0; i < n.length(); i++)
		{
			/*Get third, fifth, seventh, and nineth digit */
			if (i == 2 || i == 4 || i == 6 || i == 7)
			{
				key += n[i];
			}
		}
		return stoi(key);
	}

	/*
	Quadratic probing function used when a collision occurs*/
	int QuadraticProbing(int key, int probeKey)
	{
		int pos = probeKey;
		int i;
		for (i = 0; i%TABLE_SIZE != pos; i++)
		{
			pos = ((pos + i * i) % TABLE_SIZE);
			if (pos >= 0 && pos < TABLE_SIZE)
			{
				if (table[pos] == NULL)
				{
					return pos;
				}
			}
		}
		return -1;
	}
};



/*Function to read data from the file to the hash table*/
void ReadDataToTable(string fileName, HashTable hashTable, int probeKey)
{
	fstream file;
	char * temp = new char[10];
	file.open(fileName);
	if (file.is_open() == true)
	{
		int i = 0;
		while (file.peek() != EOF)
		{

			file.getline(temp, 10, ',');
			int val = atoi(temp);
			hashTable.Insert(val, val, probeKey);//Insert value from file
		}

	}
	file.close();
	file.clear();
}


int main()
{
	HashTable table;

	int probeNumber;
	cout << "Enter number between 1 and 450 million: ";
    cin >> probeNumber;
	
	ReadDataToTable("everybodys_socials.txt", table, probeNumber);
	table.WriteToFile("hashed_socials.txt");


	system("pause");
    return 0;
}

