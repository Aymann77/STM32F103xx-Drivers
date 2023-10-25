
# STM32F103xx-Drivers

This Repository contains a collection of Drivers for STM32F103xx Family microcontrollers , commonly used and tested with Panda Kit Uses Blue Pill Based on ARM Cortex-M3 Processor . These Drivers Follow the Layered Archeticture by Abstracting the Drivers' Components into Layers to make Using Them Much Easier in Applications .

## Authors

Mohammed Shalaby  
[@Mohammed Ayman](https://www.linkedin.com/in/mohameddayman/)

## Features:
- Peripheral Drivers: This repository provides drivers for various on-chip peripherals such as GPIO, UART, SPI, I2C, and more.
- Board Support Packages: We offer board-specific support packages for the "Panda Kit" STM32F103xx development board, making it easy to get started with your specific hardware.
- Documentation: Detailed documentation on using the drivers and integrating them into your projects.

## Prerequisites:
Before using these drivers, ensure that you have the following prerequisites:
- STM32CubeIDE for developing and debugging STM32 firmware.
- ST-Link or any compatible debugger for programming and debugging the microcontroller.
- The "Panda Kit" STM32F103xx development board.

## Installation:
Follow these steps to get started with the STM32F103xx drivers:
1. Clone this repository to your local machine:
   ```
   git clone https://github.com/Aymann77/STM32F103xx-Drivers.git
   ```
2. Open STM32CubeIDE and configure your STM32F103xx microcontroller according to your project's requirements. 
4. Copy the relevant drivers from this repository to your project's source directory.
5. Start using the drivers by including the necessary headers and calling the appropriate functions.

## Contributing

We welcome contributions to further enrich our STM32F446xx Drivers Repository. If you have enhancements, bug fixes, or additional drivers to share, please follow these contribution guidelines:

1. **Fork the Repository:** Begin by forking this repository to your GitHub account.

2. **Create a Feature Branch:** Create a dedicated feature branch for your contribution:

   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Implement and Test:** Implement your changes or additions, ensuring thorough testing.

4. **Commit and Push:** Commit your changes with clear and descriptive commit messages, then push your branch to your forked repository.

5. **Submit a Pull Request:** Create a pull request to the `main` branch of this repository, providing comprehensive details about your changes.
