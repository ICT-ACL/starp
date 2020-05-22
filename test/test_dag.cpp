#include <gtest/gtest.h>

#include "dag.h"

using namespace starp;

TEST(Dag, demo) {
    /*
     *      -> 1
     * 0 --|        -> 3
     *      -> 2 --|
     *              -> 4
     * 5
     */
    Dag dag;
    dag.add_task("echo", "{\"id\": 0}");
    dag.add_task("echo", "{\"id\": 1}");
    dag.add_task("echo", "{\"id\": 2}");
    dag.add_task("echo", "{\"id\": 3}");
    dag.add_task("echo", "{\"id\": 4}");
    dag.add_task("echo", "{\"id\": 5}");

    dag.add_edge(0, 1);
    dag.add_edge(0, 2);
    dag.add_edge(2, 3);
    dag.add_edge(2, 4);

    dag.lock();

    ASSERT_EQ(dag.get_ready_task(), 0);
    ASSERT_EQ(dag.get_ready_task(), 5);

    dag.update_on_done_task(0);
    ASSERT_EQ(dag.get_ready_task(), 1);
    ASSERT_EQ(dag.get_ready_task(), 2);

    dag.update_on_done_task(1);
    ASSERT_EQ(dag.get_ready_task(), -1);

    dag.update_on_done_task(2);
    ASSERT_EQ(dag.get_ready_task(), 3);
    ASSERT_EQ(dag.get_ready_task(), 4);

    dag.update_on_done_task(3);
    dag.update_on_done_task(4);
    dag.update_on_done_task(5);

    ASSERT_EQ(true, dag.all_done());
}


