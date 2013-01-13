int S_OPEN = 30;
int S_CLOSED = 120;

//
// Servos, defined as Motors
//

typedef struct {
    char *name;
    int open;
    int close;
    Servo servo;
} Motor;

//
// Modes for 3 servos
//

typedef struct {
    char *m;
    int l;
    int c;
    int r;
} Mode;

Mode M_OPEN    = {"open",    S_OPEN,   S_OPEN,   S_OPEN  };
Mode M_CLOSED  = {"closed",  S_CLOSED, S_CLOSED, S_CLOSED};
Mode M_CAPTURE = {"capture", S_CLOSED, S_OPEN,   S_CLOSED};
Mode M_FLUSH   = {"flush",   S_CLOSED, S_CLOSED, S_CLOSED};

//
// Ultrasonic sensors
//

typedef struct {
    char *name;
    int pin;
} UltraDef;

typedef struct {
    int v;
    int base;
    unsigned long quiet_at;
} UltraVal;

typedef struct {
    UltraDef def;
    UltraVal val;
} Ultra;

//
// States / Transitions
//

typedef struct {
    char *name;
    Mode mode;
//    Mode next;
//    Ultra ultra;
//    int type;
} State;

State S_INITIAL = { "initial", M_CLOSED };
State S_CAPTURE = { "capture", M_CAPTURE };

