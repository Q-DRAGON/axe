struct ButtonStruct;
typedef struct ButtonStruct ButtonStruct;
typedef void *(Callback)(void *);


int
actionClick(void);

ButtonStruct *
GuaButtonNew(int x, int y, int w, int h);

int
hasMouseIn(ButtonStruct *button, int x, int y);

int
GuaButtonSetAction(ButtonStruct *button, Callback *actionClick);

int
ButtonDraw(ButtonStruct *button);
