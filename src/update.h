#include <stdio.h>
#include <stdlib.h>
#include "interaction.h"
#include "Entity.h"
#include "mower.h"

void commonUpdate(Entity **entity_array, int lane, Entity* entity);

void entityUpdate(Entity** entity_array, Entity** entity, Entity** ennemy_array, int lane, Mower mower_array);

void update(Entity ** human_array, Entity ** alien_array, Mower mower_array);