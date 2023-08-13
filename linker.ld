ENTRY(Reset_Handler)
/* This is the Memory Layouts Definition */
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
}

/*
 * The '__stack' definition is required by crt0, do not remove it.
 */
__stack = ORIGIN(RAM) + LENGTH(RAM);

_estack = __stack; 	/* STM specific definition */

/* This is the Sections Layouts Definition */
SECTIONS {
	PROVIDE(intvects_base_adress = 0x08000000);
    .intvects intvects_base_adress : AT (intvects_base_adress)
	 { 
		. = ALIGN ( 4 ) ;
	    __intvects_start__ = . ;
		*(.intvect .intvect.* .isr_vector .isr_vector.*)
		__intvects_end__ = . ;
	    } > FLASH
	.text : { 
		__text_start__ = . ;
		*(.text .text.*)
		__text_end__ = . ;
            	                    } > FLASH
	.rodata : {
	    __rodata_start__ = . ;
		*(.rodata .rodata.*)
		__rodata_end__ = . ;
	                                    } > FLASH 
	.data  : ALIGN ( 4 ) {
		__data_load__ = LOADADDR ( .data );
		__data_start__ = . ;
		*(.data .data.*)
		. = ALIGN ( 4 ) ;
		__data_end__ = . ;
	                                 } > RAM AT> FLASH
	.bss : {
		__bss_start__ = . ;
		*(.bss .shbss .bss.* COMMON)
		. = ALIGN ( 4 ) ;
		__bss_end__ = . ;
	                               } > RAM
	.stack : ALIGN ( 0x8 ) {
		__stack__ = . ;
		KEEP ( *(.stack) )
									}
}
