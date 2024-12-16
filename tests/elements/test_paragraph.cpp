#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Text.h"

#include <iostream>

TEST_CASE("Paragraph class tests", "[Paragraph]") {
    Paragraph paragraph;

    SECTION("Add element works correctly") {
        const Text text("This is a text element.");
        paragraph.add_element(text);
        REQUIRE(paragraph.get_elements().front().get_content() == "This is a text element.");
    }

    SECTION("Get text returns correct value") {
        const Text text("This is a text element.");
        paragraph.add_element(text);
        REQUIRE(paragraph.get_elements().front().get_content() == "This is a text element.");
    }

    SECTION("to_json returns correct JSON") {
        Text text("This is a text element.");
        text.add_formatting_option(BOLD);
        paragraph.add_element(text);
        nlohmann::json json = paragraph.to_json();
        nlohmann::json expected_json = {
            {"type", "paragraph"},
            {
                "elements", nlohmann::json::array(
                    {
                        {
                            {"content", "This is a text element."},
                            {"formatting_options", nlohmann::json::array({"bold"})},
                            {"type", "text"},
                            {"url", ""}
                        }
                    }
                ),
            },
        };
        REQUIRE(json == expected_json);
    }
}
