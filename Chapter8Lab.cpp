// Programming Fundamentals II (COSC 1437)
// Author: Adan Garza
// Description: manages a small class roster using arrays and C-strings
#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <vector>

using namespace std;

const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;

char names[MAX_STUDENTS][31];
int scores[MAX_STUDENTS][NUM_TESTS];
double averages[MAX_STUDENTS];
char grades[MAX_STUDENTS];

void readRoster(char names[][31], int scores[][NUM_TESTS], int& count) {
    cout << "Enter number of students (1-" << MAX_STUDENTS << "): ";
    while (true) {
        if (!(cin >> count)) {
            cout << "Invalid input. Enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (count >= 1 && count <= MAX_STUDENTS) break;
        cout << "Please enter a number between 1 and " << MAX_STUDENTS << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < count; ++i) {
        cout << "Enter name for student " << (i+1) << ": ";
        cin.getline(names[i], 31);
        for (int j = 0; j < NUM_TESTS; ++j) {
            cout << "  Enter score " << (j+1) << " (0-100): ";
            while (true) {
                if (!(cin >> scores[i][j])) {
                    cout << "    Invalid score. Enter an integer 0-100: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (scores[i][j] >= 0 && scores[i][j] <= 100) break;
                cout << "    Score must be 0-100. Try again: ";
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count) {
    for (int i = 0; i < count; ++i) {
        int sum = 0;
        for (int j = 0; j < NUM_TESTS; ++j) sum += scores[i][j];
        averages[i] = static_cast<double>(sum) / NUM_TESTS;
        double a = averages[i];
        if (a >= 90.0) grades[i] = 'A';
        else if (a >= 80.0) grades[i] = 'B';
        else if (a >= 70.0) grades[i] = 'C';
        else if (a >= 60.0) grades[i] = 'D';
        else grades[i] = 'F';
    }
}

int searchRoster(const char names[][31], int count, const char target[]) {
    for (int i = 0; i < count; ++i) {
        if (strcmp(names[i], target) == 0) return i;
    }
    return -1;
}

void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < count; ++j) {
            if (strcmp(names[j], names[minIdx]) < 0) minIdx = j;
        }
        if (minIdx != i) {
            char tempName[31];
            strcpy(tempName, names[i]);
            strcpy(names[i], names[minIdx]);
            strcpy(names[minIdx], tempName);

            int tempScores[NUM_TESTS];
            for (int k = 0; k < NUM_TESTS; ++k) {
                tempScores[k] = scores[i][k];
                scores[i][k] = scores[minIdx][k];
                scores[minIdx][k] = tempScores[k];
            }

            double tempAvg = averages[i];
            averages[i] = averages[minIdx];
            averages[minIdx] = tempAvg;

            char tempGrade = grades[i];
            grades[i] = grades[minIdx];
            grades[minIdx] = tempGrade;
        }
    }
}

void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count) {
    cout << left << setw(20) << "Name";
    for (int j = 0; j < NUM_TESTS; ++j) cout << right << setw(8) << (string("Test") + to_string(j+1));
    cout << right << setw(10) << "Average" << right << setw(8) << "Grade" << '\n';
    cout << string(20 + NUM_TESTS*8 + 10 + 8, '-') << '\n';
    cout << fixed << setprecision(2);
    for (int i = 0; i < count; ++i) {
        cout << left << setw(20) << names[i];
        for (int j = 0; j < NUM_TESTS; ++j) cout << right << setw(8) << scores[i][j];
        cout << right << setw(10) << averages[i] << right << setw(8) << grades[i] << '\n';
    }
}

void printStats(const double averages[], int count) {
    if (count <= 0) {
        cout << "No students loaded.\n";
        return;
    }
    double local[MAX_STUDENTS];
    for (int i = 0; i < count; ++i) {
        local[i] = averages[i];
    }
    double high = local[0];
    double low = local[0];
    double sum = 0.0;
    for (auto v : local) {
        if (v > high) high = v;
        if (v < low) low = v;
        sum += v;
    }
    double classAvg = sum / count;
    cout << fixed << setprecision(2);
    cout << "Class high: " << high << "\n";
    cout << "Class low: " << low << "\n";
    cout << "Class average: " << classAvg << "\n";
}

int main() {
    int count = 0;
    int choice = 0;
    do {
        cout << "===== Roster Report Menu =====\n";
        cout << "1. Load roster (enter data)\n";
        cout << "2. Calculate averages and grades\n";
        cout << "3. Sort roster alphabetically\n";
        cout << "4. Search for a student\n";
        cout << "5. Print roster\n";
        cout << "6. Print class statistics\n";
        cout << "7. Quit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                readRoster(names, scores, count);
                break;
            case 2:
                if (count > 0) calcAverages(scores, averages, grades, count);
                else cout << "No roster loaded.\n";
                break;
            case 3:
                if (count > 0) sortRoster(names, scores, averages, grades, count);
                else cout << "No roster loaded.\n";
                break;
            case 4:
                if (count > 0) {
                    char target[31];
                    cout << "Enter student name to search: ";
                    cin.getline(target, 31);
                    int idx = searchRoster(names, count, target);
                    if (idx >= 0) {
                        cout << "Found " << names[idx] << " at index " << idx << ".\n";
                    } else cout << "Student not found.\n";
                } else cout << "No roster loaded.\n";
                break;
            case 5:
                if (count > 0) printRoster(names, scores, averages, grades, count);
                else cout << "No roster loaded.\n";
                break;
            case 6:
                if (count > 0) printStats(averages, count);
                else cout << "No roster loaded.\n";
                break;
            case 7:
                cout << "Quitting.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 7);
    return 0;
}
