### TODO:

Create a 'sequencer' that allows you to record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. You should be able to:
- record at a least a few seconds of button input to your RP2040 (in RAM) :heavy_check_mark:
- replay a recorded sequence on your NeoPixel :heavy_check_mark:
- loop a recording :heavy_check_mark:
- save a recording to your laptop (the Python Serial library is one way to do this) :heavy_check_mark:
- play a recording from your laptop :heavy_check_mark:
- record 'macros' (a sequence of console commands) based on keystrokes in your serial console :heavy_check_mark:
- hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
- include multiple I/O sources in a recording, and remap among the following: :heavy_check_mark:
    - inputs: BOOT button, console commands, register read/write commands
    - outputs: neopixel color, neopixel brightness, data over serial, register read/write commands

- update your sequencer to be able to record just the timestamped transitions between input values, and to be able to play data in this format :heavy_check_mark:
- give your sequencer the ability to select a range of output rates for both live and recorded input :heavy_check_mark: