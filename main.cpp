#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <iostream>
#include <string>

#include <boost/atomic.hpp>
#include <fstream>
#include "logFiveG.hh"

boost::atomic_int producer_count(0);
boost::atomic_int consumer_count(0);

boost::lockfree::queue<LogFiveG*> queue(128);

const int iterations = 10000000;
const int producer_thread_count = 1;
const int consumer_thread_count = 4;


void producer(void)
{
    std::ofstream myfile;
    std::ostringstream stringStreamFile;
    stringStreamFile << "LogPush_" <<  boost::this_thread::get_id();
    myfile.open (stringStreamFile.str()); 
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    for (int i = 0; i != iterations; ++i) {
        ++producer_count;
        std::ostringstream stringStream;
        stringStream << "Log Number:" << i;
        int first_die, sec_die;
        
        LogFiveG *value = new LogFiveG(rand() % (LOG_DEBUG + 1), stringStream.str());

        myfile << "Push:" << *value << std::endl;
        while (!queue.push(value));
    }
}

boost::atomic<bool> done (false);

void consumer(void)
{
    std::ofstream myfile;
    std::ostringstream stringStream;
    stringStream << "LogPop_" <<  boost::this_thread::get_id();
    myfile.open (stringStream.str()); 
    LogFiveG *value;
    while (!done) {
        while (queue.pop(value)) 
        {
            myfile << "Pop:" << *value << std::endl;
            delete value;
            ++consumer_count;
        }
    }

    while (queue.pop(value))
    {
        myfile << "**********************Last Pop: " << *value << "]" << std::endl;
        delete value;
        ++consumer_count;
    }
}
int main(int argc, char* argv[])
{
    using namespace std;
    std::cout << "boost::lockfree::queue is ";
    if (!queue.is_lock_free())
        std::cout << "not ";
    std::cout << "lockfree" << std::endl;

    boost::thread_group producer_threads, consumer_threads;

    for (int i = 0; i != producer_thread_count; ++i)
        producer_threads.create_thread(producer);

    for (int i = 0; i != consumer_thread_count; ++i)
        consumer_threads.create_thread(consumer);

    producer_threads.join_all();
    done = true;

    consumer_threads.join_all();

    cout << "produced " << producer_count << " objects." << endl;
    cout << "consumed " << consumer_count << " objects." << endl;
}