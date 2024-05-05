from probabilities import *

# разбиваем словарь на 2 части и возвращаем их
def divide_list(list):
    if len(list) == 2:               
        return [list[0]],[list[1]]
    else:
        n = 0
        for i in list:
            n += i[1]
        x = 0
        distance = abs(2*x - n)
        j = 0
        for i in range(len(list)):               
            x += list[i][1]
            if distance < abs(2*x - n):
                j = i         
    return list[0:j+1], list[j+1:]
c ={}

# в коды первой часть словаря добавляется 1, в коды второй 0
def label_list(list):
    list1,list2 = divide_list(list)
    for i in list1:
        i[2] += '0'
        c[i[0]] = i[2]
    for i in list2:
        i[2] += '1'
        c[i[0]] = i[2]
    if len(list1)==1 and len(list2)==1:        
        return
    # рекурсия
    label_list(list2)
    return c

# составляем сжатое слово из кодов
def compress_shannon_fano(c, seq):
    encoded = ''
    for i in seq:
        encoded += c[i[0]]
    return encoded

# находим исходное сообщение по словарю из сжатого сообщения
def decompress_shannon_fano(c, seq):
    decompressed_string = ''
    code = ''
    letter_binary = []

    for key, value in c.items():
        letter_binary.append([key,value])

    for digit in seq:
        code += digit
        pos = 0
        for letter in letter_binary:               
            if code == letter[1]:
                decompressed_string += letter_binary[pos] [0]
                code= ''
            pos += 1
    return decompressed_string

# задание полностью
def task_shannon_fano(seq, probabilities):
    probs = create_list(probabilities)
    codes = label_list(probs)
    print(codes)
    compressed = compress_shannon_fano(codes, seq)
    print(compressed)

    print(decompress_shannon_fano(codes, compressed))

    print('Длина сообщения методом Шеннона-Фано:', len(compressed))
    print('Длина в ASCII:', len(''.join(format(ord(ch), '08b') for ch in seq)))