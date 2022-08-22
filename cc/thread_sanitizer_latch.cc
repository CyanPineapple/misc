#include <iostream>
#include <mutex>
#include <latch>
#include <thread>

std::mutex mutexer;
std::latch work_done(6);


class Worker {
    public:
    Worker(std::string name) : _name(name){}

    void operator() () {
        std::cout << _name << " is done. Wait to go" << "\n";
        work_done.arrive_and_wait();
        std::cout << _name << " go home!" << "\n";
        
    }

    private:
    std::string _name;
};

int main() {

    std::cout << '\n';

    std::cout << "BOSS: START WORKING! " << '\n';
  
    Worker herb("  Herb");
    std::thread herbWork(herb);
  
    Worker scott("    Scott");
    std::thread scottWork(scott);
  
    Worker bjarne("      Bjarne");
    std::thread bjarneWork(bjarne);
  
    Worker andrei("        Andrei");
    std::thread andreiWork(andrei);
  
    Worker andrew("          Andrew");
    std::thread andrewWork(andrew);
  
    Worker david("            David");
    std::thread davidWork(david);
    

    std::cout << '\n';


    herbWork.join();
    scottWork.join();
    bjarneWork.join();
    andreiWork.join();
    andrewWork.join();
    davidWork.join();
  
}