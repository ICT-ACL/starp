#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

TEST(json, parse) {
    json j = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    ASSERT_EQ(j["name"], "Niels");
    ASSERT_EQ(j["happy"], true);
}

