#ifndef __FOOBAR_VOTING_MATRIX_H__
#define __FOOBAR_VOTING_MATRIX_H__

#include <vector>
#include "types.h"

namespace foobar
{
namespace internal
{
class raw_matrix
{
  public:
    typedef std::vector<bool> bit_vector;
    raw_matrix(size_type i, size_type j);
    bit_vector::iterator operator[](size_type i) noexcept;
    bit_vector::const_iterator operator[](size_type i) const noexcept;
    size_type i_size() const noexcept;
    size_type j_size() const noexcept;

  private:
    bit_vector arr;
    size_type _i_size;
    size_type _j_size;
};
class voting_matrix
{
  public:
    voting_matrix(size_type voter_count, size_type choice_count);
    void add_vote(size_type voter, size_type choice);
    void add_delegate(size_type voter, size_type choice);
    std::vector<size_type> get_votes() const;

  private:
    size_type count_supporters(size_type voter) const;

    raw_matrix matrix;
    raw_matrix choices;
};
} // namespace internal
} // namespace foobar

#endif