#ifndef HORIZONTALRULE_H
#define HORIZONTALRULE_H

#include "Element.h"

class HorizontalRule final : public Element {
public:
    HorizontalRule() = default;

    ~HorizontalRule() override = default;

    auto to_json() -> nlohmann::json override;
};

#endif //HORIZONTALRULE_H
