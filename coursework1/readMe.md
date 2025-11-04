
## COMP0002 Principles of Programming

## C Coursework

**Description:**

This program generates a randomly sized array with obstacles, markers and a robot in it.

There are obstacles around, forming a randomly sized circular area in the middle. The robot is able to move inside this area, but cannot move onto any grid of obstacle.

Markers are randomly distributed in the circular area. The robot has to move around to pick up markers and stop immediately when all markers are collected.

<br><br>

**Compile and Run Program:**

**Unzip** `COMP0002CW1.zip` and run a terminal program inside the directory.

**Copy** `drawapp-4.5.jar`, `graphics.c`, and `graphics.h` to the directory.

<br>

To **compile** the program, run the following command in Windows PowerShell / Command Prompt / Windows Subsystem for Linux:

`gcc -o window background.c foreground.c robot.c graphics.c window.c`

<br>

To **execute** the program, run the following command in Windows PowerShell / Windows Subsystem for Linux:

`./window | java.exe -jar drawapp-4.5.jar`

For Command Prompt, run the following command to execute the program:

`window.exe | java.exe -jar drawapp-4.5.jar`


