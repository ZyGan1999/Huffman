#include "HuffmanTree.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	std::string text;
	cin >> text;
	auto ht = new HuffmanTree(text.c_str(), text.length());

	auto es = ht->encrypt();
	es.print();

	cout << ht->decrypt(es) << endl;

    return 0;
}
