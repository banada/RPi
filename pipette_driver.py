
#  PIPETTE_DRIVER v0.01
#
#    controls a peristaltic pump motor for 
#    a low-cost automatic pipette
#
#  Copyright (C) 2013 Nathaniel Chen
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
#  The author can be reached at nathanielchen1(at)gmail.com


from sys import argv
import RPi.GPIO as GPIO
import time

#TODO eventually we want this to be in mL or uL
#for now, in seconds
gpio_pin, motor_freq, motor_time = argv

GPIO.cleanup()
#use RPi board numbering, not broadcom
GPIO.setmode(GPIO.BOARD)
GPIO.setup(gpio_pin, GPIO.OUT)

counter = 0
while counter < motor_freq * motor_time:
    GPIO.output(gpio_pin, GPIO.HIGH)
    time.sleep(1/motor_freq)
    GPIO.output(gpio_pin, GPIO.LOW)
    time.sleep(1/motor_freq)
    counter += 1

GPIO.output(gpio_pin, GPIO.LOW)
GPIO.cleanup()

#TODO include option for running until user stops it, add an argv
