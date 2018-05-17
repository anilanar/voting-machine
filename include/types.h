#ifndef __FOOBAR_TYPES_H__
#define __FOOBAR_TYPES_H__

#include <vector>
#include <unordered_map>
#include <utility>
#include <string>

namespace foobar
{
typedef size_t size_type;
typedef std::pair<std::string, size_type> vote_count;

namespace internal
{
typedef std::vector<const std::string *> ptr_vector;
typedef std::unordered_map<std::string, size_type> lookup_map;
} // namespace internal

} // namespace foobar

#endif