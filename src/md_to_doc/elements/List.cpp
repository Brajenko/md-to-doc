#include "md_to_doc/elements/List.h"

auto List::to_json() -> nlohmann::json {
    nlohmann::json json;
    json["type"] = "list";
    json["is_ordered"] = is_ordered;
    json["elements"] = nlohmann::json::array();
    for (auto &element: elements) {
        json["elements"].push_back(element.to_json());
    }
    return json;
}
