#ifndef HEADER_H
#define HEADER_H

#include "Paragraph.h"

class Header final : public Element {
public:
    Header();

    Header(const Header &) = default;

    Header &operator=(const Header &) = default;

    Header(const Paragraph &paragraph, int level);

    ~Header() override;

    [[nodiscard]] auto get_level() const -> int;

    [[nodiscard]] auto get_paragraph() const -> Paragraph;

    auto set_paragraph(const Paragraph &paragraph_) -> void;

    auto set_level(int level_) -> void;

    auto to_json() -> nlohmann::json override;

private:
    int level{1};
    Paragraph paragraph;
};

#endif //HEADER_H
