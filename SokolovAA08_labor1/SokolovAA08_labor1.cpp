#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
    string kilometerMark;
    double length;
    int diameter;
    bool underRepair;
};

struct CompressorStation {
    string name;
    int totalWorkshops;
    int workingWorkshops;
    int stationClass;
};

string getLine(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool onlyLetters(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isLetter(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool onlyLettersNumbers(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isLetter(c) && !isDigit(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

int getInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(1000, '\n');
                return value;
            }
            cout << "Please enter number between " << min << " and " << max << endl;
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter integer." << endl;
        }
    }
}

double getDouble(const string& prompt, double min, double max) {
    double value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(1000, '\n');
                return value;
            }
            cout << "Please enter number between " << min << " and " << max << endl;
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter number." << endl;
        }
    }
}

void inputPipe(Pipe& pipe) {
    cout << "\nAdding New Pipe:\n";

    while (true) {
        pipe.kilometerMark = getLine("Enter kilometer mark: ");
        if (onlyLettersNumbers(pipe.kilometerMark)) break;
        cout << "Invalid input. Use only letters and numbers.\n";
    }

    pipe.length = getDouble("Enter length (0.1-10000.0 km): ", 0.1, 10000.0);
    pipe.diameter = getInt("Enter diameter (10-2000 mm): ", 10, 2000);
    pipe.underRepair = false;

    cout << "Pipe added successfully!\n";
}

void displayPipe(const Pipe& pipe) {
    cout << "\nPipe:\n"
        << "Kilometer Mark: " << pipe.kilometerMark << "\n"
        << "Length: " << pipe.length << " km\n"
        << "Diameter: " << pipe.diameter << " mm\n"
        << "Under Repair: " << (pipe.underRepair ? "Yes" : "No") << "\n";
}

void editPipe(Pipe& pipe) {
    cout << "\nCurrent status: " << (pipe.underRepair ? "Under repair" : "Operational") << "\n";
    int change = getInt("Change status? (1-Yes, 0-No): ", 0, 1);

    if (change == 1) {
        pipe.underRepair = !pipe.underRepair;
        cout << "Status changed to: " << (pipe.underRepair ? "Under repair" : "Operational") << "\n";
    }
}

void inputStation(CompressorStation& cs) {
    cout << "\nAdding New Compressor Station\n";

    while (true) {
        cs.name = getLine("Enter station name: ");
        if (onlyLettersNumbers(cs.name)) break;
        cout << "Invalid input. Use only letters.\n";
    }

    cs.totalWorkshops = getInt("Enter total workshops (1-100): ", 1, 100);
    cs.workingWorkshops = getInt("Enter working workshops (0-" + to_string(cs.totalWorkshops) + "): ", 0, cs.totalWorkshops);
    cs.stationClass = getInt("Enter station class (1-10): ", 1, 10);

    cout << "Compressor Station added successfully!\n";
}

void displayStation(const CompressorStation& cs) {
    double efficiency = 0;
    if (cs.totalWorkshops > 0) {
        efficiency = (static_cast<double>(cs.workingWorkshops) / cs.totalWorkshops) * 100;
    }

    cout << "\nCompressor Station:\n"
        << "Name: " << cs.name << "\n"
        << "Total Workshops: " << cs.totalWorkshops << "\n"
        << "Working Workshops: " << cs.workingWorkshops << "\n"
        << "Station Class: " << cs.stationClass << "\n"
        << "Efficiency: " << efficiency << "%\n";
}

void editStation(CompressorStation& cs) {
    cout << "\nWorking workshops: " << cs.workingWorkshops << " of " << cs.totalWorkshops << "\n";

    int action = getInt("1. Start workshop\n2. Stop workshop\n0. Cancel\nChoose action: ", 0, 2);

    switch (action) {
    case 1:
        if (cs.workingWorkshops < cs.totalWorkshops) {
            cs.workingWorkshops++;
            cout << "Workshop started. Now " << cs.workingWorkshops << " working.\n";
        }
        else {
            cout << "All workshops are already working!\n";
        }
        break;
    case 2:
        if (cs.workingWorkshops > 0) {
            cs.workingWorkshops--;
            cout << "Workshop stopped. Now " << cs.workingWorkshops << " working.\n";
        }
        else {
            cout << "No workshops are working!\n";
        }
        break;
    case 0:
        cout << "Edit cancelled.\n";
        break;
    }
}

