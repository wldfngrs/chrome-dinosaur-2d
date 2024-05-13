#include "EntityComponentSystem.h"

void Entity::addGroup(Group mGroup){
	groupBitset[mGroup] = true;
	eManager.AddToGroup(this, mGroup);
}