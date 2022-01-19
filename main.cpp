#include <iostream>
#define tableSize 10
using namespace std;

class DataNode
{
public:
    int data;
    string key;
};

class HashTable
{
public:
    // static array to store addresses
    DataNode *dataArray[tableSize] = {};

    HashTable();
    ~HashTable();

    // hash function
    int hashFunction(string key);

    int hashFunction2(string key);

    // using quadratic probing
    // insert data according to key value
    void insertData(string key, int value);
    // get data according to key
    int getData(string key);

    // delete data
    void deleteData(string key);

    // print the entire table
    void printEntireTable();

    // using double hashing resolution
    void insertData2(string key, int value);

    // get data
    int getData2(string key);

    // delete data
    void deleteData2(string key);
};

void userInterface();

// test quadratic probing 

// int main()

// {

//     // table 1 for quadratic probing

//     HashTable table1;

//     table1.insertData("happy", 1);

//     table1.insertData("money", 2);

//     table1.insertData("sad", 3);

//     table1.insertData("train", 4);

//     table1.insertData("fire", 5);

//     table1.insertData("cook", 6);

//     cout << "Value of cook in lexicon is " << table1.getData("cook") << endl;

//     table1.printEntireTable();

//     cout << "Deleting \'cook\'  " << endl;

//     table1.deleteData("cook");

//     table1.printEntireTable();

//     cout << endl;

//     return 0;
// }

 
// test double hashing
// int main() 
// {
// 	// table2 for double hashing 
//     HashTable table2; 
 
 
// 	table2.insertData2("man", 7); 
// 	table2.insertData2("car", 8); 
// 	table2.insertData2("war", 9); 
// 	table2.insertData2("food", 10); 
// 	table2.insertData2("tree", 11); 
// 	table2.insertData2("break", 12); 
 
 
//     cout << "Value of war in lexicon is " << table2.getData2("war") << endl; 
// 	table2.printEntireTable(); 
 
 
//     cout << "Deleting \'wae\'  " << endl; 
// 	table2.deleteData2("war"); 
 
 
// 	table2.printEntireTable(); 
 
 
//     cout << endl; 
//     return 0; 
// } 
 


int main()

{

    userInterface();

    cout << endl;

    return 0;
}
HashTable::HashTable()
{
    for (uint i = 0; i < tableSize; i++)
    { // constructor initialize from NULL
        dataArray[i] = NULL;
    }
}

HashTable::~HashTable()
{
}

int HashTable::hashFunction(string key)
{
    int hashedIndex = 0;
    for (uint i = 0; i < key.length(); i++)
    {
        // hashing function
        hashedIndex += 33 * hashedIndex + (unsigned char)key[i];
    }

    // turn number to positive
    return hashedIndex < 0 ? hashedIndex * -1 : hashedIndex;
}

void HashTable::insertData(string key, int value)
{
    if (getData(key) == -1)
    {

        // populate data
        DataNode *newnode = new DataNode();
        newnode->data = value;
        newnode->key = key;
        int hashedIndex = hashFunction(key) % tableSize;
        //if place is empty, insert there
        if (dataArray[hashedIndex] == NULL)
        {
            // insert at correct position
            dataArray[hashedIndex] = newnode;
        }
        else // if index was not empty, insert after resolving collision
        {
            // if the index is not empty, then we need to find the next empty index
            // and insert the data there
            // quadratic probing
            cout << "Collision occured" << endl;
            int index = hashedIndex;
            int i = 1;
            while (dataArray[index] != NULL)
            {
                index = (hashedIndex + i * i) % tableSize;
                i++; // increase i to resolve collision

                // if not resolved in tableSize tries, return
                if (i == tableSize)
                    return;
            }
            dataArray[index] = newnode;
        }
    }
    else
    {
        cout << "Key already exists" << endl;
    }
}

int HashTable::getData(string key)
{

    int hashedIndex = hashFunction(key) % tableSize;

    // return -1 if not found

    if (dataArray[hashedIndex] == NULL)
    {
        return -1;
    }
    if (dataArray[hashedIndex]->key == key)
    {

        return dataArray[hashedIndex]->data;
    }
    else
    { // if collission
        // quadratic probing

        int index = hashedIndex;
        int i = 1;

        while (1)
        {
            // run until we find the key
            if (dataArray[index])
                if (dataArray[index]->key == key)
                    return dataArray[index]->data;

            index = (hashedIndex + i * i) % tableSize;
            i++;

            // if not resolved in tableSize tries, return
            if (i == tableSize)
                return -1;
        }
        if (dataArray[index])
            return dataArray[index]->data;
    }
}

void HashTable::printEntireTable()
{
    // iterate and print all key value pairs
    cout << "Entire table data: " << endl;
    for (int i = 0; i < tableSize; i++)
    {
        if (dataArray[i])
        {
            cout << dataArray[i]->key << " : " << dataArray[i]->data << endl;
        }
    }
}

void HashTable::deleteData(string key)
{
    int hashedIndex = hashFunction(key) % tableSize;
    if (dataArray[hashedIndex] == NULL)
        return;
    if (dataArray[hashedIndex]->key == key)
    { // delete the data if key matches
        delete dataArray[hashedIndex];
        dataArray[hashedIndex] = NULL;
    }
    else
    {
        int index = hashedIndex;
        int i = 1;
        // else prob until key matches
        while (1)
        {
            // probe until key found
            if (dataArray[index])
                if (dataArray[index]->key == key)
                    break;
            index = (hashedIndex + i * i) % tableSize;
            i++;
            // if i reached return
            if (i == tableSize)
                return;
        }

        if (dataArray[index])
            if (dataArray[index]->key == key)
            {

                // free memory and set null
                delete dataArray[index];
                dataArray[index] = NULL;
            }
    }
}

