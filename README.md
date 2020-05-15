# Feyncatt

### Description

An attempt at a robotic quadruped. At the current stage it's able to stand upright and do basic leg movements.

Schrödinger was too obvious a name.

TODO:
 - attempt a basic walk cycle
 - reprint the feet to be more efficient
 - make the walk cycle more fluid
 - allow turning
 - allow environmental interaction

![Model of Feyncatt](https://github.com/lumorti/feyncatt/raw/master/images/model.png "Model of Feyncatt")

### Requirements

 - a 3D printer, doesn't need to be a fancy one
 - less than 1 kg of PLA (1 kg allowed me many misprints and redesigns)

 - 14 SG90 servos ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=251&products_id=3504))
 - Arduino UNO (or equivalent) ([here](https://www.amazon.co.uk/Arduino-A000066-ARDUINO-UNO-REV3/dp/B008GRTSV6/ref=sr_1_4?dchild=1&keywords=arduino+uno&qid=1589523087&sr=8-4))
 - MPU6050 Accelerometer/Gyroscope ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=302_304&products_id=3059))
 - Ultrasonic range finder ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=302_310&products_id=3633))
 - SD card reader and SD card ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=347&products_id=2947) and [here](https://www.amazon.co.uk/SanDisk-microSDHC-Memory-Adapter-Performance/dp/B073S9SFK2/ref=sxts_sxwds-bia-wc-p13n2_0?cv_ct_cx=sd+card&dchild=1&keywords=sd+card&pd_rd_i=B073S9SFK2&pd_rd_r=ea12217e-778c-4a29-b0cc-28b6fb1dbdae&pd_rd_w=HU2K3&pd_rd_wg=L97zn&pf_rd_p=4cda869f-2b1a-4e5f-a72b-48315da95bba&pf_rd_r=GK33R476A32Y1XK90NCB&psc=1&qid=1589524623&sr=1-2-91e9aa57-911e-4628-99b3-09163b7d9294))

 - 4xAA battery pack ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=192_195_198&products_id=1441))
 - 4 NiMH batteries ([here](https://www.amazon.co.uk/AmazonBasics-Capacity-Pre-Charged-Rechargeable-Batteries-Black/dp/B00HZV9WTM/ref=sr_1_2?dchild=1&keywords=nimh&qid=1589523008&sr=8-2))
 - boost converter, LCD screen is helpful ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=140_171&products_id=3259))
 - 5 A fuse and holder (or not, it's your flammable house) ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=214_215_219&products_id=1523) and [here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=214_215_220&products_id=2230))

 - many 1" pin header jumper cables for connecting modules ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=225_233&products_id=2909))
 - some wire rated for 5 A as the main power rail ([here](https://www.amazon.co.uk/PsmGoods%C2%AE-Gauge-Silicone-Flexible-Rubber-18/dp/B074299GG5/ref=sr_1_6?dchild=1&keywords=18+awg+wire&qid=1589523305&sr=8-6))
 - switch ([here](https://www.bitsbox.co.uk/index.php?main_page=product_info&cPath=116_136&products_id=911))
 - M4 machine screws/nuts, M3 machine screws/nuts, M2 machine screws/nuts
 
### Printed Parts Required

Can probably all be printed over about a week if you just do a couple parts a day, each part takes about an hour on standard settings.

 - 14 x servoMountV3
 - 8 x servoConnectorStraight
 - 4 x foot
 - 4 x servoConnectorTwist
 - 2 x bodyConnector
 - 1 x bodyBack
 - 1 x bodyFront
 - 1 x servoConnectorHead
 - 1 x servoConnectorNeck

### Build Instructions

- print everything
- figure out all the start/mid/end PWM values for the servos
- assemble the legs
- assemble the body
- assemble the head
- wire up the body
- connect the legs 
- wire up the legs
- connect the head 
- wire up the head
- double check all the wiring
- check it all again
- turn it on, flash the Arduino with the firmware

TODO

### Usage Instructions

TODO 
