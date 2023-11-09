#pragma once
#include<iostream>

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

