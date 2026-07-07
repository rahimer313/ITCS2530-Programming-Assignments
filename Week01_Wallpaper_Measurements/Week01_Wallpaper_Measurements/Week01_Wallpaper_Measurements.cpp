// Week 08: Programming Assignment - Adding Classes
#include <iostream>
#include <string>
#include <iomanip>  // Required for setw and setprecision
#include <fstream>  // Required for report.txt file output

using namespace std;

// ============================================================================
// GLOBAL CONSTANTS (Removing Magic Numbers)
// ============================================================================
// Console Color Codes for Macbook
const string COLOR_DEFAULT = "\033[0m";
const string COLOR_INPUT = "\033[36m";
const string COLOR_LOGISTICS = "\033[33m";
const string COLOR_SUCCESS = "\033[32m";
const string COLOR_RULES = "\033[35m";
const string COLOR_ERROR = "\033[31m";

// Menu and Loop Limits
const int MENU_MIN = 1;
const int MENU_MAX = 3;
const int MENU_EXIT = 3;
const int SUPPLY_COUNT = 3; // Constant controls how many supply costs the array stores
const int ANIMATION_STEPS = 3;
const int DELAY_COUNT = 15000000;
const int ROLLS_PER_WALL = 2;

// Style Price Multipliers
const double MULTIPLIER_MINIMALIST = 1.0;
const double MULTIPLIER_MODERN = 1.25;
const double MULTIPLIER_RUSTIC = 1.50;

// Project Thresholds for Logic Checks
const int LARGE_PROJECT_WALLS = 4;
const int LARGE_PROJECT_ROLLS = 6;
const double PREMIUM_BUDGET_LIMIT = 150.00;
const double PREMIUM_ROLL_PRICE_LIMIT = 45.0;

// Enum represents wallpaper style choices.
enum WallpaperStyle {MINIMALIST = 1, MODERN = 2, RUSTIC = 3};

// Structure groups the name and cost for one supply item.
struct SupplyItem {
    string name;
    double cost;
};

// ============================================================================
// CLASS DEFINITION
// ============================================================================
class WallpaperTracker {
private: //old variables that were inside main() are now private class data members.
    string roomName;
    int wallCount;
    double pricePerRoll;
    int totalRollsNeeded;
    double totalCost;
    double supplyTotal;

    WallpaperStyle styleChoice;
    double styleMultiplier;
    string styleName;

