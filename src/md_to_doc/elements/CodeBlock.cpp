#include "md_to_doc/elements/CodeBlock.h"

auto CodeBlock::to_json() -> nlohmann::json {
    nlohmann::json json{
        {"type", "code_block"},
        {"elements", nlohmann::json::array(),}
    };
    for (auto &element: elements) {
        json["elements"].push_back(element);
    }
    return json;
}
