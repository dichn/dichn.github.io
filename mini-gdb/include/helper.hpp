#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/user.h>
#include <vector>

enum ProgramState {
    Fresh,
    Running,
    Stopped,
    Failed,
    Exited,
};

struct Result {
    int64_t i64;
    int32_t i32;
};

struct BreakpointData {
    uint64_t addr;
    uint8_t orig_byte;
};

class TargetProgram {
public:
    TargetProgram(int32_t target_pid, std::string target_executable)
        : target_pid(target_pid)
        , target_executable(target_executable)
    {
        state = ProgramState::Fresh;
        flags = 0;
    }
    void run();
    void terminate();
    void singlestep();
    void print_short_state();
    void set_breakpoint(uint64_t loc);
    uint8_t peek_byte_at(uint64_t loc);
    void poke_byte_at(uint64_t loc, uint8_t data);
    int64_t peek_word(int32_t target_pid, uint64_t addr);

    user_regs_struct get_user_struct();

    uint32_t wait();

private:
    int32_t target_pid;
    std::string target_executable;
    uint32_t flags;
    ProgramState state;
    std::vector<BreakpointData> breakpoints;
};
