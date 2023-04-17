<a href="https://github.com/savanagrawal/HomeGPT" target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/HomeGPT_icon.png" alt="HomeGPT" width="200" height="200" /></a>

\
\
</br>
This repository will follow the development of an Home Assistant project HomeGPT based on real-time embedded system. This is a post-graduate project for the [University of Glasgow](https://gla.ac.uk).




[![Linktr.ee](https://mib3avenger.com/raspberry-pi/images/icons8-link-48.png)](https://linktr.ee/homegpt)
[![Instagram](https://mib3avenger.com/raspberry-pi/images/icons8-instagram-48.png)](https://www.instagram.com/homegpt/)
[![Twitter](https://mib3avenger.com/raspberry-pi/images/icons8-twitter-48.png)](http://twitter.com/HomeGPT)
[![Youtube](https://mib3avenger.com/raspberry-pi/images/icons8-youtube-48.png)](https://www.youtube.com/@HomeGPT)


---

## Contents
- [About](#1)
- [Getting Started](#2)
- [Code](#3)
- [Libraries/Dependencies/Softwarers](#4)
- [Data Sheets](#5) 
- [Team Members](#6)
- [LicenE](#7)

---


<a id='1'></a>

### About
The HomeGPT project is a smart home automation system that makes use of cutting-edge technologies to provide a secure and comfortable living space. These technologies include face detection, mood-based lighting controls, RFID-based garage entry, and fire warning.

With the use of facial recognition, the user is able to enter the residence thanks to the face detection capability. The same functionality is employed to identify unauthorised entrance by intruders.


In accordance with mood, the device may also manage lighting. Based on the user's facial expressions, it can tell how they are feeling. Based on mood detection, it modifies light hue to calm the user. 

User may enter a home or garage with an RFID key. As a result, the homeowner doesn't require standard keys to enter the residence.
\
</br>

![RFID](https://github.com/savanagrawal/HomeGPT/img/RFID_RC522_and_Raspberry_pi_bb.png)


Last but not least, the fire detection feature activates fire alarms when smoke or fire is detected using the MQ2 smoke detector sensor. An effective, practical, and secure home automation solution is provided by HomeGPT.
\
</br>

![MQ2Sensor](https://github.com/savanagrawal/HomeGPT/img/MQ2_ADC_and_Raspberry_pi.png)




---
<a id='2'></a>

### Getting Started
\
\
\
\
\
\
</br>


---
<a id='3'></a>

### Codes

To Test
```cmake -S . -B build/ -G"Unix Makefiles"```

To Build & Run (Windows)
```cd build && make && HomeGPT.exe && cd ..```

---
<a id='4'></a>

### Libraries / Dependencies / Softwares

- Raspbian (Debian 10 : Buster/Legacy)
- C++
- OpenCV (Version: 4.7.0)
- CMake (Version: 3.0)
- Boost (Version: 1.80)
- PortAudio




---
<a id='5'></a>

### Data Sheets
- [Raspberry Pi 3 : Model B : V1.2](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_3_Model_B_V1.2.pdf)
- [Raspberry Pi Camera Module 1080P 5MP](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_Camera_Module_1080P_5MP.pdf)
- [BOB-12009: Bidirectional Logic Level Converter Board](https://github.com/savanagrawal/HomeGPT/hardware/BOB_12009_Bidirectional_Logic_Level_Converter_Board.pdf)
- [ADS1115 16-Bit ADC : 4 Channel with Programmable Gain Amplifier](https://github.com/savanagrawal/HomeGPT/hardware/ADS1115_16_Bit_ADC_4_Channel_with_Programmable_Gain_Amplifier.pdf)
- [TowerPro Servo Motor - SG90 Digital](https://github.com/savanagrawal/HomeGPT/hardware/TowerPro_Servo_Motor_SG90_Digital.pdf)
- [MQ-2 : Butane Hydrogen LPG Gas Smoke Detector](https://github.com/savanagrawal/HomeGPT/hardware/MQ_2_Butane_Hydrogen_LPG_Gas_Smoke_Detector_datasheet_and_schematics.pdf)
- [RC522 RFID Module 13.56MHz](https://github.com/savanagrawal/HomeGPT/hardware/RC522_RFID_Module_13.56MHz.pdf)

---


<a id='6'></a>
### Team Members

[@savanagrawal](https://github.com/savanagrawal) - Savan Agrawal (GUID: 2781593A) - MSc in Robotics and AI - Coding<br>
[@hrushisanap](https://github.com/hrushisanap) - Hrushikesh Sanap (GUID: 2819312S) - MSc in Robotics and AI - Fabrication and Documentation and Circuit making<br>
[@MustafaZari](https://github.com/MustafaZari) - Mustafa Zariwala (GUID: 2617991Z) - MSc in Robotics and AI - Fabrication and Documentation<br>
[@MiB3Avenger](https://github.com/MiB3Avenger) - Chinmay Nagrale (GUID: 2788044N) - MSc in Computer Systems Engineering- Coding and Circuit making<br>

<a id='7'></a>
## License
Link to [LICENSE](https://github.com/savanagrawal/HomeGPT/LICENSE) doc