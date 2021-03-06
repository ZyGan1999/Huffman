#include "HuffmanTree.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	cout << "请输入需要加密的字符串" << endl;
	std::string text;
	//cin >> text;
	getline(cin, text);
	cout << text << endl;
	system("pause");
	auto ht = new HuffmanTree(text.c_str(), text.length());
	cout << "各字符的对应编码是:" << endl;
	ht->printCode();
	cout << "这段文字的哈夫曼编码是:" << endl;
	auto es = ht->encrypt();
	es.print();
	cout << "请输入需要用此编码解密的0-1串" << endl;
	std::string ZeroOneStr;
	cin >> ZeroOneStr;
	const int length = ZeroOneStr.length();
	int * ZeroOneNum = new int(length);
	for (int i = 0; i < length; ++i) {
		ZeroOneNum[i] = ZeroOneStr[i] - '0';
	}
	HuffmanTree::EncryptedString estr(ZeroOneNum, length);
	cout << "解码结果是:" << endl;
	auto str = ht->decrypt(estr);
	for (int i = 0; str[i] != '\0'; ++i) cout << str[i];
	cout << endl;
	system("pause");
    return 0;
}
