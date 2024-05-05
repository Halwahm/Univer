import collections

# возвращает словарь {символ:количество потворений этого символа}
def get_letters_amount(seq):
    letters_dictionary = {}
    for i in seq:
        if i not in letters_dictionary:
            letters_dictionary[i] = 0
        letters_dictionary[i] += 1
    return letters_dictionary

# возвращает словарь {символ:вероятность этого символа}
def get_letters_probabilities(seq):
    probs = {}
    letters_dictionary = get_letters_amount(seq)
    total_amount = sum(letters_dictionary.values())
    for i in letters_dictionary.keys():
        probs[i] = letters_dictionary[i]/total_amount
    return probs

# возвращает словарь вероятностей алфавита для символов сообщения
def get_statistically_seq_probabilities(seq, statistically_probs):
    seq_probabilities = {}
    for i in seq:
        if i in statistically_probs:
            seq_probabilities[i] = statistically_probs[i]
    return seq_probabilities

# сортирует словарь и приводит к виду [буква, частота, код]
def create_list(data):
    list = dict(collections.Counter(data)) 
    list_sorted = sorted(iter(list.items()), key = lambda k_v:(k_v[1],k_v[0]),reverse=True)
    final_list = []
    for key,value in list_sorted:
        final_list.append([key,value,''])
    return final_list