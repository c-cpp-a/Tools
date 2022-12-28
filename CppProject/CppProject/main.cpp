#include "tools/BigInt.cpp"
#include "tools/BigInt.h"
#include "tools/code.cpp"
#include "tools/code.h"
#include "tools/maths.cpp"
#include "tools/matrix.cpp"
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;
int main() {
    string s=Code::encode_base64(string("Hello,world!"));
    // string s=Code::decode_base64("SGVsbG8sd29ybGQh");
    cout << s << ' ' << s.length();
    // for (char ch = 0; ch < 127; ++ch) {
    //     cout << ch << ':' << Code::base64_nums_hash[ch] << endl;
    // }
    // for (char ch = 0; ch < 127; ++ch) {
    //     if (ch == '=') {
    //         cout << "0,";
    //     } else if (Code::base64_nums.find(ch) == -1) {
    //         cout << "255,";
    //     } else {
    //         cout << Code::base64_nums.find(ch) << ',';
    //     }
    // }
    return 0;
}
