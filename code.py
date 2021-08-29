import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
from ctypes import *


# create access to the shared memory
SHM_SIZE = 4096
SHM_KEY1 = 65528
SHM_KEY2 = 65529

try:
	rt = CDLL('librt.so')
except:
	rt = CDLL('librt.so.1')

shmget = rt.shmget
shmget.argtypes = [c_int, c_size_t, c_int]
shmget.restype = c_int
shmat = rt.shmat
shmat.argtypes = [c_int, POINTER(c_void_p), c_int]
shmat.restype = c_void_p

shmid1 = shmget(SHM_KEY1, SHM_SIZE, 0o666)
shmid2 = shmget(SHM_KEY2, SHM_SIZE, 0o666)

if shmid1 < 0 or shmid2 < 0:
	print ("System not infected")
else: 
	a = shmat(shmid1, None, 0)
	b = shmat(shmid2, None, 0)

# obtain the string and decode it

x = string_at(a)
y = string_at(b)

a = [int(z) for z in x.split(b'a')]
b = [int(z) for z in y.split(b'a')]
# y = int(x)

print("This is in python",a)
print("This is in python",b)
# print(type(a))
# plt.plot(a,b)
# plt.show()


# Use the values to create an animated plot
fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

xar = []
yar = []

def animate(i):
    xar.append(a[i])
    yar.append(b[i])
    ax1.plot(xar,yar)

ani = animation.FuncAnimation(fig, animate, interval=100)
plt.show()

