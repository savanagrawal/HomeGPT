# #!/usr/bin/env python3
# # -*- coding: utf-8 -*-
# """
# Created on Sun Apr  9 18:34:46 2023

# @author: savan
# """

# import wave
# import struct

# MIN_MATCH_LEN = 2000
# THRESHOLD = 0.7

# def find_wav_sample(wav_file, sample_file, window_size, slide_interval):
#     # Load WAV files
#     with wave.open(wav_file, 'rb') as wav_fs, wave.open(sample_file, 'rb') as sample_fs:
#         # Read WAV headers
#         print(wav_fs.getparams())
#         wav_chunk_size, wav_fmt_chunk_size, sample_rate, byte_rate, wav_data_size, wav_fmt, wav_num_channels, wav_bits_per_sample = wav_fs.getparams()
#         sample_chunk_size, sample_fmt, sample_num_channels, sample_sample_rate, sample_byte_rate, sample_bits_per_sample = sample_fs.getparams()

#         if sample_fmt != 1 or sample_num_channels != 1 or sample_bits_per_sample != 16:
#             print("Error: Sample format is not supported")
#             return []

#         # Read sample data
#         sample_data = struct.unpack('<' + str(sample_fs.getnframes()) + 'h', sample_fs.readframes(sample_fs.getnframes()))

#         # Define variables
#         buf = bytearray(2 * MIN_MATCH_LEN)
#         window_size_samples = int(window_size * sample_sample_rate)
#         slide_interval_samples = int(slide_interval * sample_sample_rate)
#         threshold = int(THRESHOLD * 32767)

#         # Iterate over the WAV file
#         matches = []
#         sample_buf = bytearray(2 * window_size_samples)
#         wav_fs.setpos(44)
#         i = 0
#         while wav_fs.readframes(MIN_MATCH_LEN) != b'':
#             wav_fs.readinto(buf)
#             read_size = len(buf) // 2
#             j = 0
#             while j + window_size_samples <= read_size:
#                 # Extract the current window of samples from the WAV file
#                 window_buf = buf[j*2:(j+window_size_samples)*2]
#                 # Extract the corresponding window of samples from the sample data
#                 sample_start = i * slide_interval_samples
#                 sample_buf = sample_data[sample_start:sample_start+window_size_samples]

#                 # Compute the correlation between the two windows of samples
#                 corr = 0
#                 for k in range(window_size_samples):
#                     corr += sample_buf[k] * window_buf[k*2] + sample_buf[k] * window_buf[k*2+1]
#                 corr = abs(corr) / (window_size_samples * 32767)

#                 # Check if the correlation is above the threshold
#                 if corr >= threshold:
#                     matches.append(i * slide_interval_samples)
#                 j += slide_interval_samples // 2
#             i += 1

#     return matches


# matches = find_wav_sample('original.wav', 'original.wav', 0.1, 0.01)
# if len(matches) >= 7:
#     print("Match found!")
# else:
#     print("No match found.")


# # with wave.open('original.wav', 'rb') as wav_file:
# #     print('Number of channels:', wav_file.getnchannels())
# #     print('Sample rate:', wav_file.getframerate())
# #     print('Sample width (in bytes):', wav_file.getsampwidth())
# #     print('Encoding:', wav_file.getcomptype())


# # with wave.open('sample.wav', 'rb') as wav_file:
# #     print('Number of channels:', wav_file.getnchannels())
# #     print('Sample rate:', wav_file.getframerate())
# #     print('Sample width (in bytes):', wav_file.getsampwidth())
# #     print('Encoding:', wav_file.getcomptype())









# import numpy as np
# import soundfile as sf

# def find_wav_sample(original_file, sample_file, window_size, slide_interval):
#     # Load the original file and sample file
#     original, sr_original = sf.read(original_file)
#     sample, sr_sample = sf.read(sample_file)

#     # Compute the number of samples that the sliding window should cover
#     window_samples = int(window_size * sr_sample)

#     # Compute the number of samples to slide the window by
#     slide_samples = int(slide_interval * sr_sample)

#     # Compute the maximum number of windows to slide
#     max_slides = len(sample) - window_samples

#     # Compute the similarity score for each window and find the index of the maximum score
#     max_score = -1
#     max_score_index = -1
#     for i in range(0, max_slides, slide_samples):
#         window = sample[i:i+window_samples]
#         score = np.sum(np.abs(original - window)) / np.sum(np.abs(original))
#         if score > max_score:
#             max_score = score
#             max_score_index = i

#     # Compute the percentage match
#     num_claps_original = 10
#     num_claps_sample = int(max_score * num_claps_original)
#     percentage_match = num_claps_sample / num_claps_original

#     return percentage_match

# # Example usage
# original_file = 'original.wav'
# sample_file = 'sample.wav'
# window_size = 0.1 # 100ms
# slide_interval = 0.01 # 10ms

