#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const string FILE_NAME = "3.txt";
const size_t SIZE = 100;

size_t getFileSize(const string &filename) {
    ifstream file(filename, ios::binary | ios::ate);
    return file.tellg();
}

int roll(){
    return rand() % 6 + 1;
} 

int main(void){
    srand(time(0));
    ofstream file(FILE_NAME, ios::app);
    if(!file){
        cout << "Помилка відкриття";
        return 0;
    }
    while(true){
        if(getFileSize(FILE_NAME) >= SIZE){
            cout << "Файл перевищує ліміт розміру";
            break;
        }
        int num = roll();
        file << num << endl;
        cout << num << endl;
    }
    file.close();
    return 0;
}
//g++ -Wall 3.cpp -o 3