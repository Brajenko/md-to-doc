#include "md_to_doc/elements/Paragraph.h"

auto Paragraph::to_json() -> nlohmann::json {
    nlohmann::json json = {
            {"type", "paragraph"},
            {"elements", nlohmann::json::array()},
    };
    for (auto &element: elements) {
        json["elements"].push_back(element.to_json());
    }
    return json;
}
