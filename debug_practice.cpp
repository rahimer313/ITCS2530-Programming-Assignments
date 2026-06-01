#include <iostream>
#include <string>

int main() {
    // Program by Rahima
    std::string studentName = "Rima";
    
    double grade1 = 95.5;
    double grade2 = 92.0;
    double grade3 = 98.0;
    
    // Calculate total and average
    double total = grade1 + grade2 + grade3;
    double average = total / 3.0;
    
    std::cout << "Student: " << studentName << std::endl;
    std::cout << "Average Grade: " << average << "%" << std::endl;
    
    return 0;
}