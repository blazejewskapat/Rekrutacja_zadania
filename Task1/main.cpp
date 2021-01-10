#include <iostream>
#include <fstream>

using namespace std;

// Check data in file 'input.txt'
// Create file ''output.txt' with
// information about data in 'input.txt'
// Files in 'cmake-build-debug'
int main() {

    int counter = 0;
    int wrong_data = 0;
    string data;
    string message;
    fstream file;
    fstream outputfile;

    outputfile.open("output.txt", ios::out);
    outputfile << 0 << endl;
    outputfile << 0 << endl << endl;
    file.open("input.txt", ios::in);

    if (file.good() && outputfile.good()) {
        cout << "Access granted!" << endl;

        while (!file.eof()) {
            getline(file, data);

            message = data.at(4);
            message += data.at(5);
            message += data.at(6);

            if (message == "000" ||
                (data.at(7) % 2 != (counter + 1) % 2)) wrong_data++;
            else outputfile << data;

            counter++;
        }
    } else cout << "Files not available!" << endl;

    file.close();
    outputfile.close();

    outputfile.open("output.txt", ios::in | ios::out);
    if (outputfile.good()) {
        outputfile << counter << endl;
        outputfile << wrong_data;
        cout << "New file is saved!" << endl;
    }
    outputfile.close();

    return 0;
}