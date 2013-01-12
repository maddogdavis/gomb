int S_OPEN = 30;
int S_CLOSED = 120;

typedef struct {
    int sl;
    int sc;
    int sr;
} Mode;

Mode M_OPEN    = {S_OPEN,   S_OPEN,   S_OPEN  };
Mode M_CLOSED  = {S_CLOSED, S_CLOSED, S_CLOSED};
Mode M_CAPTURE = {S_CLOSED, S_OPEN,   S_CLOSED};
Mode M_FLUSH   = {S_CLOSED, S_CLOSED, S_CLOSED};
