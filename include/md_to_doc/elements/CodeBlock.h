#ifndef CODEBLOCK_H
#define CODEBLOCK_H

#include <string>
#include "ElementContainer.h"

class CodeBlock final
        : public ElementContainer<std::string> {
public:
    CodeBlock() = default;

    explicit CodeBlock(const std::vector<std::string> &lines_) : ElementContainer(lines_) {
    }

    ~CodeBlock() override = default;

    auto to_json() -> nlohmann::json override;
};

#endif //CODEBLOCK_H
