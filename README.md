# nginx-instaban
Efficient ddos protection daemon for nginx

#How does it work?

The service reads nginx error log file/files and ban every ip which is blocked by nginx for a certain time using iptables. The software is optimized for nginx logs and works without use of regular expressions for parsing. It allows you to survive a real ddos attack almost without load generation in comparison with fail2ban.

#How to use:

1) build & install //depends on libconfig++, use "sudo apt-get install libconfig++-dev" on debian based distro to install

cmake .
make
chmod +x install
sudo .install


3) configure nginx as shown in example.nginx.conf

4) configure nginx-instaban: 
sudo nano /etc/nginx-instaban.conf

5) start the service:
service nginx-instaban start

*) 
- to start the daemon at startup:
update-rc.d nginx-instaban defaults
- to remove:
update-rc.d -f nginx-instaban remove

*) to read the log file:
cat /var/log/nginx-instaban.log

*) to unistall:
chmod +x uninstall
sudo .uninstall
