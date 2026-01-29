
----feedme
# Dining Philosophers — Multithreaded Simulation in C

A compact, thread safe implementation of the classic **Dining Philosophers Problem** using POSIX threads and mutexes. The project demonstrates safe multithreading,
fine grained synchronization, and precise timing. A philosopher’s death must be detected and reported **within 10 ms** of exceeding `time_to_die`.

---

## Overview

- Each philosopher runs as a **separate thread**.
- Forks are shared between neighbors; each fork has its own **mutex**.
- A philosopher must hold **two forks** to eat.
- If a philosopher does not begin eating within `time_to_die` milliseconds since their last meal, they die.
- All actions are printed in real time:
  - `has taken a fork`
  - `is eating`
  - `is sleeping`
  - `is thinking`
  - `died`
- Philosophers do **not** communicate directly; all coordination happens through shared, mutex protected state.

---

## Program Arguments

```
./philo number_of_philosophers "time_to_die" "time_to_eat" "time_to_sleep" "[number_of_times_each_philosopher_must_eat]"
```

- **number_of_philosophers** — also the number of forks  
- **time_to_die** — max time (ms) a philosopher may go without eating  
- **time_to_eat** — time (ms) spent eating  
- **time_to_sleep** — time (ms) spent sleeping  
- **number_of_times_each_philosopher_must_eat** (optional) — simulation ends once all philosophers reach this count  

---

## Allowed External Functions

```
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
```

---

## Core Structures


### `t_data`
Global simulation state:
[`init_philo.c`](./philo.h#L27-L42).

### `t_philosopher`
Represents each philosopher thread:
[`init_philo.c`](./philo.h#L44-L54).


---

## Fork Mutex Initialization

[`init_philo.c`](./init_data.c#L51-L70).


---

## Philosopher Initialization

This function assigns fork pointers, initializes per‑philosopher mutexes, and links each philosopher to the shared data structure.
[`init_philo.c`](./init_data.c#L97-L123).


---

## Death Detection (within 10 ms)

A monitoring routine continuously checks each philosopher’s `last_meal` timestamp.  
If the elapsed time exceeds `time_to_die`, the simulation must:

- Print the death event  
- Set `death_flag` under mutex protection  
- Stop all further actions  
- Report the death **within 10 ms**  

This requires precise timing and short‑interval sleep loops.

---

## Race Detection with Valgrind

Thread safety can be verified using DRD:

```
valgrind --tool=drd --exclusive-threshold=1000000 ./philo 5 800 200 200
```

A clean run (0 races) confirms correct synchronization.

---

## Why This Project Matters

This implementation demonstrates practical skills used in systems programming:

- Thread lifecycle management  
- Fine‑grained locking  
- Deadlock avoidance  
- Race‑free shared state  
- Accurate timing under concurrency  
- Memory‑safe dynamic allocation  
- Valgrind‑verified correctness  

It serves as a compact, real‑world example of multithreaded design in C.
