//
// Created by origin on 31.07.16.
//

#include "banMgr.h"
#include "nginxConfigReader.h"

#include <string>
#include <algorithm>
#include <smmintrin.h>


void BanMgr::banCmdWrapper(const char* ipBuf) {
    char cmdBuf[1024];
    sprintf(cmdBuf, Configuration::banCmd, owner->chainName.c_str(), ipBuf);
    cout << cmdBuf << endl;
    system(cmdBuf);

    queueProtector.lock();
    {
        unbanQueue.push(unbanRecord(time(0) + owner->banTime, string(ipBuf)));
    }
    queueProtector.unlock();
}

void BanMgr::unbanCmdWrapper(string& ip) {
    char cmdBuf[1024];
    sprintf(cmdBuf, Configuration::unbanCmd, owner->chainName.c_str(), ip.c_str());
    cout << cmdBuf << endl;
    system(cmdBuf);
}

void BanMgr::UnbanThrFunc() {
    while(true) {
        time_t curr_time = time(0);

        if(queueProtector.try_lock())
        {
            if(unbanQueue.empty())
                goto ex;
            {
                unbanRecord& frontRecord = unbanQueue.front();
                while(frontRecord.first < curr_time)
                {
                    unbanCmdWrapper(frontRecord.second);
                    owner->checkIpHashTable.Remove(frontRecord.second.c_str());
                    unbanQueue.pop();
                    if(unbanQueue.empty())
                        goto ex;
                }
            }
            ex:
            queueProtector.unlock();
        }
        sleep(1);
    }
}

void BanMgr::BanIp(const char* ipBuf) {
    banCmdWrapper(ipBuf);
}

void BanMgr::StartUnbanThr() {
    thread t(&BanMgr::UnbanThrFunc, this);
    t.detach();
}