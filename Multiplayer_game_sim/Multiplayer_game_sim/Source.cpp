#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <iomanip>

const static int team_size = 5;

class Character
{
public:
	std::string GetName() { return this->name; }
	std::string GetId() { return this->id; }

	friend bool operator == (const Character& obj1, const Character& obj2)
	{
		if (obj1.name == obj2.name && obj1.id == obj2.id)
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
	int rank = 0;
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
	int damage = 0;
	int hp = 0;
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

	void SetRandomPlayersList(int number_of_players);
	auto GetPlayerList() { return this->player_list; }
	Player GetPlayerByName(std::string name);
	Player GetPlayerById(std::string id);
	void ShowPlayerInfo(Player& player_to_show);
	void RankUp(Player& player);
	void RankDown(Player& player);

private:
	std::vector<Player> player_list;
};

void PlayerManager::RankUp(Player& player)
{
	player.SetRank(player.GetRank() + 25);
}

void PlayerManager::RankDown(Player& player)
{
	player.SetRank(player.GetRank() + 25);
}

void PlayerManager::SetRandomPlayersList(int number_of_players)
{
	if (number_of_players < 10) number_of_players = 10;
	for (int i = 0; i < number_of_players; ++i)
		this->player_list.push_back(Player("Player" + std::to_string(i), "0" + std::to_string(i), rand() % 100));
}

Player PlayerManager::GetPlayerByName(std::string name)
{
	for (auto &i : this->player_list)
		if (i.GetName() == name)
			return i;
}

Player PlayerManager::GetPlayerById(std::string id)
{
	for (auto &i : this->player_list)
		if (i.GetName() == id)
			return i;
}

void PlayerManager::ShowPlayerInfo(Player& player_to_show)
{
	for (auto &i : this->player_list)
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

	void SetRandomHeroList(int number_of_heros);
	std::vector<Hero> GetHeroList() { return this->hero_list; }

private:
	std::vector<Hero> hero_list;
};

void HeroManager::SetRandomHeroList(int number_of_heros)
{
	if (number_of_heros < 10) number_of_heros = 10;
	for (int i = 0; i < number_of_heros; ++i)
		this->hero_list.push_back(Hero("Hero" + std::to_string(i), "0" + std::to_string(i), rand() % 100 + 3, rand() % 100 + 20));
}

class Team
{
public:
	Team() {};
	Team(std::string team_name) { this->name = team_name; }

	auto GetTeam() { return this->team; }
	auto GetTeamName() { return this->name; }
	void MakeWinner() { this->winner = true; }
	bool IsWinner() { return this->winner; }

	struct pair
	{
		Player player;
		Hero hero;
	};

protected:
	bool winner = false;
	std::string name;
	pair team[team_size];
	
};

class TeamManager
{
public:
	void GenerateNewTeams(PlayerManager& player_manager, HeroManager& hero_manager);
	auto GetTeamFromList(int team_index) { return this->list_of_teams[team_index]; }
	void GetTeamInfo(Team team);

protected:
	std::vector<Team> list_of_teams;
};

void TeamManager::GenerateNewTeams(PlayerManager& player_manager, HeroManager& hero_manager)
{

	Team new_team_one("Team1"),
		new_team_two("Team2");

	std::vector<int> used_numbers_player,
		used_numbers_hero;

	auto Generator = [&used_numbers_player, &used_numbers_hero, &player_manager, &hero_manager](Team& new_team)
	{
		int random_player_index = 0,
			random_hero_index = 0;

		for (int i = 0; i < team_size; ++i)
		{
			bool add_hero = true;
			bool add_player = true;

			random_player_index = rand() % player_manager.GetPlayerList().size();
			random_hero_index = rand() % hero_manager.GetHeroList().size();

			used_numbers_player.push_back(random_player_index);
			used_numbers_hero.push_back(random_hero_index);

			for (int j = 0; j < used_numbers_player.size(); ++j)
			{
				if (random_hero_index == used_numbers_hero[j])
					add_hero = false;
				if (random_player_index == used_numbers_player[j])
					add_player = false;
			}
			
			if (add_hero) new_team.GetTeam()[i].hero = hero_manager.GetHeroList()[random_hero_index];
			if (add_player) new_team.GetTeam()[i].player = player_manager.GetPlayerList()[random_player_index];
			
		}

		return new_team;
	};

	this->list_of_teams.push_back(Generator(new_team_one));
	this->list_of_teams.push_back(Generator(new_team_two));
}

void TeamManager::GetTeamInfo(Team team)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << "Team Name: \t" << team.GetTeamName();
	if (team.IsWinner())
		std::cout << "    (Winner)";
	std::cout << std::endl;
	std::cout <<  "Player id | Player name | Player rank | Hero" << std::endl;
	for (int i = 0; i < team_size; ++i)
	{
		std::cout << std::setw(6) << team.GetTeam()[i].player.GetId();
		std::cout << std::setw(15) << team.GetTeam()[i].player.GetName();
		std::cout << std::setw(11) << team.GetTeam()[i].player.GetRank();
		std::cout << std::setw(15) << team.GetTeam()[i].hero.GetName() << std::endl;
	}
	std::cout << "*************************************************" << std::endl;
}

