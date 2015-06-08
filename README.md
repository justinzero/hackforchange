# hackforchange
A simple Arduino sensor array prototype designed for demonstrating the capabilities available for firefighter safety.

This was built over the course of one day during the Southwest Florida Regional Tech Partnership's Hack For Change civic hackathon. The provided kit included sensors from Sunfounder, with little documentation; different sensors may require tweaking the code.

**Included Sensor Modules**
- Temperature
- Smoke/Gas
- Mercury Switch
- Flame Detection
- Humidity

This program takes input from each of the sensors and outputs standard JSON data to the serial interface. It could easily be adapted for the Wifi or network shields to be sent over TCP/IP. The JSON format is portable enough to allow for uploading the output to a database or converting to a spreadsheet for data visualization.
