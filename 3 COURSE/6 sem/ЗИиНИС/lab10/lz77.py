# находит подстроку максимальной длины в словаре
# вохвращает ее длину и смещение
def max_substring(buffer, dictionary):
    shift = len(dictionary)
    substring = ''

    for character in buffer:
        substring_temp = substring + character
        shift_temp = dictionary.rfind(substring_temp)
        if shift_temp < 0:
            break
        substring = substring_temp
        shift = shift_temp
    return len(substring), len(dictionary) - shift

def compress_lz77(message, lookahead_size, dictionary_size):
    dictionary = ''
    lookahead = message[:lookahead_size]

    triads = []
    while len(lookahead) != 0:
        match_length, offset = max_substring(lookahead, dictionary)
        dictionary += message[:match_length + 1]       
        dictionary = dictionary[-dictionary_size:]
        message = message[match_length:]
        last_character = message[:1]
        message = message[1:]
        lookahead = message[:lookahead_size]
        triads.append((offset, match_length, last_character))
    return triads

def decompress_lz77(compressed):
    message = ''
    for part in compressed:
        offset, match_length, character = part
        message = message + message[-offset:][:match_length] + character
    return message

def get_compressed_size(compressed):
    triads_str = ''
    for part in compressed:
        triads_str += str(part[0]) + str(part[1]) + str(part[2])
    return len(triads_str)
