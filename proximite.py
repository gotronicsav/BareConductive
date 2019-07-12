#@orga=GoTronic
#@author=Sylvain G.

import RPi.GPIO as GPIO
import time
import MPR121

sensor = MPR121.begin()
sensor.set_touch_threshold(4)
sensor.set_release_threshold(2)
#Plus la valeur du "threshold" est basse, plus le capteur
#de proximite est puissant

num_electrodes = 12

rouge = 27 #pin GPIO
jaune = 23
vert = 25

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(rouge,GPIO.OUT)
GPIO.setup(jaune,GPIO.OUT)
GPIO.setup(vert,GPIO.OUT)

while True:
    
    if sensor.touch_status_changed():
        sensor.update_touch_data()

        is_any_touch_registered = False

        for i in range(num_electrodes):
            if sensor.get_touch_data(i):
                is_any_touch_registered = True
            if sensor.is_new_touch(i):
                print ("Electrode : " + str(i))
                if i==2:
                    GPIO.output(rouge, not GPIO.input(rouge)) #inversement de l'etat
                if i==5:
                    GPIO.output(jaune, not GPIO.input(jaune))
                if i==8:
                    GPIO.output(vert, not GPIO.input(vert))
