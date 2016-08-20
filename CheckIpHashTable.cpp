//
// Created by root on 01.08.16.
//

#include "CheckIpHashTable.h"


CheckIpHashTable::CheckIpHashTable(uint _bitcount) : bitCount(_bitcount) {
    ptrCount = (size_t) pow(2, bitCount);
    dataSize =  ptrSize * ptrCount;
    dataPtr = (ListNode**)malloc(dataSize);
    memset((void*)dataPtr, 0, dataSize);
    ipBinaryMask = createMask(0, bitCount-1);
}

void CheckIpHashTable::Push(const char* ip) {
    uint wholeIp = ParseIp(ip);
    uint offset =  wholeIp & ipBinaryMask;
    ListNode** myPtr = dataPtr + offset;
    if(*myPtr == 0) {
        *myPtr = new ListNode(wholeIp);
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
        currNode->next = new ListNode(wholeIp);
    }
}

bool CheckIpHashTable::Check(const char* ip) {
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

void CheckIpHashTable::Remove(const char* ip) {
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

bool CheckIpHashTable::TryToPush(const char *ip) {
    uint wholeIp = ParseIp(ip);
    uint offset =  wholeIp & ipBinaryMask;
    ListNode** myPtr = dataPtr + offset;
    if(*myPtr == 0) {
        *myPtr = new ListNode(wholeIp);
    }
    else {
        ListNode* currNode = *myPtr;
        while(currNode->next != nullptr) {
            if(currNode->wholeIP == wholeIp)
                return false; //ip is already exist
            currNode = currNode->next;
        }
        if(currNode->wholeIP == wholeIp)
            return false; //ip is already exist
        currNode->next = new ListNode(wholeIp);
    }
    return true;
}
