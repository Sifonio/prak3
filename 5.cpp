#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

bool checkFileSize(const char* filename) {
    struct stat fileStat;
    if (stat(filename, &fileStat) != 0) {
        return false;
    }
    const long long MAX_FILE_SIZE = 1000000000; 
    return fileStat.st_size <= MAX_FILE_SIZE;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Program need two arguments" << endl;
        return 1;
    }

    ifstream inputFile(argv[1], ios::binary);
    if (!inputFile) {
        cout << "Cannot open file " << argv[1] << " for reading" << endl;
        return 1;
    }

    if (!checkFileSize(argv[1])) {
        cout << "File size exceeds limit" << endl;
        return 1;
    }

    ofstream outputFile(argv[2], ios::binary);
    if (!outputFile) {
        cout << "Cannot open file " << argv[2] << " for writing" << endl;
        return 1;
    }

    outputFile << inputFile.rdbuf();
    cout << "File copied successfully" << endl;
    return 0;
}
//g++ -Wall 5.cpp -o 5