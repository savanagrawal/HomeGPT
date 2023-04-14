#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr  9 19:44:56 2023

@author: savan
"""


import librosa
from scipy import signal


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
    per = find_per('sample.wav', 'original.wav', 10)
    if per <= 0.5:
        print("Match Found")
    else:
        print("Match not found")


if __name__ == '__main__':
    main()








