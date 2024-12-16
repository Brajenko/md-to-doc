#include "md_to_doc/elements/HorizontalRule.h"


auto HorizontalRule::to_json() -> nlohmann::json {
    return {
        {"type", "horizontal_rule"}
    };
}
