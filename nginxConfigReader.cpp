#include "nginxConfigReader.h"

void ConfigReader::nginxConfigReadFunc() {
    std::ifstream ifs(logFile);
    if (ifs.is_open())
    {
        ifs.seekg(-1,ios_base::end);
        std::string line;
        const char* strToFind_limreq = "limiting requests";
        const char* strToFind_client = "client:";
        while (true)
        {
            while (std::getline(ifs, line))
            {
                const char* result = nullptr;
                char* cmdCheckResult = strMatch((char *) line.c_str(), (char *) strToFind_limreq);
                if(cmdCheckResult != nullptr)
                {
                    result = strMatch(cmdCheckResult, (char *) strToFind_client);
                    if(result != nullptr)
                    {
                        ++result;
                        char buf[256];
                        memcpy(buf, result, 20);
                        *findChar(buf, ',') = '\0';
                        if(checkIpHashTable.TryToPush(buf))
                            banMgr->BanIp(buf);
                    }
                }
            }
            if (!ifs.eof()) break;
            ifs.clear();
            usleep(100000);
        }
    }
}

ConfigReader::ConfigReader(const char *_logFile, int _banTime, const char* _chainName, uint bitCount)
        : checkIpHashTable(bitCount), chainName(_chainName), logFile(_logFile), banTime(_banTime) {
    banMgr = new BanMgr(this);
    char* cmd = (char*)malloc(1024);
    sprintf(cmd, Configuration::chainAddCmd, chainName.c_str(), chainName.c_str());
    system(cmd);
    free(cmd);

    thread thr(&ConfigReader::nginxConfigReadFunc, this);
    thr.detach();
}