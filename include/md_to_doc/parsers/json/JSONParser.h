#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "md_to_doc/parsers/Parser.h"

namespace json_parser {
    class ElementParser {
    public:
        ElementParser() = default;

        virtual ~ElementParser() = default;

        virtual auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> = 0;
    };

    class TextParser final : public ElementParser {
    public:
        ~TextParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };


    class ParagraphParser final : public ElementParser {
    public:
        ~ParagraphParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class BlockquoteParser final : public ElementParser {
    public:
        ~BlockquoteParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class CodeBlockParser final : public ElementParser {
    public:
        ~CodeBlockParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class HeaderParser final : public ElementParser {
    public:
        ~HeaderParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class HorizontalRuleParser final : public ElementParser {
    public:
        ~HorizontalRuleParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class ListParser final : public ElementParser {
    public:
        ~ListParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class TableParser final : public ElementParser {
    public:
        ~TableParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class TableHeadersParser final : public ElementParser {
    public:
        ~TableHeadersParser() override = default;

        auto parse(const nlohmann::json &json) -> std::shared_ptr<Element> override;
    };

    class JSONParser final : public Parser {
    public:
        ~JSONParser() override = default;

        auto parse(std::istream &input_stream) -> Document override;

    private:
        static auto get_parser(const std::string &type) -> std::unique_ptr<ElementParser>;
    };

#endif //JSONPARSER_H
}
