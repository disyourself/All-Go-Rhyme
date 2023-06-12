
#include <cstddef>
#include <type_traits>

struct AnyType
{
    template <class T>
    operator T();
};

template <typename T, typename = void, typename... Args>
struct CountMember
{
    constexpr static std::size_t value = sizeof...(Args) - 1;
};

template <typename T, typename... Args>
struct CountMember<T, std::void_t<decltype(T{Args{}...})>, Args...>
{
    constexpr static size_t value = CountMember<T, void, Args..., AnyType>::value;
};

int main()
{
    struct Test
    {
        int a;
        int b;
        int c;
        int d;
    };

    CountMember<Test>();
}
