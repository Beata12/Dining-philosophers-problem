**#Dining Philosophers Problem**

This repository contains my implementation of the classic problem known as the "Dining Philosophers Problem".

**Description**

The Dining Philosophers Problem is a classic problem involving philosophers seated around a circular table with a bowl of spaghetti. Philosophers alternatively think, eat, or sleep. To eat, each philosopher needs two forks. However, managing fork access without causing deadlock or starvation among philosophers is the core challenge of this problem.


![image (5)](https://github.com/Beata12/Dining-philosophers-problem/assets/38575612/93105ef7-4092-4489-8ec5-85965ff57ffd)

**Here's what the program is about:**
The simulation involves philosophers sitting at a round table with a large bowl of spaghetti in the middle.
Philosophers alternate between eating, thinking, and sleeping.
Each philosopher requires two forks to eat, one on their left and one on their right.
When a philosopher finishes eating, they start sleeping, and upon waking up, they start thinking again.
The simulation ends when a philosopher dies of starvation.
All philosophers need to eat and should never starve.
Philosophers do not communicate with each other, and they are unaware of each other's status.



![image (5) (1)](https://github.com/Beata12/Dining-philosophers-problem/assets/38575612/1afb250b-d307-4b8b-9a4a-dcd11c396727)

**Rules:**
Each philosopher is represented by a thread.
There is one fork between each pair of philosophers, and the state of each fork is protected by a mutex.
The program is avoiding data races and ensure proper synchronization among threads.
Philosopher threads is programmed to prevent starvation and avoid dying.

**Building and Running**

To compile the program, navigate to the root directory of the project and run:

make

**To run the program:**

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

**You have to replace the parameters with appropriate values where:**

* number_of_philosophers is the number of philosophers and also the number of forks.

* time_to_die is the maximum time (in milliseconds) a philosopher can spend without eating before dying.

* time_to_eat is the time (in milliseconds) a philosopher takes to eat.

* time_to_sleep is the time (in milliseconds) a philosopher spends sleeping.

* number_of_times_each_philosopher_must_eat is an optional parameter that stops the simulation when each philosopher has eaten this many times.

