#ifndef STARP_SRC_DAG_H_
#define STARP_SRC_DAG_H_

#include "err.h"
#include "task.h"
#include <vector>
#include <queue>

namespace starp {

class Dag {
    std::vector<std::vector<task_id_t>> edges_;
    std::vector<int64_t> in_degree_;          // unfinished predecessors of each task
    task_id_t finished_;                         // number of finished tasks
    std::vector<Task> tasks_;
    std::queue<task_id_t> ready_tasks_;
    bool locked_;    // if all edges are inserted

  public:
    Dag(): finished_(0), locked_(false) {}

    task_id_t add_task(const std::string& service, const std::string& args) {
        if (locked_)
            err::Exit("Dag::add_task: the dag is already locked!\n");
        task_id_t id = tasks_.size();
        tasks_.push_back(Task(id, service, args));
        edges_.push_back(std::vector<task_id_t>());
        in_degree_.push_back(0);
        return id;
    }

    void add_edge(task_id_t src, task_id_t dst) {
        if (locked_)
            err::Exit("Dag::add_edge: the dag is already locked!\n");
        if (src >= tasks_.size() || dst >= tasks_.size())
            err::Exit("Dag::add_edge: task id out of range!\n");
        edges_[src].push_back(dst);
        in_degree_[dst]++;
    }

    void lock() {
        if (locked_)
            return;
        locked_ = true;
        // init ready tasks
        for (task_id_t id = 0; id < tasks_.size(); ++id) {
            if (in_degree_[id] == 0) {
                ready_tasks_.push(id);
                tasks_[id].set_state(TaskState::READY);
            }
        }
    }

    void update_on_done_task(task_id_t src) {
        finished_++;
        tasks_[src].set_state(TaskState::DONE);
        for (task_id_t dst : edges_[src]) {
            if ((--in_degree_[dst]) == 0) {
                ready_tasks_.push(dst);
                tasks_[dst].set_state(TaskState::READY);
            }
        }
    }

    // if there's no ready task, return -1
    task_id_t get_ready_task() {
        if (ready_tasks_.empty())
            return -1;
        task_id_t res = ready_tasks_.front();
        ready_tasks_.pop();
        return res;
    }

    bool all_done() const {
        return finished_ == tasks_.size();
    }

};

}   // namespace starp

#endif  // STARP_SRC_DAG_H_
