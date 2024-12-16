#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/Header.h"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Text.h"

TEST_CASE("Header class tests", "[Header]") {
    Paragraph paragraph;
    paragraph.add_element(Text("This is a header paragraph."));
    const int level = 1;
    const Header header(paragraph, level);

    SECTION("Constructor initializes correctly") {
        REQUIRE(header.get_level() == level);
        REQUIRE(
            header.get_paragraph().get_elements().front().get_content() ==
            "This is a header paragraph.");
    }

    SECTION("Get level returns correct value") {
        REQUIRE(header.get_level() == level);
    }

    SECTION("Get paragraph returns correct value") {
        REQUIRE(
            header.get_paragraph().get_elements().front().get_content() ==
            "This is a header paragraph.");
    }
}
