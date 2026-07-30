#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex cout_mutex; 

void thread_func(int num)
{
   lock_guard<mutex> lock(cout_mutex);
   cout << "hello from a  thread, number passed is: " << num << endl;
}

void thread_func_2(int num)
{
   lock_guard<mutex> lock(cout_mutex);
   cout << "hello from a  thread, number passed is: " << num << endl;
}

int main() {

   std::thread client_thread(thread_func, 69);
   std::thread client_thread_2(thread_func_2, 70);
   client_thread.join();
   client_thread_2.join();
   return 0;
}