# Attiny1604 examples<br />
A collection of C code for the attiny1604 and other compatible micro-controllers. I try to keep all the code in this collection as straightforward and simple as possible. You can easily copy and paste the code into your projects, allowing you to focus on what really matters, developing your projects! 😁 <br />
<br />
<h3>Examples:</h3>
<ul>
<li>Real Time Counter 1sec. periodic interupt - Attiny1604_RTC.c </li>
<li>TCA Timer overflow interupt example - Attiny1604_timer_overflow_interrupt.c</li>
<li>UART example with interrupt - Atiny1604_UART_interrupt.c</li>
<li>Led Blink (GPIO) - Attiny1604_input_GPIO.c </li>
<li>Read input pin(GPIO) - attiny1604_input_GPIO.c </li>
<li>External Pin Change Interrupt - Attiny1604_ext_pin_interrupt.c </li>
<li>PWM 6 x 8bit in Split mode TCA - Attiny1604_Split_mode_PWMx6.c</li>
<li>PWM 3 x 16bit in Single slope mode TCA - Attiny1604_16bit_PWM_TCA.c </il>
<li>Use RTC for millis() function (system tick) - RTC millis function.c </il>
<li>How to use the Internal temperature sensor - in directory /Attiny1604_internal_temperature_sensor/(main.c, uart_printf.c, uart_printf.h)</li>
<li> How to Control up to three Servo with 16bit PWM signals - Attiny1604_Servo_control_16bit.c</li>
</ul>
<br />
<h3>Libraries:</h3>
<ul>
<li>DateTime library - in folder attiny1604_DateTime_lib/ (main.c, datetime1604.c, datetime1604.h, uart_tx.c, uart_tx.h) </li>
<li>DS18b20 library - in folder attiny1604_DS18b20_lib/ (main.c, ds18b20.c, ds18b20.h, uart_tx.c, uart_tx.h) </li>
<li>Uart TX only library - in folder  /uart_tx/ (main.c, uart_tx.c, uart_tx.h) </li>
</ul>

<br />
<h3>How do I get the code to work?</h3>
For the code examples, all you need to do is copy the code into the main.c file of your new project and it will work. 
And for the libraries, you must copy or import all of the files that are in the directory. And the main.c files have an example of how you use the libery in your own main.c, or use it as startpoint for your own projects. <br />
<br />
The examples are compatible with other attiny's, like the attiny804, attiny1617, attiny204, attiny404, etc. <br />
The the code is written in Microchip studio 7.0 with GCC compiler<br />
<br />
<br />
<h3>List of external tinyAVR compatible libs:</h3> 
<ul>
<li>OLED 0.91"128x64 lib: https://github.com/wagiminator/ATtiny13-TinyOLEDdemo</li>
<li>V-USB_TinyAvr: https://github.com/12oclocker/V-USB_TinyAvr</li>
</ul
<br />
<br />
If you are looking for all the name difinations, the iotn1604.h has all the defines, bitmasks, and names of the registers and so for teh 1604. 
