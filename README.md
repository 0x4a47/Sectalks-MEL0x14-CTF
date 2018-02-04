# Sectalks MEL0x14 - Intro to Memory Corruption 
## Ramblings
This repo contains all of the files associated with my ctf used at Sectalks MEL0x14. I have included all the socat scripts, docker containers, docker-compose scripts and a couple of little automater scripts. The aim is to show a little bit more about how dockerizing a CTF works on a very small-scale! 

## How2play
In order to play on your own machine:
1. build each docker image with:
    ```
    docker build -t stackme:0.1 stackme/
    docker build -t babyecho:0.1 babyecho/
    docker build -t nopnopnop:0.1 nopnopnop/
    docker build -t legitbusiness:0.1 legitbusiness/
    docker build -t stackme:0.1 stackme/
    ```
2. check they have all built correctly with `docker images`. 
3. now, either use the `start.sh` script to start the socat wrapper on your own machine and begin playing; or
4. enter each challenge folder and use `docker-compose -d` to spin up the docker container as a daemon and play from there.

I recommend using the socat wrapper on a VPS or local VM as it's the best way to practise remotely exploiting CTF binaries! 

## Final Note!!!!!
 The code in each challenge is deliberately vulnerable and bad things can happen if exposed incorrectly. Please take measures to limit the risk on your machine by placing it in a VM or on a VPS. I am not liable if bad things happen on your machine as a result :(