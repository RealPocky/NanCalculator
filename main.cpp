#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

// --- Function Math  ---
double add(double num1, double num2) { // บวก
    return num1 + num2;
}

double subtract(double num1, double num2) { // ลบ
    return num1 - num2;
}

double multiply(double num1, double num2) { // คูณ
    return num1 * num2;
}

double divide(double num1, double num2) {   // หาร
    if (num2 == 0) {
        cout << "Error: Divide by zero!" << endl;
        return 0;
    }
    return num1 / num2;
}

// Function Prototypes
// แยกคำ ระหว่างตัวเลข กับเครื่องหมาย
void SeparateWords(string input, double *numbers, int &numCount, char *ops, int &opCount, bool *isPercent);

// คำนวณ
double calculate(double *numbers, int numCount, char *ops, int opCount, bool *isPercent);

// --- Main System ---
int main() {
    string inputEquation;

    // 1. จองพื้นที่ Heap Memory (Pointer Array)
    double *numbers = new double[100];
    char *ops = new char[100];
    bool *isPercent = new bool[100]; // จำว่าช่องไหนเป็น %

    // เคลียร์ค่าเริ่มต้น
    for(int i=0; i<100; i++) isPercent[i] = false;

    int numCount = 0;
    int opCount = 0;

    cout << "===========================" << endl;
    cout << "   Pointer Calculator" << endl;
    cout << "===========================" << endl;
    cout << "Enter equation: ";
    cin >> inputEquation;

    // 2. เรียกใช้ Parser (แยกคำ)
    SeparateWords(inputEquation, numbers, numCount, ops, opCount, isPercent);

    // 3. เรียกใช้ Calculator (คำนวณ)
    double result = calculate(numbers, numCount, ops, opCount, isPercent);

    // 4. แสดงผล
    cout << "Result: " << result << endl;

    // 5. คืนพื้นที่หน่วยความจำ (Clean up)
    delete[] numbers;
    delete[] ops;
    delete[] isPercent;

    return 0;
}

// --- Parser (แยกคำและจัดการ %) ---
void SeparateWords(string input, double* numbers, int& numCount, char* ops, int& opCount, bool* isPercent) {
    string tempNum = "";    //พักตัวเลข
    
    for (int i = 0; i < input.length(); i++) {
        char word = input[i];

        // กรณีเจอตัวเลขหรือจุดทศนิยม
        if (isdigit(word) || word == '.') {
            tempNum += word;    //เก็บพักไว้ในtempNumก่อน
        }
        // กรณีเจอเครื่องหมาย %
        else if (word == '%') {
             if (!tempNum.empty()) {
                double val = stod(tempNum);  // stod = String TO Double
                val = val / 100.0;          // แปลงเป็นทศนิยมก่อน
                
                numbers[numCount] = val;
                isPercent[numCount] = true; // Mark ว่าตัวนี้มาจาก %
                
                numCount++;     // ขยับ ตำแหน่ง index ไปช่องถัดไป
                tempNum = "";   // ทำให้tempNuว่างเพื่อเก็บข้อมูลชุดต่อไป
             }
        }
        // กรณีเจอเครื่องหมายคำนวณ (+ - * /)
        else if (word == '+' || word == '-' || word == '*' || word == '/') { 
            if (!tempNum.empty()) {
                numbers[numCount] = stod(tempNum); // stod = String TO Double
                isPercent[numCount] = false; // ตัวเลขปกติ ไม่ใช่ %
                numCount++;       // ขยับ ตำแหน่ง index ไปช่องถัดไป
                tempNum = "";     // ทำให้tempNuว่างเพื่อเก็บข้อมูลชุดต่อไป
            }
            ops[opCount] = word;    // เมื่อเก็บตัวเลขเสร็จแล้ว ก็นำเครื่องหมายไปเก็บไว้ในops[]
            opCount++;              // ขยับ ตำแหน่ง index ไปช่องถัดไป
        }
    }

    // เก็บตกตัวเลขชุดสุดท้าย
    if (!tempNum.empty()) {
        numbers[numCount] = stod(tempNum); 
        isPercent[numCount] = false;
        numCount++;       
    }
}

// --- Calculator (คำนวณตามลำดับความสำคัญ) ---
double calculate(double *numbers, int numCount, char *ops, int opCount, bool *isPercent) {
    
    // รอบที่ 1: เคลียร์ คูณ (*) และ หาร (/) ก่อน
    for (int i = 0; i < opCount; i++) {
        if (ops[i] == '*' || ops[i] == '/') {
            double res = 0;
            if (ops[i] == '*') {
                res = multiply(numbers[i], numbers[i + 1]);
            } else {
                res = divide(numbers[i], numbers[i + 1]);
            }

            // เก็บผลลัพธ์
            numbers[i] = res;
            isPercent[i] = false; // ผลคูณหารแล้ว ไม่ถือเป็น % เดิมแล้ว

            // Shift Array (ขยับกระดาน)
            // ขยับตัวเลขและสถานะ %
            for (int k = i + 1; k < numCount - 1; k++) {
                numbers[k] = numbers[k + 1];
                isPercent[k] = isPercent[k + 1]; 
            }
            // ขยับเครื่องหมาย
            for (int k = i; k < opCount - 1; k++) {
                ops[k] = ops[k + 1];
            }

            numCount--;
            opCount--;
            i--; // ถอย index เพื่อเช็คตำแหน่งเดิมซ้ำ

            /*
            
            sadk;asmd;asdwadfawd
            
            
            Help me pls
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            
            */
        }
    }

    // รอบที่ 2: บวก (+) และ ลบ (-) พร้อม Logic ของ Percent
    double finalResult = numbers[0];
    
    for (int i = 0; i < opCount; i++) {
        double nextValue = numbers[i + 1];

        // Logic Percent: ถ้าเป็นการบวกลบ แล้วตัวหลังเป็น % ให้คิดเทียบจากตัวหน้า
        // เช่น 100 - 10% คือ 100 - (100 * 0.1)
        if (isPercent[i + 1] == true) {
            nextValue = finalResult * nextValue;
        }

        if (ops[i] == '+') {
            finalResult = add(finalResult, nextValue);
        } else if (ops[i] == '-') {
            finalResult = subtract(finalResult, nextValue);
        }
    }

    return finalResult;     // คืนค่าไปยัง main เพื่อแสดงผล
}