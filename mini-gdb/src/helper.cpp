#include <signal.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "helper.hpp"

void TargetProgram::run()
{
    /* tell the kernel that we want to be traced */
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);

    /* create a C String version of the target */
    const char* ctarget = target_executable.c_str();

    /* prepare the argv */
    char* argv[] = { "jim", "jams", NULL };
    char* envp[] = { "some", "environment", NULL };

    state = ProgramState::Running;

    /* start the application */
    execve(ctarget, argv, envp);

    state = ProgramState::Failed;

    std::cout << "Game Over" << std::endl;
}

void TargetProgram::terminate()
{
    kill(target_pid, SIGKILL);
    state = ProgramState::Exited;
}

uint32_t TargetProgram::wait()
{
    int32_t status = 0;

    /* wait for the next ptrace induced block */
    waitpid(-1, &status, 0);

    return uint32_t(status);
}

void TargetProgram::singlestep()
{
    state = ProgramState::Running;
    ptrace(PTRACE_SINGLESTEP, target_pid, NULL, NULL);
}

void TargetProgram::print_short_state()
{
}

void TargetProgram::set_breakpoint(uint64_t loc)
{
    uint8_t orig_byte = peek_byte_at(loc);
    poke_byte_at(loc, 0xCC);
    breakpoints.push_back(
        BreakpointData { loc, orig_byte });
}

int64_t TargetProgram::peek_word(int32_t target_pid, uint64_t addr)
{
    int64_t word = ptrace(PTRACE_PEEKTEXT, target_pid, addr, NULL);
    return word;
}

uint8_t TargetProgram::peek_byte_at(uint64_t loc)
{
    auto start_loc = (loc / 8) * 8;
    auto offset = loc % 8;
    int64_t word = ptrace(PTRACE_PEEKTEXT, target_pid, start_loc, NULL);

    uint8_t res = (word & (0xff << (8 * offset))) >> (8 * offset);
    return res;
}

void TargetProgram::poke_byte_at(uint64_t loc, uint8_t data)
{
    auto start_loc = (loc / 8) * 8;
    auto offset = loc % 8;
    int64_t word = ptrace(PTRACE_PEEKTEXT, target_pid, start_loc, NULL);

    word = (word & !(0xff << (8 * offset))) | (uint64_t(data) << (8 * offset));
    ptrace(PTRACE_POKETEXT, target_pid, start_loc, word);
}

user_regs_struct TargetProgram::get_user_struct()
{
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, target_pid, NULL, &regs);
    return regs;
}