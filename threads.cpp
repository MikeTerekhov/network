#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void thread_func(int num)
{
   this_thread::sleep_for(std::chrono::seconds(1));
   cout << "hello from a  thread, number passed is: " << num << endl;
}

void thread_func_2(int num)
{
   cout << "hello from a  thread, number passed is: " << num << endl;
}

int main() {

   std::thread client_thread(thread_func, 69);
   std::thread client_thread_2(thread_func_2, 70);
   client_thread.join();
   client_thread_2.join();
   return 0;
}