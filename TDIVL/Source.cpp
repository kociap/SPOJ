#include "BigInteger.hpp"
#include <iostream>

int main() {
    using namespace std;
    ios::sync_with_stdio(false);

#ifdef _DEBUG
    BigInteger x("432541543165768636541643541543");
    BigInteger y("542645541524546524525424");

    cout << "x + y = " << (x + y) << "; " << (x + y == BigInteger("432542085811310161088168066967")) << endl;
    cout << "x - y = " << (x - y) << "; " << (x - y == BigInteger("432541000520227111995119016119")) << endl;
    cout << "x * y = " << (x * y) << "; " << (x * y == BigInteger("234716739923051537637440130492226530812686762703689232")) << endl;
    cout << "x / y = " << (x / y) << ", rem " << (x % y) << "; " << ((x / y == BigInteger("797097")) && (x % y == BigInteger("409953177175482001647415"))) << endl;
#endif // _DEBUG

#ifndef _DEBUG
    int t;
    cin >> t;

    while (t--) {
        BigInteger a, b;
        cin >> a >> b;
        if (a % b == 0) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }
#endif // !_DEBUG

    return 0;
}