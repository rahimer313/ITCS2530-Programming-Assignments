#include <iostream>
#include <string>
#include <iomanip>  // Required for setw and setprecision
#include <fstream>  // Required for report.txt file output
#include <windows.h> // Required for changing Console Colors on Windows

using namespace std;

// ============================================================================
// GLOBAL CONSTANTS (Removing Magic Numbers)
// ============================================================================
// Console Color Codes
const int COLOR_DEFAULT = 7;
const int COLOR_INPUT = 11;
const int COLOR_LOGISTICS = 14;
const int COLOR_SUCCESS = 10;
const int COLOR_RULES = 13;
const int COLOR_ERROR = 12;

// Menu and Loop Limits
const int MENU_MIN = 1;
const int MENU_MAX = 3;
const int MENU_EXIT = 3;
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

// ============================================================================
// FUNCTION PROTOTYPES (Declarations)
// ============================================================================
void changeColor(int colorCode);
void displayBanner();
void displayMenu();
int getValidMenuChoice();
void collectInputs(string& room, int& walls, double& basePrice);
int getValidThemeSelection();
double calculateDerivedValue(int walls, double price, double multiplier, int& rollsNeeded);
void saveReport(string room, string style, int walls, int rolls, double price, double cost);

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

    int styleChoice = 0;
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
            case 1:
                styleMultiplier = MULTIPLIER_MINIMALIST;
                styleName = "Minimalist";
                break;
            case 2:
                styleMultiplier = MULTIPLIER_MODERN;
                styleName = "Modern";
                break;
            case 3:
                styleMultiplier = MULTIPLIER_RUSTIC;
                styleName = "Rustic";
                break;
            }

            // Perform calculations using our specialized function
            totalCost = calculateDerivedValue(wallCount, pricePerRoll, styleMultiplier, totalRollsNeeded);
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