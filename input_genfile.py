# python3 input_genfile.py 10 15 10 > input.txt
import sys
from random import randint,seed
N = int(sys.argv[1])
print(N)
E = int(sys.argv[2])
W = int(sys.argv[3])
seed(5)
s = []
for i in range(E):
	u=randint(0,N-1)
	v=randint(0,N-1)
	while(u==v or (u,v) in s or (v,u) in s):
		u=randint(0,N-1)
		v=randint(0,N-1)
	
	s.extend([(u,v),(v,u)])
s.sort()
for i in s:
	w = randint(1,W)
	print(i[0],i[1],w)