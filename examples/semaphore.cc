#include <iostream>
#include <syncstream>
#include <semaphore>
#include <thread>

// https://www.bilibili.com/video/BV1Su4y1t7zB

namespace
{
    // Every condition has a semaphore representation.
    ::std::counting_semaphore<1>    mutex_sem{1};
    ::std::counting_semaphore       e_red{60};              // the number of red < 60
    ::std::counting_semaphore       e_white{50};            // the number of white < 50
    ::std::counting_semaphore       condition_1{70};        // the number of red and white < 70
    ::std::counting_semaphore       condition_2{30};        // red - white < 30
    ::std::counting_semaphore       condition_3{30};        // white - red < 30
}

namespace dsnugee
{

void put_red()
{
    e_red.acquire();
    condition_1.acquire();
    condition_2.acquire();

    mutex_sem.acquire();
    ::std::osyncstream(::std::cout) << "pick the box up\n";
    ::std::osyncstream(::std::cout) << "put red\n";

    condition_3.release();
    ::std::osyncstream(::std::cout) << "put the box down\n\n";
    mutex_sem.release();
}

void put_white()
{
    e_white.acquire();
    condition_1.acquire();
    condition_3.acquire();

    mutex_sem.acquire();
    ::std::osyncstream(::std::cout) << "pick the box up\n";
    ::std::osyncstream(::std::cout) << "put white \n";

    condition_2.release();
    ::std::osyncstream(::std::cout) << "put the box down\n\n";
    mutex_sem.release();
}

void pick_white()
{
    condition_3.acquire();

    mutex_sem.acquire();
    ::std::osyncstream(::std::cout) << "pick the box up\n";
    ::std::osyncstream(::std::cout) << "pick red\n";

    condition_1.release();
    e_white.release();
    condition_2.release();
    ::std::osyncstream(::std::cout) << "put the box down\n\n";

    mutex_sem.release();
}

void pick_red()
{
    condition_2.acquire();
    mutex_sem.acquire();
    ::std::osyncstream(::std::cout) << "pick the box up\n";
    ::std::osyncstream(::std::cout) << "pick white\n";

    condition_1.release();
    condition_3.release();
    e_red.release();
    ::std::osyncstream(::std::cout) << "put the box down\n\n";

    mutex_sem.release();
}

} // namespace dsnugee
