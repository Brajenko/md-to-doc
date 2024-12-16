#include "md_to_doc/elements/Blockquote.h"

auto Blockquote::to_json() -> nlohmann::json {
    nlohmann::json json;
    json["type"] = "blockquote";
    json["elements"] = nlohmann::json::array();
    for (auto &element: elements) {
        json["elements"].push_back(element.to_json());
    }
    return json;
}
