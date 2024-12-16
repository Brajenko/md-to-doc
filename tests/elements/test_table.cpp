#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/Table.h"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Text.h"
#include <nlohmann/json.hpp>

TEST_CASE("Table to_json function", "[Table]") {
    // Create an instance of your Table class
    Paragraph paragraph1;
    paragraph1.add_element(Text("Data1"));
    Paragraph paragraph2;
    paragraph2.add_element(Text("Data2"));
    Paragraph paragraph3;
    paragraph3.add_element(Text("Header1"));
    Paragraph paragraph4;
    paragraph4.add_element(Text("Header2"));

    std::vector<ElementContainer<Paragraph> > rows;
    ElementContainer<Paragraph> row1;
    row1.add_element(paragraph1);
    row1.add_element(paragraph2);
    rows.push_back(row1);

    TableHeaders headers;
    headers.add_element(paragraph3);
    headers.add_element(paragraph4);
    Table table(rows, headers);

    // Convert the table to JSON
    nlohmann::json json = table.to_json();

    // Define the expected JSON output
    nlohmann::json expectedJson;
    expectedJson["type"] = "table";
    expectedJson["headers"] = headers.to_json();
    expectedJson["elements"] = nlohmann::json::array({nlohmann::json::array()});
    expectedJson["elements"][0].push_back(paragraph1.to_json());
    expectedJson["elements"][0].push_back(paragraph2.to_json());

    // Compare the actual JSON output with the expected output
    REQUIRE(json == expectedJson);
}
