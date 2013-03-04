import serial
from datetime import datetime
import time
import uuid
import os

ser = serial.Serial('/dev/tty.gomb', 9600)

snap = "false && ssh snap window.sh {0} &"

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

m = {
    '*' : "controller restart"
  , 'R' : "outer trip"
  , 'r' : "outer quiet"
  , 'S' : "inner trip"
  , 's' : "inner quiet"
}

c = (0,0)

def available():
    return ser.inWaiting() > 0

def act():
    global c
    b = read()
    record(b)
    if b == '.': return
    if b == '*': return
    c = transition(c, b)

def transition(c, b):
    nc = t[(c,b)]
    doors(a[(c,nc)])
    return nc

def record(b):
    if b == '.': return
    i = ident()
    log(m[b], i)
    camera(i)

def doors(ds):
    for d in ds:
        write(d)

def read():
    return ser.read()

def write(b):
    ser.write(b)

# { CAMERA
def camera(i):
    os.system(snap.format(i))
# CAMERA }

# { UUID
def ident():
    return str(uuid.uuid4())[0:8]
# UUID }
# { LOGGING
def log(s, i):
    print msg(s, i)

def msg(s, i):
  return stamp() + " [" + i + "] gomb: " + s

def stamp():
  now = datetime.now()
  return now.strftime("%b %d %H:%M:%S")

def now():
  return datetime.now()
# LOGGING }

while available(): read()
while True:
    if available():
      act()
    sleep(0.1)
