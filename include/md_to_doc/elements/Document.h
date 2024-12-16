#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "ElementContainer.h"
#include "HorizontalRule.h"


class Document final : public ElementContainer<std::shared_ptr<Element> > {
public:
    auto to_json() -> nlohmann::json override;
};


#endif //DOCUMENT_H
