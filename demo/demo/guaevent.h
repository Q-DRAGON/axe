#ifndef guaevent_h
#define guaevent_h


struct _GuaEvent;
typedef struct _GuaEvent GuaEvent;
struct _GuaEvent {
    // type 1 是 鼠标
    // type 2 是 键盘
    int type;
    
    // state 1 是按下
    // state 2 是松开
    // state 3 是鼠标移动
    int state;
    
    // key 是键盘按键
    int key;
    
    // x y 是鼠标事件独有的属性
    int x;
    int y;
};


#endif
