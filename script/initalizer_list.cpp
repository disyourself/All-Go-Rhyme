#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;


struct element
{
    int    a;
    string b;

    element () {}
    element (int a, string b) : a (a), b (b) {}
};

class buffer
{
  public:
    buffer () {}

    buffer (initializer_list<element> &&elements)
        : m_elements (elements) {}

    vector<element> &
    GetElement ()
    {
        return m_elements;
    }

  private:
    vector<element> m_elements;
};


int
main ()
{
    element a (3, "abc");
    element b (111, "efg");

    // buffer (initializer_list<element> & elements)
    initializer_list<element> ilist = { a, b };
    buffer                    buf   = { ilist };

    // buffer (initializer_list<element> &&elements)
    buffer buf2 = { a, b };
    buffer buf4 = std::move (ilist);

    // buffer (initializer_list<element> elements)
    buffer buf3
        = { a, b };
}