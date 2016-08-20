#ifndef NGINX_INSTABAN_BANRECORD_H
#define NGINX_INSTABAN_BANRECORD_H

#include <string>
using namespace std;

class BanRecord {
public:
    string ip;
    BanRecord(const string &ip) : ip(ip) { }

    BanRecord(const BanRecord& br) {
        ip = br.ip;
    }

    BanRecord& operator=(const BanRecord& br) {
        ip = br.ip;
    }

    BanRecord(BanRecord&& br) noexcept {
        ip = move(br.ip);
    }

    BanRecord& operator=(BanRecord&& br) noexcept {
        ip = move(br.ip);
    }
};

#endif //NGINX_INSTABAN_BANRECORD_H
