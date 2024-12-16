#include "md_to_doc/elements/Table.h"

#include <utility>

Table::Table(const std::vector<ElementContainer<Paragraph> > &rows_, TableHeaders headers_)
    : ElementContainer(rows_), headers(std::move(headers_)) {
}

auto Table::get_headers() -> TableHeaders * {
    return &headers;
}

auto Table::set_headers(const TableHeaders &headers_) -> void {
    headers = headers_;
}

auto Table::to_json() -> nlohmann::json {
    nlohmann::json json;
    json["type"] = "table";
    json["headers"] = headers.to_json();
    json["elements"] = nlohmann::json::array();
    for (auto &element: elements) {
        nlohmann::json nested_elements = nlohmann::json::array();
        for (auto &nested_element: element.get_elements()) {
            nested_elements.push_back(nested_element.to_json());
        }
        json["elements"].push_back(nested_elements);
    }
    return json;
}
