#Sectalks CTF Pwn docker image.
# Pull base image.
FROM ubuntu:16.04

# Set environment variables.
ENV HOME /root
RUN id
#install gcc
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y g++-multilib
RUN apt-get install -y socat
RUN apt-get install -y gdb
#disable ASLR to be nice.
#RUN echo 0 > /proc/sys/kernel/randomize_va_space
RUN sysctl kernel.randomize_va_space=0

#Create a new user & for the challenge
RUN groupadd --gid 995 sectalks-jan
RUN useradd -m --uid 995 --gid 995 pwn-nopnopnop

#copy the current dir into the users dir
COPY . /home/pwn-nopnopnop/

#change to the users directory
WORKDIR /home/pwn-nopnopnop/
#DEBUG
#RUN ls -al

#compile the file without protections
RUN gcc -fno-stack-protector -fno-pie -m32 -Wl,--section-start=.text=0x808a000 nopnopnop.c -o nopnopnop -ldl
RUN chmod +x start.sh
EXPOSE 8889:8889

#once compiled, change to that user
USER pwn-nopnopnop

# run the file
#CMD ["bash"]
CMD ["./start.sh"]