# percentage_match = find_wav_sample(original_file, sample_file, window_size, slide_interval)
# if percentage_match >= 0.7:
#     print('Sample matches with original.')
# else:
#     print('Sample does not match with original.')



import math
import wave

def select_window_and_slide(original_file, sample_file, window_size_min=0.01, slide_interval_min=0.001):
    # Get the length of the audio files
    original_length = get_audio_length(original_file)
    sample_length = get_audio_length(sample_file)

    # Compute the maximum window size and slide interval based on the audio lengths
    window_size_max = min(original_length, sample_length)
    slide_interval_max = min(window_size_max, 1.0)

    # Compute the number of windows and slides required for each file
    num_windows_original = math.ceil((original_length - window_size_min) / slide_interval_min)
    num_windows_sample = math.ceil((sample_length - window_size_min) / slide_interval_min)

    # Compute the actual window size and slide interval for each file
    window_size_original = (original_length - window_size_min) / (num_windows_original - 1)
    slide_interval_original = (original_length - window_size_original) / (num_windows_original - 1)
    window_size_sample = (sample_length - window_size_min) / (num_windows_sample - 1)
    slide_interval_sample = (sample_length - window_size_sample) / (num_windows_sample - 1)

    # Choose the smaller of the two window sizes and the larger of the two slide intervals
    window_size = min(window_size_original, window_size_sample)
    slide_interval = max(slide_interval_original, slide_interval_sample)

    return window_size, slide_interval

def get_audio_length(audio_file):
    with wave.open(audio_file, 'r') as f:
        frames = f.getnframes()
        rate = f.getframerate()
        return frames / float(rate)



import numpy as np
import wave

def find_wav_sample(original_wav_file, sample_wav_file, threshold=0.1):
    original_audio = load_wav(original_wav_file)
    sample_audio = load_wav(sample_wav_file)

    # Set the window size and slide interval
    window_size = int(len(original_audio) * 0.1)
    slide_interval = int(window_size * 0.5)

    # Compute the dot product between the original audio and the sample audio
    dot_products = []
    for i in range(0, len(original_audio) - window_size, slide_interval):
        window = original_audio[i:i+window_size]
        # Pad the sample audio if the window size is longer than the sample audio
        if len(window) > len(sample_audio):
            padded_sample_audio = np.concatenate((sample_audio, np.zeros(len(window) - len(sample_audio))))
            dot_product = np.dot(window, padded_sample_audio)
        else:
            dot_product = np.dot(window, sample_audio[:len(window)])
        dot_products.append(dot_product)

    # Compute the maximum dot product and the threshold value
    max_dot_product = max(dot_products)
    threshold_value = threshold * max_dot_product

    # Check if the maximum dot product exceeds the threshold
    if max_dot_product >= threshold_value:
        return True
    else:
        return False




def load_wav(audio_file):
    # Load the audio file
    with wave.open(audio_file, 'rb') as f:
        num_frames = f.getnframes()
        channels = f.getnchannels()
        sample_width = f.getsampwidth()
        frame_rate = f.getframerate()
        frames = f.readframes(num_frames)

    # Convert the raw audio bytes to a numpy array
    if sample_width == 1:
        dtype = np.uint8
    else:
        dtype = np.int16
    audio = np.frombuffer(frames, dtype=dtype)

    print('audio shape:', audio.shape)
    print('audio contents:', audio)

    # Reshape the audio array into a two-dimensional array with one column for each channel
    audio = np.reshape(audio, (num_frames, channels))

    # Convert the audio array to mono
    audio = np.mean(audio, axis=1)

    return audio


window_size, slide_interval = select_window_and_slide('original.wav', 'sample.wav')
# if find_wav_sample('original.wav', 'sample.wav'):
#     print("Match found!")
# else:
#     print("No match found.")












import numpy as np
import scipy.signal as signal
import soundfile as sf

# Load the original audio file
audio_orig, sr_orig = sf.read('original.wav')

# Load the sample audio file
audio_sample, sr_sample = sf.read('sample.wav')

# Define the filter parameters
order = 1000
f_start = 0.0
f_end = sr_sample / 2
num_freqs = order // 2 + 1

# Create the frequency vector
freq = np.linspace(f_start, f_end, num_freqs, endpoint=False)

# Define the filter
filter_coeffs = signal.firwin(order, freq, pass_zero=False)

# Apply the filter to the original audio
audio_filtered = signal.convolve(audio_orig, filter_coeffs, mode='same')

# Compute the correlation between the filtered audio and the sample audio
corr = signal.correlate(audio_filtered, audio_sample)

# Check if the correlation exceeds a certain threshold
threshold = 0.7
if np.max(corr) > threshold:
    print('Match found!')
else:
    print('Match not found.')




