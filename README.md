<div align="center"><a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/HomeGPT_icon.png" alt="HomeGPT" width="200" height="200" /></a></div>

<div align="center"><img style="margin-right:0.15rem;" src="https://img.shields.io/badge/LICENSE-MIT-yellow"/> <img src="https://img.shields.io/badge/Source-open-green"/></div>

\
<b><p style="text-align: center;"> HomeGPT: Transforming Homes with a clap, smile and a wave!! </p></b>


\
This repository will follow the development of an Home Assistant project HomeGPT based on real-time embedded system. This is a post-graduate project for the [University of Glasgow](https://gla.ac.uk).




[![Linktr.ee](https://mib3avenger.com/raspberry-pi/images/icons8-link-48.png)](https://linktr.ee/homegpt)
[![Instagram](https://mib3avenger.com/raspberry-pi/images/icons8-instagram-48.png)](https://www.instagram.com/homegpt/)
[![Twitter](https://mib3avenger.com/raspberry-pi/images/icons8-twitter-48.png)](http://twitter.com/HomeGPT)
[![Youtube](https://mib3avenger.com/raspberry-pi/images/icons8-youtube-48.png)](https://www.youtube.com/@HomeGPT)


## Contents
- [Commercial](#0)
- [About](#1)
- [Getting Started](#2)
- [Docs](https://savanagrawal.github.io/HomeGPT/html/index.html)
- [Libraries/Dependencies/Softwarers](#3)
- [Hardware Description](#4) 
- [Data Sheets](#5) 
- [Team Members](#6)
- [License](#7)
- [Code of Conduct](#8)
- [Contributing](#9)



<a id='0'></a>
## Commercial
Watch our demo on Youtube.

<div align="center"><a href="https://youtu.be/LWb74aEaucY" target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/thumbnail.jpg" alt="HomeGPT" width="600"  /></a></div>




<a id='1'></a>
## About
HomeGPT revolutionizes home automation with advanced features such as facial recognition for secure access, mood-responsive lighting, RFID-enabled garage entry, and clap-activated door closures. This system elevates the living experience by seamlessly blending security, convenience, and ambiance-enhancing technology.

#### Key Features

#### 1.  Facial Recognition based Home Entry
This feature ensures **SAFETY** of your home by recognizing entrants at the main door. A person can enter only if detected an ally for the people of the house. **Intruders** are **Not Allowed** as the doors won't open for you!
Real Time feed of camera at the door compares an entrant's image using HOG Classifier to generate signal for welcoming the person by opening the door.
You have new friend coming in, No problemo! we have feature to train the model and add new allies in real time as well!

<div align="center"><a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/facial_recognition.jpg" alt="HomeGPT" width="400" style="display:flex;margin: auto;justify-content: center;"/></a></div>


#### 2. Mood based Lighting Control
This state of art feature detects the mood of a person in room and **adjusts the lights** accordingly. Researchers believe that lighting levels have effect on the intensity of emotions. So now we can **lighten up the moods** and make the feel joyous in the house at all times!
Camera feed detects facial gestures in real time and uses SVM Model that has been trained on **Kaggle** https://www.kaggle.com/datasets/jonathanoheix/face-expression-recognition-dataset dataset suing OpenCV and HOG to compare your mood and distinguish it between 7 different moods Angry, Disgust, Fear, Happy, Neutral, Sad, Surprise in real time.

<div align="center"><a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/clap-detection.gif" alt="HomeGPT" width="500" style="display:flex;margin: auto;justify-content: center;" /></a></div>


#### 3. Key less Garage Entry for Vehicles
This feature lets you sit comfortably in the car when you reach your house and lets you park the car in garage comfortably by subtarcting the hustle of getting out of the car and **open the garage door*. ***RFID** Sensor detects the unique identity of your car at arrival and opens the garage door for your ease of parking! 


<div align="center"><a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/RFID_RC522_and_Raspberry_pi_bb.png" alt="HomeGPT" width="500" style="display:flex;margin: auto;justify-content: center;" /></a></div>


#### 4. Clap Detection for Door Shut using FFT (Fast Fourier Transform) & DFT (Discrete Fourier Transform) 
One of the stand-out feature of this project is detecting your **Clap** to **shut that door behind you**. So you can move freely in your house and ensure privacy. It's annoying if you forget to close a door behind you cause you were busy imagining your fantasy! And someone shouts from behind just to get you back into this cruel world holding accountable for manners!
Real Time feed of sound is convoluted on sample sets and peaks are evaluated to judge the clap intensity. In case of match, the signal is sent to actuator to shut the door.

<div align="center"><a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/mood-detection.gif" alt="HomeGPT" width="500" style="display:flex;margin: auto;justify-content: center;" /></a></div>

\
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
"--d" -> All modules together.
```

\
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

\
<a id='4'></a>
## Hardware Description

**Raspberry pi 3:**

<a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/raspberypi.jpg" alt="Rpi" width="300" /></a>

The Raspberry Pi 3 is a highly versatile and affordable single-board computer that offers impressive computing power in a compact form factor. Powered by a quad-core ARM Cortex-A53 processor running at 1.2 GHz, and equipped with 1 GB of RAM, it delivers smooth performance for a wide range of tasks.

With its various ports, including USB, HDMI, Ethernet, and GPIO, the Raspberry Pi 3 offers extensive connectivity options for peripherals and accessories, allowing for versatile integration into different projects. This makes it popular among hobbyists, educators, and DIY enthusiasts for a wide range of applications, from media centers and retro gaming consoles to robotics and smart home systems.

Overall, the Raspberry Pi 3 is a powerful and flexible single-board computer that offers a wide range of possibilities for hobbyists, students, educators, and DIY enthusiasts alike. Its compact size, affordable price, and impressive performance make it a popular choice for a wide range of computing projects and applications.

\
**Raspberry pi Camera Module:**

<a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/camra.jpg" alt="rpicam" width="200" /></a>

The camera module is compact and lightweight, making it easy to integrate into various projects. It connects to the Raspberry Pi via a ribbon cable, and the camera is controlled through software using the Raspberry Pi's GPIO pins. The module features a fixed-focus lens and is capable of capturing still images with a resolution of up to 8 megapixels, as well as high-definition video with up to 1080p resolution.

The Raspberry Pi Camera Module is highly versatile and can be used for a wide range of applications, including time-lapse photography, motion detection, facial recognition, object tracking, and more. It can be used in combination with other Raspberry Pi accessories and sensors to create custom camera solutions for specific projects or applications.

\
**RC522 RFID Module:**

<a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/F5MGYURIGGYFLK2.jpg" alt="rfid" width="350" /></a>

The RC522 RFID sensor is a small, low-cost module that allows for easy integration of RFID (Radio-Frequency Identification) technology with microcontroller projects. It operates at 13.56 MHz frequency and uses SPI (Serial Peripheral Interface) for communication, making it compatible with popular microcontrollers like Arduino and Raspberry Pi.

The RC522 sensor is capable of reading RFID tags and cards, and it can communicate with various types of RFID cards, including MIFARE cards, which are widely used in access control, authentication, and identification applications. It offers a reading range of a few centimeters, making it suitable for short-range applications.

\
**Tower Pro Servo Motor - SG90 Digital:**

<a target="_blank"><img src="https://mib3avenger.com/raspberry-pi/images/servo.jpg" alt="servo" width="350" /></a>

The Tower Pro SG90 is a digital servo motor, a type of motor that is widely used in robotics, RC (remote control) vehicles, and other applications that require precise and controlled angular movements. The SG90 is compact and lightweight, making it suitable for small-scale projects. It offers a torque of up to 1.8 kg/cm, a rotation range of 180 degrees, and operates on a voltage range of 4.8V to 6V. The digital technology in the SG90 provides improved accuracy, responsiveness, and reliability compared to analog servo motors. It is compatible with popular microcontrollers like Arduino and Raspberry Pi, and can be easily controlled using PWM (Pulse Width Modulation) signals. The Tower Pro SG90 digital servo motor is a popular choice for hobbyists and DIY enthusiasts due to its affordability, ease of use, and reliable performance in various applications.

\
<a id='5'></a>
## Data Sheets
- [Raspberry Pi 3 : Model B : V1.2](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_3_Model_B_V1.2.pdf)
- [Raspberry Pi Camera Module 1080P 5MP](https://github.com/savanagrawal/HomeGPT/hardware/Raspberry_Pi_Camera_Module_1080P_5MP.pdf)
- [BOB-12009: Bidirectional Logic Level Converter Board](https://github.com/savanagrawal/HomeGPT/hardware/BOB_12009_Bidirectional_Logic_Level_Converter_Board.pdf)
- [ADS1115 16-Bit ADC : 4 Channel with Programmable Gain Amplifier](https://github.com/savanagrawal/HomeGPT/hardware/ADS1115_16_Bit_ADC_4_Channel_with_Programmable_Gain_Amplifier.pdf)
- [TowerPro Servo Motor - SG90 Digital](https://github.com/savanagrawal/HomeGPT/hardware/TowerPro_Servo_Motor_SG90_Digital.pdf)
- [RC522 RFID Module 13.56MHz](https://github.com/savanagrawal/HomeGPT/hardware/RC522_RFID_Module_13.56MHz.pdf)

\
<a id='6'></a>
## Team Members

|Name|Github|GUID|Course|Role|
|---|---|---|---|---|
|Savan Agrawal|[@savanagrawal](https://github.com/savanagrawal)|2781593A|MSc in Robotics and AI| Intruder, Mood and Clap detection|
|Chinmay Nagrale|[@MiB3Avenger](https://github.com/MiB3Avenger)|2788044N|MSc in Computer Systems Engineering|Threads, Peripherals Integration and Circuit Making|
|Hrushikesh Sanap|[@hrushisanap](https://github.com/hrushisanap)|2819312S|MSc in Robotics and AI|Fabrication, Documentation and Circuit Making|
|Mustafa Zariwala|[@MustafaZari](https://github.com/MustafaZari)|2617991Z|MSc in Robotics and AI|Fabrication and Documentation|

\
<a id='7'></a>
## License
View our [License](https://github.com/savanagrawal/HomeGPT/blob/main/LICENSE) here.

\
<a id='8'></a>
## Code of Conduct
We follow our [Code of Conduct](https://github.com/savanagrawal/HomeGPT/blob/main/CODE_OF_CONDUCT.md) strictly.

\
<a id='9'></a>
## Contribution Guidelines
Want to contribute? Read our [Contribution](https://github.com/savanagrawal/HomeGPT/blob/main/CONTRIBUTING) guidelines.