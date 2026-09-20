# Automated Rail-Guided Rural Transit System
> **Low-Cost Electric Light-Rail Prototype with Infrastructure-to-Vehicle Optical Communication**

An automated, low-cost guided transit prototype designed to address rural transportation and mobility challenges. The system utilizes a distributed control architecture where smart station nodes detect approaching vehicles via ultrasonic sensing and issue optical stop signals for scheduled passenger and cargo handling.

---

## System Concept & Working Principle

The system includes vehicle control and station sensing into two independent micro-controller nodes that interact autonomously:

1. **Vehicle Module:** Navigates along a physical rail track with progressive acceleration control. It features a front-mounted light-dependent resistor (LDR photoresistor) calibrated to detect station optical signals.
2. **Station Module:** Continuously scans the track using an ultrasonic sensor (HC-SR04). Upon detecting an incoming vehicle, it triggers a high-intensity signal LED.
3. **Dwell Time & Charging Cycle:** As the vehicle aligns with the station, its front LDR sensor detects the illuminated LED beam. The vehicle controller immediately reduces the motor power gradually to a really low value to allow time for passenger boarding or cargo loading. Once the internal timer elapses, the vehicle automatically resumes motion with a smooth acceleration ramp.

---

##  Hardware Architecture

### 1. Vehicle Unit (Locomotion & Reception)
* **Microcontroller:** Arduino UNO (ATmega328P)
* **Motor Driver:** L298N Dual H-Bridge Driver
* **Primary Sensor:** Light-Dependent Resistor (LDR Photoresistor) for optical signal detection
* **Actuators:** Dual DC Gearmotors with high-traction drive wheels
* **Chassis:** Laser-cut / custom MDF frame with an adjustable front sensor mount
### Power & Energy Distribution Strategy
* **Logic Unit Power (Arduino UNO):** Regulated 5V DC supply via USB AC Wall Adapter (prevents microcontroller brownouts and voltage drops during motor transients).
* **Actuators Power (L298N & Motors):** Dedicated AA Lithium Battery Bank (provides independent current path for inductive motor loads).

###  2. Station Unit (Infrastructure & Control)
* **Microcontroller:** Arduino UNO
* **Presence Sensor:** HC-SR04 Ultrasonic Distance Sensor
* **Optical Emitter:** High-intensity signal LED
* **Structure:** Balsa wood / MDF signaling post integrated into the track structure

---

##  System Control Logic & Workflow


 +-------------------------------+
 |  Vehicle in Motion on Track   |
 +-------------------------------+
                 │
                 ▼
 +-------------------------------+
 | Station: HC-SR04 detects vehicle | ──► [ Station: Turn ON Signal LED ]
 +-------------------------------+                      │
                                                        ▼
 +-------------------------------+        +----------------------------+
 | Vehicle: LDR detects LED beam | ◄───── | Optical Beam Transmission  |
 +-------------------------------+        +----------------------------+
                 │
                 ▼
 +-------------------------------+
 | Vehicle: Gradually reduces speed
  (PWM = 5)|
 +-------------------------------+
                 │
                 ▼
 +-------------------------------+
 |  Boarding/Loading Dwell Time  |
 +-------------------------------+
                 │
                 ▼
 +-------------------------------+
 | Vehicle: Progressive Ramp-Up  |
 +-------------------------------+
 ## Experimental Testbed & Results
To validate the mechatronic concept, a 1-meter balsa wood test track featuring a fully operational station module was constructed. Experimental runs confirmed 100% reliability in vehicle detection, precise optical signal trigger alignment, timed motor cutoffs, and autonomous motion resumption.
##  Engineering Insights & Design Iterations

* **Power Rail Decoupling:** During initial testing, a single 9V PP3 battery was tested to power both logic and motors. High internal resistance caused severe voltage drops during motor startup, leading to microcontroller resets and poor power for the motors to start. Isolated the power rails by supplying the Arduino UNO with a stable 5V DC source via a wall adapter while keeping an independent battery power bank for the L298N driver and DC motors, ensuring 100% system stability.

 * **Mechanical Drag & Sensor Alignment Optimization:** Integrated a passive front caster wheel to form a balanced tripod configuration (3-point support). This eliminated structural friction against the track surface and stabilized the vehicle's pitch, ensuring consistent optical alignment between the front LDR sensor and the station LED.

* **PWM Deadband And Breakout Torque Compensation:** Initial soft-start acceleration routines initialized the PWM ramp from zero, leading to a deadband state where motors were energized but lacked the breakout torque to overcome static friction. To resolve this, the ramp-up algorithm was adjusted to start directly at an empirical minimum threshold (`PWM_MIN`), enabling immediate motion engagement without motor stall.