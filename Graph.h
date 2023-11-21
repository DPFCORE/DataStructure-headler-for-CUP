#pragma once
#include<vector>
template<typename T>
struct GraphNode {
	int adjvex;
	GraphNode* next;
	int weight;
	GraphNode(int v) :adjvex(v), next(nullptr), weight(0) {}
};


template<typename T>
struct SimpleGNode{ //Using vector not LinkList
	T v;
	int dis;
	Node(int x,int y):v(x),dis(y){}
};



/*
       parameters:
       n：      顶点个数
       s：      起点
       Adj：    图的邻接表
       vis：    标记顶点是否被访问
       d：      存储起点s到其他顶点的最短距离
*/
template<typename T>
void Dijkstra(int n, int s, std::vector<std::vector<SimpleGNode<T>>> Adj, std::vector<bool> vis, std::vector<int>& d)
{
	   fill(d.begin(), d.end(), INT_MAX);
       d[s] = 0;                                             
       for (int i = 0; i < n; ++i)
       {
              int u = -1;                                    
              int MIN = INT_MAX;                                 
              for (int j = 0; j < n; ++j)                  
              {
                     if (vis[j] == false && d[j] < MIN)
                     {
                           u = j;
                           MIN = d[j];
                     }
              }
              if (u == -1)
                     return;
              vis[u] = true;                              
              for (int j = 0; j < Adj[u].size(); ++j)
              {
                     int v = Adj[u][j].v;                   
                     if (vis[v] == false && d[v] > d[u] + Adj[u][j].dis)     
                           d[v] = d[u] + Adj[u][j].dis;      
              }
       }
}


template<typename T>
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