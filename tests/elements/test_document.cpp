#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/Document.h"
#include "md_to_doc/elements/Header.h"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Text.h"
#include <nlohmann/json.hpp>


TEST_CASE("Document to_json function", "[Document]") {
    const auto paragraph = std::make_shared<Paragraph>();
    paragraph->add_element(Text("This is a paragraph."));
    const auto header = std::make_shared<Header>(*paragraph, 1);

    Document document;
    document.add_element(header);
    document.add_element(paragraph);

    nlohmann::json expectedJson;
    expectedJson["type"] = "document";
    expectedJson["elements"] = nlohmann::json::array();
    expectedJson["elements"].push_back(header->to_json());
    expectedJson["elements"].push_back(paragraph->to_json());

    REQUIRE(document.to_json() == expectedJson);
}
