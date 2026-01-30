#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // จำเป็นสำหรับการแปลง string เป็นตัวเลข

using namespace std;

// --- ZONE 1: ทีม Ma 76543th ---
double add(double num1, double num2)
{
    return num1 + num2; // บวก
}

double subtract(double num1, double num2)
{
    return num1 - num2; // ลบ
}

double multiply(double num1, double num2)
{
    return num1 * num2; // คูณ
}

double divide(double num1, double num2)
{
    if (num2 == 0)
    {
        cout << "Error: Divide by zero!" << endl;
        return 0;
    }
    return num1 / num2; // หาร
}

void SeparateWords(string input, double *numbers, int &numCount, char *ops, int &opCount);
double calculate(double *numbers, int numCount, char *ops, int opCount);

// --- ZONE 4:(Main System) ---
int main()
{
    string inputEquation;

    // จองพื้นที่ Pointer
    double *numbers = new double[100];
    char *ops = new char[100];

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

    // คืนพื้นที่หน่วยความจำ
    delete[] numbers;
    delete[] ops;

    return 0;
}

// --- ZONE 2: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: รับ input เข้ามา แล้วยัดตัวเลขใส่ numbers[] และเครื่องหมายใส่ ops[]
// สิ่งที่เปลี่ยน: ต้องส่ง int& numCount มาด้วย เพื่อนับว่าตอนนี้มีกี่ตัวแล้ว
void SeparateWords(string input, double *numbers, int &numCount, char *ops, int &opCount)
{
    string tempNum = ""; // พักตัวเลข
}

// --- ZONE 3: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: วนลูป Pointer เพื่อคำนวณ คูณ/หาร ก่อน แล้วค่อย บวก/ลบ
// สิ่งที่เปลี่ยน: ต้องรับ numCount เข้ามาด้วย จะได้รู้ว่าลูปถึงไหน
double calculate(double *numbers, int numCount, char *ops, int opCount)
{
    double currentResult;
    for (int i = 0; i < opCount; i++)
    {
        if (ops[i] == '*' || ops[i] == '/')
        {
            double currentResult = 0;
            if (ops[i] == '*')
            {
                currentResult = multiply(numbers[i], numbers[i + 1]);
            }
            else
            {
                currentResult = divide(numbers[i], numbers[i + 1]);
            }

            //เก็บผลลัพธ์ไว้ที่ช่องตัวหน้า (numbers[i])
            numbers[i] = currentResult;

            //"ขยับกระดาน" (Shift Array) เพื่อลบตัวที่ใช้แล้วทิ้งไป
            // ขยับตัวเลข: ดึงตัวข้างหลังมาทับตัวข้างหน้า (เริ่มที่ i+1)
            for (int k = i + 1; k < numCount - 1; k++)
            {
                numbers[k] = numbers[k + 1];
            }
            // ขยับเครื่องหมาย: ดึงตัวข้างหลังมาทับตัวข้างหน้า
            for (int k = i; k < opCount - 1; k++)
            {
                ops[k] = ops[k + 1];
            }

            //อัปเดตจำนวนตัวเลขและเครื่องหมายที่เหลือ
            numCount--;
            opCount--;

             // เพราะเครื่องหมายตัวต่อไปมันขยับมาแทนที่ตำแหน่งปัจจุบันแล้ว ต้องเช็คซ้ำ
            i--;
        }
    }

    //บวก (+) กับ ลบ (-) ทำจากซ้ายไปขวาได้เลย
    double finalResult = numbers[0];
    for (int i = 0; i < opCount; i++)
    {
        if (ops[i] == '+')
        {
            finalResult = add(numbers[i],numbers[i + 1]);
        }else if (ops[i] == '-')
        {
            finalResult = subtract(numbers[i],numbers[i + 1]);
        }
        return finalResult;
        
    }
    

    // ไกด์:
    // เนื่องจาก Pointer ลบช่องว่างยาก (ไม่มี .erase แบบ vector)
    // แนะนำให้คำนวณเสร็จ แล้วขยับตัวข้างหลังมาทับ หรือสร้าง array ชั่วคราวมาเก็บผลลัพธ์
    return 0;
}