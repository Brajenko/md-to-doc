#include "md_to_doc/parsers/md/MDParser.h"

#include <algorithm>

#include <sstream>

#include "md_to_doc/elements/Document.h"

#include <cctype>
#include <locale>

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    size_t pos_start = 0, pos_end;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        if (pos_end != 0 && pos_end != s.length()) {
            std::string token = s.substr(pos_start, pos_end - pos_start);
            res.push_back(token);
        }
        pos_start = pos_end + delimiter.length();
    }
    if (pos_start != s.length()) {
        res.push_back(s.substr(pos_start));
    }
    return res;
}


static void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](const unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static bool ends_with(const std::string_view str, const std::string_view suffix) {
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static bool starts_with(const std::string_view str, const std::string_view prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

static std::string remove_suffix(const std::string &s, const std::string &suffix) {
    return ends_with(s, suffix) ? s.substr(0, s.length() - suffix.length()) : s;
}

static std::string remove_prefix(const std::string &s, const std::string &prefix) {
    return starts_with(s, prefix) ? s.substr(prefix.length(), s.length()) : s;
}

namespace md_parser {
    auto ParagraphParser::parse(const std::string &line) -> PARSING_STATUS {
        std::set<FORMATTING_OPTIONS> current_options;
        std::string current_text;
        std::string current_url;
        bool is_parsing_url = false;
        size_t i = 0;
        while (i < line.size()) {
            if (line[i] == '\\') {
                if (is_parsing_url) {
                    current_url += line[i + 1];
                } else {
                    current_text += line[i + 1];
                }
                i += 2;
                continue;
            }
            if (is_parsing_url) {
                if (line[i] == ')') {
                    result->add_element(Text(current_text, current_options, current_url));
                    current_options.erase(LINK);
                    current_options.erase(IMAGE);
                    current_text = "";
                    current_url = "";
                    is_parsing_url = false;
                    i++;
                    continue;
                }
                current_url += line[i];
                i++;
                continue;
            }
            if (line[i] == '[') {
                current_options.insert(LINK);
                i++;
                continue;
            }
            if (line[i] == '!' && line[i + 1] == '[') {
                current_options.insert(IMAGE);
                i += 2;
                continue;
            }
            if (line[i] == ']' && line[i + 1] == '(' && (
                    current_options.find(LINK) != current_options.end() || current_options.find(IMAGE) !=
                    current_options.end())) {
                is_parsing_url = true;
                i += 2;
                continue;
            }
            std::optional<FORMATTING_OPTIONS> toggle_option = std::nullopt;
            if (line[i] == '*' || line[i] == '_') {
                toggle_option = line[i + 1] == line[i] ? BOLD : ITALIC;
            }
            if (line[i] == '~' && line[i + 1] == '~') {
                toggle_option = STRIKETHROUGH;
            }
            if (line[i] == '=' && line[i + 1] == '=') {
                toggle_option = HIGHLIGHT;
            }
            if (line[i] == '`') {
                toggle_option = CODE;
            }
            if (toggle_option.has_value()) {
                const bool option_on = current_options.find(toggle_option.value()) != current_options.end();
                const bool turn_on = !option_on && line[i + 1] != ' ';
                const bool turn_off = option_on && line[i - 1] != ' ';
                if (turn_on || turn_off) {
                    if (!current_text.empty()) {
                        result->add_element(Text(current_text, current_options, current_url));
                    }
                    current_text = "";
                    i += toggle_option.value() == CODE || toggle_option.value() == ITALIC ? 0 : 1;
                }
                if (turn_off) {
                    current_options.erase(toggle_option.value());
                } else if (turn_on) {
                    current_options.insert(toggle_option.value());
                }
            } else {
                current_text += line[i];
            }
            i++;
        }
        if (!current_text.empty()) {
            result->add_element(Text(current_text, current_options, current_url));
        }
        return FINISHED;
    }


    auto ParagraphParser::is_first_line(const std::string &line) -> bool {
        return true;
    }


    auto HeaderParser::parse(const std::string &line) -> PARSING_STATUS {
        const int level = get_level(line);
        result->set_level(level);
        ParagraphParser p;
        if (p.parse(line.substr(level + 1, line.size())) == ERROR) { return ERROR; }
        result->set_paragraph(dynamic_cast<Paragraph &>(*p.get_parsing_result()));
        return FINISHED;
    }

    auto HeaderParser::get_level(const std::string &line) -> int {
        int level = 0;
        while (line[level] == '#' && level != line.length()) {
            ++level;
        }
        return level != line.length() && line[level] == ' ' ? level : 0;
    }

    auto HeaderParser::is_first_line(const std::string &line) -> bool {
        return get_level(line) > 0;
    }

    auto BlockquoteParser::parse(const std::string &line) -> PARSING_STATUS {
        if (line[0] != '>') {
            return ALREADY_FINISHED;
        }
        std::size_t i = 1;
        while (line[i] == ' ') {
            i++;
        }
        ParagraphParser p;
        if (p.parse(line.substr(i, line.size())) == ERROR) { return ERROR; }
        result->add_element(*std::dynamic_pointer_cast<Paragraph>(p.get_parsing_result()));
        return ONE_MORE_LINE;
    }

    auto BlockquoteParser::is_first_line(const std::string &line) -> bool {
        return line[0] == '>';
    }

    auto CodeBlockParser::is_first_line(const std::string &line) -> bool {
        return starts_with(line, "```");
    }

    auto CodeBlockParser::parse(const std::string &line) -> PARSING_STATUS {
        if (!block_started && !starts_with(line, "```")) {
            return ERROR;
        }
        if (!block_started) {
            if (line == "```") {
                block_started = true;
                return ONE_MORE_LINE;
            }
            if (ends_with(line, "```")) {
                result->add_element(remove_prefix(remove_suffix(line, "```"), "```"));
                return FINISHED;
            }
        } else {
            if (ends_with(line, "```")) {
                result->add_element(remove_prefix(remove_suffix(line, "```"), "```"));
                return FINISHED;
            }
            result->add_element(line);
        }
        return ONE_MORE_LINE;
    }

    auto HorizontalRuleParser::is_first_line(const std::string &line) -> bool {
        if (line.length() < 3) {
            return false;
        }
        const auto chars = {'-', '*', '_'}; // TODO: вынести в константы
        return std::any_of(std::begin(chars), std::end(chars),
                           [&](const char c) { return std::count(line.begin(), line.end(), c) == line.length(); });
    }

    auto HorizontalRuleParser::parse(const std::string &line) -> PARSING_STATUS {
        return FINISHED;
    }


    auto TableParser::is_first_line(const std::string &line) -> bool {
        return line[0] == '|' && line[line.length() - 1] == '|' && line.length() >= 2;
    }

    auto TableParser::parse(const std::string &line) -> PARSING_STATUS {
        if (!starts_with(line, "|") || !ends_with(line, "|")) {
            return ALREADY_FINISHED;
        }
        std::stringstream ss(line);
        if (result->get_headers()->get_elements().empty()) {
            for (auto &header: split(line, "|")) {
                ParagraphParser p;
                trim(header);
                p.parse(header);
                result->get_headers()->add_element(*std::dynamic_pointer_cast<Paragraph>(p.get_parsing_result()));
            }
        } else if (!header_done) {
            int c = 0;
            for (auto &substr: split(line, "|")) {
                if (substr.length() < 3 || count(substr.begin(), substr.end(), '-') != substr.length()) {
                    return ERROR;
                }
                c++;
            }
            if (c != result->get_headers()->get_elements().size()) {
                return ERROR;
            }
            header_done = true;
        } else {
            ElementContainer<Paragraph> row;
            for (auto &value: split(line, "|")) {
                ParagraphParser p;
                p.parse(value);
                row.add_element(*std::dynamic_pointer_cast<Paragraph>(p.get_parsing_result()));
            }
            if (row.get_elements().size() != result->get_headers()->get_elements().size()) {
                return ALREADY_FINISHED;
            }
            result->add_element(row);
        }
        return ONE_MORE_LINE;
    }


    auto ListParser::is_first_line(const std::string &line) -> bool {
        const auto chars = {'-', '*', '+'}; //TODO: вынести в константы
        size_t i = 0;
        while (isdigit(line[i++])) {
        }
        return line[i] == ' ' || std::any_of(std::begin(chars), std::end(chars),
                                             [&](const char c) { return starts_with(line, c + " "); });
    }


    auto ListParser::parse(const std::string &line) -> PARSING_STATUS {
        if (!is_first_line(line)) {
            return ALREADY_FINISHED;
        }
        if (result->get_elements().empty()) {
            result->set_is_ordered(isdigit(line[0]));
        }
        ParagraphParser p;
        if (p.parse(
                line.substr(
                    result->get_is_ordered() ? line.find_first_of(' ', 0) : 2, line.size()
                )
            ) == ERROR) {
            return ERROR;
        }
        result->add_element(*std::dynamic_pointer_cast<Paragraph>(p.get_parsing_result()));
        return ONE_MORE_LINE;
    }


    auto MdParser::get_parser(const std::string &line) -> std::unique_ptr<ElementParser> {
        if (HeaderParser::is_first_line(line)) {
            return std::make_unique<HeaderParser>();
        }
        if (BlockquoteParser::is_first_line(line)) {
            return std::make_unique<BlockquoteParser>();
        }
        if (CodeBlockParser::is_first_line(line)) {
            return std::make_unique<CodeBlockParser>();
        }
        if (TableParser::is_first_line(line)) {
            return std::make_unique<TableParser>();
        }
        if (ListParser::is_first_line(line)) {
            return std::make_unique<ListParser>();
        }
        if (HorizontalRuleParser::is_first_line(line)) {
            return std::make_unique<HorizontalRuleParser>();
        }
        return std::make_unique<ParagraphParser>();
    }

    auto MdParser::parse(std::istream &input_stream) -> Document {
        auto result = Document();
        std::unique_ptr<ElementParser> parser = nullptr;
        std::unique_ptr<ElementParser> default_parser = std::make_unique<ParagraphParser>();
        std::vector<std::string> parsed_lines;
        auto line = std::string();
        bool run = static_cast<bool>(std::getline(input_stream, line));
        while (run) {
            if (line.empty()) {
                if (parser != nullptr) {
                    parsed_lines.clear();
                    result.add_element(parser->get_parsing_result());
                    parser = nullptr;
                }
                run = static_cast<bool>(std::getline(input_stream, line));
                continue;
            }
            if (parser == nullptr) {
                parser = get_parser(line);
            }
            parsed_lines.push_back(line);
            switch (parser->parse(line)) {
                case FINISHED:
                    parsed_lines.clear();
                    result.add_element(parser->get_parsing_result());
                    parser = nullptr;
                    run = static_cast<bool>(std::getline(input_stream, line));

                    break;
                case ERROR:
                    for (auto &parsed_line: parsed_lines) {
                        switch (default_parser->parse(parsed_line)) {
                            case FINISHED:
                                result.add_element(parser->get_parsing_result());
                                default_parser.reset();
                                break;
                            case ERROR:
                                default_parser.reset();
                                break;
                            case ONE_MORE_LINE:
                            case ALREADY_FINISHED:
                                break;
                        }
                    }
                    parser = nullptr;
                    run = static_cast<bool>(std::getline(input_stream, line));
                    break;
                case ONE_MORE_LINE:
                    run = static_cast<bool>(std::getline(input_stream, line));
                    break;
                case ALREADY_FINISHED:
                    parsed_lines.clear();
                    result.add_element(parser->get_parsing_result());
                    parser = nullptr;
                    break;
            }
        }
        if (parser != nullptr) {
            result.add_element(parser->get_parsing_result());
        }
        return result;
    }
}
