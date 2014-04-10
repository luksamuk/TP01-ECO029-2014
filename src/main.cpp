#include <iostream>
#include "TextPool.h"
#include "Hash.h"
using namespace std;

int main(void)
{
	TextPool t;
	Hashish h(10);
	t.RegisterWordsOnHash(h);

	cout << "Hello world!" << endl;
	return 0;
}
