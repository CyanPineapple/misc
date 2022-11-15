#include <iostream>
#include <chrono>

struct Clocker {

    inline static std::chrono::milliseconds::rep total_count = 1;
    std::chrono::high_resolution_clock::time_point start, end;
	bool end_flag = 0;

    Clocker() {
        start = std::chrono::high_resolution_clock::now();
    }
	
	void End() {
		if (!end_flag) {
			end_flag = 1;
			end = std::chrono::high_resolution_clock::now();
		}
	}

    ~Clocker() {
		if (!end_flag)
			end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        auto duration_count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        total_count += duration_count;
        std::cout << "@@@@@@@@@@@@@@@@@" <<  "\n";
        std::cout << "The Time is(ns): " << total_count << "\n";
        std::cout << "@@@@@@@@@@@@@@@@@" <<  "\n";

    }
};

