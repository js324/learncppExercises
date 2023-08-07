#include <iostream>
#include <string>
#include <array>
#include "Random.h"

#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

class Creature {
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_dmg;
	int m_gold;
public:
	Creature(std::string_view name, char symbol, int health, int dmg, int gold): m_name {name}, 
		m_symbol {symbol}, m_health {health}, m_dmg {dmg}, m_gold {gold} {}
	std::string& getName() {
		return m_name;
	}
	char getSymbol() {
		return m_symbol;
	}
	int getHealth() {
		return m_health;
	}
	int getDamage() {
		return m_dmg;
	}
	int getGold() {
		return m_gold;
	}
	void reduceHealth(int dmg) {
		m_health -= dmg;
	}
	bool isDead() {
		return m_health <= 0;
	}
	void addGold(int gold) {
		m_gold += gold;
	}
	void hitByCreature(Creature& creature) {
		std::cout << creature.getName() << " hit " << m_name << " for " << creature.m_dmg << " hp!\n";
		reduceHealth(creature.m_dmg);
	}
};

class Monster : public Creature {
private:
public:
	enum class Type {
		dragon,
		orc,
		slime,
		max_types
	};
	Monster(Type type) : Creature(getDefaultCreature(type)) {}
	static const Creature& getDefaultCreature(Type type)
	{
		static const std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
			{ { "dragon", 'D', 20, 4, 100 },
				{ "orc", 'o', 4, 2, 25 },
				{ "slime", 's', 1, 1, 10 } }
		};

		return monsterData.at(static_cast<std::size_t>(type));
	}
	static Monster getRandomMonster() {
		return Monster(static_cast<Type>(Random::get(0, static_cast<int>(Type::max_types) - 1)));
	}

};

class Player : public Creature {
private:
	int m_level {1};
public:
	Player(std::string_view name) : Creature(name, '@', 10, 1, 0) {}
	void levelUp() {
		m_dmg++;
		m_level++;
	}
	bool hasWon() {
		return m_level >= 20;
	}
	bool fightingMonster(Monster& monster) {
		monster.hitByCreature(*this);


		if (monster.isDead()) {
			std::cout << "You defeated the " << monster.getName() << "!";
			levelUp();
			std::cout << "You are now level " << m_level << '\n';
			potionEncounter();
			return false;
		}

		hitByCreature(monster);
		return !isDead();
	}
	bool willFight(Monster& monster) {
		
		std::cout << "Will you fight (f) or run (r)? \n";
		while (true) {
			char input{};
			std::cin >> input;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
			switch (input) {
			case 'f': 
				return fightingMonster(monster);
			case 'r': {
				//random 50/50 chance for successful flee
				bool canRun = static_cast<bool>(Random::get(0, 1));
				if (canRun) {
					std::cout << "You sucessfully ran away!"; //no longer fighting, flee from monster
					return false;
				}
				else {
					std::cout << "You could not run away!";
					hitByCreature(monster);
					
					return !isDead();
				}
			}
				default:
					std::cout << "Unrecognized input!";
					break;
			}
		}
	}
	void potionEncounter() { //pots could be seperate class
		int rand = Random::get(0, 2); 
		if (!rand) {
			std::cout << "You found a potion! Do you drink it? [y/n]";
			while (true) { // should move to seperate func honestly
				char input{};
				std::cin >> input;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin.clear();
				switch (input) {
				case 'y': {
					int potType = Random::get(0, 2);
					int bonusType = Random::get(0, 2);
					int healthBonus[] = { 2, 2, 5 };
					std::array<std::string, 3> bonusName{"Weak", "Medium", "Strong"};
					std::array<std::string, 3> typeName{"Health", "Strength", "Poison"};
					std::cout << "You drank a " << bonusName[bonusType] << " " << typeName[potType] << " potion";
					switch (potType) {
					case 0: //health
						m_health += healthBonus[bonusType];
						return;
					case 1: //strength
						m_dmg++;
						return;
					case 2: //poison
						m_health--;
						return;
					default:
						break;
					}
				}
					break;
				case 'n': 
					std::cout << "A valid decision! Moving on!";
					return;
				default:
					std::cout << "Unrecognized input!";
					break;
				}
			}
		}
	}
};

int main()
{
	std::cout << "Enter your name: ";
	std::string playerName;
	std::cin >> playerName;

	Player p{ playerName };
	while (!p.hasWon()) {
		Monster encounter = Monster::getRandomMonster();
		std::cout << "You have encountered a " << encounter.getName() << "!\n";
		while (p.willFight(encounter)) {}
		if (p.isDead()) {
			std::cout << "You have died!";
			return 0;
		}
	}
	return 0;
}