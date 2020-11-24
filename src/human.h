#ifndef HUMAN
#define HUMAN

typedef struct human Human;

Human *create_ranged(int positionX, int lane);
Human *create_tank(int positionX, int lane);
Human *create_melee(int positionX, int lane);
Human *create_factory(int positionX, int lane);

#endif