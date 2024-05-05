from probabilities import *
from shannon_fano import *
from huffman import *

# выполнить прямое и обратное преобразования сообщения, состоящего из собственных имени и фамилии. 
# Определить эффективность (в сравнении с кодами ASCII) сжатия сообщения. 
seq = 'andrey halaleenko'

# При этом таблица отсортированных символов строится: 
# а) на основе данных, полученных в лабораторной работе № 2; 
print('\nМетод Шеннона-Фано')
print('Таблица на основе данных, полученных в лабораторной работе 2')
with open('source.txt', encoding='utf8') as file:
    alphabet_statistically = file.read().replace('\n', '').replace('\r', '').lower()
probabilities_statistically = get_letters_probabilities(alphabet_statistically)
seq_probabilities = get_statistically_seq_probabilities(seq, probabilities_statistically)
task_shannon_fano(seq, seq_probabilities)

# б) динамически, на основе анализа сжимаемого сообщения
print('\nДинамическая таблица, на основе сжимаемого сообщения')
probabilities_dynamically = get_letters_probabilities(seq)

print('\nМетод Хаффмана')
task_huffman(seq, probabilities_dynamically)
