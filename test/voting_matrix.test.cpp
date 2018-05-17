#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include "voting_matrix.h"

namespace
{
using namespace foobar::internal;
using namespace testing;

TEST(raw_matrix, Reports_Correct_Size)
{
    raw_matrix m(2, 3);
    EXPECT_EQ(m.i_size(), 2);
    EXPECT_EQ(m.j_size(), 3);
}

TEST(raw_matrix, Init_To_False)
{
    raw_matrix m(2, 3);
    EXPECT_EQ(m[0][0], false);
    EXPECT_EQ(m[1][2], false);
}

TEST(raw_matrix, Access_Nth_Element)
{
    raw_matrix m(2, 3);
    m[0][1] = true;
    m[1][2] = true;
    EXPECT_EQ(m[0][0], false);
    EXPECT_EQ(m[0][1], true);
    EXPECT_EQ(m[1][2], true);
}

TEST(voting_matrix, Votes_List_Has_Correct_Vote_Counts)
{
    voting_matrix m(4, 4);
    m.add_vote(0, 1);
    m.add_vote(1, 2);
    m.add_vote(2, 3);
    m.add_vote(3, 1);
    auto votes = m.get_votes();
    ASSERT_EQ(votes.size(), 4);
    EXPECT_THAT(votes, ElementsAre(0, 2, 1, 1));
}

TEST(voting_matrix, Ignores_Circular_Delegations)
{
    voting_matrix m(4, 1);
    m.add_delegate(0, 1);
    m.add_delegate(1, 2);
    m.add_delegate(2, 0);
    m.add_vote(3, 0);

    auto votes = m.get_votes();
    ASSERT_EQ(votes.size(), 1);
    EXPECT_EQ(votes[0], 1);
}
}