#include <iostream>
using namespace std;

void displayMenu() {
    cout << "===========================" << endl;
    cout << "      NanCalculator" << endl;
    cout << "===========================" << endl;
    cout << "1. Add (+)" << endl;
    cout << "2. Subtract (-)" << endl;
    cout << "3. Multiply (*)" << endl;
    cout << "4. Divide (/)" << endl;
    cout << "5. Percent (%)" << endl;
    cout << "6. Results (=)" << endl;
    cout << "7. delete (del)" << endl;
    cout << "===========================" << endl;
    cout << "Enter choice: ";
}

int main() {
    displayMenu();
    return 0;
}