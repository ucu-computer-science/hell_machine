# CAR
---
#### Project of Morhunenko Mykola ([Myralllka](https://github.com/Myralllka)) and Yuriy Pasichnyk ([Fenix](https://github.com/Fenix-125)) :ant: :wave:
---
## Begin

We started our work with the help of our teacher Oleg Farenyuk. Firstly our Car was like a dying monster without any functions. Mr Oleg bought us a few drivers to work with it: the [first](http://grauonline.de/wordpress/?page_id=3122) and the [second](https://ru.aliexpress.com/item/32950460565.html?spm=a2g0o.detail.1000014.33.280374eaN0gGtG&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=e700e67a-c0ac-406b-9729-c6caa390c35d). The first one is up to 36V, but it is cheap Chinees driver, so it exploded. For Voltage less then 25V, it is an excellent driver for Brushless DC motors. Now we are working with the second one. After the first tests, it didn\`t explode, so we are going to continue working with it.
## First try
As I have mentioned, our first try was on the first driver for 12V. Here you can view the [result](https://www.youtube.com/watch?v=lqymeNPksB4)
___
## TODO:
|Until the presentation|Until the end of semester|Until the end of the year|
|-|-|-|
|describe the problem with the car| | |
|describe what we have done| | |
| make a short description of our responsibilities for the future|finish the first part | |
|make wheels rotate|make Car work on drivers|make the Car move. every motor have to be independent.|
| |make wheels to turn right-left|create software for the Car to rotate back and front wheels independantly|
|make the documentation to the Car| the same|the same|
|make research on sensors|work with sensors(at least two types)|work with all sensors|
___
## Description of the problem
At the Applied Science Faculty at Ukrainian Catholic University, we have a Car project. Previous year students started doing it in the SoftServe company, but the process stack on first steps, so teachers decided to relocate it to the University. Now we with Yura are working on it.
___
## What we have done
- Learned how PWM works
- Rotated the servo drive
- Rotated the step motor
- Rotated small BLDC motor using PWM (back and forward, with different speed, quick stop and with decoding of the speed signal)
- Started to write documentation
- Changed one driver (explode previous one).
- Understood for sure how does the Car works.
___
## Documentation for the Car
### How is it looks like:
It looks pretty close to the new Tesla track :) without any taste in "front-end" but with strong possibilities in "back-end".
![]()
### What is inside:
#### Motors & Drivers:
There are two types of motors inside: four Brushless DC motors inside wheels and two DC motors for turning the front and back will-pairs independently. Motors inside wheels are just simple BLDC from the hoverboard.
And [here](http://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf) is the datasheet for the driver used to rotate the motor.
#### Encoders:
Not supported yet
#### Logic:
Not supported yet
#### Sensors:
Not supported yet
#### Power:
We have two batteries 36V for BLDC motors in the wheels and two batteries 12V for everything else.
#### Magic things(in plans to understand)
Not supported yet
___
# ROS
We started working with the Robotic Operation System

# Additional
[here](https://docs.google.com/spreadsheets/d/13Saorbgh8zXmlXp2oCmv79j6O5-RJ3W5ENbF93QNehc/edit?ts=5dde4f19#gid=0) google table
[here](https://github.com/ucuapps/robert_the_robot) one git of prev course
[here](https://github.com/NiklasFauth/hoverboard-firmware-hack) general git of things like this

