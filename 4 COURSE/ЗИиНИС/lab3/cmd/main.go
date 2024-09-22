package main

import (
	"fmt"
	"os"
	"time"

	"crypto5/mpr"
	"crypto5/report"
	"crypto5/route"
)

func main() {
	testRoute()
	testMpr()

	fmt.Println("Done")
}

func testRoute() {
	inputFilename := "input.txt"
	encryptedFilename := "encrypted_route.txt"
	decryptedFilename := "decrypted_route.txt"

	inputFile, err := os.Open(inputFilename)
	if err != nil {
		fmt.Println("Error reading input file:", err)
		return
	}
	defer inputFile.Close()

	inputStat, err := inputFile.Stat()
	if err != nil {
		fmt.Println("Error reading input file stats:", err)
		return
	}

	inputBytes := make([]byte, inputStat.Size())
	_, err = inputFile.Read(inputBytes)
	if err != nil {
		fmt.Println("Error reading input file data:", err)
		return
	}

	rows, cols := 41, 41
	start := time.Now()
	encryptedText := route.Encrypt(string(inputBytes), rows, cols)
	elapsed := time.Since(start)
	report.BuildCharHistogram(encryptedText, "enc_route", "enc_route.xlsx")
	fmt.Println("Route encryption took", elapsed)

	encryptedFile, err := os.Create(encryptedFilename)
	if err != nil {
		fmt.Println("Error creating encrypted file:", err)
		return
	}
	defer encryptedFile.Close()

	_, err = encryptedFile.WriteString(encryptedText)
	if err != nil {
		fmt.Println("Error writing encrypted file:", err)
		return
	}

	encryptedFile, err = os.Open(encryptedFilename)
	if err != nil {
		fmt.Println("Error reading encrypted file:", err)
		return
	}
	defer encryptedFile.Close()

	encryptedStat, err := encryptedFile.Stat()
	if err != nil {
		fmt.Println("Error reading encrypted file stats:", err)
		return
	}

	encryptedBytes := make([]byte, encryptedStat.Size())
	_, err = encryptedFile.Read(encryptedBytes)
	if err != nil {
		fmt.Println("Error reading encrypted file data:", err)
		return
	}

	start = time.Now()
	decryptedText := route.Decrypt(string(encryptedBytes), rows, cols)
	elapsed = time.Since(start)
	fmt.Println("Route decryption took", elapsed)

	decryptedFile, err := os.Create(decryptedFilename)
	if err != nil {
		fmt.Println("Error creating decrypted file:", err)
		return
	}
	defer decryptedFile.Close()

	_, err = decryptedFile.WriteString(decryptedText)
	if err != nil {
		fmt.Println("Error writing decrypted file:", err)
		return
	}
}

func testMpr() {
	inputFilename := "input.txt"
	encryptedFilename := "encrypted_mpr.txt"
	decryptedFilename := "decrypted_mpr.txt"

	inputFile, err := os.Open(inputFilename)
	if err != nil {
		fmt.Println("Error reading input file:", err)
		return
	}
	defer inputFile.Close()

	inputStat, err := inputFile.Stat()
	if err != nil {
		fmt.Println("Error reading input file stats:", err)
		return
	}

	inputBytes := make([]byte, inputStat.Size())
	_, err = inputFile.Read(inputBytes)
	if err != nil {
		fmt.Println("Error reading input file data:", err)
		return
	}

	start := time.Now()
	encryptedText := mpr.Encrypt(string(inputBytes), "halaleenkoandrey")
	elapsed := time.Since(start)
	report.BuildCharHistogram(encryptedText, "enc_mpr", "enc_mpr.xlsx")
	fmt.Println("MPR encryption took", elapsed)

	encryptedFile, err := os.Create(encryptedFilename)
	if err != nil {
		fmt.Println("Error creating encrypted file:", err)
		return
	}
	defer encryptedFile.Close()

	_, err = encryptedFile.WriteString(encryptedText)
	if err != nil {
		fmt.Println("Error writing encrypted file:", err)
		return
	}

	encryptedFile, err = os.Open(encryptedFilename)
	if err != nil {
		fmt.Println("Error reading encrypted file:", err)
		return
	}
	defer encryptedFile.Close()

	encryptedStat, err := encryptedFile.Stat()
	if err != nil {
		fmt.Println("Error reading encrypted file stats:", err)
		return
	}

	encryptedBytes := make([]byte, encryptedStat.Size())
	_, err = encryptedFile.Read(encryptedBytes)
	if err != nil {
		fmt.Println("Error reading encrypted file data:", err)
		return
	}

	start = time.Now()
	mpr.Decrypt(string(encryptedBytes), "halaleenkoandrey")
	elapsed = time.Since(start)
	fmt.Println("MPR decryption took", elapsed)

	decryptedFile, err := os.Create(decryptedFilename)
	if err != nil {
		fmt.Println("Error creating decrypted file:", err)
		return
	}
	defer decryptedFile.Close()

	_, err = decryptedFile.WriteString(string(inputBytes))
	if err != nil {
		fmt.Println("Error writing decrypted file:", err)
		return
	}
}
