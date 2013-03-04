import serial
from datetime import datetime
import time
import uuid
import os

ser = serial.Serial('/dev/tty.gomb', 9600)

snap = "false && ssh snap window.sh {0} &"
tod = "undefined"

dawn = 0520
dusk = 1830
spy = "on"

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

  , ((0,0),'.') : (0,0)
  , ((0,1),'.') : (0,1)
  , ((1,0),'.') : (1,0)
  , ((1,1),'.') : (1,1)
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
  checks()
  if b == '*': return
  c = transition(c, b)

def record(b):
  if b == '.': return
  i = ident()
  log(m[b], i)
  camera(i)

def checks():
  t = timeofday()
  print "T="+t
  print "tod="+tod
  if (t != tod):
    settimeofday(t)

def transition(c, b):
  nc = state(c, b)
  doors(a[(c,nc)])
  return nc

def state(c, b):
  if (tod == "night"):
    return (0,0)
  elif (spy == "on"):
    return (1,0)
  else:
    return t[(c,b)]

def doors(ds):
  for d in ds:
    write(d)

def read():
  return ser.read()

def write(b):
  ser.write(b)

# CAMERA {
def camera(i):
  os.system(snap.format(i))
# } 

# { UUID
def ident():
  return str(uuid.uuid4())[0:8]
# }

# { LOGGING
def log(s, i):
  print msg(s, i)

def msg(s, i):
  return stamp() + " [" + i + "] gomb: " + s
# }

# TIME {
def now():
  return datetime.now()

def stamp():
  return now().strftime("%b %d %H:%M:%S")

def minutes():
  return int(now().strftime("%H%M"))
# }

# { TIME OF DAY
def timeofday():
  mm = minutes()
  if (mm < dawn or mm > dusk):
    return "night"
  else:
    return "day"

def settimeofday(t):
  global tod
  tod = t
  log("it is " + tod + " time", ident())
# }

def init():
  while available(): read()
  settimeofday(timeofday());

init()
while True:
  if available():
    act()
  time.sleep(0.2)
