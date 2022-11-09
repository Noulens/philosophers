# philosophers
This project is about the philosophers dilemma [dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem) and the basics of threading a process. It is an introduction on mutexes and how to create threads

##  Summary

Each philosopher is a thread and mutexes are used to prevent deadlocks and data races.

Authorized functions for the assignment: `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

Code written in accordance with **42 C** coding style.

##  Usage

Run `make` in the root of the projet and launch as follows:

    ./philo <philo_nb> <time_to_die> <time_to_eat> <time_to_sleep> [ <number_of_meals> ]

- `philo_nb` -- the number of philosophers and forks.
- `time_to_die` -- A philosopher dies if he doesn't start to eat `time_to_die` ms
  after **the beginning of his last meal** (or the simulation).
- `time_to_eat` -- The time it takes for a philosopher to eat.
- `time_to_sleep` -- The time it takes for a philosopher to sleep.
- `number_of_meals` -- (optional) simulation stops if all philosophers ate at least
  such amount of times.

- If `number_of_meals` is not specified then the simulation stops at first death.
- If `philo_nb > 200` or `time_to_* < 60` ms then it is considered as undefined behavior.
