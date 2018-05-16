#include "voting_matrix.h"

#include <stack>

using namespace foobar;
using namespace foobar::internal;

voting_matrix::voting_matrix(size_type voter_count, size_type choice_count)
    : matrix(voter_count, voter_count), choices(choice_count, voter_count) {}

void voting_matrix::add_vote(size_type voter, size_type choice)
{
    auto &_choice = this->choices[choice][voter] = true;
}

void voting_matrix::add_delegate(size_type voter, size_type delegate)
{
    this->matrix[delegate][voter] = true;
}

std::vector<size_type> voting_matrix::get_votes() const
{
    std::vector<size_type> result(this->choices.i_size(), 0);
    auto iter = result.begin();
    for (auto i = 0; i < this->choices.i_size(); i++)
    {
        for (auto j = 0; j < this->choices.j_size(); j++)
        {
            if (this->choices[i][j] == true)
            {
                *iter += this->count_supporters(j);
            }
        }
        iter++;
    }
    return result;
}

/**
 * Typical breadth-first traversal, counting the size of support-tree
 */
size_type voting_matrix::count_supporters(size_type supportee) const
{
    auto count = 0;
    std::vector<size_type> stack;
    stack.reserve(this->matrix.i_size());
    stack.push_back(supportee);

    while (stack.size() > 0)
    {
        supportee = stack.back();
        stack.pop_back();
        count++;

        auto supporters = this->matrix[supportee];
        for (auto i = 0; i < this->matrix.i_size(); i++)
        {
            auto supporter = supporters[i];
            if (supporter == true)
            {
                stack.push_back(i);
            }
        }
    }
    return count;
}

raw_matrix::raw_matrix(size_type i, size_type j) : arr(i * j), _i_size(i), _j_size(j) {}

raw_matrix::bit_vector::iterator raw_matrix::operator[](size_type i) noexcept
{
    return this->arr.begin() + (i * this->j_size());
}

raw_matrix::bit_vector::const_iterator raw_matrix::operator[](size_type i) const noexcept
{
    return this->arr.begin() + (i * this->j_size());
}

size_type raw_matrix::i_size() const noexcept
{
    return this->_i_size;
}

size_type raw_matrix::j_size() const noexcept
{
    return this->_j_size;
}