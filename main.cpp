#include <iostream>
#include "Modules/BigInt.h"

using namespace std;
int main()
{
    cout << "=================================================================================" << endl;
    // Yêu Cầu 1.1 Nhập xuất và chuyển đổi số nguyên với chuỗi theo cơ số 10 và cơ số 16
    cout << "Yeu Cau 1.1 Nhap xuat va chuyen doi so nguyen voi chuoi theo co so 10 va co so 16." << endl;

    BigInt num1, num2, num3, num4;

    // Nhâp liệu cơ số 10 và 16:
    cout << "num1 = ";
    cin >> num1;
    cout << "num2 = ";
    cin >> num2;
    cout << "num3 = ";
    cin >> num3;
    cout << "num4 = ";
    cin >> num4;

    // Xuất dữ liệu cơ số 10;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Xuat co so 10: " << endl;
    cout << "num1 (10) = " << num1 << endl;
    cout << "num2 (10) = " << num2 << endl;
    cout << "num3 (10) = " << num3 << endl;
    cout << "num4 (10) = " << num4 << endl;

    // Xuất dữ liệu cơ số 16;
    cout << "Xuat co so 16: " << endl;
    cout << "num1 (16) = " << num1.hex() << endl;
    cout << "num2 (16) = " << num2.hex() << endl;
    cout << "num3 (16) = " << num3.hex() << endl;
    cout << "num4 (16) = " << num4.hex() << endl;

    cout << "=================================================================================" << endl;
    // Yêu câu 1.2: Chuyển đổi với kiểu số nguyên int của C/C++.
    cout << "Yeu Cau 1.2 chuyen doi voi kieu so int." << endl;

    int num6, num7;
    BigInt num8, num9;

    num6 = -12345;
    num8 = (BigInt)num6;
    num9 = -23456789;
    num7 = (int)num9;

    // Xuất dữ liệu
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "Xuat du lieu: " << endl;
    cout << "num6 =\t " << num6 << " \t- Type num6: " << typeid(num6).name() << endl;
    cout << "num7 =\t " << num7 << " \t- Type num7: " << typeid(num7).name() << endl;
    cout << "num8 =\t " << num8 << " \t- Type num8: " << typeid(num8).name() << endl;
    cout << "num9 =\t " << num9 << " \t- Type num9: " << typeid(num9).name() << endl;


    cout << "=================================================================================" << endl;
    // Yêu cầu 1.3: Các phép toán số học thông thường: cộng, trừ, nhân, chia nguyên và chia lấy dư, đối,
    // trị tuyệt đối, lũy thừa với số mũ nguyên không âm.
    cout << "Yeu Cau 1.3: Cac phep toan so hoc thong thuong: cong, tru, nhan, chia nguyen va chia lay du \
tri tuyet doi, luy thua voi so mu nguyen khong am"
         << endl;

    BigInt num10, num11;
    cout << "num10 = ";
    cin >> num10;
    cout << "num11 = ";
    cin >> num11;

    // Xuất dữ liệu
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "num10 + num11: \t" << (num10 + num11) << endl;
    cout << "-num10: \t" << -num10 << endl;
    cout << "num10 - num11: \t" << (num10 - num11) << endl;
    cout << "num10 * num11: \t" << (num10 * num11) << endl;
    cout << "num10 / num11: \t" << (num10 / num11) << endl;
    cout << "num10 % num11: \t" << (num10 % num11) << endl;
    cout << "abs(num10): " << num10.abs() << endl;
    cout << "num10 ^ 2: \t" << (num10.power(2)) << endl;
    cout << "num10 ^ 3: \t" << (num10.power(3)) << endl;


    cout << "=================================================================================" << endl;
    // Yêu cầu 1.4: Các phép toán so sánh: bằng, khác, nhỏ hơn, lớn hơn, nhỏ hơn hoặc bằng, lớn hơn hoặc bằng.
    cout << "Yeu Cau 1.4: Cac phep toan so sanh: bang, khac, nho hon, lon hon, nho hon hoac bang, lon hon hoac bang." << endl;
    BigInt num12, num13;
    cout << "num12 = ";
    cin >> num12;
    cout << "num13 = ";
    cin >> num13;

    // Xuất dữ liệu
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "num12 = num13: \t" << (num12 == num13) << endl;
    cout << "num12 != num13: " << (num12 != num13) << endl;
    cout << "num12 > num13: \t" << (num12 > num13) << endl;
    cout << "num12 < num13: \t" << (num12 < num13) << endl;
    cout << "num12 >= num13: " << (num12 >= num13) << endl;
    cout << "num12 <= num13: " << (num12 <= num13) << endl;


    cout << "=================================================================================" << endl;
    // Yêu cầu 1.5: Phép toán lấy phần nguyên của căn bậc 2, bậc 3.
    cout << "Yeu Cau 1.5: Phép toan lay phan nguyen cua can bac 2, bac 3." << endl;

    BigInt num14;
    cout << "num14 = ";
    cin >> num14;

    // // Xuất dữ liệu
    // cout << "------------------------------------------------------------------------------------" << endl;
    cout << "root(2): " << num14.root(2) << endl;
    cout << "root(3): " << num14.root(3) << endl;

    return 0;
}