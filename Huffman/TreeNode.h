#pragma once
class TreeNode {
	char _char; int _freq;
	TreeNode * child[2];
	TreeNode * father;
public:
	TreeNode(char _c, int _f) : _char(_c), _freq(_f) {
		child[0] = child[1] = father = nullptr;
	}

	TreeNode(TreeNode * mergeA, TreeNode * mergeB) : _char(0), _freq(mergeA->_freq + mergeB->_freq) {
		mergeA->father = mergeB->father = this;
		child[0] = (mergeA), child[1] = (mergeB);
	}

	char getChar() const {
		return _char;
	}

	int getFrequence() const {
		return _freq;
	}

	TreeNode* getChild(bool isRight)  {
		return child[isRight];
	}

	TreeNode* getFather()  {
		return father;
	}

	int isRightChild()  {
		if (father == nullptr) return -1;
		return (this == father->child[1]);
	}

	bool operator < (const TreeNode & rhs) const {
		return _freq < rhs._freq;
	}

};