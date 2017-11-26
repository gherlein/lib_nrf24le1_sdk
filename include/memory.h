/////////////////////////////////////////////////////////////////////////////
//
// File: memory.h
//
// Copyright S. Brennen Ball, 2011
//
// The author provides no guarantees, warantees, or promises, implied or
//  otherwise.  By using this software you agree to indemnify the author
//  of any damages incurred by using it.
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
/////////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_H_
#define MEMORY_H_

#include "reg24le1.h"

//////////////////////////////////////////////////////////
// Defines for the code section of the flash memory array
//////////////////////////////////////////////////////////
#define	MEMORY_FLASH_CODE_NUM_PAGES		(32)
#define	MEMORY_FLASH_CODE_PAGE_SIZE		(MEMORY_FLASH_PAGE_SIZE)
#define MEMORY_FLASH_CODE_NUM_BYTES		(MEMORY_FLASH_CODE_NUM_PAGES * MEMORY_FLASH_CODE_PAGE_SIZE)
#define MEMORY_FLASH_CODE_START_ADDRESS	(0)
#define MEMORY_FLASH_CODE_END_ADDRESS	(MEMORY_FLASH_CODE_START_ADDRESS + MEMORY_FLASH_CODE_NUM_BYTES - 1)

///////////////////////////////////////////////////////////
// Defines for the NVRAM section of the flash memory array
///////////////////////////////////////////////////////////
#define	MEMORY_FLASH_NV_NUM_PAGES		(4)
#define	MEMORY_FLASH_NV_PAGE_SIZE		(MEMORY_FLASH_PAGE_SIZE)
#define MEMORY_FLASH_NV_NUM_BYTES		(MEMORY_FLASH_NV_NUM_PAGES * MEMORY_FLASH_NV_PAGE_SIZE)
#define MEMORY_FLASH_NV_START_ADDRESS	(MEMORY_FLASH_CODE_END_ADDRESS + 1)
#define MEMORY_FLASH_NV_END_ADDRESS		(MEMORY_FLASH_NV_START_ADDRESS + MEMORY_FLASH_NV_NUM_BYTES - 1)

//////////////////////////////////////////////
// Defines for the overall flash memory array
//////////////////////////////////////////////
#define	MEMORY_FLASH_NUM_PAGES		(MEMORY_FLASH_CODE_NUM_PAGES + MEMORY_FLASH_NV_NUM_PAGES)
#define	MEMORY_FLASH_PAGE_SIZE		(512)
#define MEMORY_FLASH_NUM_BYTES		(MEMORY_FLASH_CODE_NUM_BYTES + MEMORY_FLASH_NV_NUM_BYTES)
#define MEMORY_FLASH_START_ADDRESS	(MEMORY_FLASH_CODE_START_ADDRESS)
#define MEMORY_FLASH_END_ADDRESS	(MEMORY_FLASH_NV_END_ADDRESS)


////////////////////////////////////
// Enumeration for function returns
////////////////////////////////////
typedef enum
{
	MEMORY_FLASH_OK = 0,
	MEMORY_FLASH_BAD_PARAMS = 1
} memory_flash_return_t;


/////////////////////////////////////////////////
// Function macros for general memory operations
/////////////////////////////////////////////////
#define memory_movx_accesses_data_memory()	(PCON &= (~PCON_PMW))
#define memory_movx_accesses_code_memory()	(PCON |= PCON_PMW)

///////////////////////////////////////
// Function macros for SRAM operations
///////////////////////////////////////
#define memory_sram_map_data_retentive_as_data()		(MEMCON &= (~MEMCON_SRAM_DATA_RETENTIVE_MAPPING))
#define memory_sram_map_data_retentive_as_code()		(MEMCON |= MEMCON_SRAM_DATA_RETENTIVE_MAPPING)
#define memory_sram_map_non_data_retentive_as_data()	(MEMCON &= (~MEMCON_SRAM_DATA_NON_RETENTIVE_MAPPING))
#define memory_sram_map_non_data_retentive_as_code()	(MEMCON |= MEMCON_SRAM_DATA_NON_RETENTIVE_MAPPING)
#define memory_sram_start_at_0x0000()					(MEMCON &= (~MEMCON_SRAM_START_LOCATION))
#define memory_sram_start_at_0x8000()					(MEMCON |= MEMCON_SRAM_START_LOCATION)

////////////////////////////////////////
// Function macros for flash operations
////////////////////////////////////////
#define memory_flash_enable_write_access()				sbit_set(FSR_SB_WEN)
#define memory_flash_disable_write_access()				sbit_clear(FSR_SB_WEN)
#define memory_flash_wait_for_write_complete()			while(FSR_SB_RDYN)
#define memory_flash_get_page_start_address(page_num)	(page_num * MEMORY_FLASH_PAGE_SIZE)
#define memory_flash_get_page_end_address(page_num)		(memory_flash_get_page_start_address(page_num) + MEMORY_FLASH_PAGE_SIZE - 1)


////////////////////////////
// Function prototypes
////////////////////////////
memory_flash_return_t memory_flash_erase_page(uint8_t page_num);
memory_flash_return_t memory_flash_copy_page_to_ram(uint8_t page_num, uint8_t * page_buffer);
memory_flash_return_t memory_flash_copy_ram_to_page(uint8_t page_num, uint8_t * page_buffer);
memory_flash_return_t memory_flash_read_byte(uint16_t address, uint8_t * data_byte);
memory_flash_return_t memory_flash_read_bytes(uint16_t start_address, uint16_t num_bytes_to_read, uint8_t * data_array);
bool memory_flash_can_byte_be_written_without_page_erase(uint8_t cur_flash_val, uint8_t write_val);
memory_flash_return_t memory_flash_write_byte(uint16_t address, uint8_t write_val);
memory_flash_return_t memory_flash_write_bytes(uint16_t start_address, uint16_t num_bytes_to_write, uint8_t * data_array);
memory_flash_return_t memory_flash_write_bytes_smart(uint16_t start_address, uint16_t num_bytes_to_write, uint8_t * data_array, uint8_t * page_buffer);


#endif /* MEMORY_H_ */
