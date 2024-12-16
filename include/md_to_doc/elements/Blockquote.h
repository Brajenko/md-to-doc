#ifndef BLOCKQUOTE_H
#define BLOCKQUOTE_H

#include "ElementContainer.h"
#include "Paragraph.h"

class Blockquote final : public ElementContainer<Paragraph> {
public:
    Blockquote() = default;

    explicit Blockquote(const std::vector<Paragraph> &elements_) : ElementContainer(elements_) {
    }

    ~Blockquote() override = default;

    auto to_json() -> nlohmann::json override;
};

#endif //BLOCKQUOTE_H
