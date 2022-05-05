#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <vector>

template <typename T> 
class Timer
{
    public:
        // Starts the timer
        void start(); 

        // Ends the timer
        void end(); 

        // Displays the result of the most recent start() and end() call
        void display(); 

        // Returns the time between 'end-time' and 'start-time'
		inline std::chrono::duration<double, T> getTime() const {return endTime - startTime;} 

        // Returns the mean of all times called between start() and end()
        double getMean(); 

        // Returns the standard deviation of all times called between start() and end()
        double getSD(); 

        // Shows a detailed display of all the start() and end() calls
        void detailedDisplay(); 

    private:
        size_t noOfStartCalls {};
        size_t noOfEndCalls {};
        std::vector<std::chrono::duration<double, T>> timePoints;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};

// Specialization
template class Timer<std::milli>;
template class Timer<std::nano>;

#endif // TIMER_HPP
