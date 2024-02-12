#pragma once
class Entity
{
private:
	int hp;
	int attack;
	int defense;

public:
	Entity(int _hp, int _attack, int _defense);
	int getHp() const;
	int getattack() const;
	int getdefense() const;
	void attacking(Entity& att, Entity& victom);
};

class Hero : public Entity {

public:
	Hero(int _hp, int _attack, int _defense);
};
class Monster : public Entity {

public:
	Monster(int _hp, int _attack, int _defense);
};