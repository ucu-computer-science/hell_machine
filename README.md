# Hell Machine
---
#### Project of Morhunenko Mykola ([Myralllka](https://github.com/Myralllka)) and Yuriy Pasichnyk ([Fenix](https://github.com/Fenix-125)) :ant: :wave:
---
## Begin
  This project aims to be a final course project in Principles of Computer Organization at [Computer Science Program](http://cs.ucu.edu.ua/en/) of [Ukrainian Catholic Univercity](https://ucu.edu.ua/en/). As curator and mentor of our project, we have got our lector of this discipline - Mr. Oleg Farenyuk. At the very beginning, as the basis to start, we got a metallic frame with some machinery or, in other words: just a pile of metal. With the help of our mentor, we got few drivers to work with: the [first](http://grauonline.de/wordpress/?page_id=3122) and the [second](https://ru.aliexpress.com/item/32950460565.html?spm=a2g0o.detail.1000014.33.280374eaN0gGtG&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=e700e67a-c0ac-406b-9729-c6caa390c35d).<br><br>
  The first one is a cheap Chinees driver. Due to the datasheet, it should be up to 36V, but an experiment(it exploded) has shown that it was misleading information. For Voltage less then 25V, it was an excellent driver for BLDCs. A short success [video](https://www.youtube.com/watch?v=lqymeNPksB4) with this driver under 12V.<br><br>
  Working up with the second driver, we encounter difficulties with finding out: how to work with them. After a lot of research, we finally find some "datasheets" and guidelines to similar drivers, but unfortunately, we find out that our driver did not work.
___

## TODO:
|Until the presentation|Until the end of semester|Until the end of the year|
|----------------------|-------------------------|-------------------------|
|describe the problem with the car| | |
|describe what we have done| | |
| make a short description of our responsibilities for the future|finish the first part | |
|make wheels rotate|make Car work on drivers|make the Car move. every motor have to be independent.|
| |make wheels to turn right-left|create software for the Car to rotate back and front wheels independantly|
|make the documentation to the Car| the same|the same|
|make research on sensors|work with sensors(at least two types)|work with all sensors|
___

## Short prehistory
This project started even earlier. Our predecessors started to work on this project at [SoftServe](https://www.softserveinc.com/en-us/), but the process stack at first steps, so the University decided to break down this workflow and work on their own on this project at the campus. Now our team is working on it as our course project.

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
It looks pretty close to the new Tesla track :) without any taste in "front-end" but with strong possibilities in "back-end."
![]()

### What is inside:

#### Motors & Drivers:
There are two types of motors inside: four Brushless DC motors inside wheels and two DC motors for turning the front and back will-pairs independently. Motors inside wheels are just simple BLDC from the hoverboard.<br>
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
* [Google table](https://docs.google.com/spreadsheets/d/13Saorbgh8zXmlXp2oCmv79j6O5-RJ3W5ENbF93QNehc/edit?ts=5dde4f19#gid=0) of all used materials of the project<br>
* [Git repository](https://github.com/ucuapps/robert_the_robot) of our preventors<br>
* The inintial idea source [source](https://github.com/NiklasFauth/hoverboard-firmware-hack)<br>
