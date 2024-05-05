import collections

def create_nodes(data):
    list = dict(collections.Counter(data)) 
    list_sorted = sorted(iter(list.items()), key = lambda k_v:(k_v[1],k_v[0]),reverse=True)
    final_list = []
    for key,value in list_sorted:
        final_list.append([key,value])
    return final_list

def start_huffman_tree(nodes):
    huffman_tree = []
    huffman_tree.append(nodes) 
    return huffman_tree

def combine_nodes(nodes, huffman_tree):
    pos = 0
    newnode = []  
    if len(nodes) > 1:
        nodes.sort()
        nodes = sorted(iter(nodes), key = lambda probs:(probs[1]),reverse=False)
        nodes[pos].append("1")                       
        nodes[pos+1].append("0")
        combined_node1 = (nodes[pos] [0] + nodes[pos+1] [0])
        combined_node2 = (nodes[pos] [1] + nodes[pos+1] [1]) 
        newnode.append(combined_node1)
        newnode.append(combined_node2)
        newnodes=[]
        newnodes.append(newnode)
        newnodes = newnodes + nodes[2:]
        nodes = newnodes
        huffman_tree.append(nodes)
        combine_nodes(nodes, huffman_tree)
    return huffman_tree     

def print_huffman_tree(huffman_tree):
    huffman_tree.sort(reverse = True)
    print('Дерево Хаффмана:')
    checklist = []
    for level in huffman_tree:
        for node in level:
            if node not in checklist:
                checklist.append(node)
            else:
                level.remove(node)
    count = 0
    for level in huffman_tree:
        print('Level', count,':',level)             
        count+=1
    print()
    return checklist

def get_letters(seq):
    only_letters = []
    for letter in seq:
        if letter not in only_letters:
            only_letters.append(letter)
    return only_letters

def bin_list(seq, huffman_tree):
    letter_binary = []
    only_letters = get_letters(seq)
    checklist = print_huffman_tree(huffman_tree)
    for letter in only_letters:
        code = ''
        for node in checklist:
            if len(node) > 2 and letter in node[0]:
                code = code + node[2]
        lettercode = [letter, code]
        letter_binary.append(lettercode)
    print('Коды:')
    for letter in letter_binary:
        print(letter[0], letter[1])
    return letter_binary

def compress_huffman(letter_binary, seq):
    encoded = ''
    for character in seq:
        for item in letter_binary:
            if character in item:
                encoded = encoded + item[1]
    return encoded

def decompress_huffman(encoded, letter_binary):
    decompressed = ''
    code = ''
    for digit in encoded:
        code = code + digit
        pos = 0
        for letter in letter_binary:
            if code == letter[1]:
                decompressed = decompressed + letter_binary[pos] [0]
                code = ''
            pos += 1
    return decompressed

def task_huffman(seq, probabilities):
    nodes = create_nodes(probabilities)
    huffman_tree = start_huffman_tree(nodes)
    newnodes = combine_nodes(nodes, huffman_tree)
    letter_binary = bin_list(seq, huffman_tree)
    encoded = compress_huffman(letter_binary, seq)
    print(encoded)
    decoded = decompress_huffman(encoded, letter_binary)
    print(decoded)
    print('Длина сообщения методом Хафммана:', len(encoded))
    print('Длина в ASCII:', len(''.join(format(ord(ch), '08b') for ch in seq)))