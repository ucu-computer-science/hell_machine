# CAR
---
#### Project of Morhunenko Mykola ([Myralllka](https://github.com/Myralllka)) and Yuriy Pasichnyk ([Fenix](https://github.com/Fenix-125)) :ant: :wave:
---
## Begin

We started our work with the help of our teacher Oleg Farenyuk. Firstly our Car was like a dying monster without any functions. Mr Oleg bought us a few drivers to work with it: the [first](http://grauonline.de/wordpress/?page_id=3122) and the [second](https://ru.aliexpress.com/item/32950460565.html?spm=a2g0o.detail.1000014.33.280374eaN0gGtG&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=e700e67a-c0ac-406b-9729-c6caa390c35d). First one is up to 36V, but it is cheap Chinees drivers, so it was exploded. But for Voltage less then 25V it is an excellent driver for Brushless DC motors. Now we are working with the second one. After the first trial, it didn\`t explode, so we are going to continue working with it.
## First try
As I have mentioned, our first trie was on the first driver, from 12V. here is the [result](https://www.youtube.com/watch?v=lqymeNPksB4)
___
## TODO:
|Until the presentation|Until the end of semester|Until the end of the year|
|-|-|-|
|describe the problem with the car| | |
|describe what we have done| | |
| make short description of our responsibilities for the future|finish the first part | |
|make wheels to rotate|make car to drivers|make car to drive. every motor have to be independent.|
| |make wheels to turn right-left|create a software for car to rotate back and front wheels independantly|
|make a documentation to the car| the same|the same|
|started working with sensors|work with sensors(at least 2 types)|work with all sensors|
___
## Description of the problem
In the University, at the Applied Science Faculty, we have a car. Our previous year students started doing it in the SoftServe company, but their success was not big, so teachers decided to take it to the University. So now we with Yura are working with it.
___
## What we have done
- learned how pwm works
- rotated the servo drive
- rotated the step motor
- rotated small BLDC motor using PWM (back and force, with different speed, quick stop and with deckoding of the speed signal)
- started documentation.
- changed one driver (explode previose one).
- understand for sure how does the car works.
___
## Documentation for the car
### How is it looks like:
It looks pretty close to the new Tesla track :) without any taste in "fornt-end" but with big possibilities in "back-end".
![]()
### What is inside:
#### Motors & Drivers:
There are two types of the motors inside: four Brushless DC motors inside wheels and two DC motors for turning the front and the back sides independently. Motors inside wheels - just simple BLDC from the hoverboard.
And [here](http://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf) is the datasheet for the driver for turning motor.
#### Encoders:
Not supported yet
#### Logic:
Not supported yet
#### Sensors:
Not supported yet
#### Power:
we have two bataries 36V for BLDC mottors in the wheels and two bateries 12V for everything else.
#### Magic things(in plans to understand)
Not supported yet
___

# Additiona
[here](https://docs.google.com/spreadsheets/d/13Saorbgh8zXmlXp2oCmv79j6O5-RJ3W5ENbF93QNehc/edit?ts=5dde4f19#gid=0) google table
[here](https://github.com/ucuapps/robert_the_robot) one git of prev course
[here](https://github.com/NiklasFauth/hoverboard-firmware-hack) general git of things like this

