/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

 /*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "board_eth.h"
#include "board_spi.h"
#include "board_twi.h"
#include "compiler.h"

#include "peripherals/dma.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

WEAK void board_init(void)
{
#ifdef VARIANT_DDRAM
	bool ddram = false;
#else
	bool ddram = true;
#endif

#ifdef VARIANT_SRAM
	bool clocks = true;
#else
	bool clocks = false;
#endif

	/* Configure misc low-level stuff */
	board_cfg_lowlevel(clocks, ddram, true);

	/* Configure console */
	board_cfg_console(0);

	/* DMA Driver init */
	dma_initialize(false);

#ifdef CONFIG_HAVE_SPI_BUS
	/* Configure SPI bus */
	board_cfg_spi_bus();

#ifdef CONFIG_HAVE_SPI_AT25
	board_cfg_at25();
#endif
#endif

	/* Configure TWI bus */
	board_cfg_twi_bus();

	/* Configure PMIC */
	board_cfg_pmic();

	/* Configure LEDs */
	board_cfg_led();

#ifdef CONFIG_HAVE_ETH
	board_cfg_net(0);
	board_cfg_net(1);
#endif

#ifdef CONFIG_HAVE_LCDC
	/* Configure LCD controller/display */
	board_cfg_lcd();
#endif

#ifdef CONFIG_HAVE_NAND_FLASH
	/* Configure NAND flash */
	board_cfg_nand_flash();
#endif
}
