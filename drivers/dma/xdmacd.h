/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#ifndef _XDMACD_H_
#define _XDMACD_H_

#ifdef CONFIG_HAVE_XDMAC
/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "chip.h"
#include "dma/xdmac.h"

#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/

/** \addtogroup dmad_defines DMA Driver Defines
        @{*/

/** Pseudo Peripheral ID for memory transfers */
#define XDMACD_PERIPH_MEMORY 0xFF

/**     @}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup dmad_structs DMA Driver Structs
        @{*/

struct _xdmacd_cfg {
	uint32_t  ubc;      /**< Microblock Size */
	uint32_t  bc;       /**< Block Control */
	uint32_t  ds;       /**< Data Stride */
	uint32_t  sus;      /**< Source Microblock Stride */
	uint32_t  dus;      /**< Destination Microblock Stride */
	void     *sa;       /**< Source Address */
	void     *da;       /**< Destination Address */
	uint32_t  cfg;      /**< Configuration Register */
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_functions DMA Driver Functionos
        @{*/

/**
 * \brief Initialize DMA driver instance.
 * \param polling if true, interrupts will not be configured and xdmacd_poll
 * must be called to poll for transfer completion
 */
extern void xdmacd_initialize(bool polling);

/**
 * \brief Poll for transfers completion.
 * If polling mode is enabled, this function will call callbacks for completed
 * transfers.  If interrupt mode is enabled, this function will do nothing.
 */
extern void xdmacd_poll(void);

/**
 * \brief Allocate an DMA channel
 * \param src Source peripheral ID, XDMACD_PERIPH_MEMORY for memory.
 * \param dest Destination peripheral ID, XDMACD_PERIPH_MEMORY for memory.
 * \return Channel pointer if allocation successful, or NULL if channel
 * allocation failed.
 */
extern struct _dma_channel *xdmacd_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern int xdmacd_free_channel(struct _dma_channel* channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern int xdmacd_set_callback(struct _dma_channel* channel, struct _callback* cb);

/**
 * \brief Configure DMA for a single transfer.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \param desc_ctrl optional descriptor control
 * \param desc_addr optional descriptor address
 */
extern int xdmacd_configure_transfer(struct _dma_channel* channel,
				     struct _xdmacd_cfg *cfg, uint32_t desc_ctrl, void *desc_addr);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern int xdmacd_start_transfer(struct _dma_channel* channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool xdmacd_is_transfer_done(struct _dma_channel* channel);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern int xdmacd_stop_transfer(struct _dma_channel* channel);

/**
 * \brief Suspend DMA transfer.
 * \param channel Channel pointer
 */
extern int xdmacd_suspend_transfer(struct _dma_channel* channel);

/**
 * \brief Resume DMA transfer.
 * \param channel Channel pointer
 */
extern int xdmacd_resume_transfer(struct _dma_channel* channel);

/**
 * \brief Get size of remaining data to be transferred by DMA transfer.
 * \param channel Channel pointer
 */
extern uint32_t xdmacd_get_remaining_data_len(struct _dma_channel* channel);

/**
 * \brief Reset the specified DMA chanel.
 * \param channel Channel pointer
 */
extern int xdmacd_reset_channel(struct _dma_channel* channel);

/**
 * \brief  Get next descriptor's address for the relevant channel of given XDMA.
 * \param channel Channel pointer
 */
extern uint32_t xdmacd_get_desc_addr(struct _dma_channel* channel);

/**
 * \brief Flush the relevant channel's FIFO of given XDMAC.
 *
 * \param channel Channel pointer
 */
extern void xdmacd_fifo_flush(struct _dma_channel* channel);

/**     @}*/

/**@}*/

#endif /* CONFIG_HAVE_XDMAC */

#endif /* _XDMACD_H_ */
