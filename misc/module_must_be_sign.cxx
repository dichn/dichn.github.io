#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

#define NSS_VMINOR 65


int main(){
    std::ifstream statm("/sys/module/module/parameters/sig_enforce");
    std::ifstream securelevel("/sys/kernel/security/securelevel");
    std::ifstream lockdown("/sys/kernel/security/lockdown");
    char status = 'N';
  
    statm >> status;
    if (status == 'Y')
        std::cout << "Y" << std::endl;
    return 0;
}


// g++ module_must_be_sign.cxx -g -o my_app -g3
// ['-g3' and Get macro value from a compiled binary](https://stackoverflow.com/questions/6030602/get-macro-value-from-a-compiled-binary-with-debug)
