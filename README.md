# Philosophers

A multithreaded implementation of the classic Dining Philosophers Problem using POSIX threads/mutexes (mandatory) and processes/semaphores (bonus).

## 📋 Description

**Philosophers** is a concurrent programming challenge that simulates philosophers sitting around a table, eating spaghetti and thinking. Each philosopher needs two forks to eat, but there are only as many forks as philosophers. The goal is to implement a solution that:

- Prevents **deadlock** (all philosophers waiting forever)
- Prevents **starvation** (some philosophers never eating)
- Ensures **thread safety** with proper mutex synchronization
- Maintains accurate timing and state tracking

### The Problem

```
Classic Setup:
- N philosophers sit around a table
- N forks (one between each pair)
- Each philosopher: eats, sleeps, thinks (repeat)
- To eat: must hold BOTH left and right forks
- Critical: Prevent deadlock and starvation
```

## 🚀 Compilation

```bash
cd philo
make          # Compile the mandatory program
make bonus    # Compile the bonus program
make clean    # Remove object files
make fclean   # Complete cleanup
make re       # Recompile
```

## 💻 Usage

### Mandatory Program

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Parameters:**
- `number_of_philosophers` : Number of philosophers (and forks)
- `time_to_die` : Time in milliseconds before philosopher dies if not eating
- `time_to_eat` : Time in milliseconds to eat
- `time_to_sleep` : Time in milliseconds to sleep
- `number_of_times_each_philosopher_must_eat` (optional) : If set, stops when all philosophers have eaten this many times

### Examples

```bash
# 5 philosophers, die in 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# 4 philosophers, each must eat 10 times
./philo 4 410 100 100 10

# Single philosopher (edge case)
./philo 1 800 200 200

# Large simulation
./philo 100 800 200 200
```

### Bonus Program

```bash
cd philo_bonus
make
./philo_bonus [same parameters as mandatory]
```

## 🧠 Algorithm Overview

### Core Components

1. **Philosopher Thread Routine**
   ```
   Each philosopher repeats:
       1. Try to acquire both forks (left & right)
       2. Eat for time_to_eat
       3. Release both forks
       4. Sleep for time_to_sleep
       5. Think
   ```

2. **Deadlock Prevention**
   - **Odd/Even approach**: Philosophers with odd numbers start eating first, then even numbers
   - Alternative: Philosopher takes both forks or releases and retries
   - Result: Guarantees progress and prevents circular wait

3. **Fork Acquisition**
   ```c
   pthread_mutex_lock(left_fork);
   pthread_mutex_lock(right_fork);
   // eat
   pthread_mutex_unlock(right_fork);
   pthread_mutex_unlock(left_fork);
   ```

4. **Death Detection (Monitor Thread)**
   ```
   Angel of Death thread:
       Every iteration:
           For each philosopher:
               Check if current_time - last_meal_time > time_to_die
               If true: philosopher dies, end simulation
   ```

### Key Synchronization Primitives

- **pthread_mutex_t** : Protects forks (one per fork)
- **start_mutex** : Ensures all threads start simultaneously
- **print_mutex** : Prevents output race conditions
- **status_mutex** : Protects simulation state

### State Management

```c
typedef enum e_status
{
    NOT_STARTED = 0,    // Setup phase
    STARTED = 1,        // Simulation running
    ENDED = -1          // Someone died or all ate enough
} t_status;
```

## 📊 Technical Details

### Timing Considerations

- All times are in **milliseconds**
- Internally converted to microseconds for `usleep()`
- Precise monitoring thread tracks death times
- Small delays between philosopher starts prevent immediate deadlock

### Philosopher Numbering

- Philosopher 1 to N
- Left fork: philosopher's own fork
- Right fork: next philosopher's fork (circular)
- Odd-numbered philosophers get slight delay to avoid deadlock

### Edge Cases

**Single Philosopher:**
```
- Takes left fork
- Waits for right fork (never comes - deadlock!)
- Dies after time_to_die
- Handled specially: dies instantly
```

**Large Numbers:**
- More threads = more contention
- Timing accuracy becomes critical
- Monitor thread efficiently checks all philosophers

## 📈 Complexity

- **Time Complexity**: O(time_to_die) - depends on simulation parameters, not N
- **Space Complexity**: O(N) - for philosopher and fork structures
- **Synchronization**: Fair scheduling with mutex locks

## 📚 Project Structure

```
Philosophers/
├── philo/                       # Mandatory program
│   ├── Makefile
│   ├── includes/
│   │   └── philo.h             # Main header with structures
│   └── srcs/
│       ├── main/
│       │   └── main.c          # Entry point, initialization
│       ├── init_prog/
│       │   ├── parsing_arg.c   # Parse command line arguments
│       │   ├── philos.c        # Create philosopher structures
│       │   ├── threads.c       # Create and join threads
│       │   └── simulation_status.c  # Manage simulation state
│       ├── actions/
│       │   ├── routine.c       # Main philosopher loop
│       │   ├── eating.c        # Eating logic and fork handling
│       │   ├── monitor.c       # Death detection thread
│       │   └── action_log.c    # Thread-safe logging
│       ├── utils/
│       │   └── utils.c         # Helper functions (sleep, time, etc.)
│       └── cleanup/
│           └── cleanup.c       # Memory and mutex cleanup
├── philo_bonus/                 # Bonus program (alternative approach)
│   └── [similar structure with potential improvements]
└── README.md
```

## 🧪 Testing

```bash
# Test basic functionality
./philo 5 800 200 200

# Test with limited eating cycles
./philo 5 800 200 200 7

# Test single philosopher (should die)
./philo 1 800 200 200

# Test immediate starvation
./philo 5 100 200 200

# Test with high philosopher count
./philo 50 800 200 200

# Test rapid eating/sleeping
./philo 10 200 50 50
```

