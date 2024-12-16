#ifndef TABLE_H
#define TABLE_H

#include "ElementContainer.h"
#include "Paragraph.h"
#include "TableHeaders.h"

class Table final : public ElementContainer<ElementContainer<Paragraph> > {
public:
    Table() = default;

    explicit Table(const std::vector<ElementContainer<Paragraph> > &rows_, TableHeaders headers_);

    ~Table() override = default;

    auto get_headers() -> TableHeaders *;

    auto set_headers(const TableHeaders &headers_) -> void;

    auto to_json() -> nlohmann::json override;

private:
    TableHeaders headers;
};

#endif //TABLE_H
