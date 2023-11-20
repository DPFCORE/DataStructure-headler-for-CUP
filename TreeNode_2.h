#pragma once
#include<iostream>
#include<vector>
using namespace std;
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

template<typename T>
class TreadFunc{
TreeNode<T>* prev = nullptr;
	void InOrderTread(TreeNode<T>*& root) {
		if (root == nullptr)
			return;
		if (root->ltag == 0) {
			InOrderTread(root->lchild);
		}
		if (root->lchild == nullptr) {
			root->lchild = prev;
			root->ltag = 1;
		}
		if (prev && prev->rchild == nullptr) {
			prev->rchild = root;
			root->ltag = 1;
		}
		prev = root;
		if (root->rtag == 0) {
			InOrderTread(root->rchild);
		}
	}
};


class MyTreeFunc {
public:
	void PreOrderContru(TreeNode<char>*& root,string &s) {//扩展二叉树中序建树
		if (s.empty())
			return;
		char val = *s.begin();
		s.erase(s.begin());
		if (val!='#') {
			root = new TreeNode<char>(val);
		}
		else {
			root = NULL;
			return;
		}
		PreOrderContru(root->lchild,s);
		PreOrderContru(root->rchild,s);
	}
	template<typename T>
	void InOrderTrans(TreeNode<T>* root) {
		if (root == NULL) {
			cout << '#' << " ";
			return;
		}
		InOrderTrans<T>(root->lchild);
		cout << root->val << " ";
		InOrderTrans<T>(root->rchild);
	}
	template<typename T>
	void InOrderTranverseStack(TreeNode<T>* root) {//非递归中序遍历
		stack<TreeNode<T>*> st;
		TreeNode<T>* cur = root;
		while (cur||!st.empty()) {
			if (cur) {
				st.push(cur);
				cur = cur->lchild;
			}
			else {
				cur = st.top();
				st.pop();
				cout << cur->val;
				cur = cur->rchild;
			}
		}
	}
	template<typename T>
	void Level_Tranverse(TreeNode<T>* root) {//层序遍历
		queue<TreeNode<T>*> qu;
		TreeNode<T>* cur = root;
		qu.push(cur);
		while (!qu.empty()) {
			cur = qu.front();
			qu.pop();
			cout << cur->val;
			if (cur->lchild) {
				qu.push(cur->lchild);
			}
			if (cur->rchild) {
				qu.push(cur->rchild);
			}
		}
	}

	TreeNode<char>* prev = NULL;
	void InOrder_Treading(TreeNode<char>* root) {//中序线索化
		if (!root) {
			return;
		}
		InOrder_Treading(root->lchild);
		if (root->lchild == NULL) {
			root->lchild = prev;
			root->ltag = 1;
		}
		if (prev&&prev->rchild == NULL) {
			prev->rchild = root;
			prev->rtag = 1;
		}
		prev = root;
		InOrder_Treading(root->rchild);
	}
	
	//哈夫曼找最小
	template<typename T>
	pair<TreeNode<Information_Ele<T>>*, TreeNode<Information_Ele<T>>*> FindTwoMin(vector<TreeNode<Information_Ele<T>>*>&nums) {
		int Min = INT_MAX;
		pair<TreeNode<Information_Ele<T>>*, TreeNode<Information_Ele<T>>*> result;
		TreeNode<Information_Ele<T>>* temp = NULL;
		int rec = 0;
		for (int i = 0;i<nums.size();i++) {
			if (nums[i]->val.used == true) {
				continue;
			}
			if (nums[i]->val.frc<Min) {
				Min = nums[i]->val.frc;
				temp = nums[i];
				rec = i;
			}
		}
		result.first = temp;
		nums[rec]->val.used = true;
		Min = INT_MAX;
		for (int i = 0; i < nums.size(); i++) {
			if (nums[i]->val.used == true) {
				continue;
			}
			if (nums[i]->val.frc < Min) {
				Min = nums[i]->val.frc;
				temp = nums[i];
				rec = i;
			}
		}
		result.second = temp;
		nums[rec]->val.used = true;
		return result;
	}

