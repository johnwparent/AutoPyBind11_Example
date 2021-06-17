#include <map>
#include <deque>
#include <unordered_map>

class El {
public:
    El() = delete;
    El(int v) : a(v) { }

    int a;
};

std::ostream & operator<<(std::ostream &s, El const&v) {
    s << "El{" << v.a << '}';
    return s;
}

/// Issue #487: binding std::vector<E> with E non-copyable
class E_nc {
public:
    explicit E_nc(int i) : value{i} {}
    E_nc(const E_nc &) = delete;
    E_nc &operator=(const E_nc &) = delete;
    E_nc(E_nc &&) = default;
    E_nc &operator=(E_nc &&) = default;

    int value;
};

template <class Container> Container *one_to_n(int n) {
    auto v = new Container();
    for (int i = 1; i <= n; i++)
        v->emplace_back(i);
    return v;
}

template <class Map> Map *times_ten(int n) {
    auto m = new Map();
    for (int i = 1; i <= n; i++)
        m->emplace(int(i), E_nc(10*i));
    return m;
}

template <class NestMap> NestMap *times_hundred(int n) {
    auto m = new NestMap();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            (*m)[i].emplace(int(j*10), E_nc(100*j));
    return m;
}