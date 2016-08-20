#ifndef NGINX_INSTABAN_CONFIGREADER_H_H
#define NGINX_INSTABAN_CONFIGREADER_H_H

#include <iostream>
#include <fstream>
#include <time.h>
#include <zconf.h>
#include <thread>

#include "strFuncs.h"
#include "banMgr.h"
#include "CheckIpHashTable.h"
#include "Configuration.h"


class BanMgr;

class ConfigReader {
    string logFile;
    BanMgr* banMgr;
    void nginxConfigReadFunc();
public:
    int banTime;
    string chainName;
    CheckIpHashTable checkIpHashTable;
    ConfigReader(const char *logFile, int banTime, const char* _chainName, uint bitCount);
};

#endif //NGINX_INSTABAN_CONFIGREADER_H_H
