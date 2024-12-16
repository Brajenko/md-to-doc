#include "md_to_doc/elements/Header.h"

Header::Header(const Paragraph &paragraph, const int level)
    : level(level), paragraph(paragraph) {
}

Header::Header() = default;

auto Header::set_level(const int level_) -> void {
    level = level_;
}

auto Header::set_paragraph(const Paragraph &paragraph_) -> void {
    paragraph = paragraph_;
}

Header::~Header() = default;

auto Header::get_level() const -> int {
    return level;
}

auto Header::get_paragraph() const -> Paragraph {
    return paragraph;
}

auto Header::to_json() -> nlohmann::json {
    return nlohmann::json{{"type", "header"}, {"level", level}, {"paragraph", paragraph.to_json()}};
}
