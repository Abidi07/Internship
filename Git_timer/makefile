
#Makefile
#MCU_Device..............Attiny85
#Program_Code............LED Blink
#Programmer..............
#AVRDUDE.................Avr download and upload
#FUSES...................Parameters for avrdude to flash


#######################################################################################################################################


MCU              = attiny85
CPU_FREQUENCY    = 8e6
CC               = avr-gcc
AS               = avr-size 
AO               = avr-objcopy 
PROGRAMMER       = usbtiny
OBJ_O            = timer_int.o
OBJ_C            = timer_int.c
OBJ_ELF          = timer_int.elf
AVRDUDE          = /home/abidi/Downloads/arduino-1.8.5/hardware/tools/avr/bin/avrdude 
AVRDUDECONF      = -C/home/abidi/Downloads/arduino-1.8.5/hardware/tools/avr/etc/avrdude.conf
FUSE_EXT         = -Uefuse:w:0xFF:m
FUSE_HIGH        = -Uhfuse:w:0xD7:m
FUSE_LOW         = -Ulfuse:w:0xC2:m
LOCK             = -Ulock:w:0xFF:m
BAUD_RATE        = 19200
HF               = timer_int_all.hex
WRITE_FLASH      = -Uflash:w:timer_int_all.hex
PORT             = 
COMPILE          = avr-gcc -Wall -Os -DF_CPU=${CPU_FREQUENCY} -mmcu=attiny85
CFLAGS           = -std=c99 -Wall -g -Os -mmcu=attiny85 -DF_CPU=${CPU_FREQUENCY} -I



#######################################################################################################################################

#Following are the targets for makefile


build:
	${CC} ${CFLAGS} -c ${OBJ_C} -o ${OBJ_O}

size:
	${AS} ${OBJ_O}

elf_file: ${OBJ_O}
	${COMPILE} -o ${OBJ_ELF} ${OBJ_O}

hex_file: ${OBJ_O}
	${AO} -j .text -j .data -O ihex ${OBJ_O}  ${HF}

read: 
	${AVRDUDE} -v -F -p ${MCU} -c${PROGRAMMER} ${PORT} -U flash:r:${HF}:i

erase:
	${AVRDUDE} -v -F -p ${MCU} -c${PROGRAMMER} ${PORT} -e ${HF}:i

flash_hex:
	${AVRDUDE} ${AVRDUDECONF} -v -p${MCU} -c${PROGRAMMER} ${PORT} -b${BAUD_RATE} ${WRITE_FLASH} ${HF}.ino.hex:i

flash_fuses:
	${AVRDUDE} ${AVRDUDECONF} -v -p${MCU} -c${PROGRAMMER} ${PORT} -b ${BAUD_RATE} -e  ${LOCK}  ${FUSE_EXT} ${FUSE_HIGH} ${FUSE_LOW}	

clean:
	rm -f *.o *.s *.hex *.elf
