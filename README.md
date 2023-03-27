# LEGO-7866-arduino-nano-l293-sensors
Automated LEGO 7866 set
This is a custom DIY upgrade of the LEGO 7866 set.
The set is automated with Arduino nano, obstacle sensors, l293 motor driver.
Features:
Manual control (classic, via the original switch)

Automatic operation
    - logic and control is done by Arduino nano
   - 2 obstacle sensors recognize the direction of train movement
and accordingly close and open the passage, and turn on and
off the light signalling
   - the gaps between the wagons are recognized and until the
entire train composition has passed, the sensor does not react
   - Pass control is entirely dependent on sensors (not timed.
Eg., if a train stops between sensors, the ramp will not raise
until the train passes the exit sensor).
   - l293 is the driver that starts the ramp motors (1/2 IC
connected to H-bridge) and turns on and off the LEGO blink
modules (1/4 IC in half H-bridge mode).

Manual + automatic, they do not exclude each other
