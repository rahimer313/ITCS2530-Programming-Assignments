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

// Enum gives names to the wallpaper style choices instead of only using numbers.
enum WallpaperStyle {MINIMALIST = 1, MODERN = 2, RUSTIC = 3};

// ============================================================================
// FUNCTION PROTOTYPES (Declarations)
// ============================================================================
void changeColor(string colorCode);
void displayBanner();
void displayMenu();
int getValidMenuChoice();
void collectInputs(string& room, int& walls, double& basePrice);
WallpaperStyle getValidThemeSelection();
void collectSupplyCosts(double supplyCosts[], int size); 
double calculateSupplyTotal(const double supplyCosts[], int size); 
double calculateDerivedValue(int walls, double price, double multiplier, int& rollsNeeded);
void saveReport(string room, string style, int walls, int rolls, double price, double cost,
    const double supplyCosts[], int size, double supplyTotal);

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    int menuChoice = 0;
    string roomName = "";
    int wallCount = 0;
    double pricePerRoll = 0.0;
    int totalRollsNeeded = 0;
    double totalCost = 0.0;
    double supplyCosts[SUPPLY_COUNT] = { 0.0 }; // This array stores three extra supply costs, like tape, brush, and primer.
    double supplyTotal = 0.0;

    WallpaperStyle styleChoice = MINIMALIST;
    double styleMultiplier = MULTIPLIER_MINIMALIST;
    string styleName = "Standard";

    // ---- 1. DO-WHILE LOOP ----
    do {
        changeColor(COLOR_DEFAULT); // Reset to default white text
        displayBanner();
        displayMenu();

        menuChoice = getValidMenuChoice();

        switch (menuChoice) {
        case 1: {
            changeColor(COLOR_INPUT); // Switch text to Light Cyan for input processing
            cout << "\n--- Wallpaper Calculator ---" << endl;

            // Collect and validate base variables using references
            collectInputs(roomName, wallCount, pricePerRoll);

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

            // The first function fills the array, and the second function totals the array values.
            collectSupplyCosts(supplyCosts, SUPPLY_COUNT); 
            supplyTotal = calculateSupplyTotal(supplyCosts, SUPPLY_COUNT);

            // Perform calculations using our specialized function
            totalCost = calculateDerivedValue(wallCount, pricePerRoll, styleMultiplier, totalRollsNeeded);
            totalCost = totalCost + supplyTotal; // This adds the extra supply costs to the wallpaper cost.

            // Update the adjusted roll price reflecting theme changes
            double adjustedPrice = pricePerRoll * styleMultiplier;

            // ---- 3. FOR LOOP (Fixed Iteration) ----
            changeColor(COLOR_LOGISTICS); // Switch to Yellow for logistical feedback strings
            cout << "\nCompiling material costs against store inventories";
            for (int i = 0; i < ANIMATION_STEPS; i++) {
                cout << ".";
                for (volatile int delay = 0; delay < DELAY_COUNT; delay++); // Delay pacing
            }
            cout << " Done!" << endl;

            // Project Size Check
            if (wallCount >= LARGE_PROJECT_WALLS && totalRollsNeeded > LARGE_PROJECT_ROLLS) {
                cout << ">> Large project scale. Please secure items from matching color batches." << endl;
            }
            else {
                cout << ">> Small project scale. Standard matching retail sets will work." << endl;
            }

            // Cost Level Check
            if (totalCost >= PREMIUM_BUDGET_LIMIT || adjustedPrice > PREMIUM_ROLL_PRICE_LIMIT) {
                cout << ">> Premium budget tier. Look into wholesale coupon distributions." << endl;
            }
            else {
                cout << ">> Standard budget tier. Excellent material value choice." << endl;
            }

            // Output Report to Screen
            changeColor(COLOR_SUCCESS); // Switch to Light Green for the successful data output summary
            cout << "\n=========================================" << endl;
            cout << "        WALLPAPER PROJECT REPORT          " << endl;
            cout << "=========================================" << endl;
            cout << left << setw(20) << "Room Name:" << right << setw(21) << roomName << endl;
            cout << left << setw(20) << "Design Aesthetic:" << right << setw(21) << styleName << endl;
            cout << left << setw(20) << "Total Walls:" << right << setw(21) << wallCount << endl;
            cout << left << setw(20) << "Rolls Needed:" << right << setw(21) << totalRollsNeeded << endl;
            cout << fixed << setprecision(2);
            cout << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << adjustedPrice << endl;
            cout << left << setw(20) << "Supply 1 Cost:" << right << "$" << setw(20) << supplyCosts[0] << endl; 
            cout << left << setw(20) << "Supply 2 Cost:" << right << "$" << setw(20) << supplyCosts[1] << endl; 
            cout << left << setw(20) << "Supply 3 Cost:" << right << "$" << setw(20) << supplyCosts[2] << endl; 
            cout << left << setw(20) << "Supply Total:" << right << "$" << setw(20) << supplyTotal << endl; 
            cout << "-----------------------------------------" << endl;
            cout << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << totalCost << endl;
            cout << "=========================================" << endl;

            // Save report to flat file database
            saveReport(roomName, styleName, wallCount, totalRollsNeeded, adjustedPrice, totalCost,
                supplyCosts, SUPPLY_COUNT, supplyTotal);
            break;
        }

        case 2:
            changeColor(COLOR_RULES); // Light Purple for documentation screens
            cout << "\n--- Project Level Rules ---" << endl;
            cout << "Standard Level: Total cost calculated under $" << PREMIUM_BUDGET_LIMIT << "." << endl;
            cout << "Premium Level: Total cost $" << PREMIUM_BUDGET_LIMIT << " or higher, or adjusted roll price over $" << PREMIUM_ROLL_PRICE_LIMIT << "." << endl;
            break;

        case 3:
            changeColor(COLOR_ERROR); // Light Red for program termination feedback
            cout << "\nThank you for using the tool. Goodbye!" << endl;
            break;
        }

    } while (menuChoice != MENU_EXIT);

    return 0;
}