int HashTable::hashFunction2(string key)
{
    int hashedIndex = 0;
    for (uint i = 0; i < key.length(); i++)
    {
        // second hash function
        hashedIndex += (int)key[i] * i * i;
    }

    return hashedIndex < 0 ? (hashedIndex * (-1)) : hashedIndex;
}

void HashTable::insertData2(string key, int value)
{

    if (getData(key) == -1)
    {

        // populate data fields
        DataNode *newnode = new DataNode();
        newnode->data = value;
        newnode->key = key;

        // insert into epty spot
        int hashedIndex = hashFunction(key) % tableSize;
        if (dataArray[hashedIndex] == NULL)
        {
            dataArray[hashedIndex] = newnode;
        }
        else
        {
            // if index is not empty, then we need to find the next empty index
            int index = hashedIndex;
            int i = 1;
            while (dataArray[index] != NULL)
            { // double hashing
                index = (hashFunction(key) + i * hashFunction2(key)) % tableSize;
                i++;
                // if i reached return
                if (i == tableSize)
                    return;
            }
            dataArray[index] = newnode;
        }
    }
    else
    {
        cout << "Key already exists" << endl;
    }
}

int HashTable::getData2(string key)
{
    int hashedIndex = hashFunction(key) % tableSize;
    // if no value fuind return -1
    if (dataArray[hashedIndex] == NULL)
        return -1;
    // if value found on first probe, return it
    if (dataArray[hashedIndex]->key == key)
        return dataArray[hashedIndex]->data;
    else
    {
        // if collision occurs, resolve it
        // using double hashing
        int index = hashedIndex;
        int i = 1;
        while (1)
        {
            // run until we find the key
            if (dataArray[index])
                if (dataArray[index]->key == key)
                    return dataArray[index]->data;

            index = (hashFunction(key) + i * hashFunction2(key)) % tableSize;
            i++;
            // if i reached return
            if (i == tableSize)
                return -1;
        }

        if (dataArray[index])
            if (dataArray[index]->key == key)
                return dataArray[index]->data;
    }
}

void HashTable::deleteData2(string key)
{ // if data does not exit, return
    int hashedIndex = hashFunction(key) % tableSize;
    if (dataArray[hashedIndex] == NULL)
        return;
    if (dataArray[hashedIndex]->key == key)
    { // delete the data if key matches
        delete dataArray[hashedIndex];
        dataArray[hashedIndex] = NULL;
    }
    else
    { // if collision occurs, resolve it
        int index = hashedIndex;
        int i = 1;

        while (1)
        { // resolve using double hashing
            if (dataArray[index])
                if (dataArray[index]->key == key)
                    break;
            index = (hashFunction(key) + i * hashFunction2(key)) % tableSize;
            i++;
            // if i reached return
            if (i == tableSize)
                return;
        }
        // free memory and set null
        if (dataArray[index])
            if (dataArray[index]->key == key)
            {

                delete dataArray[index];
                dataArray[index] = NULL;
            }
    }
}

void userInterface()
{
    int choice;
    HashTable ht;
    cout << "Welcome" << endl;
    cout << "Press -9999 at any time to exit" << endl;

    cout << "Choose resolution technique" << endl;
    
    // choose the reolution method
    cout << "1. Quadratic probing" << endl;
    cout << "2. Double hashing" << endl;
    cin >> choice;
    if (choice != -9999)
    {
        if (choice == 1)
        {
            while (1)
            {   
                cout << "Quadratic Probing" << endl;
                cout << "1. Insert Value" << endl;
                cout << "2. Get Value" << endl;
                cout << "3. Delete Value" << endl;
                cout << "4. Print All" << endl;

                // choose command accordingly
                cin >> choice;
                if (choice == -9999)
                    break;
                if (choice == 1)
                {
                    string key;
                    int value;
                    cout << "Enter key" << endl;
                    cin >> key;
                    cout << "Enter value" << endl;
                    cin >> value;
                    ht.insertData(key, value);
                }
                else if (choice == 2)
                {
                    string key;
                    cout << "Enter key" << endl;
                    cin >> key;
                    cout << "Value is " << ht.getData(key) << endl;
                }
                else if (choice == 3)
                {
                    string key;
                    cout << "Enter key" << endl;
                    cin >> key;
                    ht.deleteData(key);
                }
                else if (choice == 4)
                {
                    ht.printEntireTable();
                }
                else
                {
                    cout << "Invalid choice. Try again" << endl;
                }
            }
        }
        else if (choice == 2)
        { while(1){
                // choose command accordingly

            cout << "Double Hashing" << endl;
            cout << "1. Insert Value" << endl;
            cout << "2. Get Value" << endl;
            cout << "3. Delete Value" << endl;
            cout << "4. Print All" << endl;

            cin >> choice;
            if (choice == -9999)
                return;
            if (choice == 1)
            {
                string key;
                int value;
                cout << "Enter key" << endl;
                cin >> key;
                cout << "Enter value" << endl;
                cin >> value;
                ht.insertData2(key, value);
            }
            else if (choice == 2)
            {
                string key;
                cout << "Enter key" << endl;
                cin >> key;
                cout << "Value is " << ht.getData2(key) << endl;
            }
            else if (choice == 3)
            {
                string key;
                cout << "Enter key" << endl;
                cin >> key;
                ht.deleteData2(key);
            }
            else if (choice == 4)
            {
                ht.printEntireTable();
            }
            else
            {
                cout << "Invalid choice. Try again" << endl;
            }
        }
        }
    }
    else
    {
        return;
    }
}


