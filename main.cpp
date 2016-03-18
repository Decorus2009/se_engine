#include "Yandex_requester.h"
#include "Prepositions_Dictionary.h"
#include <iostream>

using namespace std;

  
int main() {

	Yandex_requester y;
	cout << y.send_request("a") << endl;
	cout << y.send_request("b") << endl;
	cout << y.send_request("c") << endl;

	Prepositions_Dictionary PS;
	PS.print();
	
	return 0;
}
