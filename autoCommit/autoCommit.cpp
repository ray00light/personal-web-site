#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
        // what to do after receive data
        //std::cout << buffer.data();
        system("git add .");
        system("git status");
        //std::cout << "git add . done!";
        std::string tmp = buffer.data();
        //std::cout << tmp << std::endl;
        std::string subcmd = "git commit -m \"autoCommit " + tmp + "\"";
        //const char* come = subcmd;
        system(subcmd.c_str());
        //std::cout << "autoCommit done!";
        //system("git commit -m " )
    }
    return result;
}

int main( int argc, char *argv[] )
{
    const char* cmd1="inotifywait  -m -q -r -e modify -e delete -e create --timefmt '\%d-\%m-\%y \%H:\%M' --format '\%T \%:e \%w\%f' --fromfile=\"watchListAutoCommit\"";
    
    
    exec(cmd1);
    
    //exec(command);
    //std::cout << exec(command) << std::endl;
}