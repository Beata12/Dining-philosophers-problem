**#Dining Philosophers Problem**

This repository contains my implementation of the classic problem known as the "Dining Philosophers Problem". 
**The project is currently under development, and this README will be updated as progress is made.**

**Current Progress**
Makefile: Fully functional with commands for compiling the source files (all, clean, fclean, re).
Header Files: Structured to define necessary data structures and function prototypes.
Error Handling: Implemented to handle potential runtime errors effectively, ensuring robust operation.
Input Checking: Ensures correct and valid user inputs before proceeding with the simulation.

**Description**
The Dining Philosophers Problem is a classic problem involving philosophers seated around a circular table with a bowl of spaghetti. Philosophers alternatively think, eat, or sleep. To eat, each philosopher needs two forks. However, managing fork access without causing deadlock or starvation among philosophers is the core challenge of this problem.

**Building and Running**
To compile the program, navigate to the root directory of the project and run:
make

**To run the program:**
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

**You have to replace the parameters with appropriate values where:**
number_of_philosophers is the number of philosophers and also the number of forks.
time_to_die is the maximum time (in milliseconds) a philosopher can spend without eating before dying.
time_to_eat is the time (in milliseconds) a philosopher takes to eat.
time_to_sleep is the time (in milliseconds) a philosopher spends sleeping.
number_of_times_each_philosopher_must_eat is an optional parameter that stops the simulation when each philosopher has eaten this many times.

**Future Plans**
Enhance synchronization mechanisms to optimize performance.
Implement additional error checks and input validation.
Add unit tests and integration tests for robustness and reliability.
Provide a detailed documentation for each part of the project.
