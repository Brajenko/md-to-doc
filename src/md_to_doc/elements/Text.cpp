#include "md_to_doc/elements/Text.h"

#include <utility>

Text::Text() = default;

Text::~Text() = default;

Text::Text(std::string content_) : content(std::move(content_)) {
}

Text::Text(std::string content_, std::set<FORMATTING_OPTIONS> formatting_options) : content(std::move(content_)),
    formatting_options(std::move(formatting_options)) {
}

Text::Text(std::string content_, std::set<FORMATTING_OPTIONS> formatting_options,
           std::string url_) : content(std::move(content_)),
                               formatting_options(std::move(formatting_options)), url(std::move(url_)) {
}


Text &Text::operator=(const Text &other) {
    if (this != &other) {
        content = other.content;
        formatting_options = other.formatting_options;
    }
    return *this;
}


auto Text::get_content() -> std::string {
    return content;
}

auto Text::set_content(const std::string &content_) -> void {
    content = content_;
}

auto Text::get_formatting_options() -> std::set<FORMATTING_OPTIONS> {
    return formatting_options;
}

auto Text::add_formatting_option(const FORMATTING_OPTIONS option) -> void {
    formatting_options.insert(option);
}

auto Text::remove_formatting_option(const FORMATTING_OPTIONS option) -> void {
    formatting_options.erase(option);
}

auto Text::clear_formatting_options() -> void {
    formatting_options.clear();
}

auto Text::set_formatting_options(std::set<FORMATTING_OPTIONS> const &options) -> void {
    formatting_options = options;
}


auto const Text::get_url() -> std::string {
    return url;
}

auto Text::set_url(const std::string &url_) -> void {
    url = url_;
}

auto Text::to_json() -> nlohmann::json {
    std::vector<std::string> formatting_options_names;
    for (const FORMATTING_OPTIONS &formatting_option: formatting_options) {
        formatting_options_names.push_back(FORMATTING_OPTIONS_TO_STRING.at(formatting_option));
    }
    return nlohmann::json{
        {"type", "text"},
        {"content", content},
        {"formatting_options", formatting_options_names},
        {"url", url}
    };
}
