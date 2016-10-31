# nginx-instaban
Efficient ddos protection daemon for nginx

#How does it work?

The service reads nginx error log file/files and ban every ip which is blocked by nginx for a certain time using iptables. The software is optimized for nginx logs and works without use of regular expressions for parsing. It allows you to survive a real ddos attack almost without load generation in comparison with fail2ban.

#How to use:

1) build & install 
```
depends on libconfig++, use "sudo apt-get install libconfig++-dev" on debian based distro to install
```

```
cmake .
make
chmod +x install
sudo .install
```

3) configure nginx as shown in example.nginx.conf

4) configure nginx-instaban: 
```
sudo nano /etc/nginx-instaban.conf
```

5) start the service:
```
service nginx-instaban start
```

To start the daemon at startup:
```
update-rc.d nginx-instaban defaults
```
To remove:
```
update-rc.d -f nginx-instaban remove
```
To read the log file:
```
cat /var/log/nginx-instaban.log
```


To unistall:
```
chmod +x uninstall
sudo .uninstall
```

#Configuration example
```
nginxLogReaders = (
                 {
                     nginxLogPath = "/var/log/nginx/error.log"; #path to the error log file
                     banTime = 20; #20 seconds
                     chainName = "nginx-instaban"; #name of the chain in iptables -L
                     valuableBitCount = 21; #number of bits of ip address which is used as an offset inside
                                            #hashtable structure. The higher the value the larger hashtable
                                            #structure is. 20bit = 4mb, 21bit = 8 mb, 22bit = 16 mb...
                 }
#                ,
#                {
#                    nginxLogPath = "/var/log/nginx/access.log";
#                    banTime = "20";
#                    chainName = "nginx-instaban";
#                }
#                    ...
             );

commands: {
    chainAddCmd = "iptables -N %s && iptables -t filter -A INPUT -j %s"; # %%s => chainName, chainName
    banCmd = "iptables -A %s -s %s -p tcp --destination-port 80 -j DROP"; # %%s => chainName, host
    unbanCmd = "iptables -D %s -s %s -p tcp --destination-port 80 -j DROP"; # %%s => chainName, host
}
```
#Nginx configuratio example:
```
user www-data;
worker_processes 1;
pid /run/nginx.pid;

events {
        worker_connections 768;
        # multi_accept on;
}

http {
        access_log /var/log/nginx/access.log;
        error_log /var/log/nginx/error.log;
        gzip on;

        limit_conn_zone $binary_remote_addr zone=addr:10m;
        limit_req_zone $binary_remote_addr zone=one:10m rate=10r/s;
	
	server 
  {
          location / {
              limit_conn addr 1;
              limit_req zone=one burst=5;
	        }
  }
}
```
