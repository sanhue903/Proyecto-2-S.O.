#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <vector>
#include <string>

class Process {

private:
    int time;
    int priority;
public:
    std::string id;

    Process(std::string _id, int execTime) {
        id = _id;
        time = execTime;
        priority = 0;
    }
    void setTime(int t) {
        time = t;
    }
    void setPriority(int p) {
        if (priority < 9) {
            priority = p;
        }
    }
    int getTime() {
        return time;
    }
    int getPriority() {
        return priority;
    }
    std::string getID() {
        return id;
    }
};

struct Compare {
    bool operator()(Process & p1, Process & p2) {
        return p1.getPriority() > p2.getPriority();
    }
};

class Runqueues {

private:
    std::priority_queue<Process, std::vector<Process>, Compare> active; 
    std::priority_queue<Process, std::vector<Process>, Compare> expired;
    bool swapped;
public:
    Runqueues() {
        swapped = false;
    }
    void swap () {
        swapped = !swapped;
    }
    bool isEmpty() {
        return swapped ? expired.empty() : active.empty();
    }
    bool bothEmpty() {
        return active.empty() && expired.empty();
    }
    void push(Process p) {
        if (swapped) {
            expired.push(p);
        } else {
            active.push(p);
        }
    }
    void pushExpired(Process p) {
        if (swapped) {
            active.push(p);
        } else {
            expired.push(p);
        }
    }
    void pop() {
        if (swapped) {
            expired.pop();
        } else {
            active.pop();
        }
    }
    Process top() {
        return swapped ? expired.top() : active.top();
    }
};

int main(int argc, char* argv[]) {
    Process p1("a", 10);
    Process p2("b", 13);
    Process p3("c", 18);
    Process p4("d", 27);
    Process p5("f", 39);

    Runqueues _queue;

    _queue.push(p1);
    _queue.push(p2);
    _queue.push(p3);
    _queue.push(p4);
    _queue.push(p5);

    int timeSlice = 5;
    while (!_queue.bothEmpty()) {
        Process currentProcess = _queue.top();
        
        std::cout << "Sleeping for " << timeSlice << "\n";
        std::cout << "Time left in process " << currentProcess.getID() << ": " << currentProcess.getTime() << "\n";

        usleep(timeSlice);

        if (currentProcess.getTime() >= timeSlice) {
            int newTime = currentProcess.getTime() - timeSlice;
            currentProcess.setTime(newTime);
            _queue.pushExpired(currentProcess);
            _queue.pop();
        } else {
            std::cout << "Finished process " << currentProcess.getID() << "\n";
            _queue.pop();
        }

        if (_queue.isEmpty()) {
            _queue.swap();
        }
    }
    return 0;
}
