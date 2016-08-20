//
// Created by origin on 31.07.16.
//

#ifndef NGINX_INSTABAN_BANMGR_H
#define NGINX_INSTABAN_BANMGR_H

#include "stdio.h"
#include "cstring"
#include <cstdio>
#include <iostream>
#include <queue>
#include <ctime>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "strFuncs.h"

#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "CheckIpHashTable.h"

using namespace std;

class ConfigReader;
typedef pair<time_t, string> unbanRecord;

class BanMgr {
    ConfigReader* owner;
    mutex queueProtector;
    void banCmdWrapper(const char* logStringIpPtr);
    void unbanCmdWrapper(string& ip);
    void UnbanThrFunc();
    void StartUnbanThr();
public:
    queue<unbanRecord> unbanQueue;
    BanMgr(ConfigReader* _owner) : owner(_owner) {
        StartUnbanThr();
    }
    void BanIp(const char* logStringIpPtr);
};


#endif //NGINX_INSTABAN_BANMGR_H
