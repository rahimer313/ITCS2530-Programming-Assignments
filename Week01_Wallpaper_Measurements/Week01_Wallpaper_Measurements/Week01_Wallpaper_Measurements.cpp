#include <iostream>
#include <string>
#include <iomanip>  // Required for setw and setprecision
#include <fstream>  // Required for report.txt file output

using namespace std;

int main() {
    // ==========================================
    // VARIABLE DECLARATIONS
    // ==========================================
    int menuChoice = 0;
    string roomName = "";
    int wallCount = 0;
    double pricePerRoll = 0.0;
    int totalRollsNeeded = 0;
    double totalCost = 0.0;

    // New variables for RoomGPT aesthetic adjustment
    int styleChoice = 0;
    double styleMultiplier = 1.0;
    string styleName = "Standard";

    ofstream outputFile;

    // ---- 1. DO-WHILE LOOP ----
    // This loop guarantees the entire program keeps running until the user actively selects option 3.
    do {
        // Welcome Banner
        cout << "\n========================================" << endl;
        cout << "     DIY HOME IMPROVEMENT TOOL v2.0     " << endl;
        cout << "   Bridging RoomGPT Styles with Math    " << endl;
        cout << "========================================" << endl;
        cout << "Welcome! This tool helps plan your project.\n" << endl;

        // Main Menu Options
        cout << "--- MAIN MENU ---" << endl;
        cout << "1. Run Wallpaper Calculator" << endl;
        cout << "2. View Project Level Rules" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter choice (1-3): ";
        cin >> menuChoice;

        // ---- 2. WHILE LOOP (Data Validation) ----
        // This validates the main menu selection and reprompts immediately on bad data.
        while (cin.fail() || menuChoice < 1 || menuChoice > 3) {
            cout << "Error: Invalid choice. Please enter a number between 1 and 3: ";
            cin.clear();            // Clear the error flags
            cin.ignore(1000, '\n'); // Clear the bad input from the stream buffer
            cin >> menuChoice;
        }

        // Clear buffer for incoming string inputs
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

            // Loop for validation: ensures user doesn't enter a negative number of walls
            while (cin.fail() || wallCount <= 0) {
                cout << "Invalid input. Please enter a positive number of walls: ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> wallCount;
            }

            cout << "Enter base price per roll: $";
            cin >> pricePerRoll;

            // Loop for validation: ensures cost is a valid positive value
            while (cin.fail() || pricePerRoll <= 0.0) {
                cout << "Invalid input. Please enter a valid positive price: $";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> pricePerRoll;
            }

            // ---- ROOMGPT DESIGN THEME MENU ----
            cout << "\nSelect your RoomGPT Visual Theme Strategy:" << endl;
            cout << "1. Minimalist (Eco-matte wallpaper, no markup)" << endl;
            cout << "2. Modern (Sleek texture finish, 25% style premium)" << endl;
            cout << "3. Rustic (Heavy embossed textile, 50% luxury premium)" << endl;
            cout << "Enter theme choice (1-3): ";
            cin >> styleChoice;

            while (cin.fail() || styleChoice < 1 || styleChoice > 3) {
                cout << "Invalid theme selection. Enter 1, 2, or 3: ";
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> styleChoice;
            }

            // Processing the multiplier based on the chosen RoomGPT design theme
            switch (styleChoice) {
            case 1:
                styleMultiplier = 1.0;
                styleName = "Minimalist";
                break;
            case 2:
                styleMultiplier = 1.25;
                styleName = "Modern";
                break;
            case 3:
                styleMultiplier = 1.50;
                styleName = "Rustic";
                break;
            }

            // Calculations incorporating the derived style markup values
            pricePerRoll = pricePerRoll * styleMultiplier;
            totalRollsNeeded = wallCount * 2;
            totalCost = totalRollsNeeded * pricePerRoll;

            // ---- 3. FOR LOOP (Fixed Iteration) ----
            // Simulates processing project logistics through exactly 3 structural loops
            cout << "\nCompiling material costs against store inventories";
            for (int i = 0; i < 3; i++) {
                cout << ".";
                // A micro delay loop to provide structural pacing to console actions
                for (volatile int delay = 0; delay < 15000000; delay++);
            }
            cout << " Done!" << endl;

            cout << "\n--- Project Status ---" << endl;

            // Compound Condition 1: Project Size Check
            if (wallCount >= 4 && totalRollsNeeded > 6) {
                cout << ">> Large project scale. Please secure items from matching color batches." << endl;
            }
            else {
                cout << ">> Small project scale. Standard matching retail sets will work." << endl;
            }

            // Compound Condition 2: Cost Level Check
            if (totalCost >= 150.00 || pricePerRoll > 45.0) {
                cout << ">> Premium budget tier. Look into wholesale coupon distributions." << endl;
            }
            else {
                cout << ">> Standard budget tier. Excellent material value choice." << endl;
            }

            // Output Report to Screen
            cout << "\n=========================================" << endl;
            cout << "       WALLPAPER PROJECT REPORT          " << endl;
            cout << "=========================================" << endl;
            cout << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
            cout << left << setw(20) << "Design Aesthetic:" << right << setw(21) << styleName << endl;
            cout << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
            cout << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;
            cout << fixed << setprecision(2);
            cout << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << pricePerRoll << endl;
            cout << "-----------------------------------------" << endl;
            cout << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
            cout << "=========================================" << endl;

            // Save Report to File
            outputFile.open("report.txt");
            if (outputFile.is_open()) {
                outputFile << "=========================================" << endl;
                outputFile << "       WALLPAPER PROJECT REPORT          " << endl;
                outputFile << "=========================================" << endl;
                outputFile << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
                outputFile << left << setw(20) << "Design Aesthetic:" << right << setw(21) << styleName << endl;
                outputFile << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
                outputFile << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;
                outputFile << fixed << setprecision(2);
                outputFile << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << pricePerRoll << endl;
                outputFile << "-----------------------------------------" << endl;
                outputFile << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
                outputFile << "=========================================" << endl;
                outputFile.close();
                cout << "\nSuccess: Report accurately saved to 'report.txt'." << endl;
            }
            else {
                cout << "\nError: Unable to open file for writing output report." << endl;
            }
            break;
        }

        case 2:
            cout << "\n--- Project Level Rules ---" << endl;
            cout << "Standard Level: Total cost calculated under $150.00." << endl;
            cout << "Premium Level: Total cost $150.00 or higher, or adjusted roll price over $45.00." << endl;
            break;

        case 3:
            cout << "\nThank you for using the tool. Goodbye!" << endl;
            break;
        }

    } while (menuChoice != 3); // Loop ends when menuChoice is exactly 3

    return 0;
}