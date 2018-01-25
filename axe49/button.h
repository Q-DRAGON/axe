struct ButtonStruct;
typedef struct ButtonStruct ButtonStruct;
typedef void *(GuaTaskCallback)(void *);

int
actionClick(void);

ButtonStruct *
GuaButtonNew(int x, int y, int w, int h);

int
hasMouseIn(ButtonStruct *button, int x, int y);

int
GuaButtonSetAction(ButtonStruct *button, GuaTaskCallback *actionClick);

int
ButtonDraw(ButtonStruct *button);
