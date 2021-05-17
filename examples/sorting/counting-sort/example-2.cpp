#include <iostream>
#include <string>
#include <vector>
#include "dragon/sorting/counting-sort.hpp"

struct Character {
  std::string name;
  int rank;
};

int main () {
  std::vector<Character> characters= {
    {
      "Mikasa",
      5
    },
    {
      "Touka",
      1
    },
    {
      "kugisaki",
      7
    },
    {
      "Kurisu",
      4
    },
    {
      "Christina",
      3
    }
  };
  std::cout<<"Before sorting:\n";
  for (auto character : characters) {
    std::cout<<character.name<<": "<<character.rank<<"\n";
  }
  std::cout<<"\n";
  dragon::counting_sort(characters.begin(), characters.end(), [](const Character& character) {
    return character.rank;
  });
  std::cout<<"After sorting\n";
  for (auto character : characters) {
    std::cout<<character.name<<": "<<character.rank<<"\n";
  }
}