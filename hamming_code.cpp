
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool isPowerOfTwo(int position) {
    return position > 0 && (position & (position - 1)) == 0;
}

vector<int> generateHammingCode(const string& data) {
    int m = static_cast<int>(data.length());
    int r = 0;

    while ((1 << r) < m + r + 1) {
        ++r;
    }

    int n = m + r;
    vector<int> code(n + 1, 0);

    int j = 0;
    for (int i = 1; i <= n; ++i) {
        if (!isPowerOfTwo(i)) {
            code[i] = data[j] - '0';
            ++j;
        }
    }

    for (int p = 1; p <= n; p <<= 1) {
        int parity = 0;
        for (int i = 1; i <= n; ++i) {
            if ((i & p) != 0) {
                parity ^= code[i];
            }
        }
        code[p] = parity;
    }

    return code;
}

void displayCode(const vector<int>& code) {
    int n = static_cast<int>(code.size()) - 1;

    cout << "\nGenerated Hamming Code: ";
    for (int i = n; i >= 1; --i) {
        cout << code[i];
    }
    cout << endl;
}

void detectAndCorrect(const string& received) {
    int n = static_cast<int>(received.length());
    vector<int> code(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        code[i] = received[n - i] - '0';
    }

    int errorPosition = 0;
    for (int p = 1; p <= n; p <<= 1) {
        int parity = 0;
        for (int i = 1; i <= n; ++i) {
            if ((i & p) != 0) {
                parity ^= code[i];
            }
        }
        if (parity == 1) {
            errorPosition += p;
        }
    }

    if (errorPosition == 0) {
        cout << "\nNo error detected." << endl;
    } else if (errorPosition <= n) {
        cout << "\nError detected at position: " << errorPosition << endl;
        code[errorPosition] ^= 1;
        cout << "Error corrected successfully." << endl;
    } else {
        cout << "\nInvalid error position." << endl;
        return;
    }

    cout << "Corrected Hamming Code: ";
    for (int i = n; i >= 1; --i) {
        cout << code[i];
    }
    cout << endl;
}

int main() {
    string data;
    string received;

    cout << "=================================\n";
    cout << "       HAMMING CODE SYSTEM\n";
    cout << "=================================\n";

    cout << "\nEnter binary data: ";
    cin >> data;

    for (char bit : data) {
        if (bit != '0' && bit != '1') {
            cout << "Invalid input! Enter binary digits only." << endl;
            return 1;
        }
    }

    if (data.empty()) {
        cout << "Data cannot be empty." << endl;
        return 1;
    }

    vector<int> code = generateHammingCode(data);
    displayCode(code);

    cout << "\nEnter received Hamming Code: ";
    cin >> received;

    if (received.length() != code.size() - 1) {
        cout << "Invalid received code length!" << endl;
        return 1;
    }

    for (char bit : received) {
        if (bit != '0' && bit != '1') {
            cout << "Invalid input! Enter binary digits only." << endl;
            return 1;
        }
    }

    detectAndCorrect(received);

    return 0;
}
