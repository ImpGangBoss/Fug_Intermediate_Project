#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <iomanip>

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
	void SetRank(int new_rank) { this->rank = new_rank; }

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
	//Player PlayerManager::CreatePlayer(std::string name, std::string id, int rank) { return Player(name, id, rank); }
	//void DeletePlayer(Player& player_to_delete) { this->player_list.remove(player_to_delete); }
	void ShowPlayerInfo(Player& player_to_show);
	void RankUp(Player& player);
	void RankDown(Player& player);

private:
	std::list<Player> player_list;
};

void PlayerManager::RankUp(Player& player)
{
	player.SetRank(player.GetRank() + 25);
}

void PlayerManager::RankDown(Player& player)
{
	player.SetRank(player.GetRank() - 25);
}

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

void PlayerManager::ShowPlayerInfo(Player& player_to_show)
{
	for (auto i : this->player_list)
		if (i == player_to_show)
		{
			std::cout << "--------------------------------" << std::endl;
			std::cout << "Name: \t" << player_to_show.GetName() << std::endl;
			std::cout << "Id:   \t" << player_to_show.GetId() << std::endl;
			std::cout << "Rank: \t" << player_to_show.GetRank() << std::endl;
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
	//Hero GetHeroByName(std::string name);
	//Hero GetHeroById(std::string id);
	//Hero CreateHero(std::string name, std::string id, int damage, int hp) { return Hero(name, id, damage, hp); }
	//void DeleteHero(Hero& hero_to_delete) { this->hero_list.remove(hero_to_delete); }
	//void ShowHeroInfo(Hero& hero_to_show);

private:
	std::list<Hero> hero_list;
};


void HeroManager::SetHeroList()
{
	for (int i = 0; i < 20; ++i)
		this->hero_list.push_back(Hero("Hero" + std::to_string(i), "0" + std::to_string(i), rand() % 100 + 3, rand() % 100 + 20));
}

/*
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
*/

class Team
{
public:
	Team() {};
	Team(std::string team_name) { this->name = team_name; }
	void MakePair(Player& player, Hero& hero) { this->team.push_back(std::make_pair(player, hero)); }
	auto GetTeam() { return this->team; }
	auto GetTeamName() { return this->name; }
	void MakeWinner() { this->winner = true; }
	bool IsWinner() { return this->winner; }

protected:
	bool winner = false;
	std::string name;
	std::vector<std::pair <Player, Hero>> team;
};

class TeamManager
{
public:
	void GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list);
	auto GetTwoTeams(int team_pair_index) { return this->list_of_teams[team_pair_index]; }
	Team ChangeTeamRank(Team& team, PlayerManager& player_manager);
	void GetTeamInfo(Team team);

protected:
	std::vector<std::pair<Team, Team>> list_of_teams;
	const int team_size = 5;
};

void TeamManager::GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list)
{

	Team new_team_one("Team1"),
		new_team_two("Team2");

	std::vector<Player> player_vector;
	std::vector<Hero> hero_vector;

	for (auto &i : player_list)
		player_vector.push_back(i);

	for (auto &j : hero_list)
		hero_vector.push_back(j);

	auto Generator = [&player_vector, &hero_vector](Team& team, int team_size)
	{
		int random_player_index = 0,
			random_hero_index = 0;

		for (int i = 0; i < team_size; ++i)
		{
			random_player_index = rand() % player_vector.size();
			random_hero_index = rand() % hero_vector.size();
			team.MakePair(player_vector[random_player_index], hero_vector[random_hero_index]);
			player_vector.erase(player_vector.begin() + random_player_index);
			hero_vector.erase(hero_vector.begin() + random_hero_index);
		}

		return team;
	};

	new_team_one = Generator(new_team_one, this->team_size);
	new_team_two = Generator(new_team_two, this->team_size);

	this->list_of_teams.push_back(std::make_pair(new_team_one, new_team_two));
}

