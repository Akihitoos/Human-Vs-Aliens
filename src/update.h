#ifndef UPDATE_H
#define UPDATE_H

#include "interaction.h"
#include "time.h"

void commonUpdate(Entity **entity_array, int lane, Entity* entity);

int CanMove(Entity* entity, Entity* target, Entity *entity_array);

int entityUpdate(Entity** entity_array, Entity** entity, Entity** ennemy_array, int lane, Mower mower_array);

int update (Entity ** human_array, Entity ** alien_array, Player *human_player, Player *alien_human, Mower mower_array);

#endif