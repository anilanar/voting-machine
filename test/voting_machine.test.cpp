#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utility>
#include "voting_machine.h"

namespace
{
using namespace foobar;
using namespace testing;

TEST(voting_machine, Counts_Votes)
{
    voting_machine machine;
    machine.add_vote("H", "X2");
    machine.add_delegation("A", "B");
    machine.add_vote("C", "X1");
    machine.add_delegation("B", "C");
    machine.add_delegation("D", "E");
    machine.add_delegation("E", "F");
    machine.add_delegation("F", "D");
    machine.add_vote("G", "X1");

    auto votes = machine.get_votes();

    EXPECT_THAT(votes, ElementsAre(
                           vote_count{"X2", 1},
                           vote_count{"X1", 4},
                           vote_count{"invalid", 3}));
}
} // namespace