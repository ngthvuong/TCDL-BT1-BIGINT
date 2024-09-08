#include <iostream>
#include "Modules/BigInt.h"

using namespace std;

int main()
{

    BigInt num1 = "123";
    BigInt num2 = num1;



    cout << "nhap num1 = ";
    cin >> num1;

    cout << num1 << endl;
    cout << num2 << endl;
   
    cout << "num1 = num2: " <<  (num1 == num2) << endl;
    cout << "num1 != num2: " <<  (num1 != num2) << endl;

    cout << "num1 > num2: " <<  (num1 > num2) << endl;
    cout << "num1 < num2: " <<  (num1 < num2) << endl;
    cout << "num1 >= num2: " <<  (num1 >= num2) << endl;
    cout << "num1 <= num2: " <<  (num1 <= num2) << endl;

    cout << "num1 + num2: " <<  (num1 + num2) << endl;
    cout << "-num1: " << -num1 << endl;
    cout << "num1 - num2: " << (num1 - num2) << endl;
    cout << "num1 * num2: " << (num1 * num2) << endl;
    cout << "num1 / num2: " << (num1 / num2) << endl;
    cout << "num1 % num2: " << (num1 % num2) << endl;



    cout << "abs(num1): " << num1.abs() << endl;






    return 0;
}