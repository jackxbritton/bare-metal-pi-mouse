#ifndef MOUSE_H
#define MOUSE_H

int mouse_init(void);
void mouse_cleanup(void);
int mouse_interrupt_handler(void);

extern int mouse_x, mouse_y;

#endif
