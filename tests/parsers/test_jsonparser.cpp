#include "catch2/catch_all.hpp"
#include "md_to_doc/parsers/json/JSONParser.h"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Text.h"
#include "md_to_doc/elements/Blockquote.h"
#include "md_to_doc/elements/CodeBlock.h"
#include "md_to_doc/elements/Header.h"
#include "md_to_doc/elements/HorizontalRule.h"
#include "md_to_doc/elements/List.h"
#include "md_to_doc/elements/Table.h"
#include "md_to_doc/elements/TableHeaders.h"

#include <sstream>

TEST_CASE("JSONParser parses text element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "text",
                "content": "This is a text element.",
                "url": "",
                "formatting_options": []
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto text = std::dynamic_pointer_cast<Text>(result);
    REQUIRE(text != nullptr);
    REQUIRE(text->get_content() == "This is a text element.");
}

TEST_CASE("JSONParser parses paragraph element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "paragraph",
                "elements": [
                    {
                        "type": "text",
                        "content": "This is a text element.",
                        "url": "",
                        "formatting_options": []
                    }
                ]
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto paragraph = std::dynamic_pointer_cast<Paragraph>(result);
    REQUIRE(paragraph != nullptr);
    REQUIRE(paragraph->get_elements().front().get_content() == "This is a text element.");
}

TEST_CASE("JSONParser parses blockquote element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "blockquote",
                "elements": [
                    {
                        "type": "paragraph",
                        "elements": [
                            {
                                "type": "text",
                                "content": "This is a text element.",
                                "url": "",
                                "formatting_options": []
                            }
                        ]
                    }
                ]
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto blockquote = std::dynamic_pointer_cast<Blockquote>(result);
    auto paragraph = blockquote->get_elements().front();
    REQUIRE(blockquote != nullptr);
    REQUIRE(paragraph.get_elements().front().get_content() == "This is a text element.");
}

TEST_CASE("JSONParser parses code block element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "code_block",
                "elements": ["Code Block"]
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto code_block = std::dynamic_pointer_cast<CodeBlock>(result);
    REQUIRE(code_block != nullptr);
    REQUIRE(code_block->get_elements().front() == "Code Block");
}

TEST_CASE("JSONParser parses header element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "header",
                "level": 1,
                "paragraph": {
                    "type": "paragraph",
                    "elements": [
                        {
                            "type": "text",
                            "content": "Header",
                            "url": "",
                            "formatting_options": []
                        }
                    ]
                }
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto header = std::dynamic_pointer_cast<Header>(result);
    REQUIRE(header != nullptr);
    REQUIRE(header->get_level() == 1);
    REQUIRE(header->get_paragraph().get_elements().front().get_content() == "Header");
}

TEST_CASE("JSONParser parses horizontal rule element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "horizontal_rule"
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto horizontal_rule = std::dynamic_pointer_cast<HorizontalRule>(result);
    REQUIRE(horizontal_rule != nullptr);
}

TEST_CASE("JSONParser parses list element correctly", "[JSONParser]") {
    std::string json_str = R"({
        "type": "document",
        "elements": [
            {
                "type": "list",
                "is_ordered": false,
                "elements": [
                    {
                        "type": "paragraph",
                        "elements": [
                            {
                                "type": "text",
                                "content": "Item 1",
                                "url": "",
                                "formatting_options": []
                            }
                        ]
                    },
                    {
                        "type": "paragraph",
                        "elements": [
                            {
                                "type": "text",
                                "content": "Item 2",
                                "url": "",
                                "formatting_options": []
                            }
                        ]
                    }
                ]
            }
        ]
    })";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto list = std::dynamic_pointer_cast<List>(result);
    REQUIRE(list != nullptr);
    REQUIRE(list->get_elements().size() == 2);
    REQUIRE(list->get_elements()[0].get_elements().front().get_content() == "Item 1");
    REQUIRE(list->get_elements()[1].get_elements().front().get_content() == "Item 2");
}

TEST_CASE("JSONParser parses table element correctly", "[JSONParser]") {
    std::string json_str = R"({
  "type": "document",
  "elements": [
    {
            "elements": [
                [
                    {
                        "elements": [
                            {
                                "content": "Cell1",
                                "formatting_options": [],
                                "type": "text",
                                "url": ""
                            }
                        ],
                        "type": "paragraph"
                    },
                    {
                        "elements": [
                            {
                                "content": "Cell2",
                                "formatting_options": [],
                                "type": "text",
                                "url": ""
                            }
                        ],
                        "type": "paragraph"
                    }
                ]
            ],
            "headers": [
                {
                    "elements": [
                        {
                            "content": "Header1",
                            "formatting_options": [],
                            "type": "text",
                            "url": ""
                        }
                    ],
                    "type": "paragraph"
                },
                {
                    "elements": [
                        {
                            "content": "Header2",
                            "formatting_options": [],
                            "type": "text",
                            "url": ""
                        }
                    ],
                    "type": "paragraph"
                }
            ],
            "type": "table"
        }
  ]
})";
    std::istringstream input_stream(json_str);
    json_parser::JSONParser parser;
    auto result = parser.parse(input_stream).get_elements().front();
    auto table = std::dynamic_pointer_cast<Table>(result);
    REQUIRE(table != nullptr);
    auto headers = table->get_headers()->get_elements();
    REQUIRE(headers.size() == 2);
    REQUIRE(headers[0].get_elements().front().get_content() == "Header1");
    REQUIRE(headers[1].get_elements().front().get_content() == "Header2");
    auto rows = table->get_elements();
    REQUIRE(rows.size() == 1);
    auto cells = rows[0].get_elements();
    REQUIRE(cells.size() == 2);
    REQUIRE(cells[0].get_elements().front().get_content() == "Cell1");
    REQUIRE(cells[1].get_elements().front().get_content() == "Cell2");
}
