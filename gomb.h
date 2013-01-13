int S_OPEN = 30;
int S_CLOSED = 120;

typedef struct {
    char *m;
    int sl;
    int sc;
    int sr;
} Mode;

Mode M_OPEN    = {"open",    S_OPEN,   S_OPEN,   S_OPEN  };
Mode M_CLOSED  = {"closed",  S_CLOSED, S_CLOSED, S_CLOSED};
Mode M_CAPTURE = {"capture", S_CLOSED, S_OPEN,   S_CLOSED};
Mode M_FLUSH   = {"flush",   S_CLOSED, S_CLOSED, S_CLOSED};

//
// Ultrasonic sensors
//

int ULTRA_HISTORY = 10;

typedef struct {
    char *name;
    int pin;
} UltraDef;

typedef struct {
    int v;
    int base;
} UltraVal;

typedef struct {
    int* vs;
    int i;
    int quiet_at;
} UltraHistory;

typedef struct {
    UltraDef def;
    UltraVal val;
    UltraHistory hist;
} Ultra;


//typedef struct {
//    char *m
//    Mode current;
//    Mode next;
//    Ultra ultra;
//    int type;
//} Transition;

