#ifndef TABLEHEADERS_H
#define TABLEHEADERS_H
#include "ElementContainer.h"
#include "Paragraph.h"


class TableHeaders final : public ElementContainer<Paragraph> {
public:
    auto to_json() -> nlohmann::json override;
};


#endif //TABLEHEADERS_H