class Session
{
public:
	Session() {};
	void CalculateWinner(Team& team1, Team& team2);
	Team GetWinner() { return this->winner; }
	Team GetLooser() { return this->looser; }
	time_t GetSessionTime() { return this->strt_time; }

private:
	time_t strt_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());;
	Team  winner, looser;
};

void Session::CalculateWinner(Team& first_team, Team& second_team)
{
	int first_team_damage = 0,
		first_team_hp = 0,
		second_team_damage = 0,
		second_team_hp = 0;

	for (int i = 0; i < team_size; ++i)
	{
		first_team_damage += first_team.GetTeam()[i].hero.GetDamage();
		first_team_hp += first_team.GetTeam()[i].hero.GetHP();

		second_team_damage += second_team.GetTeam()[i].hero.GetDamage();
		second_team_hp += second_team.GetTeam()[i].hero.GetHP();
	}

	first_team_hp -= second_team_damage;
	second_team_hp -= first_team_damage;

	if (first_team_hp >= second_team_hp)
	{
		this->looser = second_team;
		first_team.MakeWinner();
		this->winner = first_team;
		return;
	}

	this->looser = first_team;
	second_team.MakeWinner();
	this->winner = second_team;
	return;
}

class GameManager
{
public:
	GameManager() {};
	void PerformGameSession();

	HeroManager GetHeroManager() { return this->hero_manager; }
	PlayerManager GetPlayerManager() { return this->player_manager; }
	TeamManager GetTeamManager() { return this->team_manager; }
	auto GetSessionList() { return this->game_sessions; }
	void ShowPlayers();

private:
	std::vector<Session> game_sessions;
	TeamManager team_manager;
	HeroManager hero_manager;
	PlayerManager player_manager;
};

void GameManager::ShowPlayers()
{
	for (auto& i : this->player_manager.GetPlayerList())
		this->player_manager.ShowPlayerInfo(i);
}

void GameManager::PerformGameSession()
{
	Session curr_session;

	this->player_manager.SetRandomPlayersList(10);
	this->hero_manager.SetRandomHeroList(20);

	ShowPlayers();

	this->team_manager.GenerateNewTeams(this->player_manager, this->hero_manager);

	auto first_team = this->team_manager.GetTeamFromList(0);
	auto second_team = this->team_manager.GetTeamFromList(1);

	curr_session.CalculateWinner(first_team, second_team);
	this->team_manager.GetTeamInfo(curr_session.GetWinner());

	for (int i = 0; i < team_size; ++i)
	{
		curr_session.GetWinner().GetTeam()[i].player.SetRank(curr_session.GetWinner().GetTeam()[i].player.GetRank() + 25);
		curr_session.GetWinner().GetTeam()[i].player.SetRank(curr_session.GetWinner().GetTeam()[i].player.GetRank() - 25);
	}

	this->team_manager.GetTeamInfo(curr_session.GetWinner());
}

int main()
{
	srand(time(nullptr));

	GameManager game;
	game.PerformGameSession();

	system("pause >> void");
	return 0;
}