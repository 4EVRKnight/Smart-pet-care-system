# Smart-pet-care-system

hello, We're doing a project on Arduino UNO, which is about the "Smart Pet care system".
our system's functionalities are the following,

1. There is a main gate (Controlled by a servo motor(let's say Servo1)), which should be opened(open position=0 degrees) only for 5 seconds if it detects my RFID tag(A0 84 2C 0E - this is my RFID tag's UID) using RFID module (RC522). this is because, after setting this RFID tag on the pet's collar band, the door should be opened only when the RFID module detects the tag on the pet's collar band. When the pet gets inside the system (the system is like a home), the main gate should be closed(close position=90 degrees) (after 5 seconds). when the pet wants to go outside, the pet will come near the main gate, the RFID and the Servo motor will do the same job again and after the pet goes out, the main gate will be closed (after 5 seconds).

2. There is a food dispenser (it's a cuboid chamber with an empty space of 26cms vertically), which should dispense the food using another servo motor(let's say Servo2), which means, the bottom of the chamber has a hole to output the food. So, Servo2 hides the hole(normally hidden) while blocking the food, and it should be opened(open position=45 degrees) once every 6 hours only for 3 seconds and close(close position=0 degrees) the hole. In that way, food distribution should happen. 

3. Within the lid of the above-said chamber, there is an ultrasonic sensor to measure the availability of the food. if the empty space exceeds 16cms(the length is measured by the Ultrasonic sensor), there is a LED light, which should blink. Otherwise, it should be turned off. it means if there's less food, a blinking LED indicates to refill the food, after refilling the food, the LED should be off.

4. There is a Water Pump and a Water Level Sensor in charge to keep the water level constant. This means, besides dispensing food there is a water bowl in our system, which provides water for the pet. When the water level sensor reads a value below 280, the water pump should be turned on for 5 seconds in order to maintain the water level in the water bowl.

following are the pin connections with numbers on my Arduino UNO,

"
0-

1-

2- trigger

3- echo

4- Servo2

5- LED

6-

7- Water Pump

8- Servo1

9- RST

10- SDA

11- MOSI

12- MISO

13- SCK

A0- Water Level Sensor
"


## Features

1. **RFID-Controlled Pet Gate**: 
   - Uses an RC522 RFID module to detect a specific RFID tag attached to your pet's collar.
   - Opens a servo-controlled gate for 5 seconds when the tag is detected, allowing the pet to enter or exit.
   - Automatically closes the gate after 5 seconds.

2. **Automated Food Dispenser**: 
   - Dispenses food every 6 hours using a servo motor to control the food release mechanism.
   - Integrated ultrasonic sensor monitors the food level, triggering an LED to blink when the food is low.

3. **Water Level Management**: 
   - Monitors the water level in a bowl using a water level sensor.
   - Activates a water pump for 5 seconds to refill the bowl when the water level drops below a specified threshold.

## Technical Details

- **Arduino Uno** is the main microcontroller.
- **RC522 RFID Module** detects the pet's RFID tag.
- **Servo Motors** (Servo1 for gate control, Servo2 for food dispensing) manage physical movements.
- **Ultrasonic Sensor** monitors the food level.
- **Water Level Sensor** and **Water Pump** maintain water availability.
- **Non-blocking Code**: The project utilizes the `millis()` function to manage timing events, ensuring simultaneous operation of all components without delays.

## Hardware Requirements

- Arduino Uno
- RC522 RFID Module
- 2x Servo Motors
- Ultrasonic Sensor
- Water Level Sensor
- Water Pump
- LEDs
- Breadboard and connecting wires

## How It Works

This system is designed to operate autonomously, providing food and water to your pet while ensuring they can move in and out of a designated area. The use of non-blocking code ensures that the system remains responsive, handling multiple tasks at once without interruption.

## Installation and Setup

1. Clone the repository.
2. Connect the hardware components according to the provided pin configuration.
3. Upload the Arduino code to your Arduino Uno.
4. Place the RFID tag on your pet's collar.
5. Power the system and monitor its operation.

