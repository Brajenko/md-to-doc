#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "ElementContainer.h"
#include "Text.h"

class Paragraph final : public ElementContainer<Text> {
public:
    Paragraph() = default;

    explicit Paragraph(const std::vector<Text> &elements_) : ElementContainer(elements_) {
    }

    ~Paragraph() override = default;

    auto to_json() -> nlohmann::json override;
};

#endif //PARAGRAPH_H
