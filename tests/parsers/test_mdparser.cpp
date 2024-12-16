#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "md_to_doc/parsers/md/MDParser.h"
#include <sstream>
#include <iostream>
#include "md_to_doc/elements/Text.h"

TEST_CASE("HeaderParser parses headers correctly", "[HeaderParser]") {
    md_parser::HeaderParser parser;
    std::string line = "# Header";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Header>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    REQUIRE(result->get_level() == 1);
    REQUIRE(result->get_paragraph().get_elements().size() == 1);
    auto result_text = result->get_paragraph().get_elements().front();
    REQUIRE(result_text.get_content() == "Header");
}

TEST_CASE("BlockquoteParser parses blockquotes correctly", "[BlockquoteParser]") {
    md_parser::BlockquoteParser parser;
    const std::string line = "> Blockquote";
    REQUIRE(parser.parse(line) == md_parser::ONE_MORE_LINE);
    auto result = std::dynamic_pointer_cast<Blockquote>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_elements().front().get_content() == "Blockquote");
}

TEST_CASE("CodeBlockParser parses code blocks correctly", "[CodeBlockParser]") {
    md_parser::CodeBlockParser parser;
    const std::string line = "```Code Block```";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<CodeBlock>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    REQUIRE(result->get_elements().front() == "Code Block");
}

TEST_CASE("ParagraphParser parses paragraphs correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "This is a paragraph.";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is a paragraph.");
}

TEST_CASE("ParagraphParser parses bold text correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "**This is bold text**";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is bold text");
    REQUIRE(result_text.get_formatting_options() == std::set{BOLD});
}

TEST_CASE("ParagraphParser parses italic text correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "_This is italic text_";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is italic text");
    REQUIRE(result_text.get_formatting_options() == std::set{ITALIC});
}

TEST_CASE("ParagraphParser parses inline code correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "`This is inline code`";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is inline code");
    REQUIRE(result_text.get_formatting_options() == std::set{CODE});
}

TEST_CASE("ParagraphParser parses links correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "[This is a link](http://example.com)";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is a link");
    REQUIRE(result_text.get_url() == "http://example.com");
    REQUIRE(result_text.get_formatting_options() == std::set{LINK});
}

TEST_CASE("ParagraphParser parses images correctly", "[ParagraphParser]") {
    md_parser::ParagraphParser parser;
    std::string line = "![This is an image](http://example.com/image.png)";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<Paragraph>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto result_text = result->get_elements().front();
    REQUIRE(result_text.get_content() == "This is an image");
    REQUIRE(result_text.get_url() == "http://example.com/image.png");
    REQUIRE(result_text.get_formatting_options() == std::set{IMAGE});
}

TEST_CASE("TableParser parses tables correctly", "[TableParser]") {
    md_parser::TableParser parser;
    // REQUIRE(parser.parse(line) == FINISHED);
    parser.parse("| Header1 | Header2 |");
    parser.parse("|---------|---------|");
    parser.parse("| Cell1   | Cell2   |");
    auto result = std::dynamic_pointer_cast<Table>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto headers = result->get_headers()->get_elements();
    REQUIRE(headers.size() == 2);
    REQUIRE(headers[0].get_elements().front().get_content()== "Header1");
    REQUIRE(headers[1].get_elements().front().get_content() == "Header2");
}

TEST_CASE("ListParser parses lists correctly", "[ListParser]") {
    md_parser::ListParser parser;
    parser.parse("- Item 1");
    parser.parse("- Item 2");
    auto result = std::dynamic_pointer_cast<List>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
    auto items = result->get_elements();
    REQUIRE(items.size() == 2);
    REQUIRE(items[0].get_elements()[0].get_content() == "Item 1");
    REQUIRE(items[1].get_elements()[0].get_content() == "Item 2");
}

TEST_CASE("HorizontalRuleParser parses horizontal rules correctly", "[HorizontalRuleParser]") {
    md_parser::HorizontalRuleParser parser;
    const std::string line = "---";
    REQUIRE(parser.parse(line) == md_parser::FINISHED);
    auto result = std::dynamic_pointer_cast<HorizontalRule>(parser.get_parsing_result());
    REQUIRE(result != nullptr);
}

TEST_CASE("MdParser parses document correctly", "[MdParser]") {
    md_parser::MdParser parser;
    std::istringstream input_stream("# Header\nParagraph\n```\nCode Block\n```\n## Header\n1. fsdlfksd\n2. fsdf\n");
    Document doc = parser.parse(input_stream);
    REQUIRE(doc.get_elements().size() == 5);
    REQUIRE(
        std::dynamic_pointer_cast<Header>(doc.get_elements()[0])->get_paragraph().get_elements().front()
        .get_content() == "Header")
    ;
    REQUIRE(
        std::dynamic_pointer_cast<Paragraph>(doc.get_elements()[1])->get_elements().front().get_content(
        ) == "Paragraph");
    REQUIRE(
        std::dynamic_pointer_cast<CodeBlock>(doc.get_elements()[2])->get_elements().front() == "Code Block"
    );
    REQUIRE(
        std::dynamic_pointer_cast<Header>(doc.get_elements()[3])->get_paragraph().get_elements().front()
        .get_content() == "Header"
    );
    REQUIRE(std::dynamic_pointer_cast<Header>(doc.get_elements()[3])->get_level() == 2);
}
