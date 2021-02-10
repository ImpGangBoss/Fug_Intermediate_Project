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
	void RankUp() { this->rank += 25; }
	void RankDown() { this->rank -= 25; }

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

	void SetPlayersList();
	std::list<Player> GetPlayerList() { return this->player_list; }

	Player GetPlayerByName(std::string name);
	Player GetPlayerById(std::string id);
	Player CreatePlayer(std::string name, std::string id, int rank);
	void ShowPlayerInfo(const Player& player_to_show);

private:
	std::list<Player> player_list;
};

Player PlayerManager::CreatePlayer(std::string name, std::string id, int rank) { return Player(name, id, rank); }

void PlayerManager::SetPlayersList()
{
	for (int i = 0; i < 10; ++i)
		this->player_list.push_back(Player("Player" + std::to_string(i), "0" + std::to_string(i), rand() % 100));
}

Player PlayerManager::GetPlayerByName(std::string name)
{
	for (auto i : this->player_list)
		if (i.GetName() == name)
			return i;
}


Player PlayerManager::GetPlayerById(std::string id)
{
	for (auto i : this->player_list)
		if (i.GetName() == id)
			return i;
}

void PlayerManager::ShowPlayerInfo(const Player& player_to_show)
{
	for (auto i : this->player_list)
		if (i == player_to_show)
		{
			std::cout << "--------------------------------" << std::endl;
			std::cout << "Name: \t" << i.GetName() << std::endl;
			std::cout << "Id:   \t" << i.GetId() << std::endl;
			std::cout << "Rank: \t" << i.GetRank() << std::endl;
			std::cout << "--------------------------------" << std::endl;

			break;
		}
}

class HeroManager
{
public:
	HeroManager() {};

	void SetHeroList();
	std::list<Hero> GetHeroList() { return this->hero_list; }

	Hero GetHeroByName(std::string name);
	Hero GetHeroById(std::string id);
	Hero CreateHero(std::string name, std::string id, int damage, int hp) { return Hero(name, id, damage, hp); }
	void ShowHeroInfo(Hero& hero_to_show);

private:
	std::list<Hero> hero_list;
};

void HeroManager::SetHeroList()
{
	for (int i = 0; i < 20; ++i)
		this->hero_list.push_back(Hero("Hero" + std::to_string(i), "0" + std::to_string(i), rand() % 100 + 3, rand() % 100 + 20));
}

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
			std::cout << "--------------------------------" << std::endl;
			std::cout << "Name:   \t" << i.GetName() << std::endl;
			std::cout << "Id:     \t" << i.GetId() << std::endl;
			std::cout << "Damage: \t" << i.GetDamage() << std::endl;
			std::cout << "HP:     \t" << i.GetHP() << std::endl;
			std::cout << "--------------------------------" << std::endl;

			break;
		}
}

class Team
{
public:
	Team() {};
	void MakePair(Player& player, Hero& hero) { this->team.push_back(std::make_pair(player, hero)); }
	std::vector<std::pair <Player, Hero>> GetTeam() { return this->team; }
	void SetTeamName(std::string team_name) { this->name = team_name; }
	std::string GetTeamName() { return this->name; }

protected:
	std::string name;
	std::vector<std::pair <Player, Hero>> team;
};

class TeamManager
{
public:
	void GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list);
	std::pair <Team, Team> GetTwoTeams(int team_pair_index) { return this->list_of_teams[team_pair_index]; }
	void GetTeamsInfo(Team team);

protected:
	std::vector<std::pair<Team, Team>> list_of_teams;
	const int team_size = 5;
};

