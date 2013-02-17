import serial
import time

ser = serial.Serial('/dev/tty.usbmodem1d11', 9600)

t = {
    ((0,0),'r') : (1,0)
  , ((0,0),'s') : (0,1)
  , ((0,1),'r') : (1,1)
  , ((0,1),'S') : (0,0)
  , ((1,0),'R') : (0,0)
  , ((1,0),'s') : (1,1)
  , ((1,1),'R') : (0,1)
  , ((1,1),'S') : (1,0)

  , ((0,0),'R') : (0,0)
  , ((0,0),'S') : (0,0)
  , ((0,1),'R') : (0,1)
  , ((0,1),'s') : (0,1)
  , ((1,0),'r') : (1,0)
  , ((1,0),'S') : (1,0)
  , ((1,1),'r') : (1,1)
  , ((1,1),'s') : (1,1)
}

a = {
    ((0,0),(0,0)) : [           ]
  , ((0,0),(0,1)) : [        'C']
  , ((0,0),(1,0)) : ['A','B'    ] 
  , ((0,0),(1,1)) : ['A','B','C']
  , ((0,1),(0,0)) : [        'c'] 
  , ((0,1),(0,1)) : [           ]
  , ((0,1),(1,0)) : ['A','B','c']
  , ((0,1),(1,1)) : ['A','B'    ] 
  , ((1,0),(0,0)) : ['a','b'    ] 
  , ((1,0),(0,1)) : ['a','b','C'] 
  , ((1,0),(1,0)) : [           ]
  , ((1,0),(1,1)) : [        'C'] 
  , ((1,1),(0,0)) : ['a','b','c'] 
  , ((1,1),(0,1)) : ['a','b'    ] 
  , ((1,1),(1,0)) : [        'c'] 
  , ((1,1),(1,1)) : [           ]
}

c = (0,0)

def available():
    return ser.inWaiting() > 0

def act():
    global c
    b = read()
    print b
    if b == '.': return
    if b == '*': return
    c = transition(c, b)
    print c

def transition(c, b):
    nc = t[(c,b)]
    doors(a[(c,nc)])
    return nc

def doors(ds):
    for d in ds:
        write(d)

def read():
    return ser.read()

def write(b):
    ser.write(b)

while available(): read()
while True:
    if available():
      act()
