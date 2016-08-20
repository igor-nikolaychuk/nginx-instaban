//
// Created by root on 31.07.16.
//

#include "IpHashTableGeneric.h"

template <class T>
void IpHashTableGeneric<T>::Push(const char* ip, T&& value) {
    uint wholeIp = ParseIp(ip);
    uint offset =  wholeIp & ipBinaryMask;
    ListNode** myPtr = dataPtr + offset;
    if(*myPtr == 0) {
        *myPtr = new ListNode(move(value), wholeIp);
    }
    else {
        ListNode* currNode = *myPtr;
        while(currNode->next != nullptr) {
            if(currNode->wholeIP == wholeIp)
                return;
            currNode = currNode->next;
        }
        if(currNode->wholeIP == wholeIp)
            return;
        currNode->next = new ListNode(move(value), wholeIp);
    }
}

template <class T>
bool IpHashTableGeneric<T>::Check(const char* ip) {
    uint wholeIp = ParseIp(ip);
    uint offset =  wholeIp & ipBinaryMask;
    ListNode** myPtr = dataPtr + offset;
    if(*myPtr == 0) {
        return false;
    }
    else {
        ListNode* currNode = *myPtr;
        do {
            if(currNode->wholeIP == wholeIp)
                return true;
            currNode = currNode->next;
        } while (currNode != nullptr);
    }
    return false;
}

template <class T>
void IpHashTableGeneric<T>::Remove(const char* ip) {
    uint wholeIp = ParseIp(ip);
    uint offset =  wholeIp & ipBinaryMask;
    ListNode** myPtr = dataPtr + offset;
    ListNode* currNode = *myPtr;
    if(currNode == 0)
        return;
    if(currNode->wholeIP == wholeIp)
    {
        *myPtr = currNode->next;
        delete currNode;
    }
    else {
        ListNode* nextNode = currNode->next;
        if(nextNode == nullptr)
            return;
        do {
            if(nextNode->wholeIP == wholeIp)
            {
                currNode->next = nextNode->next;
                delete nextNode;
            }
            currNode = currNode->next;
            nextNode = nextNode->next;
        } while(nextNode != nullptr);
    }
}