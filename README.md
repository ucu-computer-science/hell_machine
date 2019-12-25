# Hell Machine

#### Project of Morhunenko Mykola ([Myralllka](https://github.com/Myralllka)) and Yuriy Pasichnyk ([Fenix](https://github.com/Fenix-125)) :ant: :wave:
---

  This project aims to be a final course project in Principles of Computer Organization at [Computer Science Program](http://cs.ucu.edu.ua/en/) of [Ukrainian Catholic Univercity](https://ucu.edu.ua/en/). As curator and mentor of our project, we have our lector of this discipline - Mr. Oleg Farenyuk. All workflows, results, and details are on the [Wiki page](https://github.com/Myralllka/hell_machine/wiki). Also, more photos, presentations, and other materials you cat view on our [Google Drive](https://drive.google.com/open?id=1ABIGUnLVCTMDhI9LD8ZWX-bDr1mLIJnS).

## Project structure
All directories are System Workbench for STM32 projects (SW4STM32).

* [4wheelsSTM32F411](https://github.com/Myralllka/hell_machine/tree/master/4wheelsSTM32F411) - 
* [BCMotor](https://github.com/Myralllka/hell_machine/tree/master/BCMotor) - 
* [led](https://github.com/Myralllka/hell_machine/tree/master/led) - 
* [rotary_motor](https://github.com/Myralllka/hell_machine/tree/master/rotary_motor) - rotation of the wills with bluetooth (wthout angle conrol)
* [sonar](https://github.com/Myralllka/hell_machine/tree/master/sonar) - usage of the [JSN-SR04T](https://www.roboter-bausatz.de/media/pdf/83/0f/93/JSN-SR04T_outputmode.pdf) (Ultrasonic double integration module; ultrasonic sensor).
* [whils_turn](https://github.com/Myralllka/hell_machine/tree/master/whils_turn) - other varian of will turning


## Documentation for the Car
| Characteristics | Description |
| --------------- | :---------: |
| Max Speed       | +0 m / s    |
| Length          | +- 1.2 m    |
| Width           | +- 0.4 m    |
| Hight           | +- 0.3 m    |
| Acum Capacity   | +- 2.0 Ah   |
| Distance Ctrls. | +- 5.0 m    |
|                 |             |

### How is it looks like:
  It looks pretty close to the new Tesla track :) without any taste in "front-end" but with strong possibilities in "back-end."
![top image](https://github.com/Myralllka/hell_machine/blob/master/Media/first_steps/photo_2019-11-27_23-41-37.jpg)
![schematics](https://user-images.githubusercontent.com/44115554/71449843-2a1ad780-275f-11ea-8a52-69982922a718.png)
![in_action](https://user-images.githubusercontent.com/44115554/71450255-f6dc4680-2766-11ea-945c-3368f94b8e9e.gif)


### What is inside:
<!-- Description and specifications of all elements on the schematic -->
<!-- #### Motors & Drivers:
There are two types of motors inside: four Brushless DC motors inside wheels and two DC motors for turning the front and back will-pairs independently. Motors inside wheels are just simple BLDC from the hoverboard.<br>
And [here](http://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf) is the datasheet for the driver used to rotate the motor.
<!--
#### Encoders:
Not supported yet
<!--
#### Logic:
Not supported yet
<!--
#### Sensors:
Not supported yet
<!--
#### Power:
We have two batteries 36V for BLDC motors in the wheels and two batteries 12V for everything else.
<!--
#### Magic things(in plans to understand)
Not supported yet
___
<!--
#### ROS
We started working with the Robotic Operation System. -->


## Team Achievements
- STM32 (STM32F3DISCOVERY, STM32F103 (blue pill)) timers, interucpts, GPIO
- PWM usage ([servo](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf), [step motors](http://eeshop.unl.edu/pdf/Stepper+Driver.pdf))
- Driver usage ([first](http://grauonline.de/wordpress/?page_id=3122), [second](https://ru.aliexpress.com/item/32950460565.html?spm=a2g0o.detail.1000014.33.280374eaN0gGtG&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=e700e67a-c0ac-406b-9729-c6caa390c35d))
- [Ultrasonic sonar](https://www.roboter-bausatz.de/media/pdf/83/0f/93/JSN-SR04T_outputmode.pdf) usage
- Electrisiety workwlow (5V - 12V - 36V) experience
- Soldering skills

# Additional
* [Google table](https://docs.google.com/spreadsheets/d/13Saorbgh8zXmlXp2oCmv79j6O5-RJ3W5ENbF93QNehc/edit?ts=5dde4f19#gid=0) of all used materials of the project<br>
* [Git repository](https://github.com/ucuapps/robert_the_robot) of our preventors<br>
* The inintial idea [source](https://github.com/NiklasFauth/hoverboard-firmware-hack)<br>
