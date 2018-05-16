#include <iostream>
#include "voting_machine.h"

using namespace std;
using namespace foobar;

int main()
{
    voting_machine machine;
    std::string voter;
    std::string type;
    std::string votee;

    while (std::cin >> voter)
    {
        std::cin >> type;
        std::cin >> votee;
        if (type == "pick")
            machine.add_vote(voter, votee);
        else
            machine.add_delegation(voter, votee);
    }

    for (const auto &p : machine.get_votes())
    {
        cout << p.second << " " << p.first << "\n";
    }
}