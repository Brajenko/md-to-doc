#include <catch2/catch_all.hpp>
#include <md_to_doc/elements/CodeBlock.h>
#include <nlohmann/json.hpp>

TEST_CASE("CodeBlock to_json() method works correctly", "[CodeBlock]") {
    CodeBlock code_block;
    code_block.add_element("Sample code");

    nlohmann::json expected_json = {
        {"type", "code_block"},
        {"elements", {"Sample code"}}
    };

    REQUIRE(code_block.to_json() == expected_json);
}
