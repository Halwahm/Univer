from lz77 import *
from datetime import datetime

# 1. Разработать авторское приложение в соответствии с целью лабораторной работы. 
# предусмотреть возможность оперативного изменения размеров окон (n1, n2). 
# 2. С помощью приложения выполнить прямое и обратное преобразования произвольного текста длиной несколько килобайт. 
# Формат представления параметров p и q выбрать по указанию преподавателя. 
with open('source.txt',  encoding='utf8') as file:
    stringToEncode = file.read().replace('\n', '').replace('\r', '').lower()

dictionary_size = int(input('Длина буфера словаря: '))
lookahead_size = int(input('Длина буфера кодирования:' ))
print(compress_lz77('ACAGAATAGAGA', dictionary_size, lookahead_size))
print(decompress_lz77(compress_lz77('ACAGAATAGAGA', dictionary_size, lookahead_size)))

# 3. Изменяя размеры окон, оценить скорость и эффективность
# (используя соотношения на с. 76) выполнения операций сжатия/ распаковки.
dictionary_size = 10
lookahead_size = 5
while dictionary_size < 10240: 
    print('\nДлина буфера словаря:', dictionary_size)
    print('Длина буфера кодирования:', lookahead_size)
    start_time = datetime.now()
    compressed = compress_lz77(stringToEncode, dictionary_size, lookahead_size)
    compress_time = datetime.now() - start_time
    cipher_size = get_compressed_size(compressed)
    ratio = cipher_size / len(stringToEncode)
    print('Эффективность:', ratio)
    start_time = datetime.now()
    decompress_lz77(compressed)
    decompress_time = datetime.now() - start_time
    print('Время компрессии:', compress_time)
    print('Время декомпрессии:', decompress_time)
    dictionary_size *= 2
    lookahead_size *= 2