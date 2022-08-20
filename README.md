# getUpTimer
The code for a simple Arduino circuit to remind me to move from the desk periodically

I've a tendency to spend 8 hours slumped over the desk, which isn't good for me. I built a simple arduino circuit to buzz every half hour, to remind me to move

The circuit has three LEDs attached, a piezo buzzer, and two buttons. The LEDs light in turn after 10 minute intervals (green, yellow, red). After 30 minutes, the piezo buzzer goes off, and will continue to buzz until either the reset or sleep button are pressed. The reset button starts the count again. The sleep button pauses the run until pressed again.

Time since start and current status are outputted via the serial port


