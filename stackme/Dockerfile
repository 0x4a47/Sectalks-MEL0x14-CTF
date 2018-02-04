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

#disable ASLR to be nice.
#RUN echo 0 > /proc/sys/kernel/randomize_va_space
RUN sysctl kernel.randomize_va_space=0

#Create a new user & for the challenge
RUN groupadd --gid 995 sectalks-jan
RUN useradd -m --uid 995 --gid 995 pwn-stackme

#copy the current dir into the users dir
COPY . /home/pwn-stackme/

#change to the users directory
WORKDIR /home/pwn-stackme/
#DEBUG
#RUN ls -al

#compile the file without protections
RUN gcc -fno-stack-protector -z execstack -fno-pie -m32 -Wl,--section-start=.text=0x808a000 stackme.c -o stackme
RUN chmod +x start.sh
EXPOSE 8887:8887

#once compiled, change to that user
USER pwn-stackme

# run the file
#CMD ["bash"]
CMD ["./start.sh"]
