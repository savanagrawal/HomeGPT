
<a href="https://github.com/savanagrawal/HomeGPT" target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/HomeGPT_icon.png" alt="HomeGPT" width="200" height="200" /></a>

\
This repository will follow the development of an Home Assistant project HomeGPT based on real-time embedded system. This is a post-graduate project for the [University of Glasgow](https://gla.ac.uk).




[![Linktr.ee](https://mib3avenger.com/raspberry-pi/images/icons8-link-48.png)](https://linktr.ee/homegpt)
[![Instagram](https://mib3avenger.com/raspberry-pi/images/icons8-instagram-48.png)](https://www.instagram.com/homegpt/)
[![Twitter](https://mib3avenger.com/raspberry-pi/images/icons8-twitter-48.png)](http://twitter.com/HomeGPT)
[![Youtube](https://mib3avenger.com/raspberry-pi/images/icons8-youtube-48.png)](https://www.youtube.com/@HomeGPT)


## Contents
- [About](#1)
- [Getting Started](#2)
- [Docs](https://savanagrawal.github.io/HomeGPT/html/index.html)
- [Libraries/Dependencies/Softwarers](#3)
- [Data Sheets](#4) 
- [Team Members](#5)
- [License](#6)
- [Code of Conduct](#7)
- [Contributing](#8)


<a id='1'></a>
## About
The HomeGPT project is a smart home automation system that makes use of cutting-edge technologies to provide a secure and comfortable living space. These technologies include face detection -> mood-based lighting controls -> RFID-based garage entry -> and fire warning.

With the use of facial recognition -> the user is able to enter the residence thanks to the face detection capability. The same functionality is employed to identify unauthorised entrance by intruders.

![RFID](https://mib3avenger.com/raspberry-pi/images/facial_recognition.jpg)

In accordance with mood -> the device may also manage lighting. Based on the user's facial expressions -> it can tell how they are feeling. Based on mood detection -> it modifies light hue to calm the user. 

User may enter a home or garage with an RFID key. As a result -> the homeowner doesn't require standard keys to enter the residence.

</br>

![RFID](https://mib3avenger.com/raspberry-pi/images/RFID_RC522_and_Raspberry_pi_bb.png)


Last but not least -> the fire detection feature activates fire alarms when smoke or fire is detected using the MQ2 smoke detector sensor. An effective -> practical -> and secure home automation solution is provided by HomeGPT.

</br>

![MQ2Sensor](https://mib3avenger.com/raspberry-pi/images/MQ2_ADC_and_Raspberry_pi.png)


<a id='2'></a>

## Getting Started
1. Clone the repository.
```sh
git clone https://github.com/savanagrawal/HomeGPT
git submodule init
git submodule update
```
2. Create build directory.
```sh
mkdir build && cd build
```
3. Build the binaries.
```sh
cmake ../
make
```
4. Run Program.
```sh
sudo ./HomeGPT --module
```

All the modules are listed as:

```sh
"--create-intruder-dataset" -> Create Intruder dataset
"--cid" -> Create Intruder dataset
"--train-intruder-model" -> Train Intruder model
"--tim" -> Train Intruder model
"--detect-intruder" -> Detect Intruder
"--di" -> Detect Intruder
"--detect-clap" -> Detect Claps
"--dc" -> Detect Claps
"--rfid" -> Read RFID.
"--imd" -> Start Intruder and Mood detection together.
```


<a id='3'></a>

## Libraries / Dependencies / Softwares

- Raspbian (Debian 10 : Buster/Legacy)
- C++
- OpenCV
- CMake
- Boost
- PortAudio
- twyleg/spidevpp - A ported version to work with C++11.
- twyleg/mfrc522-cpp


<a id='4'></a>
## Data Sheets
- [Raspberry Pi 3 : Model B : V1.2](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_3_Model_B_V1.2.pdf)
- [Raspberry Pi Camera Module 1080P 5MP](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_Camera_Module_1080P_5MP.pdf)
- [BOB-12009: Bidirectional Logic Level Converter Board](https://github.com/savanagrawal/HomeGPT/hardware/BOB_12009_Bidirectional_Logic_Level_Converter_Board.pdf)
- [ADS1115 16-Bit ADC : 4 Channel with Programmable Gain Amplifier](https://github.com/savanagrawal/HomeGPT/hardware/ADS1115_16_Bit_ADC_4_Channel_with_Programmable_Gain_Amplifier.pdf)
- [TowerPro Servo Motor - SG90 Digital](https://github.com/savanagrawal/HomeGPT/hardware/TowerPro_Servo_Motor_SG90_Digital.pdf)
- [MQ-2 : Butane Hydrogen LPG Gas Smoke Detector](https://github.com/savanagrawal/HomeGPT/hardware/MQ_2_Butane_Hydrogen_LPG_Gas_Smoke_Detector_datasheet_and_schematics.pdf)
- [RC522 RFID Module 13.56MHz](https://github.com/savanagrawal/HomeGPT/hardware/RC522_RFID_Module_13.56MHz.pdf)


<a id='5'></a>
## Team Members

[@savanagrawal](https://github.com/savanagrawal) - Savan Agrawal (GUID: 2781593A) - MSc in Robotics and AI - Intruder, Mood and Clap detection.<br>
[@hrushisanap](https://github.com/hrushisanap) - Hrushikesh Sanap (GUID: 2819312S) - MSc in Robotics and AI - Fabrication, Documentation and Circuit Making<br>
[@MustafaZari](https://github.com/MustafaZari) - Mustafa Zariwala (GUID: 2617991Z) - MSc in Robotics and AI - Fabrication and Documentation<br>
[@MiB3Avenger](https://github.com/MiB3Avenger) - Chinmay Nagrale (GUID: 2788044N) - MSc in Computer Systems Engineering - Threads, Peripherals Integration and Circuit Making<br>

<a id='6'></a>
## License
View our [License](https://github.com/savanagrawal/HomeGPT/blob/main/LICENSE) here.


<a id='7'></a>
## Code of Conduct
We follow our [Code of Conduct](https://github.com/savanagrawal/HomeGPT/blob/main/CODE_OF_CONDUCT.md) strictly.

<a id='8'></a>
## Contribution Guidelines
Want to contribute? Read our [Contribution](https://github.com/savanagrawal/HomeGPT/blob/main/CONTRIBUTING) guidelines.