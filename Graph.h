#pragma once
#include<vector>
template<typename T>
struct GraphNode {//边节点
	int adjvex;
	GraphNode* next;
	int weight;
	GraphNode(int v) :adjvex(v), next(nullptr), weight(0) {}
};





template<typename T>//图的点节点
struct VNode{
	GraphNode<T>* head;
	T data;
	VNode(T val) :data(val), head(nullptr) {}
};





template<typename T>
class GPool {
public:
	std::vector<VNode<T>> Vlist;
	void append(std::pair<T,T> nums);
	int find(T val);
	void DFSNode(std::vector<T>& result, int cur,std::vector<bool>&used);
};








template<typename T>
int GPool<T>::find(T val) {
	for (int i = 0; i < this->Vlist.size(); i++) {
		if (this->Vlist[i].data == val) {
			return i;
		}
	}
	return -1;
}

template<typename T>
void GPool<T>::DFSNode(std::vector<T>& result, int cur, std::vector<bool>& used) {
	result.push_back(this->Vlist[cur].data);
	if (result.size() == this->Vlist.size()) {
		return;
	}
	if (!this->Vlist[cur].head) {
		return;
	}
	for (GraphNode<T>* n = this->Vlist[cur].head; n != nullptr; n = n->next) {
		if (used[n->adjvex] == false) {
			used[n->adjvex] = true;
			DFSNode(result, n->adjvex, used);
		}
		else {
			continue;
		}
	}
}

template<typename T>
void GPool<T>::append(std::pair<T, T> nums) {
	int pos = this->find(nums.first);
	int pos2 = this->find(nums.second);
	if (pos == -1) {
		this->Vlist.push_back(VNode<T>(nums.first));
		pos = this->Vlist.size() - 1;
	}
	if (pos2 == -1) {
		this->Vlist.push_back(VNode<T>(nums.second));
		pos2 = this->Vlist.size() - 1;
	}
	if (this->Vlist[pos].head) {
		GraphNode<T>* cur = this->Vlist[pos].head;
		while (cur->next) {
			cur = cur->next;
		}
		cur->next = new GraphNode<T>(pos2);
	}
	else {
		this->Vlist[pos].head = new GraphNode<T>(pos2);
	}
}