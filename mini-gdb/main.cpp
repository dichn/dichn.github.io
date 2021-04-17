#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/user.h>
#include <unistd.h>

#include "helper.hpp"

void showhelp()
{
    std::cout << "Below are the commands you can use:" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "s - singlestep" << std::endl;
    std::cout << "y - run & wait until next syscall" << std::endl;
    std::cout << "r - dump registers" << std::endl;
    std::cout << "c - continue until next breakpoint" << std::endl;
    std::cout << "b $addr - set a breakpoint at $addr" << std::endl;
    std::cout << "lsb - list breakpoints" << std::endl;
    std::cout << "h - show the help" << std::endl;
    std::cout << "q - quit" << std::endl;
}

void input_loop(TargetProgram& prg)
{
    std::string line;
    while (1) {
        printf("(mini-gdb) ");
        std::getline(std::cin, line);
        if (line == "h") {
            showhelp();
        } else if (line == "r") {
            struct user_regs_struct regs;
            regs = prg.get_user_struct();

            printf("RIP: 0x%016lx ", regs.rip);
        } else if (line.rfind("b ", 0) == 0) {
            std::string address = line.erase(0, 4);
            uint64_t addr = stoull(address);
            prg.set_breakpoint(addr);
        }
    }
}

void target_start(const std::string& target)
{
    pid_t target_pid;
    target_pid = fork();

    TargetProgram prg = TargetProgram(target_pid, target);

    if (target_pid == 0) {
        std::cout << "TRG: running " << target << std::endl;
        prg.run();
    } else {
        /* wait for the first stop... */
        prg.wait();

        /* then start the input loop */
        input_loop(prg);
    }
}

int main()
{
    std::cout << "look who is coming :D" << std::endl;
    target_start("/home/dichen/src/sinfonie/draft/a.out");
}