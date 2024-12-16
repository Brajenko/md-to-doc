#include <catch2/catch_all.hpp>
#include <md_to_doc/elements/Blockquote.h>
#include <nlohmann/json.hpp>

TEST_CASE("Blockquote to_json() method works correctly", "[Blockquote]") {
    Paragraph p;
    p.add_element(Text("This is a blockquote."));
    Blockquote blockquote;
    blockquote.add_element(p);

    nlohmann::json expected_json = {
        {"type", "blockquote"},
        {
            "elements", {
                {
                    {"type", "paragraph"},
                    {
                        "elements",
                        {
                            {
                                {"type", "text"},
                                {"content", "This is a blockquote."},
                                {"url", ""},
                                {"formatting_options", nlohmann::json::array()},
                            }
                        }
                    }
                }
            }
        }
    };

    REQUIRE(blockquote.to_json() == expected_json);
}
