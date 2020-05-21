#ifndef STARP_SRC_TASK_H_
#define STARP_SRC_TASK_H_

namespace starp {
enum struct TaskState {
    INIT,
    READY,
    RUNNING,
    DONE,
    FAILED
};

class Task {
    uint32_t id_;
    std::string service_;   // name of rpc service
    std::string args_;  // json formatted arguments
    TaskState state_;
  public:
    explicit Task(uint32_t id, const std::string service, const std::string args):
        id_(id), service_(service), args_(args), state_(TaskState::INIT) {}

    uint32_t id() const {
        return id_;
    }

    void set_state(TaskState state) {
        state_ = state;
    }

    TaskState state() {
        return state_;
    }

    std::string service() {
        return service_;
    }

    std::string args() {
        return args_;
    }
};

}   // namespace starp

#endif  // STARP_SRC_TASK_H_
