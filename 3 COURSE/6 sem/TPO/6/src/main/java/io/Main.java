package io;

import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;

public class Main {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No args");
            return;
        }

        String inputPath = args[0];
        File file = new File(inputPath);

        if (file.isDirectory()) {
            writeDirectoryStructure(file, "output.txt");
        } else {
            readAndPrintFileInfo(file);
        }
    }

    // Method to write the directory structure to a text file
    private static void writeDirectoryStructure(File directory, String outputFile) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFile))) {
            Files.walkFileTree(directory.toPath(), new SimpleFileVisitor<Path>() {
                int depth = 0;

                @Override
                public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                    bw.write(getIndent(depth) + "[" + dir.getFileName() + "]");
                    bw.newLine();
                    depth++;
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                    bw.write(getIndent(depth) + file.getFileName());
                    bw.newLine();
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                    depth--;
                    return FileVisitResult.CONTINUE;
                }
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Method to get the indentation based on the depth level
    private static String getIndent(int depth) {
        StringBuilder indent = new StringBuilder();
        for (int i = 0; i < depth; i++) {
            indent.append("  "); // Example indentation with two spaces
        }
        return indent.toString();
    }

    // Method to read information about files from a text file and print statistics
    private static void readAndPrintFileInfo(File file) {
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            int folderCount = 0;
            int fileCount = 0;
            int totalFileNameLength = 0;
            int totalFilesInFolder = 0;

            String line;
            while ((line = br.readLine()) != null) {
                if (line.startsWith("[")) {
                    folderCount++;
                    totalFilesInFolder = 0;
                } else {
                    fileCount++;
                    totalFileNameLength += line.length();
                    totalFilesInFolder++;
                }
            }

            double averageFilesInFolder = (double) fileCount / folderCount;
            double averageFileNameLength = (double) totalFileNameLength / fileCount;

            System.out.println("Folders: " + folderCount);
            System.out.println("Files: " + fileCount);
            System.out.println("Average number of files in a folder: " + averageFilesInFolder);
            System.out.println("Average file name length: " + averageFileNameLength);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
