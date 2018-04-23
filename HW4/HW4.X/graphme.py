#!/usr/bin/env python

import matplotlib.pyplot as plt
import math
import sys

shape = 'sine'

def main(arg):

    pointarray = []
    timearray = []

    print arg

    if arg == 'triangle':
        wave_period = 1./5    #s/wave
        duration = wave_period
    elif arg == 'sine':
        wave_period = 1./10
        duration = wave_period
    else:
        print "arg invalid"
        sys.exit()

    samp = 1000.  #samp/s
    numsamps = samp*duration
    time = 0.


    # for i in range(1, int(numsamps)):
    #     if shape == 'triangle':
    #         pointarray.append(int(1024./3.3 * triangle(3.3, time, wave_period)))
    #     elif shape == 'sine':
    #         pointarray.append(int(1024./3.3 * sine(1.65, time, wave_period)))
    #     timearray.append(time)
    #     time += 1./samp

    for i in range(0, int(numsamps)):
        if arg == 'triangle':
            pointarray.append(triangle(3.3, time, wave_period))
        elif arg == 'sine':
            pointarray.append(sine(1.65, time, wave_period))
        timearray.append(time)
        time += 1./samp


    plt.plot(pointarray)
    plt.show()


def triangle(amp, time, wave_period):
    '''
    Given the desired amplitude, time, and waveform wave_period, returns the voltage of the reference wave with that amplitude and wave_period at the given time.
    '''

    return (amp*2)/wave_period * (wave_period/2 - math.fabs(time % (wave_period) - wave_period/2))



def sine(amp, time, wave_period):
    '''
    Given the desired amplitude, time, and waveform wave_period, returns the voltage of the reference wave with that amplitude and wave_period at the given time.
    '''

    phase = 0.
    return amp * math.sin(2.*math.pi*1./wave_period*time+phase) + 1.65








if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(sys.argv[1])
    else:
        print "Argument: 'triangle or sine'"
