#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class Program {
private:
    int fileCount;
    string* fileNames;
    string** sortedLists;

    void getFilesNames() {
        cout << "Enter file count:\n";
        cin >> fileCount;

        fileNames = new string[fileCount];

        cout << "Enter file location(s):\n";

        for (int index = 0; index < fileCount; index++) {
            string fileName;
            std::cin >> fileName;
            fileNames[index] = fileName;
        }

        sortedLists = new string*[fileCount];
    }

    void getSortedLists() {
        for (int index = 0; index < fileCount; index++) {
            fstream file;
            file.open(fileNames[index]);

            

            file.close();
        }
    }
public:
    void run() {
        getFilesNames();
    }
};



int main() {
    Program().run();
}
