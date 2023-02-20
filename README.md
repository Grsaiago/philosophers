<div align="center">
  <img src="https://user-images.githubusercontent.com/98427284/220205344-186f40c7-7e22-47be-a1ee-c873b157ee71.png" height="150" width="150"/>

</div>

<h1 align ="center">
  42 Cursus' Philosophers

</h1>
<p>Think, Spaghetti, Sleep, repeat. This <a href="https://42.rio/">42rio</a> project is about learning how threads, shared memory, mutexes, and deadlocks work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.</p>

### Mandatory Install
Where the multithreaded magic happens 😄
```sh
git clone https://github.com/Grsaiago/philosophers.git && cd philosophers && cd philo && make
```

### Bonus Install
The magic still happens, but this time with ✨UNIX Semaphores✨
```sh
git clone https://github.com/Grsaiago/philosophers.git && cd philosophers && cd philo_bonus && make
```

### Usage

```sh
./philo <num_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_times_must_eat]
```

### Examples

```c
./philo 1 800 200 200 // Not enough forks, one philo tries to eat but dies out 😥
./philo 5 800 200 200 // No one dies
./philo 5 800 200 200 7 // Simulation stops when all philosophers eat 7 times
./philo 4 410 200 200 // No one dies
./philo 4 310 200 100 // One philosopher dies
./philo 4 500 200 1.2 // Invalid arguments
./philo 4 0 200 200 // Invalid arguments
./philo 4 -500 200 200 // Invalid arguments
./philo 4 2147483647 200 200 // No one dies
./philo 4 200 210 200 // One philosopher dies
```

## Tips for the project
- First and foremost, the multithread chapter of The Linux Programming Interface is a great starter!
- <a href ="https://man7.org/linux/man-pages/man7/pthreads.7.html"> Pthread's man pages</a> (RTFM)
- <a href="https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2">Codevault's playlist on multithread</a> is a GEM 
## ✨Author✨

🧔 **Gabriel Saiago**
- Github: [@Grsaiago](https://github.com/Grsaiago)
- LinkedIn: [@grsaiago](https://www.linkedin.com/in/grsaiago/)
