#ifndef ELEMENTCONTAINER_H
#define ELEMENTCONTAINER_H

#include <vector>

#include "Element.h"

template<typename T>
class ElementContainer : public Element {
public:
    ElementContainer() = default;

    explicit ElementContainer(const std::vector<T> &elements_) : elements(elements_) {
    }

    ElementContainer(const ElementContainer &other) = default;

    ElementContainer &operator=(const ElementContainer &other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }

    ElementContainer &operator+=(const ElementContainer &other) {
        elements.insert(elements.end(), other.elements.begin(), other.elements.end());
        return *this;
    }

    ElementContainer &operator+=(const T &element) {
        elements.push_back(element);
        return *this;
    }

    ~ElementContainer() override = default;

    auto add_element(T element) -> void {
        elements.push_back(element);
    }

    auto get_elements() -> std::vector<T> {
        return elements;
    }

    auto set_elements(const std::vector<T> &elements_) -> void {
        elements = elements_;
    }

    [[nodiscard]] auto is_empty() const -> bool {
        return elements.empty();
    }

    auto to_json() -> nlohmann::json override { return nlohmann::json{}; }

protected:
    std::vector<T> elements;
};

#endif //ELEMENTCONTAINER_H
