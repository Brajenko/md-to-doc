#include "md_to_doc/elements/Document.h"

auto Document::to_json() -> nlohmann::json {
    nlohmann::json json;
    json["type"] = "document";
    json["elements"] = nlohmann::json::array();
    for (const auto &element: elements) {
        json["elements"].push_back(element->to_json());
    }
    return json;
}
