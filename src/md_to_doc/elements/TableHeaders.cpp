#include "md_to_doc/elements/TableHeaders.h"

auto TableHeaders::to_json() -> nlohmann::json {
    nlohmann::json json = nlohmann::json::array();
    for (auto &header: elements) {
        json.push_back(header.to_json());
    }
    return json;
}
