#include <stdio.h>
#include <unistd.h>
#include <elf.h>
#include "main.h"

/* Function declarations */
void print_magic(Elf64_Ehdr header);
void print_class(Elf64_Ehdr header);
void print_data(Elf64_Ehdr header);
void print_version(Elf64_Ehdr header);
void print_osabi(Elf64_Ehdr header);
void print_abiversion(Elf64_Ehdr header);
void print_type(Elf64_Ehdr header);
void print_entry(Elf64_Ehdr header);
void print_elf_header(Elf64_Ehdr header);

/**
 * main - Entry point
 *
 * @argc: Number of arguments passed on the command line
 *
 * @argv: Array of pointers to strings containing the command-line arguments
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	int fd;
	Elf64_Ehdr header;

	/* Check if the correct number of arguments passed on the command line */
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		exit(98);
	}

	/* Open the specified file in read-only mode */
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		exit(98);
	}

	/* Read the ELF header from the file */
	if (read(fd, &header, sizeof(header)) != sizeof(header))
	{
		perror("Failed to read ELF header");
		exit(98);
	}

	/* Check if the file is actually an ELF file */
	if (header.e_ident[EI_MAG0] != ELFMAG0 || header.e_ident[EI_MAG1] != ELFMAG1
			|| header.e_ident[EI_MAG2] != ELFMAG2 ||
			header.e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Error: Not an ELF file\n");
		exit(98);
	}

	/* Print the required information from the ELF header */
	print_elf_header(header);

	/* Close the file and exit with status code 0 */
	close(fd);
	return (0);
}

/* Function to print the magic number */
/*
 * print_magic: Prints the magic number from the ELF header
 *
 * @header: The ELF header
 */
void print_magic(Elf64_Ehdr header)
{
	printf("Magic: %02x %02x %02x %02x %02x %02x %02x %02x %02x
			%02x %02x %02x %02x %02x %02x %02x\n",
			header.e_ident[0], header.e_ident[1],
			header.e_ident[2], header.e_ident[3],
			header.e_ident[4], header.e_ident[5],
			header.e_ident[6], header.e_ident[7],
			header.e_ident[8], header.e_ident[9],
			header.e_ident[10], header.e_ident[11],
			header.e_ident[12], header.e_ident[13],
			header.e_ident[14], header.e_ident[15]);
}

/* Function to print the class */
/**
 * print_class: Prints the class of ELF header
 *
 * @header: The ELF header
 */
void print_class(Elf64_Ehdr header)
{
	printf("Class: %s\n",
			header.e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "ELF32");
}

/* Function to print the data encoding */
/**
 * print_data: Prints the data encoding of ELF header
 *
 * @header: The ELF header
 */
void print_data(Elf64_Ehdr header)
{
	printf("Data: %s\n", header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement,
			little endian" : "2's complement, big endian");
}

/* Function to print the version */
/**
 * print_version: Prints the version from thr ELF header
 *
 * @header: The ELF header
 */
void print_version(Elf64_Ehdr header)
