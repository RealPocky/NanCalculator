#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // จำเป็นสำหรับการแปลง string เป็นตัวเลข

using namespace std;

// --- ZONE 1: ทีม Math ---
double add(double num1, double num2) {
    return num1 + num2; // บวก
}

double subtract(double num1, double num2) {
    return num1 - num2; // ลบ
}

double multiply(double num1, double num2) {
    return num1 * num2; // คูณ
}

double divide(double num1, double num2) {
    if (num2 == 0) {
        cout << "Error: Divide by zero!" << endl;
        return 0;
    }
    return num1 / num2; // หาร
}

// --- ZONE 2: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: รับ input เข้ามา แล้วยัดตัวเลขใส่ numbers[] และเครื่องหมายใส่ ops[]
// สิ่งที่เปลี่ยน: ต้องส่ง int& numCount มาด้วย เพื่อนับว่าตอนนี้มีกี่ตัวแล้ว
void SeparateWords(string input, double* numbers, int& numCount, char* ops, int& opCount) {
    string tempNum = ""; //พักตัวเลข

}

// --- ZONE 3: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: วนลูป Pointer เพื่อคำนวณ คูณ/หาร ก่อน แล้วค่อย บวก/ลบ
// สิ่งที่เปลี่ยน: ต้องรับ numCount เข้ามาด้วย จะได้รู้ว่าลูปถึงไหน
double calculate(double* numbers, int numCount, char* ops, int opCount) {
    // ไกด์:
    // เนื่องจาก Pointer ลบช่องว่างยาก (ไม่มี .erase แบบ vector)
    // แนะนำให้คำนวณเสร็จ แล้วขยับตัวข้างหลังมาทับ หรือสร้าง array ชั่วคราวมาเก็บผลลัพธ์
    return 0; 
}

// --- ZONE 4:(Main System) ---
int main() {
    string inputEquation;

    // จองพื้นที่ Pointer
    double* numbers = new double[100]; 
    char* ops = new char[100];
    
    // ตัวแปรช่วยนับจำนวนรอบ
    int numCount = 0;
    int opCount = 0;

    cout << "===========================" << endl;
    cout << "   Pointer Calculator" << endl;
    cout << "===========================" << endl;
    cout << "Enter equation: ";

    cin >> inputEquation; // รับสมการจากผู้ใช้

    // ส่ง Pointer และตัวนับจำนวน ไปแยกส่วนประกอบ
    SeparateWords(inputEquation, numbers, numCount, ops, opCount);

    // ส่ง Pointer และจำนวนรอบที่ได้ ไปคำนวณ
    double result = calculate(numbers, numCount, ops, opCount);

    // แสดงผล
    cout << "Result: " << result << endl;

    //คืนพื้นที่หน่วยความจำ
    delete[] numbers;
    delete[] ops;

    return 0;
}