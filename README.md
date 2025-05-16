HW#11:
  to assemble: nasm -f elf32 -g -F dwarf -o hw11translate2Ascii.o hw11translate2Ascii.asm
  to link and load: ld -m elf_i386 -o hw11translate2Ascii hw11translate2Ascii.o
  Desc: this program takes the number of bytes of data, converts them to ascii characters, and prints that data to the screen
