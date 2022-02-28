import time
import numpy as np

Arg1 = "a6_123"
wierdVal = 0xcbf29ce484222325
hexf 	 = 0xffffffffffffffff
hexf2 	 = 0x10000000000000000
i = 0
while (i != len(Arg1)):
	wierdVal *= 0x100000001b3
	wierdVal = wierdVal%hexf2
	onething = wierdVal & 0xFF
	wierdVal -= onething
	wierdVal += onething ^ ord(Arg1[i])
	i += 1

print(hex(wierdVal&0xffffffff))
#jeg skal lave sådan så det er en 64 bit værdi