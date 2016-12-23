#include<iostream>
#include <vector>

enum class Color { White, Wheatish, Black };
enum class Game { Cricket, Soccer, BasketBall};
enum class Height { Small, Average, High };

class Human {
	public:
	std::string name;
	Color color;
	Game game;
	Height height ;
};


template <typename T> class FilterCriteria {
	public:
	virtual bool isMatched(T* item) = 0;
};

template <typename T> class IFilter {
	public:
	virtual std::vector<T*> filter(std::vector<T*> items, FilterCriteria<T>& criteria)=0;
};

class HumanFilter :public IFilter<Human> {
	typedef std::vector<Human*> Humans;
	public:
	Humans filter(const Humans collections, FilterCriteria<Human>& criteria) override {
	Humans result;
		for (auto& item : collections) {
			if(criteria.isMatched(item)){
				result.push_back(item);	
			}
		}
		return result;
	}
};

class GameFilterCriteria :public FilterCriteria<Human> {
	public:
	explicit GameFilterCriteria(const Game game): m_game {game} {}
	bool isMatched(Human* h ) override {
		return h->game == m_game;
	}
	private:
	Game m_game;
};

class ColorimetryCriteria :public FilterCriteria<Human> {
	public:
	explicit ColorimetryCriteria(const Color color): m_color {color} {}
	bool isMatched(Human* h ) override {
		return h->color == m_color;
	}
	private:
	Color m_color;
};

template <typename T> class CombinedCriteria :public FilterCriteria<T>
{
  	public:
  	CombinedCriteria(FilterCriteria<T> &game, FilterCriteria<T> &color): m_game{game}, m_color{color} { }

  	bool isMatched(T* item) override
  	{
    		return m_game.isMatched(item) && m_color.isMatched(item);
  	}
	private:  
  	FilterCriteria<T> &m_game;
  	FilterCriteria<T> &m_color;
};

int main() {

	Human asian{"Asian", Color::Wheatish, Game::Cricket, Height::Average};
	Human european {"European", Color::White, Game::Soccer, Height::High};
	Human african{ "African", Color::Black, Game::BasketBall, Height::High};
	Human australian{ "Australia", Color::White, Game::Cricket, Height::High};

	std::vector<Human*> human {&asian, &european, &african, &australian};
        	
	HumanFilter human_filter;

	std::cout<<std::endl<<" -->Empower human_filter to filter by cricket playing country <--\n";
	GameFilterCriteria game(Game::Cricket);
	auto cricket_playing_country = human_filter.filter(human, game);
	for (auto & item : cricket_playing_country) {
		std::cout<<"\t" <<item->name << " is cricket playing country.\n";
	}
	
	std::cout<<std::endl<<" -->Empower human_filter to filter by colorimentry criteria <--\n";
	
	ColorimetryCriteria color(Color::White);
	auto white_color_human = human_filter.filter(human, color);
	for (auto & item : white_color_human) {
		std::cout<<"\t"<< item->name << " are white color human.\n";
	}

	std::cout<<std::endl<<" -->Empower human_filter to filter by cricket plyaing country and colorimentry criteria <--\n";

	CombinedCriteria<Human> cricket_and_white{ game , color };
	auto cricekt_white_human = human_filter.filter(human, cricket_and_white);
	for (auto & value : cricekt_white_human) {
		std::cout<<"\t"<< value->name << " are white color cricket playing human.\n";
	}
	return 1;
}
