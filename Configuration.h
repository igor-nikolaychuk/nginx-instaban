//
// Created by root on 01.08.16.
//

#ifndef NGINX_INSTABAN_CONFIGURATION_H
#define NGINX_INSTABAN_CONFIGURATION_H


class Configuration {
public:
    static const char *myLogPath;
    static const char *chainAddCmd;
    static const char *banCmd;
    static const char *unbanCmd;
};


#endif //NGINX_INSTABAN_CONFIGURATION_H
