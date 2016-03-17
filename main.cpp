#include "Yandex_requester.h"
#include <iostream>
using namespace std;


int main() {

	Yandex_requester y;
	cout << y.send_request("a") << endl;
	cout << y.send_request("b") << endl;
	cout << y.send_request("c") << endl;


	return 0;
}
