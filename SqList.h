#pragma once
#include<iostream>

struct DListNode {
	int val;
	DListNode* next;
	DListNode* prev;
	DListNode(int val) :val(val), next(NULL), prev(NULL) {}
};

void DPushBack(DListNode*& head,int val) {
	if (head == NULL) {
		head = new DListNode(val);
		head->next = head;
		head->prev = head;
	}
	else {
		DListNode* cur = head->prev;
		DListNode* newNode = new DListNode(val);
		newNode->next = head;
		cur->next = newNode;
		newNode->prev = cur;
		head->prev = newNode;
	}
}

void D_PrintList(DListNode* head) {
	DListNode* cur = head;
	std::cout << cur->val << " ";
	cur = cur->next;
	while (cur!=head) {
		std::cout << cur->val << " ";
		cur = cur->next;
	}
}

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* reverseList(ListNode* head){
    if(head == NULL){
        return NULL;
    }
    if(head->next == NULL){
        return head;
    }
    ListNode* cur = head;
    ListNode* prev = NULL;
    while(cur){
        ListNode* tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    return prev;
}

void PushBack(ListNode** head,int data){
    ListNode* newNode = new ListNode(data);
    if(*head == NULL){
        *head = newNode;
    }  
    else{
        ListNode* cur = *head;
        while(cur->next){
            cur = cur->next;
        }
        cur->next = newNode;
    }  
 }

void ShowList(ListNode* head){
    ListNode* cur = head;
    while(cur){
        std::cout<<cur->val<<" ";
        cur = cur->next;
    }
    std::cout<<'\n';
}

void PushFront(ListNode** head,int data){
    ListNode* newNode = new ListNode(data);
    if(head == NULL){
        *head = newNode;
    }
    else{
        newNode->next = *head;
        *head = newNode;
    }
}

