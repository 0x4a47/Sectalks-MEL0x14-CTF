#!/bin/bash
cd /root/sectalks-jan-binexp-ctf/babyecho/
docker-compose up -d
sleep 2
cd /root/sectalks-jan-binexp-ctf/ 

cd /root/sectalks-jan-binexp-ctf/stackme/
docker-compose up -d 
sleep 2
cd /root/sectalks-jan-binexp-ctf/

cd /root/sectalks-jan-binexp-ctf/nopnopnop/
docker-compose up -d
sleep 2
cd /root/sectalks-jan-binexp-ctf/

cd /root/sectalks-jan-binexp-ctf/legitbusiness/
docker-compose up -d
sleep 2
cd /root/sectalks-jan-binexp-ctf/

cd /root/sectalks-jan-binexp-ctf/simplywild/
docker-compose up -d 
sleep 2
cd /root/sectalks-jan-binexp-ctf/

docker ps --all
