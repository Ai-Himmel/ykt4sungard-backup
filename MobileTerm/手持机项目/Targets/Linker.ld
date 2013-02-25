GROUP(-lgcc -lc -lg -lm -lARMPos -lext -lcard -lcontactless -lmagcard 
-lsound -ldb -lfinger -ljpg -lsim -lusb -lupdown -lprinter -ltcpip -lrf433 libWiFi.a)
MEMORY
{
      ram  : ORIGIN = 0x0C060000, LENGTH = 7808k   
}

ENTRY(_start)

SECTIONS
{	
	.text :
  	{
		_stext  =  .;
                *(.text)
    		. = ALIGN(4);
    		
    		__CTOR_LIST__ = .;
     		LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
		*(.ctors)
     		LONG(0)
     		__CTOR_END__ = .;
     		__DTOR_LIST__ = .;
     		LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
     		*(.dtors)
     		LONG(0)
     		__DTOR_END__ = .;
     	 	
     	 	*(.rodata)
  		*(.rodata*)
  		*(.glue_7t)
		*(.glue_7)
        	
        	. = ALIGN(4);
     		_etext = .;
	} > ram  
 
	.data :   		
	{
		. = ALIGN(4);
		_data = .;
        
		*(.data)
		. = ALIGN(4);
		_edata = .;
	} > ram


	.bss :
	{
		. = ALIGN(4);
       		_start_bss = .;
	
		*(.bss)
		*(COMMON)
		. = ALIGN(4);
		_end_bss = .;
	} > ram
	
	. = ALIGN(4);
	end = .;                           
	_end = .;
}