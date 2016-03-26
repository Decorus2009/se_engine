#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]) {

    string s = "Hellp";
    cout << s[s.length() - 1] << endl;

    cout << s << endl;
    s.erase(s.length() - 2, 2);
    cout << s << endl;


    return 0;
}