	template<typename T>
	int Fnums(vector<TreeNode<Information_Ele<T>>*> nums) {
		int cnt = 0;
		for (int i = 0;i<nums.size();i++) {
			if (!nums[i]->val.used) {
				cnt++;
			}
		}
		return cnt;
	}
	//哈夫曼建树
	template<typename T>
	TreeNode<Information_Ele<T>>* Huffuman(vector<TreeNode<Information_Ele<T>>*> nums) {
		int cnt = 0;
		while (Fnums<T>(nums) != 1 && Fnums<T>(nums) != 0) {
			pair<TreeNode<Information_Ele<T>>*, TreeNode<Information_Ele<T>>*> MinPair = FindTwoMin<T>(nums);
			TreeNode<Information_Ele<T>>* t1 = MinPair.first;
			TreeNode<Information_Ele<T>>* t2 = MinPair.second;
			TreeNode<Information_Ele<T>>* subroot = new TreeNode<Information_Ele<T>>(Information_Ele<T>(MinPair.first->val.frc + MinPair.second->val.frc));
			subroot->lchild = t1;
			subroot->rchild = t2;
			nums.push_back(subroot);
			cout << Fnums(nums) << endl;
		}
		for (int i = 0; i < nums.size(); i++) {
			if (!nums[i]->val.used) {
				return nums[i];
			}
		}
		return nums[0];
	}

	//求huffman编码
	template<typename T>
	void HuffmanCode(TreeNode<Information_Ele<T>>* &root, string path, vector<pair<T, string>>& result) {
		if (!root->lchild && !root->rchild) {
			result.push_back({ root->val.data,path });
			return;
		}
		if (root->lchild) {
			path += '0';
			HuffmanCode<T>(root->lchild, path, result);
			path.pop_back();
		}
		if (root->rchild) {
			path += '1';
			HuffmanCode<T>(root->rchild, path, result);
			path.pop_back();
		}
	}
	//将数据转变为树节点
	template<typename T>
	vector<TreeNode<Information_Ele<T>>*> TransformToTreeNode(vector<Information_Ele<T>>& nums) {
		vector<TreeNode<Information_Ele<T>>*> result;
		for (int i = 0; i < nums.size(); i++) {
			TreeNode<Information_Ele<T>>* NewNode = new TreeNode<Information_Ele<T>>(nums[i]);
			result.push_back(NewNode);
		}
		return result;
	}




	//-------打印树---------

	template<typename T>
	int Height(TreeNode<T>* root) {
		if (root == NULL)
			return 0;
		return max(Height(root->rchild), Height(root->lchild)) + 1;
	}
	template<typename T>
	void PrintTree(vector<vector<char>>& Container, TreeNode<T>* root, int h, int& seq,int height) {
		if (root == NULL)
			return;
		PrintTree(Container, root->rchild, h + 1, seq,height);
		if (root->val.data!=' ') {
			Container[seq + 2][h * 3+1] = root->val.data;
		}
		else {
			Container[seq + 2][h * 3+1] = '*';
		}
		Container[seq+1][h * 3+2] = '---';
		Container[seq][h*3+0] = '|';
		seq++;
		PrintTree(Container, root->lchild, h + 1, seq,height);
	}

	int height;
	int width;

	void fillArray(TreeNode<Information_Ele<char>>* T, char* a, int i, int j)
	{
		int ti=0, tj=0;
		if (T) 
		{
			*(a + (i * width) + j) = T->val.data; 
			if (T->lchild) 
			{
				for (ti = i + 1, tj = j - 1; tj > j - (height - i + 1) / 2; tj--)
				{
					*(a + ((ti)*width) + tj) = -1;
					ti++;
				}
			}
			if (T->rchild)
			{
				for (ti = i + 1, tj = j + 1; tj < j + (height - i + 1) / 2; tj++)
				{
					*(a + ((ti)*width) + tj) = 1;
					ti++;
				}
			}
			fillArray(T->lchild, a, ti, j - (height - i + 1) / 2);
			fillArray(T->rchild, a, ti, j + (height - i + 1) / 2);
		}
	}
	void printBiTree(TreeNode<Information_Ele<char>>* T)
	{
		int i, j;
		int n = Height(T); 
		width = (2 << n) - 3; 
		height = (2 << (n - 1)) - 1; 
		char* a = (char*)malloc(sizeof(char) * (width * height)); 
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				*(a + (i * width) + j) = 0;
			}
		}
		fillArray(T, a, 0, (width - 1) / 2);
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (*(a + (i * width) + j) == -1)
				{
					printf("/");
				}
				else if (*(a + (i * width) + j) == 1)
				{
					printf("\\");
				}
				else if (*(a + (i * width) + j) == 0)
				{
					printf(" ");
				}
				else
				{
					printf("%c", *(a + (i * width) + j));
				}
			}
			printf("\n");
		}
	}
};
