#include <iostream>

using namespace std;

int main()
{
    double wall_Length;
    double wall_Width;
    double roll_Size;
    double wallArea;
    double rolls_Needed;

    // Ask user for measurements
    cout << "Enter the wall length in feet: ";
    cin >> wall_Length;

    cout << "Enter the wall width in feet: ";
    cin >> wall_Width;

    cout << "How many square feet does one wallpaper roll cover? ";
    cin >> roll_Size;

    // Calculate wall area
    wallArea = wall_Length * wall_Width;

    // Calculate wallpaper rolls needed
    rolls_Needed = wallArea / roll_Size;

    // Display results
    cout << "\n----- Wallpaper Project Summary -----" << endl;

    cout << "Your wall area is "
        << wallArea
        << " square feet." << endl;

    cout << "You will need approximately "
        << rolls_Needed
        << " wallpaper rolls to cover the wall." << endl;

    return 0;
}