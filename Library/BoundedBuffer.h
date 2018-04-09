#include <iostream>
#include <queue>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

class BoundedBuffer {

public:
        static BoundedBuffer& getInstance() {
            static BoundedBuffer object;
            return object;
        }

        int getMaxQueueSize() {
            return max_size;
        }

        void addItem() {
            std::unique_lock<std::mutex> l(lock);

            not_full.wait(l, [this](){return max_size != q.size();});

            if (q.size() == max_size) {
                std::cout << "BUG!! The Queue is full!!! \n";
                return;
            }
            q.push((rand() % 100) + 1);

            l.unlock();
            not_empty.notify_one();
        }

        void delItem() {
            std::unique_lock<std::mutex> l(lock);

            not_empty.wait(l, [this](){return 0 != q.size();});

            if(q.size() == 0) {
                std::cout << "BUG!! The Queue is empty \n";
                return;
            }
            q.pop();

            /* The unlock here is strictly not needed, as its automatically
             * going to be unlocked once it goes out of scope, but doing it
             * this way allows the other waiting thread to get hold of the lock
             * sooner. Its a small optimization
             */
            l.unlock();
            not_full.notify_one();
        }

        void printQueue(){
            std::queue<int> temp = q;

            while(!temp.empty()) {
                std::cout << temp.front() << " ";
                temp.pop();
            }
            std::cout << std::endl;
        }

private:
        std::condition_variable not_full;
        std::condition_variable not_empty;
        std::mutex lock;

        BoundedBuffer() {
            std::cout << "Constructing the BoundedBuffer object()\n";
            srand(time(NULL));
            max_size = 5;
        };

        ~BoundedBuffer() {
            std::cout << "Destroying the BoundedBuffer object()\n";

        };

        BoundedBuffer(const BoundedBuffer&);
        BoundedBuffer& operator=(const BoundedBuffer&);
        std::queue<int> q;
        int max_size;
};
