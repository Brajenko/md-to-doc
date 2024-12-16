#include <catch2/catch_all.hpp>
#include <md_to_doc/elements/List.h>
#include <md_to_doc/elements/Paragraph.h>
#include <nlohmann/json.hpp>

TEST_CASE("List to_json() method works correctly", "[List]") {
    Paragraph p1;
    p1.add_element(Text("First item"));
    Paragraph p2;
    p2.add_element(Text("Second item"));

    List list;
    list.add_element(p1);
    list.add_element(p2);
    list.set_is_ordered(true);

    nlohmann::json expected_json = {
        {"type", "list"},
        {"is_ordered", true},
        {
            "elements", {
                {
                    {"type", "paragraph"}, {
                        "elements", {
                            {
                                {"type", "text"}, {"content", "First item"}, {"url", ""},
                                {"formatting_options", nlohmann::json::array()}
                            }
                        }
                    }
                },
                {
                    {"type", "paragraph"}, {
                        "elements", {
                            {
                                {"type", "text"}, {"content", "Second item"}, {"url", ""},
                                {"formatting_options", nlohmann::json::array()}
                            }
                        }
                    }
                }
            }
        }
    };

    REQUIRE(list.to_json() == expected_json);
}
