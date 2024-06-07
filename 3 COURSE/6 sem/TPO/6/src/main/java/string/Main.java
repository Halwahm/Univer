package string;

import java.util.*;
import java.util.regex.*;
import java.util.stream.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    // Task 1: Find the sentences with the same words
    public static void findSentencesWithSameWords(List<String> sentences) {
        Map<String, Integer> sentenceWordCount = new HashMap<>();
        for (String sentence : sentences) {
            String[] words = sentence.split("\\s+");
            for (String word : words) {
                sentenceWordCount.put(word, sentenceWordCount.getOrDefault(word, 0) + 1);
            }
        }

        int maxCount = Collections.max(sentenceWordCount.values());
        if (maxCount > 1) {
            System.out.println("Sentences with the same words:");
            for (Map.Entry<String, Integer> entry : sentenceWordCount.entrySet()) {
                if (entry.getValue() == maxCount) {
                    System.out.println(getSentenceContainingWord(sentences, entry.getKey()));
                }
            }
        } else {
            System.out.println("No sentences with the same words found.");
        }
    }

    // Utility method to get the sentence containing a specific word
    public static String getSentenceContainingWord(List<String> sentences, String word) {
        for (String sentence : sentences) {
            if (sentence.contains(word)) {
                return sentence;
            }
        }
        return null;
    }

    // Task 2: Sort sentences by the number of words
    public static void sortSentencesByWordCount(List<String> sentences) {
        sentences.sort(Comparator.comparingInt(s -> s.split("\\s+").length));
        for (String sentence : sentences) {
            System.out.println(sentence);
        }
    }

    // Task 3: Find a word in the first sentence that doesn't occur in other sentences
    public static void findUniqueWordInFirstSentence(List<String> sentences) {
        String firstSentence = sentences.get(0);
        Set<String> uniqueWords = new HashSet<>(Arrays.asList(firstSentence.split("\\s+")));
        for (int i = 1; i < sentences.size(); i++) {
            String[] words = sentences.get(i).split("\\s+");
            for (String word : words) {
                uniqueWords.remove(word);
            }
        }
        if (!uniqueWords.isEmpty()) {
            System.out.println("Unique word in the first sentence: " + uniqueWords.iterator().next());
        } else {
            System.out.println("No unique words in the first sentence.");
        }
    }

    // Utility method to split text into sentences
    public static List<String> splitIntoSentences(String text) {
        List<String> sentences = new ArrayList<>();
        Pattern pattern = Pattern.compile("[^.!?]+");
        Matcher matcher = pattern.matcher(text);
        while (matcher.find()) {
            sentences.add(matcher.group().trim());
        }
        return sentences;
    }

    // Task 4: Find and print words of a specified length in all interrogative sentences
    public static void findWordsInInterrogativeSentences(List<String> sentences, int wordLength) {
        Pattern pattern = Pattern.compile("[^.!?]+\\?");
        for (String sentence : sentences) {
            Matcher matcher = pattern.matcher(sentence);
            if (matcher.find()) {
                String interrogativeSentence = matcher.group().trim();
                for (String word : interrogativeSentence.split("\\s+")) {
                    if (word.length() == wordLength) {
                        System.out.println(word);
                    }
                }
            }
        }
    }

    // Task 5: Swap first and last words in each sentence
    public static void swapFirstAndLastWords(List<String> sentences) {
        for (String sentence : sentences) {
            String[] words = sentence.split("\\s+");
            if (words.length > 1) {
                String firstWord = words[0];
                words[0] = words[words.length - 1];
                words[words.length - 1] = firstWord;
                System.out.println(String.join(" ", words));
            } else {
                System.out.println(sentence);
            }
        }
    }

    // Task 6: Print words in alphabetical order with new line for each new letter
    public static void printWordsInAlphabeticalOrder(List<String> sentences) {
        List<String> words = new ArrayList<>();
        for (String sentence : sentences) {
            words.addAll(Arrays.asList(sentence.split("\\s+")));
        }
        Collections.sort(words);
        char currentLetter = '\0';
        for (String word : words) {
            if (word.charAt(0) != currentLetter) {
                currentLetter = word.charAt(0);
                System.out.println();
            }
            System.out.print(word + " ");
        }
    }

    // Task 7: Sort words by the ratio of vowels to total letters in each word
    private static List<String> extractWords(String text) {
        List<String> words = new ArrayList<>();
        List<String> sentences = splitIntoSentences(text);
        for (String sentence : sentences) {
            words.addAll(Arrays.asList(sentence.split("\\s+")));
        }
        return words;
    }

    private static double calculateVowelRatio(String word) {
        int vowelCount = 0;
        for (char c : word.toLowerCase().toCharArray()) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowelCount++;
            }
        }
        return (double) vowelCount / word.length();
    }

    // Task 8: Sort words starting with vowels alphabetically by the first consonant
    public static void sortWordsStartingWithVowels(List<String> sentences) {
        List<String> words = extractWords(sentences);
        words.removeIf(word -> !isVowel(word.charAt(0)));
        words.sort(Comparator.comparingInt(word -> {
            for (char c : word.toCharArray()) {
                if (!isVowel(c)) {
                    return c;
                }
            }
            return -1; // Default if no consonant found (should not happen)
        }));
        System.out.println(words);
    }

    private static boolean isVowel(char c) {
        return "aeiouAEIOU".indexOf(c) != -1;
    }

    // Task 9: Sort words by the number of occurrences of a specified letter in each word
    public static void sortWordsByLetterFrequency(List<String> sentences, char letter) {
        List<String> words = extractWords(sentences);
        words.sort(Comparator.comparingInt(word -> {
            int count = 0;
            for (char c : word.toLowerCase().toCharArray()) {
                if (c == letter) {
                    count++;
                }
            }
            return count;
        }));
        System.out.println(words);
    }

    // Task 10: Find the occurrences of each word from a given list in each sentence
    public static void findWordOccurrences(List<String> sentences, List<String> wordList) {
        for (String word : wordList) {
            System.out.println("Occurrences of '" + word + "' in each sentence:");
            for (String sentence : sentences) {
                int count = countWordOccurrences(sentence, word);
                System.out.println(sentence + ": " + count);
            }
            System.out.println();
        }
    }

    private static int countWordOccurrences(String sentence, String word) {
        Pattern pattern = Pattern.compile("\\b" + Pattern.quote(word) + "\\b", Pattern.CASE_INSENSITIVE);
        Matcher matcher = pattern.matcher(sentence);
        int count = 0;
        while (matcher.find()) {
            count++;
        }
        return count;
    }

    // Task 11: Remove substrings with the maximum length starting and ending with specified characters
    public static void removeMaxSubstring(List<String> sentences, char startChar, char endChar) {
        for (String sentence : sentences) {
            int maxStartIndex = -1;
            int maxEndIndex = -1;
            int maxLength = -1;
            for (int i = 0; i < sentence.length(); i++) {
                if (sentence.charAt(i) == startChar) {
                    for (int j = i + 1; j < sentence.length(); j++) {
                        if (sentence.charAt(j) == endChar) {
                            int length = j - i - 1;
                            if (length > maxLength) {
                                maxLength = length;
                                maxStartIndex = i;
                                maxEndIndex = j;
                            }
                            break;
                        }
                    }
                }
            }
            if (maxStartIndex != -1 && maxEndIndex != -1) {
                String substringToRemove = sentence.substring(maxStartIndex, maxEndIndex + 1);
                String newSentence = sentence.replace(substringToRemove, "");
                System.out.println(newSentence);
            } else {
                System.out.println(sentence);
            }
        }
    }

    // Utility method to extract words from sentences
    public static List<String> extractWords(List<String> sentences) {
        List<String> words = new ArrayList<>();
        for (String sentence : sentences) {
            words.addAll(Arrays.asList(sentence.split("\\s+")));
        }
        return words;
    }

    // Task 12: Remove words of a specified length starting with a consonant
    public static void removeWordsStartingWithConsonant(String text, int wordLength, char[] consonants) {
        List<String> words = extractWords(text);
        words.removeIf(word -> word.length() == wordLength && startsWithConsonant(word, consonants));
        System.out.println(String.join(" ", words));
    }

    private static boolean startsWithConsonant(String word, char[] consonants) {
        char firstChar = Character.toLowerCase(word.charAt(0));
        for (char consonant : consonants) {
            if (firstChar == consonant) {
                return true;
            }
        }
        return false;
    }

    // Task 13: Sort words in text by the number of occurrences of a specified character, then alphabetically
    public static void sortWordsByCharOccurrences(String text, char specifiedChar) {
        List<String> words = extractWords(text);
        words.sort((word1, word2) -> {
            int occurrences1 = countCharOccurrences(word1, specifiedChar);
            int occurrences2 = countCharOccurrences(word2, specifiedChar);
            if (occurrences1 != occurrences2) {
                return occurrences2 - occurrences1;
            } else {
                return word1.compareTo(word2);
            }
        });
        System.out.println(words);
    }

    private static int countCharOccurrences(String word, char specifiedChar) {
        int count = 0;
        for (char c : word.toLowerCase().toCharArray()) {
            if (c == specifiedChar) {
                count++;
            }
        }
        return count;
    }

    // Task 14: Find the longest palindrome substring in the text
    public static void findLongestPalindromeSubstring(String text) {
        String longestPalindrome = "";
        for (int i = 0; i < text.length(); i++) {
            for (int j = i + 1; j <= text.length(); j++) {
                String substring = text.substring(i, j);
                if (isPalindrome(substring) && substring.length() > longestPalindrome.length()) {
                    longestPalindrome = substring;
                }
            }
        }
        System.out.println(longestPalindrome);
    }

    private static boolean isPalindrome(String str) {
        StringBuilder reversed = new StringBuilder(str).reverse();
        return str.equals(reversed.toString());
    }

    // Task 15: Transform each word in the text by removing all subsequent occurrences of its first letter
    public static void transformWords(String text) {
        List<String> words = extractWords(text);
        for (int i = 0; i < words.size(); i++) {
            String word = words.get(i);
            if (word.length() > 0) { // Проверка на нулевую длину слова
                char firstLetter = word.charAt(0);
                String transformedWord = word.replaceAll("(?i)" + String.valueOf(firstLetter) + "(?!" + Pattern.quote(word.substring(1)) + ")", "");
                words.set(i, transformedWord);
            }
        }
        System.out.println(String.join(" ", words));
    }


    // Task 16: Replace words of a specified length in a sentence with a given substring
    public static void replaceWordsWithSubstring(String text, int wordLength, String replacementSubstring) {
        List<String> sentences = splitIntoSentences(text);
        for (String sentence : sentences) {
            String[] words = sentence.split("\\s+");
            for (int i = 0; i < words.length; i++) {
                if (words[i].length() == wordLength) {
                    words[i] = replacementSubstring;
                }
            }
            System.out.println(String.join(" ", words));
        }
    }


    public static void main(String[] args) {
        String text = "This is a sample text. It contains multiple sentences. Each sentence has some words in it. "
                + "Are there any questions? How many sentences contain the word 'sentence'? "
                + "Is it possible to find a word that appears only in the first sentence? "
                + "What is the longest word in this text? "
                + "What happens if we swap the first and last words in each sentence? "
                + "Can we print all the words in alphabetical order? ";
        List<String> sentences = Arrays.asList(text.split("\\.\\s*"));

        System.out.println("Task 1:");
        Main.findSentencesWithSameWords(sentences);

        System.out.println("\nTask 2:");
        Main.sortSentencesByWordCount(sentences);

        System.out.println("\nTask 3:");
        Main.findUniqueWordInFirstSentence(sentences);

        System.out.println("\nTask 4:");
        Main.findWordsInInterrogativeSentences(sentences, 5);

        System.out.println("\nTask 5:");
        Main.swapFirstAndLastWords(sentences);

        System.out.println("\nTask 6:");
        Main.printWordsInAlphabeticalOrder(sentences);

        System.out.println("\nTask 7:");
        Main.sortWordsByCharOccurrences(text, 'a');

        System.out.println("\nTask 8:");
        Main.sortWordsStartingWithVowels(sentences);

        System.out.println("\nTask 9:");
        Main.sortWordsByLetterFrequency(sentences, 'e');

        System.out.println("\nTask 10:");
        Main.findWordOccurrences(sentences, Arrays.asList("word", "sentence", "text"));

        System.out.println("\nTask 11:");
        Main.removeMaxSubstring(sentences, 'e', 't');

        System.out.println("\nTask 12:");
        Main.removeWordsStartingWithConsonant(text, 4, new char[]{'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'});

        System.out.println("\nTask 13:");
        Main.sortWordsByCharOccurrences(text, 's');

        System.out.println("\nTask 14:");
        Main.findLongestPalindromeSubstring(text);

        System.out.println("\nTask 15:");
        Main.transformWords(text);

        System.out.println("\nTask 16:");
        Main.replaceWordsWithSubstring(text, 5, "REPLACED");
    }
}

