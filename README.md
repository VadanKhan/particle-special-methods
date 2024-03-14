# Particle Physics Simulation

This project simulates particle physics interactions using C++. It includes the creation of various particles, calculation of their four-momenta, and operations such as sum and dot product of four-momenta.

## Files

- `main.cpp`: This is the main script that creates particles, performs operations on them, and prints out their details.
- `particle.h`: This is the header file for the `particle` class. The `particle` class represents a particle in the simulation. It includes methods for getting and setting particle properties, printing particle data, and performing operations such as sum and dot product of four-momenta.

## Particle Class

The `particle` class includes the following methods:

- `get_type()`: Returns the type of the particle.
- `get_energy()`, `get_px()`, `get_py()`, `get_pz()`: Return the energy and momentum components of the particle's four-momentum.
- `get_charge()`: Returns the charge of the particle.
- `is_empty()`: Checks if the particle is empty.
- `set_type()`, `set_energy()`, `set_px()`, `set_py()`, `set_pz()`, `set_charge()`: Set the type, energy, momentum components, and charge of the particle.
- `print_data()`: Prints the details of the particle.
- `charge_conjugate()`: Flips the particle to an anti-particle.
- `operator+()`: Returns the sum of the four-momenta of two particles.
- `dotProduct()`: Returns the dot product of the four-momenta of two particles.

Additionally, the class includes the following special member functions:

- **Copy Constructor**: Creates a new object as a copy of an existing object. It correctly copies the `type`, `charge`, and `four_momentum` members. It also prints out "Calling copy constructor" when it is invoked.
- **Copy Assignment Operator**: Assigns the values of one object to another. It correctly handles self-assignment and memory management. It also prints out "Calling copy assignment operator" when it is invoked.
- **Move Constructor**: Creates a new object by moving the resources of an existing object. It correctly handles the case where the source object is left in a valid but unspecified state. After the move operation, the original `particle` object is left with a `nullptr` for `four_momentum` and its `type` is set to "Ghost". It also prints out "Calling move constructor" when it is invoked.
- **Move Assignment Operator**: Assigns the values of one object to another by moving resources. It correctly handles self-assignment and memory management. After the move operation, the original `particle` object is left with a `nullptr` for `four_momentum` and its `type` is set to "Ghost". It also prints out "Calling move assignment operator" when it is invoked.
- **Destructor**: Deletes the `four_momentum` pointer to prevent memory leaks. It also prints out "Destroying" followed by the type of the particle.


## Built With

* GCC - The GNU Compiler Collection

## Build & run Instructions

### Prerequisites

You will need a C++ compiler that supports C++17. The code has been tested with GCC 11.

### Compiling

1. Open a terminal in the project directory.
2. Compile the program using the following command:

**For Windows** This command will produce the following file in the same directory you're running on:

`g++ assignment-4.cpp -o assignment-4.exe -std=gnu++17`

Which you can then execute in a terminal using:

`./assignment-4.exe`


**For Mac** This command will produce the following file in the same directory you're running on:

`g++ assignment-4.cpp -o assignment-4.o -std=gnu++17`

Which you can then execute in a terminal using:

`./assignment-4.o`

Note: One can also use make files to automate this compilation.
**For Windows**: you can install MinGW's makefile.exe and then use 'nmake' command when in root directory
Note this will expect the Makefile to be in root directory with name "Makefile"
**For Mac**: Can just run `make`.
Note this will expect the Makefile to be in root directory with name "Makefile"

You can find out more about Makefiles [here](https://www.gnu.org/software/make/manual/html_node/Introduction.html) or [in this simple starter guide](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/) but we won't cover these in the course.

## Authors

* 10823198 - 4 vector particle simulator (OOP) - [Student Github](https://github.com/VadanKhan)