void saveToFile(const Pipe& pipe, const CompressorStation& station, bool hasPipe, bool hasStation) {
    ofstream file("TextFile4.txt");

    if (!file) {
        cout << "Error creating file!" << endl;
        return;
    }

    if (hasPipe) {
        file << "Pipe:" << endl;
        file << "KilometerMark: " << pipe.kilometerMark << endl;
        file << "Length: " << pipe.length << endl;
        file << "Diameter: " << pipe.diameter << endl;
        file << "UnderRepair: " << pipe.underRepair << endl;
        file << endl;
    }

    if (hasStation) {
        file << "CompressorStation:" << endl;
        file << "Name: " << station.name << endl;
        file << "TotalWorkshops: " << station.totalWorkshops << endl;
        file << "WorkingWorkshops: " << station.workingWorkshops << endl;
        file << "StationClass: " << station.stationClass << endl;
        file << endl;
    }

    file.close();
    cout << "Data saved to TextFile1.txt" << endl;
}

void loadFromFile(Pipe& pipe, CompressorStation& station, bool& hasPipe, bool& hasStation) {
    ifstream file("TextFile4.txt");

    if (!file) {
        cout << "No saved data found!" << endl;
        return;
    }

    hasPipe = false;
    hasStation = false;
    string line;

    while (getline(file, line)) { //не моё
        if (line == "Pipe:") {
            hasPipe = true;

            
            getline(file, line);
            pipe.kilometerMark = line.substr(line.find(": ") + 2);

           
            getline(file, line);
            pipe.length = stod(line.substr(line.find(": ") + 2));

            
            getline(file, line);
            pipe.diameter = stoi(line.substr(line.find(": ") + 2));

          
            getline(file, line);
            pipe.underRepair = stoi(line.substr(line.find(": ") + 2));

        }
        else if (line == "CompressorStation:") {
            hasStation = true;

           
            getline(file, line);
            station.name = line.substr(line.find(": ") + 2);

           
            getline(file, line);
            station.totalWorkshops = stoi(line.substr(line.find(": ") + 2));

            
            getline(file, line);
            station.workingWorkshops = stoi(line.substr(line.find(": ") + 2));

           
            getline(file, line);
            station.stationClass = stoi(line.substr(line.find(": ") + 2));
        }
    }

    file.close();

    if (hasPipe || hasStation) {
        cout << "Data loaded from TextFile2.txt" << endl;
    }
    else {
        cout << "No valid data found in file" << endl;
    }
}

void displayMenu() {
   
    cout << "1. Add Pipe" << endl;
    cout << "2. Add Compressor Station" << endl;
    cout << "3. View All Objects" << endl;
    cout << "4. Edit Pipe" << endl;
    cout << "5. Edit Compressor Station" << endl;
    cout << "6. Save to File" << endl;
    cout << "7. Load from File" << endl;
    cout << "0. Exit" << endl;
}

int main() {
    Pipe pipe;
    CompressorStation station;
    bool hasPipe = false;
    bool hasStation = false;

    while (true) {
        displayMenu();
        int choice = getInt("Enter your choice: ", 0, 7);

        switch (choice) {
        case 1:
            inputPipe(pipe);
            hasPipe = true;
            break;
        case 2:
            inputStation(station);
            hasStation = true;
            break;
        case 3:
            if (hasPipe) displayPipe(pipe);
            else cout << "No pipe data." << endl;

            if (hasStation) displayStation(station);
            else cout << "No station data." << endl;
            break;
        case 4:
            if (hasPipe) editPipe(pipe);
            else cout << "No pipe to edit." << endl;
            break;
        case 5:
            if (hasStation) editStation(station);
            else cout << "No station to edit." << endl;
            break;
        case 6:
            saveToFile(pipe, station, hasPipe, hasStation);
            break;
        case 7:
            loadFromFile(pipe, station, hasPipe, hasStation);
            break;
        case 0:
            cout << "Goodbye!" << endl;
            return 0;
        }
    }
}