#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;  
std::condition_variable cv;  
int counter = 1;  
bool turn_even = false;  

// нечётные числа
void PrintOdd() {
    while (counter <= 10) {
        std::unique_lock<std::mutex> lock(mtx);  
        cv.wait(lock, [] { return !turn_even; });  
        if (counter > 10) break;  
        std::cout << "Odd: " << counter << std::endl;
        counter++;  
        turn_even = true;  
        cv.notify_one();  
    }
}

// чётные числа
void PrintEven() 
{
    while (counter <= 10) {
        std::unique_lock<std::mutex> lock(mtx);  
        cv.wait(lock, [] { return turn_even; });  
        if (counter > 10) break;  
        std::cout << "Even: " << counter << std::endl;
        counter++;  
        turn_even = false;  
        cv.notify_one(); 
    }
}

int main() 
{     
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    
    t1.join();
    t2.join();

    return 0;
}
