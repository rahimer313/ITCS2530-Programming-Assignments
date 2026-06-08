#include <iostream>
#include <string>
#include <iomanip>  // Required for setw and setprecision
#include <fstream>  // Required for report.txt file output

using namespace std;

int main() {
    // ==========================================
    // VARIABLE DECLARATIONS
    // ==========================================
    int menuChoice;
    string roomName;
    int wallCount;
    double pricePerRoll;
    int totalRollsNeeded;
    double totalCost;
    ofstream outputFile;

    // 1. Welcome Banner
    cout << "========================================" << endl;
    cout << "     DIY HOME IMPROVEMENT TOOL          " << endl;
    cout << "========================================" << endl;
    cout << "Welcome! This tool helps plan your project.\n" << endl;

    // 2. Main Menu Options
    cout << "--- MAIN MENU ---" << endl;
    cout << "1. Run Wallpaper Calculator" << endl;
    cout << "2. View Project Level Rules" << endl;
    cout << "3. Exit Program" << endl;
    cout << "Enter choice (1-3): ";
    cin >> menuChoice;

    // Menu Input Validation
    if (menuChoice < 1 || menuChoice > 3) {
        cout << "Error: Invalid choice. Ending program." << endl;
        return 1;
    }

    // Clear buffer for the upcoming string input
    cin.ignore();

    // Switch Statement for Navigation
    switch (menuChoice) {
    case 1: {
        cout << "\n--- Wallpaper Calculator ---" << endl;

        // Gather Inputs
        cout << "Enter room name (ex: Master Bedroom): ";
        getline(cin, roomName);

        cout << "Enter number of walls: ";
        cin >> wallCount;

        cout << "Enter price per roll: $";
        cin >> pricePerRoll;

        // Calculations
        totalRollsNeeded = wallCount * 2;
        totalCost = totalRollsNeeded * pricePerRoll;

        cout << "\n--- Project Status ---" << endl;

        // Compound Condition 1: Project Size Check
        if (wallCount >= 4 && totalRollsNeeded > 6) {
            cout << ">> Large project. Please buy matching batches." << endl;
        }
        else {
            cout << ">> Small project. Standard rolls will work." << endl;
        }

        // Compound Condition 2: Cost Level Check
        if (totalCost >= 150.00 || pricePerRoll > 45.0) {
            cout << ">> Premium budget level. Look for coupons." << endl;
        }
        else {
            cout << ">> Standard budget level. Excellent value choice." << endl;
        }

        // Output to Screen
        cout << "\n=========================================" << endl;
        cout << "       WALLPAPER PROJECT REPORT          " << endl;
        cout << "=========================================" << endl;
        cout << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
        cout << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
        cout << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;
        cout << fixed << setprecision(2);
        cout << left << setw(20) << "Price Per Roll:" << right << "$" << setw(20) << pricePerRoll << endl;
        cout << "-----------------------------------------" << endl;
        cout << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
        cout << "=========================================" << endl;

        // Save to File
        outputFile.open("report.txt");

        outputFile << "=========================================" << endl;
        outputFile << "       WALLPAPER PROJECT REPORT          " << endl;
        outputFile << "=========================================" << endl;
        outputFile << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
        outputFile << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
        outputFile << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;
        outputFile << fixed << setprecision(2);
        outputFile << left << setw(20) << "Price Per Roll:" << right << "$" << setw(20) << pricePerRoll << endl;
        outputFile << "-----------------------------------------" << endl;
        outputFile << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
        outputFile << "=========================================" << endl;

        outputFile.close();
        cout << "\nSuccess: Report saved to 'report.txt'." << endl;

        break;
    }

    case 2:
        cout << "\n--- Project Level Rules ---" << endl;
        cout << "Standard Level: Total cost under $150.00." << endl;
        cout << "Premium Level: Total cost $150.00 or higher, or roll price over $45.00." << endl;
        break;

    case 3:
        cout << "\nThank you for using the tool. Goodbye!" << endl;
        break;
    }

    return 0;
}