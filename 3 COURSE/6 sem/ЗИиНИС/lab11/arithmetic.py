from probabilities import *
from shannon_fano import *

def get_intervals(probs):
    intervals = []
    lower = 0
    upper = 0
    for key, value in probs.items():
        upper += value
        intervals.append((key, lower, upper))
        lower += value
    return intervals

def compress(seq, probs):
    lower = 0
    higher = 1

    intervals = get_intervals(probs)

    for character in seq:  
        current_range = higher - lower
        for element in intervals:        
            if(character == element[0]):
                char_upper = element[2]
                char_lower = element[1]
        higher = lower + (current_range * char_upper)
        lower = lower + (current_range * char_lower)    
    return lower

def decompress(code, intervals, length):                        
    decompressed = ''
    for _ in range(length):
        print('Код:', code)
        for element in intervals:
            if code >= element[1] and code < element[2]:
                decompressed += element[0]
                print('Буква:', element[0])
                char_upper = element[2]
                char_lower = element[1]
                current_range = char_upper - char_lower
                code = (code - char_lower)/current_range
                break
    return decompressed

def get_overflow_pos(seq, decompressed):
    pos = 0
    for i in range(len(seq)):
            if seq[i] != decompressed[i]:
                pos = i
                print('Позиция переполнения:', pos)
                print('Исходный символ:',seq[i])
                print('Полученный:',decompressed[i])
                break

def task(seq):
    probs = get_letters_probabilities(seq)
    print('\nВероятности букв:')
    for key, value in probs.items():
        print(key, value)

    intervals = get_intervals(probs)
    print('\nИнтервалы:')
    for element in intervals:
        print(element[0], element[1], element[2])

    compressed = compress(seq, probs)
    print('\nРезультат прямого преобразования:',compressed)
    
    decompressed = decompress(compressed, intervals, len(seq))
    print('\nРезультат обратного преобразования:', decompressed)

    owerflow = get_overflow_pos(seq, decompressed)

    efficiency = (len(str(compressed)) + len(seq))/ len(seq)
    print('\nЭффективность сжатия арифметическим методом:', efficiency)

    task_shannon_fano(seq, probs)