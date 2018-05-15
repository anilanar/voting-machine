#include <vector>

namespace foobar
{

typedef unsigned int size_type;

class VotingMatrix
{
  public:
    VotingMatrix(size_type voterCount, size_type choiceCount);
    void AddVote(size_type voter, size_type choice);
    void AddDelegate(size_type voter, size_type choice);
    std::vector<size_type> GetVotes();

  private:
    size_type CountSupporters(size_type voter);

    Matrix matrix;
    std::vector<Choice> choices;
};
class Matrix
{
  public:
    typedef std::vector<bool> Vector;
    Matrix(size_type size);
    Vector::iterator operator[](size_type i);
    Vector::const_iterator operator[](size_type i) const;
    size_type size() const noexcept;

  private:
    Vector arr;
    size_type _size;
};
struct Choice
{
    bool hasVoter;
    size_type voter;
};
} // namespace foobar