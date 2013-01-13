
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

int MODE_OPEN = 0;
int MODE_CLOSED = 1;

typedef struct {
    char *m;
    int l;
    int c;
    int r;
} Mode;

Mode M_OPEN    = {"open",    MODE_OPEN,   MODE_OPEN,   MODE_OPEN  };
Mode M_CLOSED  = {"closed",  MODE_CLOSED, MODE_CLOSED, MODE_CLOSED};
Mode M_CAPTURE = {"capture", MODE_CLOSED, MODE_OPEN,   MODE_CLOSED};
Mode M_FLUSH   = {"flush",   MODE_CLOSED, MODE_CLOSED, MODE_CLOSED};

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

