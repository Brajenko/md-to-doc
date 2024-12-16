#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/Text.h"

TEST_CASE("Text class tests", "[Text]") {
    std::string content = "This is a text element.";
    Text text(content);

    SECTION("Constructor initializes correctly") {
        REQUIRE(text.get_content() == content);
    }

    SECTION("Get content returns correct value") {
        REQUIRE(text.get_content() == content);
    }

    SECTION("Set content updates the value correctly") {
        std::string new_content = "Updated text content.";
        text.set_content(new_content);
        REQUIRE(text.get_content() == new_content);
    }

    SECTION("Constructor with formatting options initializes correctly") {
        std::set options = {BOLD, ITALIC};
        Text formatted_text(content, options);
        REQUIRE(formatted_text.get_content() == content);
        REQUIRE(formatted_text.get_formatting_options() == options);
    }

    SECTION("Add formatting option works correctly") {
        text.add_formatting_option(BOLD);
        REQUIRE(text.get_formatting_options().count(BOLD) == 1);
    }

    SECTION("Remove formatting option works correctly") {
        text.add_formatting_option(BOLD);
        text.remove_formatting_option(BOLD);
        REQUIRE(text.get_formatting_options().count(BOLD) == 0);
    }

    SECTION("Set formatting options updates the value correctly") {
        std::set new_options = {STRIKETHROUGH, HIGHLIGHT};
        text.set_formatting_options(new_options);
        REQUIRE(text.get_formatting_options() == new_options);
    }
}
