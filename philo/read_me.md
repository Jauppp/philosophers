# Ressources
- [The Dining Philosophers Problem](https://medium.com/swlh/the-dining-philosophers-problem-bbdb92e6b788)
- [Threads, mutex and concurrent programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)

```mermaid
graph TD

```

<p align="center">
  <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" alt="project-logo">
</p>
<p align="center">
    <h1 align="center">PHILOSOPHERS</h1>
</p>
<p align="center">
    <em>Sync, Eat, Ponder, Repeat-Encapsulating the core actions and loop in the Philosopher project's simulation of philosophers dining together.</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/Jauppp/philosophers?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/Jauppp/philosophers?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/Jauppp/philosophers?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/Jauppp/philosophers?style=default&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>

<br><!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary><br>

- [ Overview](#-overview)
- [ Features](#-features)
- [ Repository Structure](#-repository-structure)
- [ Modules](#-modules)
- [ Getting Started](#-getting-started)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Tests](#-tests)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)
</details>
<hr>

##  Overview

The Philo project is an open-source C application simulating the philosophical dining behavior of multiple philosophers. This project uses a Makefile as its build script, allowing for seamless compilation and execution, with options for clean, rebuild, and help.The core functionality resides within various source files, managing essential aspects such as data structures (philo/inc/philo.h), initialization (philo/src/initialisation.c), main program flow (philo/src/main.c), time-keeping (philo/src/time.c), philosopher routines (philo/src/routine.c), custom error handling (philo/src/utils/error_management.c), data structure creation and manipulation (philo/src/utils/structs_handler.c), argument validation (philo/src/utils/parsing.c), and a robust message system (philo/src/utils/display.c).Utilizing mutexes for synchronization, Philo simulates philosophers eating, thinking, and sleeping patterns while ensuring that each philosopher takes turns dining with appropriate rest periods. It also accounts for error scenarios with graceful handling and logging capabilities. With these features, the project allows users to explore the philosophical thought experiment in a dynamic and engaging way.

---

##  Features

| Feature   | Description                                                                                                                       |
|----------|-------------------------------------------------------------------------------------------------------------------------------|
| ⚙️       | **Architecture** The project follows an architecture based on the classic dining philosophers problem in concurrent computing. The source code is structured in multiple `C` files, including headers and utilities under the directories `inc` and `src`. A primary Makefile orchestrates the compilation of sources into a single executable.                           |
| 🔩       | **Code Quality** The code adheres to a consistent, modern style. It includes helpful comments throughout, error handling mechanisms, and a mix of local variables and global ones where appropriate. Functions and data structures are well-defined and easy to follow.                              |
| 📄       | **Documentation** Detailed comments for functions and major sections of the code provide ample insight into what each component does. The readme file also explains the purpose of the project and installation steps.                               |
| 🔌       | **Integrations** The project does not integrate with external APIs or services; it is a standalone solution for simulating the dining philosophers problem using C language constructs.                   |
| 💻      | **Platform Compatibility** The code has been tested on Linux systems using GCC/G++ compiler and should theoretically be compatible with any other POSIX-compliant operating system.             |
| ⏱       | **Running Time** As the program runs concurrently, running time varies depending on factors such as the number of philosophers and the processing power of your machine. The main factors influencing efficiency are synchronization, scheduling, and data access contention between philosophers.         |
| 🎨      | **Visual Interaction** No graphical interface is provided for this project; it runs solely from the command-line or terminal interface.                            |

---

##  Repository Structure

```sh
└── philosophers/
    └── philo
        ├── Makefile
        ├── inc
        ├── read_me.md
        └── src
```

---

##  Modules

<details closed><summary>philo</summary>

| File                                                                          | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| ---                                                                           | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| [Makefile](https://github.com/Jauppp/philosophers/blob/master/philo/Makefile) | The provided Makefile for the philo project is the primary build script for an open-source C application. This makefile orchestrates the compilation of source files and their dependencies into the executable philo. The main functionality is written across multiple files located under src, while utility functions are stored in utils. Additionally, this file offers clean, rebuild, help options to facilitate user interactions. It also supports running additional diagnostic tools like Valgrind for memory leak checks and race detection. |

</details>

<details closed><summary>philo.inc</summary>

| File                                                                            | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| ---                                                                             | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| [philo.h](https://github.com/Jauppp/philosophers/blob/master/philo/inc/philo.h) | The `philo/inc/philo.h` header file, crucial for the philosophers repositorys architecture, outlines the data structures and function prototypes necessary to manage multiple philosophers who eat, think, sleep, and take forks as per given rules. This includes a struct for each fork, philosopher, and argument variables like time to eat, sleep, and die. The file also houses utility functions for error management, parsing input, creating structures, and displaying status messages, ultimately enabling the programs core functionality of simulating the philosophers' actions and interactions. |

</details>

<details closed><summary>philo.src</summary>

| File                                                                                              | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| ---                                                                                               | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| [initialisation.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/initialisation.c) | This file, initialisation.c, kick-starts the philo project by establishing necessary mutexes and variables. It initializes forks, assigns each philosopher unique identities, and launches individual threads. The core function `init_philo` configures resources to ensure synchronized dining amongst the philosophers."                                                                                                                                                                                                                                                                  |
| [main.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/main.c)                     | Instantiating a data structure containing essential parameters for each philosopher, such as thread ID, meal count limit, and death timestamp.-Launching threads for each philosopher to perform eating, thinking, and sleeping actions according to the rules defined.-Ensuring proper cleanup of resources when the philosophers' dining session is over, including destroying allocated memory, and lock-free critical sections.Ultimately, it ensures synchronized, simulated dining behavior among a defined number of philosophers adhering to given time constraints and meal limits. |
| [time.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/time.c)                     | Time.c` measures time elapsed between events like eating, thinking, and sleeping.2. Provides function to calculate the duration since a specific point in time (e.g., last meal).3. Implemented `get_time_elapsed()` for measuring intervals in milliseconds.4. Features a wait function that introduces randomness in philosopher actions, based on provided delay.5. Maintains consistency by locking time measurements with a mutex.                                                                                                                                                      |
| [routine.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/routine.c)               | The `philo/src/routine.c` file orchestrates the dining routine for each philosopher, regulating their thinking, eating, and sleeping patterns. By coordinating access to the philosophers virtual forks, this module ensures each meal is followed by appropriate rest before another commences, thus simulating philosophical contemplation in a digital environment.                                                                                                                                                                                                                       |

</details>

<details closed><summary>philo.src.utils</summary>

| File                                                                                                        | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   |
| ---                                                                                                         | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| [error_management.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/error_management.c) | In the `philosopher` repository, the file `philo/src/utils/error_management.c` serves as a custom error handling mechanism for the project. This function, named `derr()`, facilitates logging and reporting of errors to the standard error stream, enhancing the applications fault-tolerance and debugging capabilities. The function gracefully handles diverse error scenarios, providing useful insights in case of an issue.                                                                                                                                                                       |
| [structs_handler.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/structs_handler.c)   | The utils_handler.c' file is an integral part of the Philo project's architecture. It primarily handles the creation and manipulation of data structures required by the philosophers, such as forks and philosopher instances. The function `create_t_fork` generates a fork object, while `create_t_philo` creates a philosopher instance, assigning each philosopher their specific forks and identifying data. The routine thread function and the cleanup function `destroy_t_fork` are also defined in this file, ensuring the smooth functioning of the philosophers within the program.           |
| [parsing.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/parsing.c)                   | In this code residing at philo/src/utils/parsing.c, crucial error handling functions for validating arguments are implemented, ensuring that only numerical values are accepted in the input parameters. These checks contribute significantly to the robustness and integrity of the philo program within the repository architecture, thereby enhancing its overall functionality and usability.                                                                                                                                                                                                        |
| [_atoi.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/_atoi.c)                       | The _atoi.c utility in the philo/src/utils/ directory takes a character pointer as input and converts it to an integer value. This function is critical for handling numerical arguments across the Philosopher project, ensuring accurate data processing. It accounts for leading whitespaces, handles positive or negative integers, and employs range checks for overflow and underflow protection in its algorithm.                                                                                                                                                                                  |
| [display.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/display.c)                   | Empower** the communication within the Philosopher program by crafting customizable message outputs.The `philo/src/utils/display.c` file within the repository structure serves as the message generator, offering essential functionalities for displaying specific messages formatted to the applications standards. It provides key utility functions such as `ft_putendl_fd()`, `ft_putl_fd()`, and `status_message()`. These enable flexible logging, printing statuses with timestamps and process IDs, contributing to the robustness of the Philosopher system in its management of philosophers. |
| [routine_utils.c](https://github.com/Jauppp/philosophers/blob/master/philo/src/utils/routine_utils.c)       | This C file, `routine_utils.c`, embedded in the `philo` folder of the `philosophers` repository, houses functions essential for coordinating meal routines among philosophers. It manages when philosophers start eating (`get_starting_time`), waits for their starting time (`wait_to_go`), checks if a philosopher is alive or not (`alive`), ensures all philosophers have eaten required meals (`all_fed`), and sets meal limits (`meal_limit`). This coordination helps facilitate the thinking process in this thought experiment.                                                                 |

</details>

---

##  Getting Started

**System Requirements:**

* **C**: `version x.y.z`

###  Installation

<h4>From <code>source</code></h4>

> 1. Clone the philosophers repository:
>
> ```console
> $ git clone https://github.com/Jauppp/philosophers
> ```
>
> 2. Change to the project directory:
> ```console
> $ cd philosophers
> ```
>
> 3. Install the dependencies:
> ```console
> $ gcc -o myapp main.c
> ```

###  Usage

<h4>From <code>source</code></h4>

> Run philosophers using the command below:
> ```console
> $ ./myapp
> ```

###  Tests

> Run the test suite using the command below:
> ```console
> $ /* No common unit test framework in C */
> ```

---

##  Project Roadmap

- [X] `► INSERT-TASK-1`
- [ ] `► INSERT-TASK-2`
- [ ] `► ...`

---

##  Contributing

Contributions are welcome! Here are several ways you can contribute:

- **[Report Issues](https://github.com/Jauppp/philosophers/issues)**: Submit bugs found or log feature requests for the `philosophers` project.
- **[Submit Pull Requests](https://github.com/Jauppp/philosophers/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.
- **[Join the Discussions](https://github.com/Jauppp/philosophers/discussions)**: Share your insights, provide feedback, or ask questions.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/Jauppp/philosophers
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="center">
   <a href="https://github.com{/Jauppp/philosophers/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=Jauppp/philosophers">
   </a>
</p>
</details>

---

##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- List any resources, contributors, inspiration, etc. here.

[**Return**](#-overview)

---
