#include "Entity.h"

Entity::Entity(int _hp, int _attack, int _defense)
{
	hp = _hp;
	attack = _attack;
	defense = _defense;
}

int Entity::getHp() const
{
	return hp;
}

int Entity::getattack() const
{
	return attack;
}

int Entity::getdefense() const
{
	return defense;
}

void Entity::attacking(Entity& att, Entity& victom)
{
	int point = att.attack - victom.defense;
	if (point >= 0) {
		victom.hp -= point;
	}
}

Hero::Hero(int _hp, int _attack, int _defense)
	: Entity(_hp, _attack, _defense)
{

}
Monster::Monster(int _hp, int _attack, int _defense)
	: Entity(_hp, _attack, _defense)
{
}
