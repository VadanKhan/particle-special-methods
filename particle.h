#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Beginning of particle class
class particle
{
  const double LIGHT_SPEED = 2.99792458e8; // ms^-1
  const double ELECTRON_MASS = 0.51099;    // MeV
  const double MUON_MASS = 105.66;         // MeV
  const double TAU_MASS = 1776.9;          // MeV, there is higher uncertainty as much rarer
  const int LEPTON_CHARGE = -1;            // "e" (elementary charge)

private:
  std::string type{"Ghost"};
  std::vector<double> *four_momentum; // in MeV/c
  int charge{0};                      // in "e" (elementary charge)

public:
  // Default constructor
  particle() : four_momentum(new std::vector<double>(4, 0.0)) {}

  // Parameterized constructor
  particle(std::string particle_type, double energy_input, std::vector<double> three_momentum_input)
      : type{particle_type}, four_momentum(new std::vector<double>(4))
  {
    if (type == "e")
    {
      charge = LEPTON_CHARGE;
    }
    else if (type == "mu")
    {
      charge = LEPTON_CHARGE;
    }
    else if (type == "tau")
    {
      charge = LEPTON_CHARGE;
    }
    else if (type == "Ghost")
    {
      charge = 0;
    }
    else
    {
      throw std::invalid_argument("Invalid particle type. Must be 'e', 'mu', or 'tau'.");
    }

    // Validate the energy component
    if (energy_input < 0 || energy_input > LIGHT_SPEED)
    {
      throw std::invalid_argument(
          "Energy must be non-negative and less than the speed of light (3E8 ms^-1)");
    }

    // Push back the elements to four_momentum
    four_momentum->at(0) = energy_input;
    for (int i = 0; i < 3; ++i)
    {
      four_momentum->at(i + 1) = three_momentum_input.at(i);
    }
  }

  // Destructor
  ~particle()
  {
    std::cout << "Destroying " << type << "\n";
    delete four_momentum;
  }

  // Copy constructor
  particle(const particle &input_particle)
      : type{input_particle.type},
        four_momentum(new std::vector<double>(*input_particle.four_momentum)),
        charge{input_particle.charge}
  {
    std::cout << "Calling copy constructor\n";
  }

  // Move constructor
  particle(particle &&input_particle) noexcept
    : type{std::move(input_particle.type)}, four_momentum{input_particle.four_momentum},
      charge{std::move(input_particle.charge)}
  {
    std::cout << "Calling move constructor\n";
    input_particle.four_momentum = nullptr;
    input_particle.type = "Ghost";  // Added to help identify null vectors after moving
  }

  // Copy Assignment operator
  particle &operator=(const particle &input_particle)
  {
    std::cout << "Calling copy assignment operator\n";
    if (this != &input_particle)
    {
      type = input_particle.type;
      delete four_momentum;
      four_momentum = new std::vector<double>(*input_particle.four_momentum);
      charge = input_particle.charge;
    }
    return *this;
  }

  // Move assignment operator
  particle &operator=(particle &&input_particle) noexcept
  {
    std::cout << "Calling move assignment operator\n";
    if (this != &input_particle)
    {
      type = std::move(input_particle.type);
      delete four_momentum;
      four_momentum = input_particle.four_momentum;
      input_particle.four_momentum = nullptr;
      charge = std::move(input_particle.charge);
      input_particle.type = "Ghost";  // Added to help identify null vectors after moving
    }
    return *this;
  }

  // Getter methods
  std::string get_type() const { return type; }
  double get_energy() const { return four_momentum->at(0); }
  double get_px() const { return four_momentum->at(1); }
  double get_py() const { return four_momentum->at(2); }
  double get_pz() const { return four_momentum->at(3); }
  int get_charge() const { return charge; }

  // method to check if the particle is empty (as extra did not use narrower error catching)
  bool is_empty() const
  {
    if (four_momentum == nullptr)
    {
      return true;
    }
    try
    {
      get_energy();
      get_px();
      get_py();
      get_pz();
    }
    catch (const std::exception &e)
    {
      return true;
    }
    return false;
  }

  // Setter methods
  void set_type(const std::string &t)
  {
    if (t != "e" && t != "mu" && t != "tau")
    {
      throw std::invalid_argument("Invalid particle type. Must be 'e', 'mu', or 'tau'.");
    }
    type = t;
  }
  void set_energy(double E)
  {
    if (E < 0 || E > LIGHT_SPEED)
    {
      throw std::invalid_argument(
          "Energy must be non-negative and less than the speed of light (3E8 ms^-1)");
    }
    four_momentum->at(0) = E;
  }
  void set_px(double px) { four_momentum->at(1) = px; }
  void set_py(double py) { four_momentum->at(2) = py; }
  void set_pz(double pz) { four_momentum->at(3) = pz; }
  void set_charge(int c) { charge = c; }

  // Method to print out the details of a particle
  void print_data(const std::string &name = "Particle") const
  {
    std::cout.precision(3); // 2 significant figures
    std::cout << name << ": [type,charge,E,px,py,pz] = [" << type << "," << charge << ","
              << four_momentum->at(0) << "," << four_momentum->at(1) << "," << four_momentum->at(2)
              << "," << four_momentum->at(3) << "]" << std::endl;
    return;
  }

  // Implementation of flipping to antiparticle, that returns a pointers to be called in chain.
  particle& charge_conjugate() {
      charge = -charge;
      return *this;
  }

  // Overloaded operator for sum
  std::vector<double> operator+(const particle &p)
  {
    std::vector<double> sum_four_momentum(4);
    for (int i = 0; i < 4; ++i)
    {
      sum_four_momentum[i] = four_momentum->at(i) + p.four_momentum->at(i);
    }
    return sum_four_momentum;
  }

  // Function for the dot product of two particle four-vectors
  double dotProduct(const particle &p)
  {
    double dot_product = four_momentum->at(0) * p.four_momentum->at(0);
    for (int i = 1; i < 4; ++i) // 4vector dotting setting 3-momentum as negative.
    {
      dot_product -= four_momentum->at(i) * p.four_momentum->at(i);
    }
    return dot_product;
  }
};

#endif
