#ifndef NGINX_INSTABAN_IPHASHTABLE_H
#define NGINX_INSTABAN_IPHASHTABLE_H

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "IpParser.h"
#include "BinaryOps.h"
#include "BanRecord.h"

using namespace std;

#define ptrSize sizeof(int*)

template<class T>
class IpHashTableGeneric {
    class ListNode {
    public:
        T data;
        uint wholeIP;
        ListNode* next;
        ListNode(T&& _data, uint _wholeIP): wholeIP(_wholeIP), next(nullptr), data(move(_data)) {
        }
    };
    uint bitCount;
    uint ipBinaryMask;
    ListNode** dataPtr;
    size_t dataSize;
    size_t ptrCount;
public:
    IpHashTableGeneric(uint _bitcount) : bitCount(_bitcount) {
        ptrCount = pow(2, bitCount);
        dataSize =  ptrSize * ptrCount;
        dataPtr = (ListNode**)malloc(dataSize);
        memset((void*)dataPtr, 0, dataSize);
        ipBinaryMask = createMask(0, bitCount-1);
    }

    void Push(const char* ip, T&& value);
    bool Check(const char* ip);
    void Remove(const char* ip);
};


#endif //NGINX_INSTABAN_IPHASHTABLE_H