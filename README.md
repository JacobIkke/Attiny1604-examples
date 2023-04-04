# Attiny1604 examples<br />
A collection of C code for the attiny1604 micro-controller. <br />
<br />
<p>Examples:</p>
<ul>
<li>DateTime library - in folder attiny1604_DateTime_lib/ (main.c, datetime1604.c, datetime1604.h, uart_tx.c, uart_tx.h) </li>
<li>DS18b20 library - in folder attiny1604_DS18b20_lib/ (main.c, ds18b20.c, ds18b20.h, uart_tx.c, uart_tx.h) </li>
<li>Real Time Counter - Attiny1604_RTC.c </li>
<li>TCA Timer overflow interupt example - Attiny1604_timer_overflow_interrupt.c</li>
<li>Led Blink (GPIO) - Attiny1604_input_GPIO.c </li>
<li>Uart TX only library - in folder  /uart_tx/ (main.c, uart_tx.c, uart_tx.h) </li>
<li>Read input pin(GPIO) - attiny1604_input_GPIO.c </li>
<li>External Pin Change Interrupt - Attiny1604_ext_pin_interrupt.c </li>
</ul>
<br />
The examples are compatible with other attiny's, like the attiny804, attiny1617, attiny204, attiny404, etc. <br />
The the code is written in Microchip studio 7.0 with GCC compiler<br />
<br />
<br />
<p>List of external tinyAVR compatible libs:</p> 
<ul>
<li>OLED 0.91"128x64 lib: https://github.com/wagiminator/ATtiny13-TinyOLEDdemo</li>
<li>V-USB_TinyAvr: https://github.com/12oclocker/V-USB_TinyAvr</li>
</ul
<br />
<br />
If you are looking for all the name difinations, the iotn1604.h has all the defines, bitmasks, and names of the registers and so for teh 1604. 
