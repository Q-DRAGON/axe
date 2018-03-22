// 保护头文件：避免重复引用头文件可能出现的重复定义的情况，
// 结尾加上 end if
#ifndef __button__
#define __button__

typedef struct _ButtonStruct ButtonStruct;
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
DrawButton(void *button);

#endif
