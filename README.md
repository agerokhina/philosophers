# Philosophers Project

This project is an implementation of the classic Dining Philosophers problem in C using POSIX threads. The goal is to simulate a set of philosophers who alternate between thinking, eating, and sleeping while sharing forks (resources) without causing deadlocks or race conditions.

## Project Requirements

- **Concurrency:** Each philosopher is represented by a thread.
- **Synchronization:** Forks are implemented as mutexes to prevent multiple philosophers from using the same fork at the same time.
- **Monitoring:** Separate monitor threads check for philosopher death conditions and, if specified, for the required number of meals.
- **Timing:** Accurate timing functions (based on `gettimeofday`) are used to simulate the delays for eating, sleeping, and thinking.
- **Input Validation:** The program validates command-line arguments.
- **Norminette Compliance:** The project follows the 42 Norminette rules, including limits on function length and style guidelines.

## Usage

The program is executed with the following parameters:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

- **number_of_philosophers:** Number of philosophers (and forks).
- **time_to_die:** Time in milliseconds before a philosopher dies if they haven't started eating.
- **time_to_eat:** Time in milliseconds a philosopher spends eating.
- **time_to_sleep:** Time in milliseconds a philosopher spends sleeping.
- **number_of_meals** (optional): If provided, the simulation stops when each philosopher has eaten at least this many times.

### Examples

```bash
./philo 5 800 200 200
./philo 3 800 200 200 3
```

## Implementation Details

- **Philosopher Threads:** Each philosopher continuously cycles through:
  - **Taking forks:** Forks are picked up in a predefined order to prevent deadlocks.
  - **Eating:** When eating, the philosopher updates the last time they ate and decreases their meal count.
  - **Sleeping and Thinking:** After eating, the philosopher sleeps and then thinks before attempting to eat again.
- **Forks as Mutexes:** Each fork is a mutex, ensuring exclusive access.
- **Monitor Threads:**
  - **Death Monitor:** Checks if any philosopher has exceeded the allowed `time_to_die` and marks them as dead.
  - **Meal Monitor:** (If the number of meals is specified) Checks if all philosophers have eaten the required number of times.
- **Time Management:** Uses functions such as `get_time()`, `ft_usleep()`, and `time_stamp()` for accurate time measurement.
- **Error Handling:** The project validates inputs, checks thread creation, and properly joins threads and destroys mutexes upon exit.

## Compilation

To compile the project, use the following command (assuming all source files are in the same directory):

```bash
cc -Wall -Wextra -Werror -pthread philo.c validations.c time.c destroys.c -o philo
```

If a Makefile is provided, simply run:

```bash
make
```

## Test cases ???
Not die:
5 800 200 200 
5 800 200 200 7
4 410 200 200
3 700 200 100
?
5 600 150 150
100 800 200 200
103 800 200 200
200 800 200 200

Extra cases:
3 800 200 200 3
199 650 200 200
3 500 130 150 3
200 650 200 200

Die:
3 300 130 150 3
4 800 200 99999999
1 800 200 200
4 310 200 100
4 200 205 200

Not correct:
-5 600 200 200
4 -3 200 200
4 600 -5 200
4 600 200 -5
4 600 200 200 -3

Test for memory leaqs
// valgrind --leak-check=full  --track-origins=yes  ./philo 1 300 150 150

## Known Issues & Debugging Tips

- **Premature Philosopher Death:** If philosophers are dying too soon, check the timing calculations (especially in the `eating` function where `last_time_eating` must be updated correctly) and mutex synchronization.
- **CPU Load:** Busy-wait have been minimized by using `usleep(CPU_PAUSE)`; ensure that this value is appropriate for your system.

## Conclusion

This project implements the Dining Philosophers problem according to the 42 project requirements, focusing on correct thread management, synchronization, and adherence to coding standards. If you have any questions or suggestions for improvements, feel free to open an issue or contact the maintainer.
