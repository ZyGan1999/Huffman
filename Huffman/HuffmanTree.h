#pragma once
#include "TreeNode.h"
#include <iostream>
#include <map>
#include <queue>
#include <cstring>
#include <algorithm>
class HuffmanTree {
	TreeNode* root;
	char * _string;
	int _length;
	std::map<char, TreeNode *> pointerToLeaves;

public:

	static const int MAX_ENCRYPTED_SIZE = 65535;
	static const int MAX_STRING_SIZE = 65535;

	void printCode() {
		int WPL = 0;
		//输出字符与它对应的编码
		for (auto i : pointerToLeaves) {
			std::cout << i.first << ' ';
			int * data = new int(MAX_ENCRYPTED_SIZE);
			int top = 0;
			auto p = i.second;
			while (p != root) {
				data[top++] = p->isRightChild();
				p = p->getFather();
			}
			std::reverse(data, data + top);
			for (int i = 0; i < top; ++i)
			std::cout << data[i];
			std::cout << std::endl;
			WPL += top * i.second->getFrequence();
		}
		std::cout << "WPL = " << WPL << std::endl;
		std::cout << "-----------------------------------" << std::endl;
	}

	class EncryptedString {
		//加密字符串
	public:
		int * data; int length;
		EncryptedString(int * _data, int _length) : data(_data), length(_length) {}
		void print() {
			for (int i = 0; i < length; ++i)
				std::cout << data[i];
			std::cout << std::endl;
		}
	};

	HuffmanTree(const char * string, int length) :_length(length) {
		_string = new char[length];
		strcpy(_string, string);
		/*构造Huffman树*/
		std::map<char, int> charSetFreq;
		std::priority_queue<TreeNode> pq;
		for (int i = 0; i < length; i++)
			charSetFreq[string[i]]++;
		for (auto itPair : charSetFreq)
			pq.push(TreeNode(itPair.first, itPair.second));
		

		while (pq.size() > 1) {
			TreeNode * head = new TreeNode(pq.top()); pq.pop();
			TreeNode * nodeAfterHead = new TreeNode(pq.top()); pq.pop();
			//对应字符与叶结点
			if (head->getChar() != 0) pointerToLeaves[head->getChar()] = head;
			if (nodeAfterHead->getChar() != 0) pointerToLeaves[nodeAfterHead->getChar()] = nodeAfterHead;
			
			pq.push(TreeNode(head, nodeAfterHead));
		}
		//树根
		root = new TreeNode(pq.top());
		//特判，保证单个节点有编码
		if (root->getChar() != 0) {
			pointerToLeaves[root->getChar()] = root;
			root = new TreeNode(root, root);
		}
	}

	EncryptedString encrypt()  {
		int * data = new int[MAX_ENCRYPTED_SIZE]; int top = 0;
		//自底向上加密字符串
		for (int i = _length - 1; i >= 0; i--) {
			TreeNode * pointer = pointerToLeaves[_string[i]];
			
			while (~(pointer->isRightChild())) {
				data[top++] = pointer->isRightChild();
				pointer = pointer->getFather();
			}
		}
		std::reverse(data, data + top);
		return EncryptedString(data, top);
	}

	char * decrypt(EncryptedString encryptedString) const {
		//解密 顺着给定的01串在树上寻找字符
		TreeNode * pointer = root;
		char * string = new char[MAX_STRING_SIZE]; int top = 0;
		for (int i = 0; i < encryptedString.length; i++) {
			if (pointer->getChar() != 0) {
				//是否叶子结点
				string[top++] = pointer->getChar();
				pointer = root;
			}
			pointer = pointer->getChild(encryptedString.data[i]);
		}
		if (pointer->getChar() != 0)
			string[top++] = pointer->getChar();
		string[top] = '\0';
		return string;
	}
};
