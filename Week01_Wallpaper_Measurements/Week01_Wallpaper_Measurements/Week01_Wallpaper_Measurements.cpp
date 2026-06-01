#include <iostream>
#include <string>   // Required for string variables and getline
#include <iomanip>  // Required for setw, setprecision, left, right
#include <fstream>  // Required for file output (report.txt)

using namespace std;

int main()
{
    // ---- Variable Declarations ----
    string clientName;
    double wallLength = 0.0;
    double wallWidth = 0.0;
    int customRollsInStock = 0; // Added integer type requirement
    double rollCoverage = 0.0;

    double totalWallArea = 0.0;
    double totalRollsNeeded = 0.0;

    // ---- 1. Friendly Introduction Banner ----
    cout << "=====================================================" << endl;
    cout << "      WELCOME TO THE PREMIUM WALLPAPER CALCULATOR     " << endl;
    cout << "=====================================================" << endl;
    cout << "This tool will calculate your project needs and save a" << endl;
    cout << "professional summary report automatically.\n" << endl;

    // ---- 2. User Input with Validation (Mixed Types) ----

    // Input 1: String with spaces (using getline)
    cout << "Enter the client or project name: ";
    getline(cin, clientName);

    // Input 2: Double for Wall Length
    cout << "Enter the wall length (in feet): ";
    cin >> wallLength;
    if (wallLength <= 0) {
        cout << "Error: Length must be a positive number. Exiting program." << endl;
        return 1; // Gracefully exit due to invalid input
    }   // Added a random comment

    // Input 3: Double for Wall Width
    cout << "Enter the wall width (in feet): ";
    cin >> wallWidth;
    if (wallWidth <= 0) {
        cout << "Error: Width must be a positive number. Exiting program." << endl;
        return 1;
    }

    // Input 4: Integer for inventory count
    cout << "How many rolls do you currently have in stock? ";
    cin >> customRollsInStock;
    if (customRollsInStock < 0) {
        cout << "Error: Stock cannot be negative. Exiting program." << endl;
        return 1;
    }

    // Input 5: Double for roll size coverage
    cout << "How many square feet does one wallpaper roll cover? ";
    cin >> rollCoverage;
    if (rollCoverage <= 0) {
        cout << "Error: Roll coverage must be greater than zero. Exiting program." << endl;
        return 1;
    }

    // ---- 3. Compute Derived Values ----
    totalWallArea = wallLength * wallWidth;
    totalRollsNeeded = totalWallArea / rollCoverage;

    // ---- 4. Formatted, Readable Console Output (Table) ----
    cout << "\n" << string(45, '-') << endl;
    cout << "| " << left << setw(25) << "PROJECT SUMMARY" << right << setw(16) << "VALUE" << " |" << endl;
    cout << string(45, '-') << endl;

    // Setting fixed floating-point precision to 2 decimal places for neatness
    cout << fixed << setprecision(2);

    cout << "| " << left << setw(25) << "Client/Project Name:" << right << setw(16) << clientName.substr(0, 15) << " |" << endl;
    cout << "| " << left << setw(25) << "Total Wall Area:" << right << setw(13) << totalWallArea << " sqf |" << endl;
    cout << "| " << left << setw(25) << "Rolls Currently Owned:" << right << setw(16) << customRollsInStock << " |" << endl;
    cout << "| " << left << setw(25) << "Total Rolls Required:" << right << setw(16) << totalRollsNeeded << " |" << endl;
    cout << string(45, '-') << endl;

    // ---- 5. Save Report to File (report.txt) ----
    ofstream outFile;
    outFile.open("report.txt");

    // Replicating the neat table structure to the external text file
    outFile << "=====================================================" << endl;
    outFile << "               OFFICIAL PROJECT REPORT               " << endl;
    outFile << "=====================================================" << endl;
    outFile << string(45, '-') << endl;
    outFile << "| " << left << setw(25) << "METRIC" << right << setw(16) << "DETAILS" << " |" << endl;
    outFile << string(45, '-') << endl;

    outFile << fixed << setprecision(2);
    outFile << "| " << left << setw(25) << "Project Target:" << right << setw(16) << clientName.substr(0, 15) << " |" << endl;
    outFile << "| " << left << setw(25) << "Dimensions:" << right << setw(8) << wallLength << "x" << setw(7) << wallWidth << " |" << endl;
    outFile << "| " << left << setw(25) << "Calculated Area:" << right << setw(13) << totalWallArea << " sqf |" << endl;
    outFile << "| " << left << setw(25) << "Current Stock:" << right << setw(16) << customRollsInStock << " |" << endl;
    outFile << "| " << left << setw(25) << "Total Rolls Needed:" << right << setw(16) << totalRollsNeeded << " |" << endl;
    outFile << string(45, '-') << endl;

    outFile.close(); // Clean up and close the file
    cout << "\nReport successfully exported and saved to 'report.txt'!" << endl;

    return 0;
}