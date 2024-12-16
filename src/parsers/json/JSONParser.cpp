#include "md_to_doc/parsers/json/JSONParser.h"

#include <iostream>

#include "md_to_doc/elements/Text.h"
#include "md_to_doc/elements/Paragraph.h"
#include "md_to_doc/elements/Blockquote.h"
#include "md_to_doc/elements/CodeBlock.h"
#include "md_to_doc/elements/Header.h"
#include "md_to_doc/elements/HorizontalRule.h"
#include "md_to_doc/elements/List.h"
#include "md_to_doc/elements/Table.h"
#include "md_to_doc/elements/TableHeaders.h"


namespace json_parser {
    auto TextParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = Text();
        result.set_content(json["content"]);
        result.set_url(json["url"]);
        auto formatting_options = std::set<FORMATTING_OPTIONS>();
        for (const auto &formatting_option: json["formatting_options"]) {
            for (const auto &pair: FORMATTING_OPTIONS_TO_STRING) {
                if (pair.second == formatting_option) {
                    formatting_options.insert(pair.first);
                }
            }
        }
        result.set_formatting_options(formatting_options);
        return std::make_shared<Text>(result);
    }


    auto ParagraphParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = Paragraph();
        auto text_parser = TextParser();
        for (const auto &element: json["elements"]) {
            result.add_element(*dynamic_cast<Text *>(text_parser.parse(element).get()));
        }
        return std::make_shared<Paragraph>(result);
    }


    auto BlockquoteParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = Blockquote();
        auto paragraph_parser = ParagraphParser();
        for (const auto &element: json["elements"]) {
            result.add_element(*std::dynamic_pointer_cast<Paragraph>(paragraph_parser.parse(element)));
        }
        return std::make_shared<Blockquote>(result);
    }


    auto CodeBlockParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = CodeBlock();
        for (const auto &element: json["elements"]) {
            result.add_element(element);
        }
        return std::make_shared<CodeBlock>(result);
    }


    auto HeaderParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = Header();
        auto paragraph_parser = ParagraphParser();
        result.set_level(json["level"]);
        result.set_paragraph(*std::dynamic_pointer_cast<Paragraph>(paragraph_parser.parse(json["paragraph"])));
        return std::make_shared<Header>(result);
    }


    auto HorizontalRuleParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = HorizontalRule();
        return std::make_shared<HorizontalRule>(result);
    }


    auto ListParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = List();
        auto paragraph_parser = ParagraphParser();
        result.set_is_ordered(json["is_ordered"]);
        for (const auto &element: json["elements"]) {
            result.add_element(*std::dynamic_pointer_cast<Paragraph>(paragraph_parser.parse(element)));
        }
        return std::make_shared<List>(result);
    }


    auto TableHeadersParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = TableHeaders();
        auto paragraph_parser = ParagraphParser();
        for (const auto &element: json) {
            result.add_element(*std::dynamic_pointer_cast<Paragraph>(paragraph_parser.parse(element)));
        }
        return std::make_shared<TableHeaders>(result);
    }


    auto TableParser::parse(const nlohmann::json &json) -> std::shared_ptr<Element> {
        auto result = Table();
        auto table_headers_parser = TableHeadersParser();
        auto paragraph_parser = ParagraphParser();
        result.set_headers(*std::dynamic_pointer_cast<TableHeaders>(table_headers_parser.parse(json["headers"])));
        for (const auto &row: json["elements"]) {
            auto ec = ElementContainer<Paragraph>();
            for (const auto &element: row) {
                ec.add_element(*std::dynamic_pointer_cast<Paragraph>(paragraph_parser.parse(element)));
            }
            result.add_element(ec);
        }

        return std::make_shared<Table>(result);
    }


    auto JSONParser::get_parser(const std::string &type) -> std::unique_ptr<ElementParser> {
        if (type == "text") {
            return std::make_unique<TextParser>();
        } else if (type == "paragraph") {
            return std::make_unique<ParagraphParser>();
        } else if (type == "blockquote") {
            return std::make_unique<BlockquoteParser>();
        } else if (type == "code_block") {
            return std::make_unique<CodeBlockParser>();
        } else if (type == "header") {
            return std::make_unique<HeaderParser>();
        } else if (type == "horizontal_rule") {
            return std::make_unique<HorizontalRuleParser>();
        } else if (type == "list") {
            return std::make_unique<ListParser>();
        } else if (type == "table") {
            return std::make_unique<TableParser>();
        }
        return nullptr;
    }


    auto JSONParser::parse(std::istream &input_stream) -> Document {
        nlohmann::json json = nlohmann::json::parse(input_stream);
        auto result = Document();
        for (const auto &element: json["elements"]) {
            const auto parser = get_parser(element["type"]);
            result.add_element(parser->parse(element));
        }
        return result;
    }
}
