#include "catch2/catch_all.hpp"
#include "md_to_doc/elements/HorizontalRule.h"


TEST_CASE("HorizontalRule to_json() method works correctly", "[HorizontalRule]") {
    HorizontalRule hr;
    nlohmann::json expected_json = {
        {"type", "horizontal_rule"}
    };
    REQUIRE(hr.to_json() == expected_json);
}
