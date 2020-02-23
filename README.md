# Hell Machine

#### Project of Morhunenko Mykola ([Myralllka](https://github.com/Myralllka)) and Yuriy Pasichnyk ([Fenix](https://github.com/Fenix-125)) :ant: :wave:
---

  This project aims to be a final course project in Principles of Computer Organization at [Computer Science Program](http://cs.ucu.edu.ua/en/) of [Ukrainian Catholic Univercity](https://ucu.edu.ua/en/). As curator and mentor of our project, we have our lector of this discipline - Mr. Oleg Farenyuk. All workflows, results, and details are on the [Wiki page](https://github.com/Myralllka/hell_machine/wiki). Also, more photos, presentations, and other materials you cat view on our [Google Drive](https://drive.google.com/open?id=1ABIGUnLVCTMDhI9LD8ZWX-bDr1mLIJnS).

## Project structure
All directories are System Workbench for STM32 projects (SW4STM32).

* [4wheelsSTM32F411](https://github.com/Myralllka/hell_machine/tree/master/4wheelsSTM32F411) - The main project.
* [BCMotor](https://github.com/Myralllka/hell_machine/tree/master/BCMotor) - training project for the small BCMotor
* [led](https://github.com/Myralllka/hell_machine/tree/master/led) - just training project
* [rotary_motor](https://github.com/Myralllka/hell_machine/tree/master/rotary_motor) - rotation of the wheels with bluetooth (wthout angle conrol)
* [sonar](https://github.com/Myralllka/hell_machine/tree/master/sonar) - usage of the [JSN-SR04T](https://www.roboter-bausatz.de/media/pdf/83/0f/93/JSN-SR04T_outputmode.pdf) (Ultrasonic double integration module; ultrasonic sensor).
* [whils_turn](https://github.com/Myralllka/hell_machine/tree/master/whils_turn) - other varian of wheel turning
* [supension](https://github.com/Myralllka/hell_machine/tree/master/supension) - auto control of the supension (using ADC and interupts)

## Documentation for the Car
| Characteristics | Description |
| --------------- | :---------: |
| Max Speed       | +- 5 m / s  |
| Length          | +- 1.2 m    |
| Width           | +- 0.4 m    |
| Hight           | +- 0.3 m    |
| Acum Capacity   | +- ??? Ah   |
| Distance Ctrls. | +- ??? m    |
|                 |             |

### How is it looks like:
### It looks pretty close to the new Tesla track :) without any taste in "front-end" but with strong possibilities in "back-end."<br>
![image](https://drive.google.com/uc?export=view&id=1U94w5piADHNLzKi0OwvMuK8d6Tnl2rWY)
### [Schmetics](https://github.com/Myralllka/hell_machine/blob/master/schematic_hell_machine_wiring.pdf) of the wiering.<br>
![schematics](https://user-images.githubusercontent.com/44115554/71449843-2a1ad780-275f-11ea-8a52-69982922a718.png)
### How it moves on 20% of power.<br>
![in_action](https://user-images.githubusercontent.com/44115554/71450255-f6dc4680-2766-11ea-945c-3368f94b8e9e.gif)

## Team Achievements
- STM32 (STM32F4DISCOVERY, STM32F3DISCOVERY, STM32F103 (blue pill)) timers, interucpts, GPIO
- PWM usage ([servo](http://www.ee.ic.ac.uk/pcheung/teaching/DE1_EE/stores/sg90_datasheet.pdf), [step motors](http://eeshop.unl.edu/pdf/Stepper+Driver.pdf))
- Driver usage ([first](http://grauonline.de/wordpress/?page_id=3122), [second](https://ru.aliexpress.com/item/32950460565.html?spm=a2g0o.detail.1000014.33.280374eaN0gGtG&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.13338.128125.0&scm_id=1007.13338.128125.0&scm-url=1007.13338.128125.0&pvid=e700e67a-c0ac-406b-9729-c6caa390c35d))
- [Ultrasonic sonar](https://www.roboter-bausatz.de/media/pdf/83/0f/93/JSN-SR04T_outputmode.pdf) usage
- Accelerometers (I2C)
- Gyroscope (SPI)
- Electrisiety workwlow (5V - 12V - 36V) experience
- Soldering skills
- ROS basics

## More information
for more information you can view our [wiki](https://github.com/Myralllka/hell_machine/wiki) page

# Additional
* [List](https://github.com/Myralllka/hell_machine/wiki/Materials-List) of all used materials of the project<br>
* [Git repository](https://github.com/ucuapps/robert_the_robot) of our preventors<br>
* The inintial idea [source](https://github.com/NiklasFauth/hoverboard-firmware-hack)<br>
