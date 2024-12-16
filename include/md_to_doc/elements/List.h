#ifndef LIST_H
#define LIST_H

#include "ElementContainer.h"
#include "Paragraph.h"

class List final : public ElementContainer<Paragraph> {
public:
    List() = default;

    explicit List(const std::vector<Paragraph> &elements_) : ElementContainer(elements_) {
    }

    explicit List(const std::vector<Paragraph> &elements_, const bool is_ordered_) : ElementContainer(elements_),
        is_ordered(is_ordered_) {
    }

    ~List() override = default;

    [[nodiscard]] auto get_is_ordered() const -> bool {
        return is_ordered;
    }

    auto set_is_ordered(const bool is_ordered_) -> void {
        is_ordered = is_ordered_;
    }

    auto to_json() -> nlohmann::json override;

private:
    bool is_ordered{false};
};

#endif //LIST_H
