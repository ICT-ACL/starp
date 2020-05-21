#include <gtest/gtest.h>

#include "task.h"

using namespace starp;

TEST(Task, construct) {
    Task t(1, "echo", "{\"id\": 1}");
    ASSERT_EQ(t.state(), TaskState::INIT);

    std::cout << "id: " << t.id() << std::endl;
    std::cout << "service: " << t.service() << std::endl;
    std::cout << "args: " << t.args() << std::endl;
    std::cout << "state: " << (int)t.state() << std::endl;

    t.set_state(TaskState::DONE);
    ASSERT_EQ(t.state(), TaskState::DONE);
}

