#include "HuffmanTree.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	std::string text;
	cin >> text;
	auto ht = new HuffmanTree(text.c_str(), text.length());
	ht->printCode();
	auto es = ht->encrypt();
	es.print();
	int a[15] = { 0,1,1,0,1,1,1,0,1,1,0,0,1,1,0 };
	HuffmanTree::EncryptedString estr(a, 15);
	//auto str = ht->decrypt(es);
	cout << ht->decrypt(estr) << endl;
	system("pause");
    return 0;
}
