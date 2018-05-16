#ifndef __FOOBAR_TYPES_H__
#define __FOOBAR_TYPES_H__

#include <vector>
#include <unordered_map>
#include <string>

namespace foobar
{
typedef size_t size_type;
namespace internal
{
typedef std::vector<const std::string *> ptr_vector;
typedef std::unordered_map<std::string, size_type> lookup_map;
} // namespace internal
} // namespace foobar

#endif