// ============================================================================
// FUNCTION DEFINITIONS
// ============================================================================

void changeColor(string colorCode) {
    cout << colorCode;
}

void displayBanner() {
    cout << "\n==========================================" << endl;
    cout << "    DIY INTERIOR DESIGN & PLANNING TOOL   " << endl;
    cout << "       Modularized Functions Edition      " << endl;
    cout << "==========================================" << endl;
    cout << "Welcome! This tool helps plan your project.\n" << endl;
}

void displayMenu() {
    cout << "--- MAIN MENU ---" << endl;
    cout << "1. Run Wallpaper Calculator" << endl;
    cout << "2. View Project Level Rules" << endl;
    cout << "3. Exit Program" << endl;
    cout << "Enter choice (" << MENU_MIN << "-" << MENU_MAX << "): ";
}

int getValidMenuChoice() {
    int choice;
    cin >> choice;
    while (cin.fail() || choice < MENU_MIN || choice > MENU_MAX) {
        cout << "Error: Invalid choice. Please enter a number between " << MENU_MIN << " and " << MENU_MAX << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> choice;
    }
    cin.ignore();
    return choice;
}

void collectInputs(string& room, int& walls, double& basePrice) {
    cout << "Enter room name (ex: Master Bedroom): ";
    getline(cin, room);

    while (room == "") { 
        cout << "Invalid input. Please enter a room name: "; 
        getline(cin, room); 
    }

    cout << "Enter number of walls: ";
    cin >> walls;
    while (cin.fail() || walls <= 0) {
        cout << "Invalid input. Please enter a positive number of walls: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> walls;
    }

    cout << "Enter base price per roll: $";
    cin >> basePrice;
    while (cin.fail() || basePrice <= 0.0) {
        cout << "Invalid input. Please enter a valid positive price: $";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> basePrice;
    }
}

WallpaperStyle getValidThemeSelection() {
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

void collectSupplyCosts(double supplyCosts[], int size) { 
    cout << "\nEnter three extra supply costs, such as tape, brush, or primer." << endl; 

    for (int i = 0; i < size; i++) { 
        cout << "Supply " << i + 1 << " cost: $"; 
        cin >> supplyCosts[i]; 

        while (cin.fail() || supplyCosts[i] < 0.0) { 
            cout << "Invalid input. Please enter 0 or higher: $"; 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cin >> supplyCosts[i]; 
        } 
    } 
} 

double calculateSupplyTotal(const double supplyCosts[], int size) { 
    double total = 0.0; 

    for (int i = 0; i < size; i++) { 
        total += supplyCosts[i]; 
    } 

    return total; 
} 

double calculateDerivedValue(int walls, double price, double multiplier, int& rollsNeeded) {
    rollsNeeded = walls * ROLLS_PER_WALL;
    double adjustedPrice = price * multiplier;
    return rollsNeeded * adjustedPrice;
}

void saveReport(string room, string style, int walls, int rolls, double price, double cost, const double supplyCosts[], int size, double supplyTotal) {
    ofstream outputFile("report.txt");
    if (outputFile.is_open()) {
        outputFile << "=========================================" << endl;
        outputFile << "        WALLPAPER PROJECT REPORT          " << endl;
        outputFile << "=========================================" << endl;
        outputFile << left << setw(20) << "Room Name:" << right << setw(21) << room << endl;
        outputFile << left << setw(20) << "Design Aesthetic:" << right << setw(21) << style << endl;
        outputFile << left << setw(20) << "Total Walls:" << right << setw(21) << walls << endl;
        outputFile << left << setw(20) << "Rolls Needed:" << right << setw(21) << rolls << endl;
        outputFile << fixed << setprecision(2);
        outputFile << left << setw(20) << "Adjusted Roll Price:" << right << "$" << setw(20) << price << endl;
        
        for (int i = 0; i < size; i++) { 
            outputFile << left << setw(20) << "Supply Cost:" << right << "$" << setw(20) << supplyCosts[i] << endl; 
        } 
        outputFile << left << setw(20) << "Supply Total:" << right << "$" << setw(20) << supplyTotal << endl; 

        outputFile << "-----------------------------------------" << endl;
        outputFile << left << setw(20) << "Total Cost:" << right << "$" << setw(20) << cost << endl;
        outputFile << "=========================================" << endl;
        outputFile.close();
        cout << "\nSuccess: Report accurately saved to 'report.txt'." << endl;
    }
    else {
        cout << "\nError: Unable to open file for writing output report." << endl;
    }
}