    SupplyItem supplies[SUPPLY_COUNT];

public:
    WallpaperTracker();
    void runProgram();
    void changeColor(string colorCode) const;
    void displayBanner();
    void displayMenu();
    int getValidMenuChoice();
    void collectInputs();
    WallpaperStyle getValidThemeSelection();
    void collectSupplyCosts();
    double calculateSupplyTotal();
    double calculateDerivedValue();
    void showReport() const;
    void saveReportToFile(string filename) const;
    void showProjectRules() const;
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() { // Main became shorter because the object now runs the program.
    WallpaperTracker tracker;
    tracker.runProgram();

    return 0;
}

// ============================================================================
// CLASS MEMBER FUNCTION DEFINITIONS
// ============================================================================
// The constructor initializes all variables to safe starting values and runs automatically when the object is created.
WallpaperTracker::WallpaperTracker() {
    roomName = "";
    wallCount = 0;
    pricePerRoll = 0.0;
    totalRollsNeeded = 0;
    totalCost = 0.0;
    supplyTotal = 0.0;

    styleChoice = MINIMALIST;
    styleMultiplier = MULTIPLIER_MINIMALIST;
    styleName = "Minimalist";

    for (int i = 0; i < SUPPLY_COUNT; i++) {
        supplies[i].name = "";
        supplies[i].cost = 0.0;
    }
}

void WallpaperTracker::runProgram() {
    int menuChoice = 0;
// ---- 1. DO-WHILE LOOP ----
    do {
        changeColor(COLOR_DEFAULT); // Reset to default white text
        displayBanner();
        displayMenu();

        menuChoice = getValidMenuChoice();

        switch (menuChoice) {
        case 1:
            changeColor(COLOR_INPUT); // Switch text to Light Cyan for input processing
            cout << "\n--- Wallpaper Calculator ---" << endl;
            // Collect and validate base variables using references
            collectInputs();
            // Theme Selection
            styleChoice = getValidThemeSelection();
            // Set multipliers based on selection rules
            switch (styleChoice) {
            case MINIMALIST:
                styleMultiplier = MULTIPLIER_MINIMALIST;
                styleName = "Minimalist";
                break;
            case MODERN:
                styleMultiplier = MULTIPLIER_MODERN;
                styleName = "Modern";
                break;
            case RUSTIC:
                styleMultiplier = MULTIPLIER_RUSTIC;
                styleName = "Rustic";
                break;
            }

            collectSupplyCosts();
            supplyTotal = calculateSupplyTotal();
            totalCost = calculateDerivedValue() + supplyTotal;

            changeColor(COLOR_LOGISTICS);
            cout << "\nCompiling material costs against store inventories";
            for (int i = 0; i < ANIMATION_STEPS; i++) {
                cout << ".";
                for (volatile int delay = 0; delay < DELAY_COUNT; delay++);
            }
            cout << " Done!" << endl;

            if (wallCount >= LARGE_PROJECT_WALLS && totalRollsNeeded > LARGE_PROJECT_ROLLS) {
                cout << ">> Large project scale. Please secure items from matching color batches." << endl;
            }
            else {
                cout << ">> Small project scale. Standard matching retail sets will work." << endl;
            }

            if (totalCost >= PREMIUM_BUDGET_LIMIT || pricePerRoll * styleMultiplier > PREMIUM_ROLL_PRICE_LIMIT) {
                cout << ">> Premium budget tier. Look into wholesale coupon distributions." << endl;
            }
            else {
                cout << ">> Standard budget tier. Excellent material value choice." << endl;
            }

            showReport();
            saveReportToFile("report.txt");
            break;

        case 2:
            showProjectRules();
            break;

        case 3:
            changeColor(COLOR_ERROR);
            cout << "\nThank you for using the tool. Goodbye!" << endl;
            break;
        }

    } while (menuChoice != MENU_EXIT);

    changeColor(COLOR_DEFAULT);
}

void WallpaperTracker::changeColor(string colorCode) const {
    cout << colorCode;
}

void WallpaperTracker::displayBanner() {
    cout << "\n==========================================" << endl;
    cout << "    DIY INTERIOR DESIGN & PLANNING TOOL   " << endl;
    cout << "          Week 08 Classes Edition         " << endl;
    cout << "==========================================" << endl;
    cout << "Welcome! This tool helps plan your wallpaper project.\n" << endl;
}

void WallpaperTracker::displayMenu() {
    cout << "--- MAIN MENU ---" << endl;
    cout << "1. Run Wallpaper Calculator" << endl;
    cout << "2. View Project Level Rules" << endl;
    cout << "3. Exit Program" << endl;
    cout << "Enter choice (" << MENU_MIN << "-" << MENU_MAX << "): ";
}

int WallpaperTracker::getValidMenuChoice() {
    int choice;

    cin >> choice;

    while (cin.fail() || choice < MENU_MIN || choice > MENU_MAX) {
        cout << "Error: Invalid choice. Please enter a number between "
             << MENU_MIN << " and " << MENU_MAX << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> choice;
    }

    cin.ignore(1000, '\n');
    return choice;
}

void WallpaperTracker::collectInputs() {
    cout << "Enter room name (ex: Master Bedroom): ";
    getline(cin, roomName);

    while (roomName == "") {
        cout << "Invalid input. Please enter a room name: ";
        getline(cin, roomName);
    }

    cout << "Enter number of walls: ";
    cin >> wallCount;

    while (cin.fail() || wallCount <= 0) {
        cout << "Invalid input. Please enter a positive number of walls: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> wallCount;
    }

    cout << "Enter base price per roll: $";
    cin >> pricePerRoll;

    while (cin.fail() || pricePerRoll <= 0.0) {
        cout << "Invalid input. Please enter a valid positive price: $";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> pricePerRoll;
    }
}

WallpaperStyle WallpaperTracker::getValidThemeSelection() {
    int themeChoice;

    cout << "\nSelect your RoomGPT Visual Theme Strategy:" << endl;
    cout << "1. Minimalist (Eco-matte wallpaper, no markup)" << endl;
    cout << "2. Modern (Sleek texture finish, 25% style premium)" << endl;
    cout << "3. Rustic (Heavy embossed textile, 50% luxury premium)" << endl;
    cout << "Enter theme choice (1-3): ";

    cin >> themeChoice;

    while (cin.fail() || themeChoice < MENU_MIN || themeChoice > MENU_MAX) {
        cout << "Invalid theme selection. Enter 1, 2, or 3: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> themeChoice;
    }

    return static_cast<WallpaperStyle>(themeChoice);
}

void WallpaperTracker::collectSupplyCosts() {
    cout << "\nEnter three extra supplies, such as tape, brush, or primer." << endl;
    cin.ignore(1000, '\n');

    for (int i = 0; i < SUPPLY_COUNT; i++) {
        cout << "Supply " << i + 1 << " name: ";
        getline(cin, supplies[i].name);

        while (supplies[i].name == "") {
            cout << "Invalid input. Please enter a supply name: ";
            getline(cin, supplies[i].name);
        }

        cout << supplies[i].name << " cost: $";
        cin >> supplies[i].cost;

        while (cin.fail() || supplies[i].cost < 0.0) {
            cout << "Invalid input. Please enter 0 or higher: $";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> supplies[i].cost;
        }

        cin.ignore(1000, '\n');
    }
}

double WallpaperTracker::calculateSupplyTotal() {
    double total = 0.0;

    for (int i = 0; i < SUPPLY_COUNT; i++) {
        total += supplies[i].cost;
    }

    return total;
}

double WallpaperTracker::calculateDerivedValue() {
    totalRollsNeeded = wallCount * ROLLS_PER_WALL;
    double adjustedPrice = pricePerRoll * styleMultiplier;

    return totalRollsNeeded * adjustedPrice;
}

void WallpaperTracker::showReport() const {
    double adjustedPrice = pricePerRoll * styleMultiplier;

    changeColor(COLOR_SUCCESS);

    cout << "\n=========================================" << endl;
    cout << "        WALLPAPER PROJECT REPORT          " << endl;
    cout << "=========================================" << endl;
    cout << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
    cout << left << setw(20) << "Design Aesthetic:" << right << setw(21) << styleName << endl;
    cout << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
    cout << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;

    cout << fixed << setprecision(2);
    cout << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << adjustedPrice << endl;

    for (int i = 0; i < SUPPLY_COUNT; i++) {
        string supplyLabel = supplies[i].name + ":";
        cout << left << setw(20) << supplyLabel << right << "$" << setw(20) << supplies[i].cost << endl;
    }

    cout << left << setw(20) << "Supply Total:" << right << "$" << setw(20) << supplyTotal << endl;
    cout << "-----------------------------------------" << endl;
    cout << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
    cout << "=========================================" << endl;
}

void WallpaperTracker::saveReportToFile(string filename) const {
    ofstream outputFile(filename.c_str());
    double adjustedPrice = pricePerRoll * styleMultiplier;

    if (outputFile.is_open()) {
        outputFile << "=========================================" << endl;
        outputFile << "        WALLPAPER PROJECT REPORT          " << endl;
        outputFile << "=========================================" << endl;
        outputFile << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
        outputFile << left << setw(20) << "Design Aesthetic:" << right << setw(21) << styleName << endl;
        outputFile << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
        outputFile << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;

        outputFile << fixed << setprecision(2);
        outputFile << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << adjustedPrice << endl;

        for (int i = 0; i < SUPPLY_COUNT; i++) {
            string supplyLabel = supplies[i].name + ":";
            outputFile << left << setw(20) << supplyLabel << right << "$" << setw(20) << supplies[i].cost << endl;
        }

        outputFile << left << setw(20) << "Supply Total:" << right << "$" << setw(20) << supplyTotal << endl;
        outputFile << "-----------------------------------------" << endl;
        outputFile << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
        outputFile << "=========================================" << endl;

        outputFile.close();
        cout << "\nSuccess: Report accurately saved to '" << filename << "'." << endl;
    }
    else {
        cout << "\nError: Unable to open file for writing output report." << endl;
    }
}

void WallpaperTracker::showProjectRules() const {
    changeColor(COLOR_RULES);

    cout << "\n--- Project Level Rules ---" << endl;
    cout << "Standard Level: Total cost calculated under $" << PREMIUM_BUDGET_LIMIT << "." << endl;
    cout << "Premium Level: Total cost $" << PREMIUM_BUDGET_LIMIT
         << " or higher, or adjusted roll price over $"
         << PREMIUM_ROLL_PRICE_LIMIT << "." << endl;
}