#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr  9 19:44:56 2023

@author: savan
"""

import argparse

import librosa
import numpy as np
from scipy import signal
from scipy.signal import find_peaks
import matplotlib.pyplot as plt


def find_offset(within_file, find_file, window):
    y_within, sr_within = librosa.load(within_file, sr=None)
    y_find, _ = librosa.load(find_file, sr=sr_within)

    c = signal.correlate(y_within, y_find[:sr_within*window], mode='valid', method='fft')
    c = c**2
    peak = np.argmax(c)
    print(peak)
    print(c[peak])
    print(max(c))
    thres = max(c)/4
    print(thres)
    print(len(c))
    print(len(c)/100)
    count = 0

    for i in c:
        if i > thres:
            count += 1
            
    print(count)
    print((count/len(c))*100)

    if (count/len(c)) * 100 <= 0.5:
        print("Match Found")
    else:
        print("Match not found")

    offset = round(peak / sr_within, 2)

    fig, ax = plt.subplots()
    ax.plot(c)
    peaks, _ = find_peaks(c, height=0)
    # print(peaks)
    return offset

def find_per(within_file, find_file, window):
    y_within, sr_within = librosa.load(within_file, sr=None)
    y_find, _ = librosa.load(find_file, sr=sr_within)

    c = signal.correlate(y_within, y_find[:sr_within*window], mode='valid', method='fft')
    c = c**2

    thres = max(c)/4
    count = 0

    for i in c:
        if i > thres:
            count += 1

    return (count/len(c)) * 100 


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--window', metavar='seconds', type=int, default=10)
    args = parser.parse_args()
    offset = find_offset('sample.wav', 'original.wav', args.window)
    print(f"Offset: {offset}s" )
    
    per = find_per('sample.wav', 'original.wav', args.window)
    if per <= 0.5:
        print("Match Found")
    else:
        print("Match not found")


if __name__ == '__main__':
    main()








