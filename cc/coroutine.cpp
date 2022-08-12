#include <coroutine>
#include <iostream>


class ReturnObject {
public:
	struct promise_type {
		int _value;
		ReturnObject get_return_object() {
			return { 
				.h_ = std::coroutine_handle<promise_type>::from_promise(*this)
			};

		}	
		std::suspend_never initial_suspend() {return {};}
		std::suspend_always final_suspend() noexcept {return {};}
		void unhandled_exception() {}
		std::suspend_always yield_value(int a) {_value = a; return {};}
	};

	std::coroutine_handle<promise_type> h_;
	operator std::coroutine_handle<promise_type>() const { return h_; }
  	operator std::coroutine_handle<>() const { return h_; }
};


ReturnObject count() {

	for (int i = 0; ; i++) {
		co_yield i;
	}

}


int main() {
	auto h = count();
	auto handler = h.h_;


	auto &pro = handler.promise();
	for (int i = 0; i < 3; i++) {
		std::cout << "Main: " << pro._value << "\n";
		handler();
	}
	handler.destroy();
}