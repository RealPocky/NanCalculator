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

double modulo(double num1, double num2){ 
    return fmod(num1, num2);    //เปอร์เซน
}

void SeparateWords(string input, double *numbers, int &numCount, char *ops, int &opCount, bool *isPercent);
double calculate(double *numbers, int numCount, char *ops, int opCount, bool *isPercent);

// --- ZONE 4:(Main System) ---
int main()
{
    string inputEquation;

    // จองพื้นที่ Pointer
    double *numbers = new double[100];
    char *ops = new char[100];

    bool *isPercent = new bool[100]; // สร้าง Array มาจำช่องไหนเป็น%
    // เคลียร์ค่าเริ่มต้นให้เป็น false ทั้งหมด
    for(int i=0; i<100; i++) isPercent[i] = false;

    // ตัวแปรช่วยนับจำนวนรอบ
    int numCount = 0;
    int opCount = 0;

    cout << "===========================" << endl;
    cout << "   Pointer Calculator" << endl;
    cout << "===========================" << endl;
    cout << "Enter equation: ";

    cin >> inputEquation; // รับสมการจากผู้ใช้

    // ส่ง Pointer และตัวนับจำนวน ไปแยกส่วนประกอบ
    SeparateWords(inputEquation, numbers, numCount, ops, opCount, isPercent);

    // ส่ง Pointer และจำนวนรอบที่ได้ ไปคำนวณ
    double result = calculate(numbers, numCount, ops, opCount, isPercent);
    // แสดงผล
    cout << "Result: " << result << endl;

    // คืนพื้นที่หน่วยความจำ
    delete[] numbers;
    delete[] ops;
    delete[] isPercent;  // [เพิ่มใหม่] อย่าลืมคืนเมมโม

    return 0;
}

// --- ZONE 2: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: รับ input เข้ามา แล้วยัดตัวเลขใส่ numbers[] และเครื่องหมายใส่ ops[]
// สิ่งที่เปลี่ยน: ต้องส่ง int& numCount มาด้วย เพื่อนับว่าตอนนี้มีกี่ตัวแล้ว
void SeparateWords(string input, double* numbers, int& numCount, char* ops, int& opCount, bool* isPercent) {
    string tempNum = ""; //พักตัวเลข
    int i = 0;
    for (i = 0; i < input.length(); i++) {
        char word = input[i];

        // กรณีที่ 1 เจอตัวเลข หรือ ทดศนิยม
        if (isdigit(word) || word == '.'){
            tempNum += word; //เก็บพักไว้ในtempNumก่อน
        }
       // [เพิ่มใหม่] ถ้าเจอ %
        else if (word == '%') {
             if (!tempNum.empty()) {
                double val = stod(tempNum); 
                val = val / 100.0;          // หาร 100 ให้เป็นทศนิยม (เช่น 50 -> 0.5)
                
                numbers[numCount] = val;    // เก็บค่า 0.5
                isPercent[numCount] = true; // [สำคัญ] ติ๊กถูกว่าช่องนี้มาจาก % นะ
                
                numCount++;
                tempNum = ""; // เคลียร์ตัวเลข
             }
             // หมายเหตุ: ไม่เก็บ % ลงใน ops[] เพราะเราแปลงค่าตัวเลขไปแล้ว
        }

        // กรณีที่ 2: เจอเครื่องหมาย (+ - * /)
        else if (word == '+' || word == '-' || word == '*' || word == '/') { 
            if (!tempNum.empty()) {
                numbers[numCount] = stod(tempNum);
                // ช่องนี้ไม่ใช่ % (เพราะไม่เจอ % ก่อนหน้า)
                isPercent[numCount] = false; 
                numCount++;       
                tempNum = "";    
            }
            ops[opCount] = word;
            opCount++; 
        }
    }

    // จบลูปแล้วถ้ายังมีตัวเลขค้างอยู่ ให้แปลงเป็น double และเอาไปเก็บไวใน numbers[]เหมือนเดิม
    if (!tempNum.empty()) {
        numbers[numCount] = stod(tempNum); 
        isPercent[numCount] = false; // ตัวสุดท้ายถ้าไม่มี % ต่อท้าย ก็เป็น false
        numCount++;       
        tempNum = "";    
    }
}

// --- ZONE 3: (เปลี่ยนเป็น Pointer) ---
// หน้าที่: วนลูป Pointer เพื่อคำนวณ คูณ/หาร ก่อน แล้วค่อย บวก/ลบ
// สิ่งที่เปลี่ยน: ต้องรับ numCount เข้ามาด้วย จะได้รู้ว่าลูปถึงไหน
double calculate(double *numbers, int numCount, char *ops, int opCount, bool *isPercent) {
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
                currentResult = divide(numbers[i], numbers[i + 1]);
           
            //เก็บผลลัพธ์ไว้ที่ช่องตัวหน้า (numbers[i])
            numbers[i] = currentResult;
            // ผลลัพธ์ใหม่ ไม่ถือว่าเป็น percent แล้ว
            isPercent[i] = false;

            //"ขยับกระดาน" (Shift Array) เพื่อลบตัวที่ใช้แล้วทิ้งไป
            // ขยับตัวเลข: ดึงตัวข้างหลังมาทับตัวข้างหน้า (เริ่มที่ i+1)
            // Shift Array numbers และ isPercent
            for (int k = i + 1; k < numCount - 1; k++)
            {
                numbers[k] = numbers[k + 1];
                isPercent[k] = isPercent[k + 1]; // ขยับสถานะ % ตามมาด้วย
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
    // สูตร: ถ้าตัวหลังเป็น % ให้เอา (ตัวหน้า * ตัวหลัง) ก่อน แล้วค่อย บวก/ลบ
    double finalResult = numbers[0];
    for (int i = 0; i < opCount; i++)
    {
        // ให้แปลงจาก 0.5 เป็น (finalResult * 0.5)
        // เช่น 100 - 0.5(%) -> 100 - (100*0.5) -> 100 - 50
        if (isPercent[i + 1] == true){
            numbers[i + 1] = finalResult * numbers[i + 1];
        }

        if (ops[i] == '+') {
            finalResult = add(finalResult, numbers[i + 1]);
        } 
        else if (ops[i] == '-') {
            finalResult = subtract(finalResult, numbers[i + 1]);
        }
    }
        return finalResult;

    // ไกด์:
    // เนื่องจาก Pointer ลบช่องว่างยาก (ไม่มี .erase แบบ vector)
    // แนะนำให้คำนวณเสร็จ แล้วขยับตัวข้างหลังมาทับ หรือสร้าง array ชั่วคราวมาเก็บผลลัพธ์
    return 0;
}