# RTOS
```
The real-time operating system (RTOS) that has been implemented is designed to provide efficient
task scheduling and synchronization for embedded systems. This RTOS incorporates key features
such as preemption, round-robin scheduling, Priority Inheritance, as well as support for mutexes, counting semaphores,
and mailboxes. These features enable the system to handle concurrent tasks, prioritize critical
operations, and ensure efficient resource sharing.

Preemption, a fundamental feature of this RTOS, allows tasks to be interrupted and preempted
by higher-priority tasks. This mechanism ensures that critical tasks can be executed in a
timely manner, even in the presence of lower-priority tasks. By allowing tasks to be preempted,
the RTOS significantly enhances responsiveness and enables the system to meet stringent
real-time requirements.

Another important scheduling mechanism integrated into this RTOS is round-robin scheduling.
Round-robin ensures fair allocation of CPU time among tasks of equal priority. Each task is
granted a fixed time slice or quantum, after which the next task in the queue is executed.
This approach prevents any single task from monopolizing the CPU and ensures a balanced
distribution of processing time.

To facilitate synchronization and resource sharing, this RTOS incorporates synchronization
primitives such as mutexes, counting semaphores, and mailboxes. Mutexes provide mutual
exclusion, allowing only one task to access a shared resource at a time. Counting semaphores
enable synchronization between multiple tasks by allowing a specified number of tasks to access
a shared resource simultaneously. Mailboxes provide a communication mechanism between tasks,
allowing them to exchange data and messages in a controlled manner.

By combining preemption, round-robin scheduling, and synchronization mechanisms, this RTOS
provides a reliable and efficient platform for concurrent task execution in embedded systems.
It offers the ability to meet real-time constraints, prioritize critical operations, and ensure
the proper use of shared resources. With these features,the implemented RTOS offers a robust
foundation for building complex, responsive, and reliable embedded applications.
```

## Table of Contents
- [Hardware](#hardware)
- [State Machine of the RTOS](#state_machine_of_the_rtos)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Features](#features)
- [License](#license)


## Hardware
```
Stm32f103
```
  
## State Machine of the RTOS
![alt text](./images/rtos.ppm)

## Getting Started
```
- In a Firmware Over The Air (FOTA) project, a NodeMCU-based telematics unit can be used to
  download firmware updates wirelessly from a remote server
- To download firmware updates from a remote server, the NodeMCU must first connect
  to a Wi-Fi network.
  Once connected, the NodeMCU can use standard communication protocols such as HTTP or
  MQTT to communicate with the remote server and check if any update is available or not,
  if it found it will download the firmware update as a hex file. The NodeMCU can store the
  firmware update in its internal flash memory or external storage such as an SD card or EEPROM.
- Once the firmware update is downloaded, the NodeMCU can initiate the update process on
  the target device using the bootloader.
```

## Usage
1. Configurations
```
You can configure the RTOS throught the OS_config.h file located in service/include folder
```
2. Using the features of the RTOS
```
You can use the RTOS by including the OS_interface.h file located in service/include folder
```
## Features
1. mutex
2. semaphore
3. mailbox
4. priority ineritance
5. preemption(high priority task can interrupt low priority task)
6. round robin(for the tasks that equal in priority)

## License
```
This Project is released under the MIT License ↗. Feel free to use it in your own projects, 
modify it, and distribute it as needed. If you find any issues or have suggestions for
improvement, please open an issue or submit a pull request.
```







