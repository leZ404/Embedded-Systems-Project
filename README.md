# Embedded-Systems-Project
Project 1 -  Software Engineering Bachelor First Year.


This project was designed as part of the embedded systems integrator project for the first year (INF1900) in software and computer engineering at the Polytechnic School of Montreal.

## Usage

To use this robot, you need to follow these six instructions:

1. **Clean the library:** 
   - In the `project/Application/lib` folder, use the command:
     ```
     make clean
     ```

2. **Compile the library:** 
   - In the `project/Application/lib` folder, use the command:
     ```
     make
     ```

3. **Clean the app folder:** 
   - In the `project/Application/app` folder, use the command:
     ```
     make clean
     ```

4. **Compile and install the executable on the robot:** 
   - In the `project/Application/app` folder, use the command:
     ```
     make install
     ```
   - To debug, use:
     ```
     make debug
     ```

### Starting the Course

- Choose the desired state using the push button placed on the breadboard.
- Once the LED shows the color of the requested route, press the push button on the motherboard to confirm the choice.

## Folder Structure

### lib Folder

This folder contains all the classes to control and manipulate the robot and its peripherals. 

- **Class handling output devices:**
  - motor.cpp
  - del.cpp
  - sonorite.cpp
  - usart.cpp
  - LineSensor.cpp

- **Class handling input devices:**
  - Button.cpp
  - Interrupt.cpp
  - can.cpp

- **Class handling the external memory of the robot:**
  - memoire_24.cpp
  - loadingMemoireExterne.cpp

### app Folder

This folder is the executable of the robot. It includes all the files of the library.
