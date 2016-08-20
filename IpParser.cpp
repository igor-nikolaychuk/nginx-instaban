#include "IpParser.h"

u_int ParseIp(const char *p) {
    u_int dwIP=0,dwIP_Part=0;
    while(true)
    {
        if(p[0] == 0)
        {
            dwIP = (dwIP << 8) | dwIP_Part;
            break;
        }
        if(p[0]=='.')
        {
            dwIP = (dwIP << 8) | dwIP_Part;
            dwIP_Part = 0;
            p++;
        }
        dwIP_Part = (dwIP_Part*10)+(p[0]-'0');
        p++;
    }
    return dwIP;
}