void TeamManager::GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list)
{
	Team new_team_one,
		new_team_two;

	std::vector<Player> player_vector;
	std::vector<Hero> hero_vector;

	for (auto &i : player_list)
		player_vector.push_back(i);

	for (auto &j : hero_list)
		hero_vector.push_back(j);

	int random_player_index = 0,
		random_hero_index = 0;

	for (int i = 0; i < this->team_size; ++i)
	{
		random_player_index = rand() % player_vector.size();
		random_hero_index = rand() % hero_vector.size();
		new_team_one.MakePair(player_vector[random_player_index], hero_vector[random_hero_index]);
		player_vector.erase(player_vector.begin() + random_player_index);
		hero_vector.erase(hero_vector.begin() + random_hero_index);

		random_player_index = rand() % player_vector.size();
		random_hero_index = rand() % hero_vector.size();
		new_team_two.MakePair(player_vector[random_player_index], hero_vector[random_hero_index]);
		player_vector.erase(player_vector.begin() + random_player_index);
		hero_vector.erase(hero_vector.begin() + random_hero_index);
	}

	this->list_of_teams.push_back(std::make_pair(new_team_one, new_team_two));
}

void TeamManager::GetTeamsInfo(Team team)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << "Team Name: \t" << team.GetTeamName() << std::endl;
	std::cout << "P_id  P_name  P_rank  Hero" << std::endl;
	for (auto &j : team.GetTeam())
		std::cout << j.first.GetId() << "\t" << j.first.GetName() << "\t" << j.first.GetRank() << "\t" << j.second.GetName() << "\t" << std::endl;
	std::cout << "*************************************************" << std::endl;
}

class Session
{
public:
	Session() {};
	Session(std::pair<Team, Team> team_pair);
	Team CalculateWinner(Team& team_one, Team& team_two);
	Team GetWinner() { return this->winner; }

private:
	std::time_t strt_time;
	Team team_one,
		team_two,
		winner;
};

Session::Session(std::pair<Team, Team> team_pair)
{
	this->strt_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	this->team_one = team_one;
	this->team_two = team_two;
	this->winner = CalculateWinner(std::get<0>(team_pair), std::get<1>(team_pair));
}

Team Session::CalculateWinner(Team& team_one, Team& team_two)
{
	int first_team_damage = 0,
		first_team_hp = 0,
		second_team_damage = 0,
		second_team_hp = 0;

	for (auto &i : team_one.GetTeam())
	{
		first_team_damage += i.second.GetDamage();
		first_team_hp += i.second.GetHP();
	}

	for (auto &j : team_two.GetTeam())
	{
		second_team_damage += j.second.GetDamage();
		second_team_hp += j.second.GetHP();
	}

	first_team_hp -= second_team_damage;
	second_team_hp -= first_team_damage;

	if (first_team_hp >= second_team_hp)
	{
		for (auto &i : team_one.GetTeam())
			i.first.RankUp();

		for (auto &j : team_two.GetTeam())
			j.first.RankDown();

		return team_one;
	}

	for (auto &i : team_one.GetTeam())
		i.first.RankDown();

	for (auto &j : team_two.GetTeam())
		j.first.RankUp();

	return team_two;
}

class GameManager
{
public:
	GameManager() {};
	void PerformGameSession();
	//void SetPlayerList(std::list<Player> user_player_list) { this->player_list = user_player_list; }
	//void SetHeroList(std::list<Hero> user_hero_list) { this->hero_list = user_hero_list; }

private:
	std::vector<Session> game_sessions;
	//std::list<Player> player_list;
	//std::list<Hero> hero_list;
};

void GameManager::PerformGameSession()
{
	TeamManager team_manager;
	HeroManager hero_manager;
	PlayerManager player_manager;

	hero_manager.SetHeroList();
	player_manager.SetPlayersList();

	player_manager.ShowPlayerInfo(player_manager.GetPlayerByName("Player1"));

	team_manager.GenerateNewTeams(player_manager.GetPlayerList(), hero_manager.GetHeroList());
	team_manager.GetTwoTeams(0).first.SetTeamName("Team1");
	team_manager.GetTwoTeams(0).second.SetTeamName("Team2");

	Session session(team_manager.GetTwoTeams(0));
	team_manager.GetTeamsInfo(session.GetWinner());

	this->game_sessions.push_back(session);
}

int main()
{
	srand(time(nullptr));

	GameManager game;
	game.PerformGameSession();

	system("pause >> void");
	return 0;
}