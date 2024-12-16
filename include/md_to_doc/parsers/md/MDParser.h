#ifndef MDPARSER_H
#define MDPARSER_H

#include <memory>
#include <string>

#include "md_to_doc/elements/Blockquote.h"
#include "md_to_doc/elements/CodeBlock.h"
#include "md_to_doc/elements/Table.h"
#include "md_to_doc/elements/List.h"
#include "md_to_doc/elements/Document.h"
#include "md_to_doc/elements/Header.h"
#include "md_to_doc/elements/Element.h"
#include "md_to_doc/parsers/Parser.h"


namespace md_parser {
    enum PARSING_STATUS {
        ONE_MORE_LINE,
        FINISHED,
        ERROR,
        ALREADY_FINISHED,
    };

    class ElementParser {
    public:
        ElementParser() = default;

        virtual ~ElementParser() = default;

        virtual auto parse(const std::string &line) -> PARSING_STATUS = 0;

        auto static is_first_line(const std::string &line) -> bool;

        virtual const auto get_parsing_result() -> std::shared_ptr<Element> = 0;
    };


    class HeaderParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        auto static get_level(const std::string &line) -> int;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<Header> result = std::make_shared<Header>();
    };

    class BlockquoteParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<Blockquote> result = std::make_shared<Blockquote>();
    };

    class CodeBlockParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<CodeBlock> result = std::make_shared<CodeBlock>();
        bool block_started = false;
    };

    class ParagraphParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<Paragraph> result = std::make_shared<Paragraph>();
    };

    class TableParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<Table> result = std::make_shared<Table>();
        bool header_done = false;
    };


    class ListParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<List> result = std::make_shared<List>();
    };


    class HorizontalRuleParser final : public ElementParser {
    public:
        auto parse(const std::string &line) -> PARSING_STATUS override;

        auto static is_first_line(const std::string &line) -> bool;

        const auto get_parsing_result() -> std::shared_ptr<Element> override { return result; }

    private:
        std::shared_ptr<HorizontalRule> result = std::make_shared<HorizontalRule>();
    };


    class MdParser final : Parser {
    public:
        ~MdParser() override = default;

        Document parse(std::istream &input_stream) override;

    private:
        auto static get_parser(const std::string &line) -> std::unique_ptr<ElementParser>;
    };
}
#endif //MDPARSER_H
