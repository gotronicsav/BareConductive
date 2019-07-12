import MPR121
from gpiozero import RGBLED
import subprocess
import pygame
from pygame.mixer import Sound
from glob import glob
from time import sleep

sensor = MPR121.begin()
sensor.set_touch_threshold(40)
sensor.set_release_threshold(20)

led = RGBLED(6, 5, 26, active_high=False)

num_electrodes = 12

# Convertion des fichier MP3 en WAV
led.blue = 1
subprocess.call("picap-samples-to-wav soundtable", shell=True) #soundtable = nom du dossier
led.off()

# init
pygame.mixer.pre_init(frequency=44100, channels=64, buffer=1024)
pygame.init()

sounds = [Sound(path) for path in glob("soundtable/.wavs/*.wav")] #soundtable = nom du dossier

def play_sounds_when_touched():
    if sensor.touch_status_changed(): #verifie si une electrode a ete touchee
        sensor.update_touch_data()

        is_any_touch_registered = False

        for i in range(num_electrodes): #regarde quelle electrode a ete touchee
            if sensor.get_touch_data(i):
                is_any_touch_registered = True
            if sensor.is_new_touch(i):
                print ("Son joue : " + str(i))
                sound = sounds[i] #joue le son dont le numero est le meme que celui de l'electrode
                sound.play()

        if is_any_touch_registered:
            led.red = 1
        else:
            led.off()

running = True
while running:
    try:
        play_sounds_when_touched()
    except KeyboardInterrupt:
        led.off()
        running = False
    sleep(0.01)