void TeamManager::GetTeamInfo(Team team)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << "Team Name: \t" << team.GetTeamName();
	if (team.IsWinner())
		std::cout << "    (Winner)";
	std::cout << std::endl;
	std::cout <<  "Player id | Player name | Player rank | Hero" << std::endl;
	for (auto& j : team.GetTeam())
	{
		std::cout << std::setw(6) << j.first.GetId();
		std::cout << std::setw(15) << j.first.GetName();
		std::cout << std::setw(11) << j.first.GetRank();
		std::cout << std::setw(15) << j.second.GetName() << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
}

class Session
{
public:
	Session() {};
	Session(std::pair<Team, Team> team_pair);
	Team CalculateWinner(Team& team_one, Team& team_two);
	Team GetWinner() { return this->winner; }
	Team GetLooser() { return this->looser; }
	Team GetFirstTeam() { return this->team_one; }
	Team GetSecondTeam() { return this->team_two; }
	time_t GetSessionTime() { return this->strt_time; }

private:
	time_t strt_time;
	Team team_one,
		team_two,
		winner,
		looser;
};

Session::Session(std::pair<Team, Team> team_pair)
{
	this->strt_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	this->team_one = std::get<0>(team_pair);
	this->team_two = std::get<1>(team_pair);
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
		this->looser = team_two;
		team_one.MakeWinner();
		return team_one;
	}

	this->looser = team_one;
	team_two.MakeWinner();
	return team_two;
}

class GameManager
{
public:
	GameManager() {};
	void PerformGameSession();

	HeroManager GetHeroManager() { return this->hero_manager; }
	PlayerManager GetPlayerManager() { return this->player_manager; }
	TeamManager GetTeamManager() { return this->team_manager; }
	std::vector<Session> GetSessionList() { return this->game_sessions; }
	//void ShowSession(std::vector<Session> sessions);
	void ShowPlayers();
	//void ShowHeroes();

private:
	std::vector<Session> game_sessions;
	TeamManager team_manager;
	HeroManager hero_manager;
	PlayerManager player_manager;
};

/*
void GameManager::ShowSession(std::vector<Session> sessions)
{
	for (auto& i : sessions)
	{
		std::cout << "1st Team | 2nd Team | Winner | Time " << std::endl;
		std::cout << i.GetFirstTeam().GetTeamName() << " "
			<< i.GetSecondTeam().GetTeamName() << " "
			<< i.GetWinner().GetTeamName() << " "
			<< i.GetSessionTime() << std::endl;
	}
}
*/

void GameManager::ShowPlayers()
{
	for (auto& i : this->player_manager.GetPlayerList())
		this->player_manager.ShowPlayerInfo(i);
}

/*
void GameManager::ShowHeroes()
{
	for (auto& j : this->hero_manager.GetHeroList())
		this->hero_manager.ShowHeroInfo(j);
}
*/

void GameManager::PerformGameSession()
{
	this->hero_manager.SetHeroList();
	this->player_manager.SetPlayersList();

	//ShowPlayers();

	/*
	auto test_player = this->player_manager.GetPlayerByName("Player0");
	this->player_manager.ShowPlayerInfo(test_player);
	test_player.SetRank(120);
	this->player_manager.ShowPlayerInfo(test_player);
	this->player_manager.RankDown(test_player);
	this->player_manager.ShowPlayerInfo(test_player);
	*/

	auto player_list = this->player_manager.GetPlayerList();
	auto hero_list = this->hero_manager.GetHeroList();

	this->team_manager.GenerateNewTeams(player_list, hero_list);

	Session session(this->team_manager.GetTwoTeams(0));

	this->team_manager.GetTeamInfo(session.GetWinner());

	for (auto &i : session.GetWinner().GetTeam())
		i.first.SetRank(i.first.GetRank() + 25);

	for (auto& i : session.GetLooser().GetTeam())
		i.first.SetRank(i.first.GetRank() - 25);

	this->team_manager.GetTeamInfo(session.GetWinner());

	this->game_sessions.push_back(session);

	//ShowPlayers();
}

int main()
{
	srand(time(nullptr));

	GameManager game;
	game.PerformGameSession();

	system("pause >> void");
	return 0;
}