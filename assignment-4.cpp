/*
 * Particle Physics Simulation
 *
 * This project simulates particle physics interactions using C++. It includes the creation of
 * various particles, calculation of their four-momenta, and operations such as sum and dot
 * product of four-momenta.
 *
 * Files:
 * - `main.cpp`: This is the main script that creates particles, performs operations on them,
 *   and prints out their details.
 * - `particle.h`: This is the header file for the `particle` class. The `particle` class
 *   represents a particle in the simulation. It includes methods for getting and setting
 *   particle properties, printing particle data, and performing operations such as sum and
 *   dot product of four-momenta.
 *
 * Particle Class:
 * The `particle` class includes the following methods:
 * - `get_type()`: Returns the type of the particle.
 * - `get_energy()`, `get_px()`, `get_py()`, `get_pz()`: Return the energy and momentum
 *   components of the particle's four-momentum.
 * - `get_charge()`: Returns the charge of the particle.
 * - `is_empty()`: Checks if the particle is empty.
 * - `set_type()`, `set_energy()`, `set_px()`, `set_py()`, `set_pz()`, `set_charge()`: Set the
 *   type, energy, momentum components, and charge of the particle.
 * - `print_data()`: Prints the details of the particle.
 * - `charge_conjugate()`: Flips the particle to an anti-particle.
 * - `operator+()`: Returns the sum of the four-momenta of two particles.
 * - `dotProduct()`: Returns the dot product of the four-momenta of two particles.
 *
 * Built With:
 * - GCC - The GNU Compiler Collection
 *
 * Authors:
 * - 10823198 - 4 vector particle simulator (OOP)
 */


#include "particle.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::string;

// Implementation of functions goes here

// End of particle class and associated member functions

// Main program
int main()
{
  // Create the following particles:
  // two electrons, four muons, one antielectron, one antimuon
  // Use the parameterised constructor to do these
  std::vector<double> three_momentum_electron{1, 0, 0};
  particle electron1("e", 0.51099, three_momentum_electron);
  particle electron2("e", 0.51099, three_momentum_electron);

  std::vector<double> three_momentum_muon{0, 1, 0};
  particle muon1("mu", 105.66, three_momentum_muon);
  particle muon2("mu", 105.66, three_momentum_muon);
  particle muon3("mu", 105.66, three_momentum_muon);
  particle muon4("mu", 105.66, three_momentum_muon);

  std::vector<double> three_momentum_anti_e{1, 0, 0};
  particle antielectron1("e", 0.51099, three_momentum_anti_e);
  antielectron1.charge_conjugate();

  std::vector<double> three_momentum_anti_mu{0, 1, 0};
  particle antimuon1("mu", 105.66, three_momentum_anti_mu);
  antimuon1.charge_conjugate();

  // (optional but nice) Print out the data from all the particles (put them in a vector)
  std::cout << "=================================================\n";
  std::cout << "Details of each instantiated particle:\n";
  std::vector<particle*> particles{&electron1, &electron2, &muon1, &muon2,
                                   &muon3,     &muon4,     &antielectron1, &antimuon1};
  int i = 1;
  for (const auto &particle : particles)
  {
      particle->print_data("Particle " + std::to_string(i) );
      ++i;
  }

  // Sum the four-momenta of the two electrons
  std::cout << "=================================================\n";
  std::cout << "4vector sum of the first two electrons:\n";
  std::vector<double> sum_electrons = electron1 + electron2;
  std::cout << "[" << sum_electrons[0] << ", " << sum_electrons[1] << ", "
            << sum_electrons[2] << ", " << sum_electrons[3] << "]\n";

  // Do the dot product of the first two four-muons
  std::cout << "=================================================\n";
  std::cout << "4vector dot of the first two muons:\n";
  double dot_product_muons = muon1.dotProduct(muon2);
  std::cout << "Dot product: " << dot_product_muons << "\n";

  // Assignment operator of an electron to a new electron
  std::cout << "=================================================\n";
  std::cout << "Assignment operator of an electron to a new electron:\n";
  particle new_electron;
  new_electron = electron1;
  new_electron.print_data("Copy by assignment new electron");
  electron1.print_data("Original Electron");

  // Copy constructor of the first muon to a new muon
  std::cout << "=================================================\n";
  std::cout << "Copy constructor of the first muon to a new muon:\n";
  particle new_muon{muon1};
  new_muon.print_data("Copy by construction new Muon");
  muon1.print_data("Original Muon");

  // Move the antielectron into another antielectron using the move constructor
  std::cout << "=================================================\n";
  std::cout << "Move the antielectron into another antielectron using the move constructor:\n";
  antielectron1.print_data("Old Anti-Electron");
  particle new_antielectron(std::move(antielectron1));
  new_antielectron.print_data("New Anti-Electron");
  if (antielectron1.is_empty()) {
    std::cout << "Code has detected original particle is empty after moving\n";
  }

  // Assign the antimuon to another antimuon using the move assignment
  std::cout << "=================================================\n";
  std::cout << "Assign the antimuon to another antimuon using the move assignment:\n";
  antimuon1.print_data("Old Antimuon");
  particle new_antimuon;
  new_antimuon = std::move(antimuon1);
  new_antimuon.print_data("New Anti-Muon");
  if (antimuon1.is_empty()) {
    std::cout << "Code has detected original particle is empty after moving\n";
  }

  std::cout << "=================================================\n";
  return 0;
}