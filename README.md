# Creating the README.md content based on the provided description

readme_content = """
# Optimization of HPGe Detectors Using Geant4 Simulation

This project focuses on the optimization of High Purity Germanium (HPGe) detectors for detecting and analyzing gamma radiation with high accuracy, a critical tool in the field of nuclear physics.

## Project Overview

HPGe detectors are widely used for precise gamma radiation detection due to their high resolution. This research explores an optimization method for HPGe detector configuration, utilizing the **Geant4 simulation program**. The goal is to enhance detection efficiency and improve the accuracy of measurements.

## Key Features

- **Geant4 Simulation Setup**: The project includes the configuration of the Geant4 simulation environment for modeling HPGe detectors.
- **Detector Configuration Optimization**: Various configurations of HPGe detectors are tested and optimized to achieve higher detection efficiency.
- **Result Analysis**: The analysis compares the efficiency and accuracy of different configurations, highlighting the most effective setup for gamma radiation measurements.

## Benefits

By using the Geant4 program for optimization, this project demonstrates significant improvements in the effectiveness and reliability of HPGe detectors in gamma radiation measurements.

## Contact Information

For further details, contact:
- **Email**: 20230059@student.hcmus.edu.vn
"""

# Saving the content to a README.md file
file_path = "/mnt/data/README.md"
with open(file_path, "w") as f:
    f.write(readme_content)

file_path
