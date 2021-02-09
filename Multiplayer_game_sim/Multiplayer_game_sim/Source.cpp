#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime> 

class Character
{
public:
	std::string GetName() { return this->name; }
	std::string GetId() { return this->id; }

protected:
	std::string name;
	std::string id;
};

class Player : public Character
{
public:
	Player() {};
	Player(std::string name, std::string id, int rank);

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
	Hero(std::string hr_name, std::string hr_id, int damage, int hp);

private:
	int damage;
	int hp;
};

Hero::Hero(std::string hr_name, std::string hr_id, int damage, int hp)
{
	this->name = hr_name;
	this->id = hr_id;
	this->damage = damage;
	this->hp = hp;
}

class PlayerManager
{
public:
	PlayerManager() {};
	Player CreatePlayer(std::string name, std::string id, int rank);
	Player GetPlayerByName(std::string name);
	Player GetPlayerById(std::string id);
	void DeletePlayer(Player plr_to_dlt);
	void ShowPlayerInfo(Player plr_to_shw);
};

class HeroManager
{
public:
	HeroManager() {};
	Hero CreateHero(std::string name, std::string id, int damage, int hp);
	Hero GetHeroByName(std::string name);
	Hero GetHeroById(std::string id);
	void DeleteHero(Hero plr_to_dlt);
	void ShowHeroInfo(Hero plr_to_shw);
};

class Team
{
public:
	Team() {};
private:
	std::string name;
	std::vector<std::pair <Player, Hero>> team;
};

class TeamManager
{
public:
	Team GenerateNewTeam();
	void GetTeamInfo();
};

class Session
{
public:
	Session() {};
	Session(Team team_one, Team team_two, Team winner);
	Team CalculateWinner(Team team_one, Team team_two);

private:
	std::time_t strt_time;
	Team team_one,
		team_two,
		winner;
};

Session::Session(Team team_one, Team team_two, Team winner)
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

	system("pause >> void");
	return 0;
}