#include "voting_machine.h"
#include "voting_matrix.h"

using namespace foobar;

size_type get_index(const std::string &elem, internal::ptr_vector &vec, internal::lookup_map &map);

void voting_machine::add_vote(const std::string &voter, const std::string &choice)
{
    auto voter_idx = get_index(voter, this->voters, this->voters_map);
    auto choice_idx = get_index(choice, this->choices, this->choices_map);
    this->instructions.push_back({VOTE, voter_idx, choice_idx});
}

void voting_machine::add_delegation(const std::string &voter, const std::string &delegate)
{
    auto voter_idx = get_index(voter, this->voters, this->voters_map);
    auto delegate_idx = get_index(delegate, this->voters, this->voters_map);
    this->instructions.push_back({DELEGATION, voter_idx, delegate_idx});
}

std::vector<std::pair<std::string, size_type>> voting_machine::get_votes() const
{
    internal::voting_matrix matrix(this->voters.size(), this->choices.size());
    for (const auto &i : this->instructions)
    {
        if (i.type == VOTE)
            matrix.add_vote(i.voter, i.votee);
        else
            matrix.add_delegate(i.voter, i.votee);
    }

    auto votes = matrix.get_votes();
    std::vector<std::pair<std::string, size_type>> result(votes.size() + 1);
    auto result_iter = result.begin();
    auto total_votes = 0;
    for (auto choice_idx = 0; choice_idx < votes.size(); choice_idx++)
    {
        result_iter->first = *this->choices[choice_idx];
        auto vote_count = votes[choice_idx];
        result_iter->second = vote_count;
        total_votes += vote_count;
        result_iter++;
    }
    result_iter->first = "invalid";
    result_iter->second = this->voters.size() - total_votes;
    return result;
}

size_type get_index(const std::string &elem, internal::ptr_vector &vec, internal::lookup_map &map)
{
    auto elem_idx = static_cast<size_type>(vec.size());
    auto elem_insertion = map.insert({elem, elem_idx});
    if (elem_insertion.second == true)
    {
        auto iter = elem_insertion.first;
        vec.push_back(&iter->first);
    }
    else
    {
        elem_idx = elem_insertion.first->second;
    }

    return elem_idx;
}