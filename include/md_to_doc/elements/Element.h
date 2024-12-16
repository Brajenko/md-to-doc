#ifndef ELEMENT_H
#define ELEMENT_H
#include <nlohmann/json.hpp>

class Element {
public:
    Element();

    Element(const Element &) = default;

    Element &operator=(const Element &) = default;

    virtual ~Element() = default;

    virtual auto to_json() -> nlohmann::json = 0;
};


#endif //ELEMENT_H
