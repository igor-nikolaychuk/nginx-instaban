//
// Created by root on 01.08.16.
//

#ifndef NGINX_INSTABAN_CHECKIPHASHTABLE_H
#define NGINX_INSTABAN_CHECKIPHASHTABLE_H

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "IpParser.h"
#include "BinaryOps.h"

#define ptrSize sizeof(int*)

class CheckIpHashTable {
    class ListNode{
    public:
        uint wholeIP;
        ListNode* next;
        ListNode(uint _wholeIP): wholeIP(_wholeIP), next(nullptr) { }
    };
    uint bitCount;
    uint ipBinaryMask;
    ListNode** dataPtr;
    size_t dataSize;
    size_t ptrCount;
public:
    CheckIpHashTable(uint _bitcount);
    bool TryToPush(const char* ip); //returns true if push was successful
    void Push(const char* ip);
    bool Check(const char* ip);
    void Remove(const char* ip);
};


#endif //NGINX_INSTABAN_CHECKIPHASHTABLE_H
