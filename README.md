# V-2D-XY-Digitizer the Unplotter
2D (XY) Scanner / Digitizer based on V plotter design of polar machines like gocupi

### The Math behind

![image](https://user-images.githubusercontent.com/11083514/46237650-cf3cd980-c37d-11e8-8ee5-98169dc075ce.png)

Tanks to Debra for the drawing and math, taken from her project [YAWP](http://www.geekmomprojects.com/yawp-yet-another-wall-plotter/)

Other references: http://setosa.io/ev/sine-and-cosine/

----
The circuit draws around 30mA. Outputs are open collector with 20 Ohm resistors for protection. Nice to see that they have added a “fools diode” D1 that will short out your power suply if you switch GND and VCC connections.

One thing to note - the encoder has a 5V linear regulator inside, so you want to power it with at least 7V power supply. Make sure the power dissipation in the internal regulator is within reasonable limits. The heat management is not spectacular in the encoder - case is connected to the chasis ground, not circuit ground and the internal LM7805 regulator in D-PAK packege relies on a big ground plane to act as a heatsink.

https://wemakethings.net/2014/05/26/rotary-encoder-teardown/
