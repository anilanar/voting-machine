#include "voting_matrix.h"

#include <stack>

using namespace foobar;

VotingMatrix::VotingMatrix(size_type voterCount, size_type choiceCount)
    : matrix(voterCount), choices(choiceCount, {false, 0}) {}

void VotingMatrix::AddVote(size_type voter, size_type choice)
{
    auto &_choice = this->choices[choice];
    _choice.hasVoter = true;
    _choice.voter = voter;
}

void VotingMatrix::AddDelegate(size_type voter, size_type delegate)
{
    this->matrix[delegate][voter] = true;
}

std::vector<size_type> VotingMatrix::GetVotes()
{
    auto result = std::vector<size_type>(this->choices.size(), 0);
    auto iter = result.begin();
    for (auto choice : this->choices)
    {
        *iter = choice.hasVoter
                    ? this->CountSupporters(choice.voter)
                    : 0;
        iter++;
    }
    return result;
}

/**
 * Typical breadth-first traversal, counting the size of support-tree
 */
size_type VotingMatrix::CountSupporters(size_type supportee)
{
    auto count = 0;
    auto stack = std::vector<size_type>();
    stack.reserve(this->matrix.size());
    stack.push_back(supportee);

    while (stack.size() > 0)
    {
        supportee = stack.back();
        stack.pop_back();
        count++;

        auto supporters = this->matrix[supportee];
        for (auto i = 0; i < this->matrix.size(); i++)
        {
            auto supporter = supporters[i];
            if (supporter == true) {
                stack.push_back(i);
            }
        }
    }
    return count;
}

Matrix::Matrix(size_type size) : arr(size), _size(size) {}

Matrix::Vector::iterator Matrix::operator[](size_type i)
{
    return this->arr.begin() + (i * this->size);
}

Matrix::Vector::const_iterator Matrix::operator[](size_type i) const
{
    return this->arr.begin() + i;
}

size_type Matrix::size() const noexcept
{
    return this->_size;
}