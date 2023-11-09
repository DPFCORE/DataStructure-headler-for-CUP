#pragma once
template<typename T>
struct TreeNode {
	T val;
	TreeNode* lchild;
	TreeNode* rchild;
	int ltag;
	int rtag;
	int frc;
	TreeNode(T data) :val(data), lchild(nullptr), rchild(nullptr),ltag(0),rtag(0),frc(0) {}
};

template<typename T>
struct Information_Ele {
	T data;
	int frc;
	bool used;
	Information_Ele(T data, int frc) :data(data), frc(frc),used(false) {};
	Information_Ele(int frc) :data('*'),frc(frc), used(false) {};
};





