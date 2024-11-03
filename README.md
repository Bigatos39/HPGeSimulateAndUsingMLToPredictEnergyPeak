# Optimization of HPGe Detectors Using Geant4 Programing

This project focuses on the optimization of High Purity Germanium (HPGe) detectors for detecting and analyzing gamma radiation with high accuracy, a critical tool in the field of nuclear physics.

## Project Overview

HPGe detectors are widely used for precise gamma radiation detection due to their high resolution. This research explores an optimization method for HPGe detector configuration, utilizing the **Geant4 simulation program**. The goal is to enhance detection efficiency and improve the accuracy of measurements.

## Contact Information

For further details, contact:
- **Email**: 20230059@student.hcmus.edu.vn, rasagenvi@gmail.com

## How to Run

1. **Install Geant4**: Follow the official [Geant4 installation guide](https://geant4.web.cern.ch/support/download) to install the required simulation environment.
2. **Configure the simulation environment**: Update the configuration files according to your specific detector requirements.
3. **Clone this repository**:
    ```bash
    git clone https://github.com/Bigatos39/HPGeSimulateAndUsingMLToPredictEnergyPeak.git
    cd HPGeSimulate
    ```
4. **Run the simulation with the viewer**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ./sim 
    ```
5. **Run the simulation**:
    ```bash
    cd build
    ./sim simulation.mac
    ```
6. **See the energy distribution**:
   ```bash
   g++ -o energyDistribution energyDistribution.cc
   ./energyDistribution
   ``` 
