#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <ctime> 

class Character
{
public:
	std::string GetName() { return this->name; }
	std::string GetId() { return this->id; }

	friend bool operator == (const Character& obj1, const Character& obj2)
	{
		if (obj1.name == obj2.name && obj1.name == obj2.name)
			return true;
	}

protected:
	std::string name;
	std::string id;
};

class Player : public Character
{
public:
	Player() {};
	Player(std::string name, std::string id, int rank);

	int GetRank() { return this->rank; }

private:
	int rank;
};

Player::Player(std::string name, std::string id, int rank)
{
	this->name = name;
	this->id = id;
	this->rank = rank;
}

class Hero : public Character
{
public:
	Hero() {};
	Hero(std::string name, std::string id, int damage, int hp);

	int GetDamage() { return this->damage; }
	int GetHP() { return this->hp; }

private:
	int damage;
	int hp;
};

Hero::Hero(std::string name, std::string id, int damage, int hp)
{
	this->name = name;
	this->id = id;
	this->damage = damage;
	this->hp = hp;
}

class PlayerManager
{
public:
	PlayerManager() {};

	void SetPlayersList(std::list<Player> user_players_list) { this->players_list = user_players_list; }

	Player GetPlayerByName(std::string name);
	Player GetPlayerById(std::string id);
	Player CreatePlayer(std::string name, std::string id, int rank) { return Player(name, id, rank); }
	void ShowPlayerInfo(Player& player_to_show);

private:
	std::list<Player> players_list;
};

Player PlayerManager::GetPlayerByName(std::string name)
{
	for (auto i : this->players_list)
		if (i.GetName() == name)
			return i;
}


Player PlayerManager::GetPlayerById(std::string id)
{
	for (auto i : this->players_list)
		if (i.GetName() == id)
			return i;
}

void PlayerManager::ShowPlayerInfo(Player& player_to_show)
{
	for (auto i: this->players_list)
		if (i == player_to_show)
		{
			std::cout << "Name: \t" << i.GetName() << std::endl;
			std::cout << "Id:   \t" << i.GetId() << std::endl;
			std::cout << "Rank: \t" << i.GetRank() << std::endl;
		}
}

class HeroManager
{
public:
	HeroManager() {};

	void SetHeroList(std::list<Hero> user_hero_list) { this->hero_list = user_hero_list; }

	Hero GetHeroByName(std::string name);
	Hero GetHeroById(std::string id);
	Hero CreateHero(std::string name, std::string id, int damage, int hp) { return Hero(name, id, damage, hp); }
	void ShowHeroInfo(Hero& hero_to_show);

private:
	std::list<Hero> hero_list;
};

Hero HeroManager::GetHeroByName(std::string name)
{
	for (auto i : this->hero_list)
		if (i.GetName() == name)
			return i;
}


Hero HeroManager::GetHeroById(std::string id)
{
	for (auto i : this->hero_list)
		if (i.GetName() == id)
			return i;
}

void HeroManager::ShowHeroInfo(Hero& hero_to_show)
{
	for (auto i : this->hero_list)
		if (i == hero_to_show)
		{
			std::cout << "Name:   \t" << i.GetName() << std::endl;
			std::cout << "Id:     \t" << i.GetId() << std::endl;
			std::cout << "Damage: \t" << i.GetDamage() << std::endl;
			std::cout << "HP:     \t" << i.GetHP() << std::endl;
		}
}

class Team
{
public:
	Team() {};
	void MakePair(Player& player, Hero& hero) { this->team.push_back(std::make_pair(player, hero)); }

private:
	std::string name;
	std::vector<std::pair <Player, Hero>> team;
};

class TeamManager
{
public:
	Team GenerateNewTeam(std::list<Player> player_list, std::list<Hero> hero_list, Team previous_team = {});
	void GetTeamInfo();

private:
	std::list<Team> list_of_teams;
	const int team_size = 5;
};

Team TeamManager::GenerateNewTeam(std::list<Player> player_list, std::list<Hero> hero_list, Team previous_team)
{
	Team new_team;

	/*for (int j = 0; j < this->team_size; ++j)
		new_team.MakePair(std::advance(player_list.begin(), j), std::advance(hero_list.begin(), j));*/

	return new_team;
}



class Session
{
public:
	Session() {};
	Session(Team& team_one, Team& team_two);
	Team CalculateWinner(Team& team_one, Team& team_two);

private:
	std::time_t strt_time;
	Team team_one,
		team_two,
		winner;
};

Session::Session(Team& team_one, Team& team_two)
{
	this->strt_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	this->team_one = team_one;
	this->team_two = team_two;
	this->winner = CalculateWinner(team_one, team_two);
}

class GameManager
{
public:
	GameManager() {};
	Session PerformGameSession();

private:
	std::vector<Session> game_sessions;
};

int main()
{
	std::srand(std::time(nullptr));

	system("pause >> void");
	return 0;
}