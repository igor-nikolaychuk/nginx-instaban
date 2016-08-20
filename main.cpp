#include <iostream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <zconf.h>
#include <libconfig.h++>

#include "nginxConfigReader.h"
#include "IpParser.h"
#include "IpHashTableGeneric.h"
#include "BanRecord.h"
#include "BinaryOps.h"
#include "Configuration.h"
#include "strFuncs.h"

#define cfgFilePath "/etc/nginx-instaban.conf"

using namespace libconfig;
using namespace std;

BanMgr* banMgr = nullptr;

int main() {
    Config cfg;
    try
    {
        cfg.readFile(cfgFilePath);
    }
    catch(const FileIOException &fioex)
    {
        std::cerr << "I/O error while reading file." << std::endl;
        return(EXIT_FAILURE);
    }
    catch(const ParseException &pex)
    {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
        << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }

    try
    {
        Configuration::myLogPath = cfg.lookup("instabanLogPath");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "No 'instabanLogPath' setting in configuration file." << endl;
    }

    try
    {
        Configuration::chainAddCmd = cfg.lookup("commands.chainAddCmd");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "No 'commands.chainAddCmd' setting in configuration file." << endl;
    }

    try
    {
        Configuration::banCmd = cfg.lookup("commands.banCmd");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "No 'commands.banCmd' setting in configuration file." << endl;
    }

    try
    {
        Configuration::unbanCmd = cfg.lookup("commands.unbanCmd");
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "No 'commands.unbanCmd' setting in configuration file." << endl;
    }

    try
    {
        Setting& logReaders = cfg.lookup("nginxLogReaders");
        int count = logReaders.getLength();
        for(int i = 0; i < count; ++i)
        {
            const Setting &logReader = logReaders[i];
            const char* logPath;
            int banTime;
            int bitCount;
            const char* chainName;

            logReader.lookupValue("nginxLogPath", logPath);
            logReader.lookupValue("banTime", banTime);
            logReader.lookupValue("chainName", chainName);
            logReader.lookupValue("valuableBitCount", bitCount);

            new ConfigReader(logPath, banTime, chainName, bitCount);
        }
    }
    catch(const SettingNotFoundException &nfex)
    {
        cerr << "Can't read 'nginxLogReaders' setting in configuration file." << endl;
    }

    cout << "Working!" << endl;
    while(true)
        sleep(INT_MAX);
    return 0;
}