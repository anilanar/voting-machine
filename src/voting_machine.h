#ifndef __FOOBAR_VOTING_MACHINE_H__
#define __FOOBAR_VOTING_MACHINE_H__

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#include "types.h"

namespace foobar
{
class voting_machine
{
  public:
    void add_vote(const std::string &voter, const std::string &choice);
    void add_delegation(const std::string &voter, const std::string &delegate);
    std::vector<std::pair<std::string, size_type>> get_votes() const;

  private:
    typedef std::vector<const std::string *> key_vector;
    enum instruction_type
    {
        VOTE,
        DELEGATION,
    };
    struct instruction
    {
        instruction_type type;
        size_type voter;
        size_type votee;
    };

    internal::ptr_vector voters;
    internal::ptr_vector choices;
    internal::lookup_map voters_map;
    internal::lookup_map choices_map;
    std::vector<instruction> instructions;
};
} // namespace foobar

#endif