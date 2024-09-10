#include <iostream>
#include "Modules/BigInt.h"

using namespace std;
int main()
{
    // // Yêu Cầu 1.1 Nhập xuất và chuyển đổi số nguyên với chuỗi theo cơ số 10 và cơ số 16
    // cout << "=================================================================================" << endl;
    // cout << "Yeu Cau 1.1 Nhap xuat va chuyen doi so nguyen voi chuoi theo co so 10 va co so 16." << endl;

    // BigInt num1, num2, num3, num4;

    // // Nhâp liệu cơ số 10 và 16:
    // cout << "num1 = ";
    // cin >> num1;
    // cout << "num2 = ";
    // cin >> num2;
    // cout << "num3 = ";
    // cin >> num3;
    // cout << "num4 = ";
    // cin >> num4;

    // // Xuất dữ liệu cơ số 10;
    // cout << "------------------------------------------------------------------------------------" << endl;
    // cout << "Xuat co so 10: " << endl;
    // cout << "num1 (10) = " << num1 << endl;
    // cout << "num2 (10) = " << num2 << endl;
    // cout << "num3 (10) = " << num3 << endl;
    // cout << "num4 (10) = " << num4 << endl;

    // // Xuất dữ liệu cơ số 16;
    // cout << "Xuat co so 16: " << endl;
    // cout << "num1 (16) = " << num1.hex() << endl;
    // cout << "num2 (16) = " << num2.hex() << endl;
    // cout << "num3 (16) = " << num3.hex() << endl;
    // cout << "num4 (16) = " << num4.hex() << endl;

    cout << "=================================================================================" << endl;
    cout << "Yeu Cau 1.2 chuyen doi voi kieu so int." << endl;

    int num6, num7;
    BigInt num8, num9;

    num6 = -12345;
    num8 = (BigInt) num6;
    num9 = -23456789;
    num7 = (int) num9;

    // Xuất dữ liệu
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Xuat du lieu: " << endl;
    cout << "num6 =\t " << num6 << " \t- Type num6: " << typeid(num6).name() << endl;
    cout << "num7 =\t " << num7 << " \t- Type num7: " << typeid(num7).name() << endl;
    cout << "num8 =\t " << num8 << " \t- Type num8: " << typeid(num8).name() << endl;
    cout << "num9 =\t " << num9 << " \t- Type num9: " << typeid(num9).name() << endl;




    // BigInt num2;

    // BigInt num1 = "123";
    // BigInt num2 = num1;
    // int a = -0;
    // BigInt num3 = (BigInt) a;
    // a = (int)num3;
    // cout << "num3 = " << num3 << endl;
    // cout << "a = " << a << endl;

    // cout << "nhap num1 = ";
    // cin >> num1;

    // cout << "num1_10 :" << num1 << endl;
    // cout << "num1_16 :" << num1.hex() << endl;

    // cout << "num1 = num2: " << (num1 == num2) << endl;
    // cout << "num1 != num2: " << (num1 != num2) << endl;
    // cout << "num1 > num2: " << (num1 > num2) << endl;
    // cout << "num1 < num2: " << (num1 < num2) << endl;
    // cout << "num1 >= num2: " << (num1 >= num2) << endl;
    // cout << "num1 <= num2: " << (num1 <= num2) << endl;

    // cout << "num1 + num2: " << (num1 + num2) << endl;
    // cout << "-num1: " << -num1 << endl;
    // cout << "num1 - num2: " << (num1 - num2) << endl;
    // cout << "num1 * num2: " << (num1 * num2) << endl;
    // cout << "num1 / num2: " << (num1 / num2) << endl;
    // cout << "num1 % num2: " << (num1 % num2) << endl;
    // cout << "num1 ^ 2: " << (num1.power(2)) << endl;
    // cout << "num1 ^ 4: " << (num1.power(4)) << endl;

    // cout << "abs(num1): " << num1.abs() << endl;
    // cout << "root(2): " << num1.root(2) << endl;
    // cout << "root(3): " << num1.root(3) << endl;

    return 0;
}