**Expected Behavior:**
- Philosophers print actions: "has taken a fork", "is eating", "is sleeping", "is thinking"
- If someone dies: "died" is printed
- All actions should have timestamps
- No output after simulation ends

## 🎁 Bonus Program

The bonus program implements the same Dining Philosophers Problem but uses **POSIX Semaphores and Processes** instead of threads/mutexes.

### Key Differences from Mandatory

| Feature | Mandatory | Bonus |
|---------|-----------|-------|
| **Synchronization** | Mutexes (pthread_mutex) | Semaphores (sem_t) |
| **Process Model** | Threads | Processes (fork()) |
| **Fork Synchronization** | One mutex per fork (N mutexes) | One shared semaphore for all forks |
| **Memory Sharing** | Shared memory (same process) | Named semaphores (kernel IPC) |
| **Additional Sync** | start_mutex, print_mutex | Named semaphores for: print, simulation_end, meals, start, check, full |

### Semaphores Used in Bonus

```c
sem_t *forks             // Shared for all N forks (initialized to N)
sem_t *print             // Protect stdout output
sem_t *simulation_end    // Signal when to end (wait by main)
sem_t *meals             // Track meal completion
sem_t *sem_check         // Monitor checking
sem_t *start             // Synchronize philosopher startup
sem_t *sem_full          // Track full philosophers
```

### Why Semaphores?

**Advantages:**
- ✅ Processes are more independent (each has own memory space)
- ✅ No issues with shared memory corruption
- ✅ Better isolation between philosophers
- ✅ Can handle more concurrent philosophers (kernel-managed)
- ✅ Named semaphores work across processes

**Fork Semaphore Model:**
```
- One SHARED semaphore for ALL forks (initialized to N)
- When philosopher eats: sem_wait() twice (for 2 forks)
- After eating: sem_post() twice (to release forks)
- Prevents more than N/2 philosophers from eating simultaneously
```
- sem_wait() = acquire (decrement), sem_post() = release (increment)
- No mutex needed for state - each process independent
```

### Bonus Compilation & Usage

```bash
cd philo_bonus
make

# Same usage as mandatory program
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

### Implementation Details

**Semaphore-based Fork Model:**
```c
sem_t *forks;  // Shared semaphore, initialized to N (number of philosophers)

// To eat (acquire 2 forks):
sem_wait(forks);      // Acquire one fork
sem_wait(forks);      // Acquire second fork
// eat
sem_post(forks);      // Release first fork
sem_post(forks);      // Release second fork
```

**Process Creation with fork():**
```c
for (i = 0; i < num_philos; i++)
{
    pid = fork();
    if (pid == 0)
        exit(philo_routine(&philos[i]));  // Child process
}
// Parent waits for simulation_end semaphore signal
sem_wait(sema.simulation_end);
```

**Named Semaphores (IPC):**
```c
// Create semaphore accessible across processes
sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, N)
// Cleanup after simulation
sem_unlink("/forks_sem")
```

### Project Structure (Bonus)

```
philo_bonus/
├── Makefile
├── includes/
│   └── philo_bonus.h        # Structures with semaphores (sem_t pointers)
└── bonus/
    ├── main/
    │   └── main_bonus.c     # Entry point with fork() calls, manages processes
    ├── init_prog/
    │   ├── parsing_arg_bonus.c    # Parse command line
    │   ├── semaphores_bonus.c     # Create named semaphores (sem_open, sem_unlink)
    │   └── philos_bonus.c         # Create philosopher structures
    ├── actions/
    │   ├── routine_bonus.c        # Process-based philosopher loop (philo_routine)
    │   ├── monitor_bonus.c        # Monitor process for death detection
    │   └── action_log_bonus.c     # Thread-safe logging with print semaphore
    ├── utils/
    │   └── utils_bonus.c          # Helper functions (time, sleep, etc.)
    └── cleanup/
        └── cleanup_bonus.c        # Clean semaphores and processes
```

### Testing Bonus

```bash
# Test with processes instead of threads
./philo_bonus 5 800 200 200

# Test with many philosophers
./philo_bonus 200 800 200 200

# Test with limited eating cycles
./philo_bonus 10 800 200 200 5
```

### Bonus Advantages in Practice

- Handles higher concurrency (processes > threads)
- More robust to process crashes (isolation)
- Better for demonstrating IPC concepts
- Cleaner resource management (OS-level cleanup)

---



## 📌 Key Challenges & Solutions

### Challenge 1: Deadlock
**Problem**: All philosophers take left fork, wait for right fork forever
**Solution**: Odd-numbered philosophers start with delay, ensuring eating pattern

### Challenge 2: Race Conditions
**Problem**: Multiple threads modifying shared state simultaneously
**Solution**: All shared data protected by mutexes (forks, status, timestamps)

### Challenge 3: Starvation
**Problem**: Some philosophers never get to eat
**Solution**: Fair mutex implementation + death monitoring ensures constant eating cycles

### Challenge 4: Accurate Timing
**Problem**: Precise millisecond tracking with threads is difficult
**Solution**: Monitor thread frequently checks death times, optimal check frequency

### Challenge 5: Single Philosopher Edge Case
**Problem**: Special handling required
**Solution**: Detected and handled separately with instant death

## 🎯 Learning Outcomes

✅ Deep understanding of threading and concurrency
✅ Mutex and synchronization primitives
✅ Race condition detection and prevention
✅ Deadlock analysis and solutions
✅ Real-time system design
✅ POSIX threads (pthread) API

## 👤 Author

[@itaharbo91](https://github.com/itaharbo91)

---

**GitHub Description**: Multithreaded Dining Philosophers Problem implementation with deadlock prevention using POSIX threads and mutexes.