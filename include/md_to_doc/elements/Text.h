#ifndef TEXT_H
#define TEXT_H
#include <set>
#include <string>

#include <boost/unordered_map.hpp>
#include <boost/assign/list_of.hpp>

#include "Element.h"

enum FORMATTING_OPTIONS {
    BOLD, ITALIC, STRIKETHROUGH, HIGHLIGHT, CODE,
    LINK, IMAGE
};

const boost::unordered_map<FORMATTING_OPTIONS, std::string> FORMATTING_OPTIONS_TO_STRING = boost::assign::map_list_of
        (BOLD, "bold")
        (ITALIC, "italic")
        (STRIKETHROUGH, "strikethrough")
        (HIGHLIGHT, "highlight")
        (CODE, "code")
        (LINK, "link")
        (IMAGE, "image");

class Text final : public Element {
public:
    Text();

    explicit Text(std::string content_);

    explicit Text(std::string content_, std::set<FORMATTING_OPTIONS> formatting_options);

    explicit Text(std::string content_, std::set<FORMATTING_OPTIONS> formatting_options, std::string url_);

    Text(const Text &other) = default;

    Text &operator=(const Text &other);

    ~Text() override;

    auto get_content() -> std::string;

    auto set_content(const std::string &content_) -> void;

    auto get_formatting_options() -> std::set<FORMATTING_OPTIONS>;

    auto add_formatting_option(FORMATTING_OPTIONS option) -> void;

    auto remove_formatting_option(FORMATTING_OPTIONS option) -> void;

    auto clear_formatting_options() -> void;

    auto set_formatting_options(const std::set<FORMATTING_OPTIONS> &options) -> void;

    auto const get_url() -> std::string;

    auto set_url(const std::string &url_) -> void;

    auto to_json() -> nlohmann::json override;

private:
    std::string content;
    std::set<FORMATTING_OPTIONS> formatting_options;
    std::string url;
};


#endif //TEXT_H
