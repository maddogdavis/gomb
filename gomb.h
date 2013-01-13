
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
// Triggers
//

int T_NONE = 100;
int T_ACTIVE = 200;
int T_QUIET = 300;

//
// States / Transitions
//

struct state {
    char *name;
    Mode mode;
    int trigger_c;
    int trigger_f;
    struct state *next;
};

typedef struct state State;

State S_INITIAL = { "initial", M_CLOSED,  T_NONE,   T_NONE,   0 /* S_INITIAL */};
State S_OPEN    = { "open",    M_OPEN,    T_ACTIVE, T_NONE,   0 /* S_CAPTURE */};
State S_CAPTURE = { "capture", M_CAPTURE, T_NONE,   T_ACTIVE, 0 /* S_FLUSH */  };
State S_FLUSH   = { "flush",   M_FLUSH,   T_QUIET,  T_NONE,   0 /* S_OPEN */   };
