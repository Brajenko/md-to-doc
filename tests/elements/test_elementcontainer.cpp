#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/ElementContainer.h"
#include "md_to_doc/elements/Text.h"

TEST_CASE("ElementContainer class tests", "[ElementContainer]") {
    ElementContainer<Text> container;

    SECTION("Constructor initializes correctly") {
        REQUIRE(container.get_elements().empty());
    }

    SECTION("Add element works correctly") {
        Text text("Sample text");
        container.add_element(text);
        REQUIRE(container.get_elements().size() == 1);
        REQUIRE(container.get_elements().front().get_content() == "Sample text");
    }

    SECTION("Set elements works correctly") {
        Text text1("Text 1");
        Text text2("Text 2");
        std::vector<Text> elements = {text1, text2};
        container.set_elements(elements);
        REQUIRE(container.get_elements().size() == 2);
        REQUIRE(container.get_elements()[0].get_content() == "Text 1");
        REQUIRE(container.get_elements()[1].get_content() == "Text 2");
    }

    SECTION("Get elements returns correct value") {
        Text text1("Text 1");
        Text text2("Text 2");
        container.add_element(text1);
        container.add_element(text2);
        auto elements = container.get_elements();
        REQUIRE(elements.size() == 2);
        REQUIRE(elements[0].get_content() == "Text 1");
        REQUIRE(elements[1].get_content() == "Text 2");
    }

    SECTION("Operator += works correctly with another container") {
        Text text1("Text 1");
        Text text2("Text 2");
        ElementContainer<Text> other_container;
        other_container.add_element(text1);
        other_container.add_element(text2);
        container += other_container;
        REQUIRE(container.get_elements().size() == 2);
        REQUIRE(container.get_elements()[0].get_content() == "Text 1");
        REQUIRE(container.get_elements()[1].get_content() == "Text 2");
    }

    SECTION("Operator += works correctly with a single element") {
        Text text("Sample text");
        container += text;
        REQUIRE(container.get_elements().size() == 1);
        REQUIRE(container.get_elements().front().get_content() == "Sample text");
    }
}
