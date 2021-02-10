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
	void RankUp() { this->rank = this->rank + 25; }
	void RankDown() { this->rank = this->rank - 25; }

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
	void DeletePlayer(Player& player_to_delete) { this->player_list.remove(player_to_delete); }
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
	void DeleteHero(Hero& hero_to_delete) { this->hero_list.remove(hero_to_delete); }
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
	Team(std::string team_name) { this->name = team_name; }
	void MakePair(Player& player, Hero& hero) { this->team.push_back(std::make_pair(player, hero)); }
	std::vector<std::pair <Player, Hero>> GetTeam() { return this->team; }
	auto GetTeamName() { return this->name; }

protected:
	std::string name;
	std::vector<std::pair <Player, Hero>> team;
};

class TeamManager
{
public:
	void GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list);
	auto GetTwoTeams(int team_pair_index) { return this->list_of_teams[team_pair_index]; }
	void GetTeamsInfo(Team team);

protected:
	std::vector<std::pair<Team, Team>> list_of_teams;
	const int team_size = 5;
};

void TeamManager::GenerateNewTeams(std::list<Player> player_list, std::list<Hero> hero_list)
{
	std::string team_name1, team_name2;

	std::cout << "Enter names of 2 teams: " << std::endl;

	std::getline(std::cin, team_name1);
	std::getline(std::cin, team_name2);

	Team new_team_one(team_name1),
		new_team_two(team_name2);

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

void TeamManager::GetTeamsInfo(Team team)
{
	std::cout << "*************************************************" << std::endl;
	std::cout << "Team Name: \t" << team.GetTeamName() << std::endl;
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
	Team GetFirstTeam() { return this->team_one; }
	Team GetSecondTeam() { return this->team_two; }
	time_t GetSessionTime() { return this->strt_time; }

private:
	time_t strt_time;
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

	HeroManager GetHeroManager() { return this->hero_manager; }
	PlayerManager GetPlayerManager() { return this->player_manager; }
	TeamManager GetTeamManager() { return this->team_manager; }
	std::vector<Session> GetSessionList() { return this->game_sessions; }
	void ShowSession(std::vector<Session> sessions);
	void ShowPlayers();
	void ShowHeroes();

private:
	std::vector<Session> game_sessions;
	TeamManager team_manager;
	HeroManager hero_manager;
	PlayerManager player_manager;
};

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

void GameManager::ShowPlayers()
{
	for (auto i : this->player_manager.GetPlayerList())
		player_manager.ShowPlayerInfo(i);
}

void GameManager::ShowHeroes()
{
	for (auto j : this->hero_manager.GetHeroList())
		hero_manager.ShowHeroInfo(j);
}

void GameManager::PerformGameSession()
{
	this->hero_manager.SetHeroList();
	this->player_manager.SetPlayersList();

	ShowHeroes();
	ShowPlayers();

	auto player_list = this->player_manager.GetPlayerList();
	auto hero_list = this->hero_manager.GetHeroList();

	this->team_manager.GenerateNewTeams(player_list, hero_list);

	auto first_team = std::get<0>(this->team_manager.GetTwoTeams(0));
	auto second_team = std::get<1>(this->team_manager.GetTwoTeams(0));

	Session session(this->team_manager.GetTwoTeams(0));
	this->team_manager.GetTeamsInfo(session.GetWinner());

	this->game_sessions.push_back(session);

	ShowSession(this->game_sessions);
	ShowPlayers();
}

/*void MainMenu(GameManager &game)
{
	system("cls");

	std::cout << "\t\tMain Menu" << std::endl;
	std::cout << "(1) Start Game" << std::endl;
	std::cout << "(2) Players" << std::endl;
	std::cout << "(3) Heroes" << std::endl;
	std::cout << "(4) Sessions" << std::endl;
	std::cout << "(0) Exit" << std::endl;

	int switcher = 0;
	std::cin >> switcher;

	switch (switcher)
	{
	case 1:
		;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 0:
		exit(0);
	default:
		break;
	}
}
*/
int main()
{
	srand(time(nullptr));

	GameManager game;
	game.PerformGameSession();

	/*while (true)
		MainMenu(game);*/

	system("pause >> void");
	return 0;
}