#ifndef MOUSE_H
#define MOUSE_H

int mouse_init(void);
void mouse_cleanup(void);
int mouse_interrupt_handler(void);
int mouse_get(int *x, int *y);

#endif
