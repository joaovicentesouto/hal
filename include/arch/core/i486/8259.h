/*
 * MIT License
 *
 * Copyright(c) 2011-2019 The Maintainers of Nanvix
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @addtogroup i486-core-8259 8259 Chip
 * @ingroup i486-core
 *
 * @brief Programmable Interrupt Controller
 */
/**@{*/

#ifndef ARCH_I486_8259_H_
#define ARCH_I486_8259_H_

	/**
	 * @name Provided Interface
	 */
	/**@{*/
	#define __interrupt_level_set
	#define __interrupt_mask
	#define __interrupt_unmask
	#define __interrupt_ack
	/**@}*/

	/**
	 * @name Master PIC Registers
	 */
	/**@{*/
	#define PIC_CTRL_MASTER 0x20 /**< Control */
	#define PIC_DATA_MASTER 0x21 /**< Data    */
	/**@}*/

	/**
	 * @name Slave PIC Registers
	 */
	/**@{*/
	#define PIC_CTRL_SLAVE 0xa0 /**< Control register. */
	#define PIC_DATA_SLAVE 0xa1 /**< Data register.    */
	/**@}*/

	/**
	 * @name Commands Codes
	 */
	/**@{*/
	#define PIC_EOI	0x20 /**< End of Interrupt */
	/**@}*/

	/**
	 * @brief Number of hardware interrupts in the i486 architecture.
	 */
	#define I486_NUM_HWINT 16

	/**
	 * @brief Number of interrupt levels.
	 */
	#define I486_NUM_INTLVL 6

	/**
	 * @name Interrupt Levels
	 */
	/**@{*/
	#define I486_INTLVL_5 5 /**< Level 0: all hardware interrupts disabled. */
	#define I486_INTLVL_4 4 /**< Level 1: clock interrupts enabled.         */
	#define I486_INTLVL_3 3 /**< Level 2: disk interrupts enabled.          */
	#define I486_INTLVL_2 2 /**< Level 3: network interrupts enabled        */
	#define I486_INTLVL_1 1 /**< Level 4: terminal interrupts enabled.      */
	#define I486_INTLVL_0 0 /**< Level 5: all hardware interrupts enabled.  */
	/**@}*/

	/**
	 * @name Interrupt Levels Masks
	 */
	/**@{*/
	#define I486_INTLVL_MASK_5 0xfffb /**< Mask for interrupt level 5.  */
	#define I486_INTLVL_MASK_4 0xfefa /**< Mask for interrupt level 4.  */
	#define I486_INTLVL_MASK_3 0x3eba /**< Mask for interrupt level 3.  */
	#define I486_INTLVL_MASK_2 0x30ba /**< Mask for interrupt level 2.  */
	#define I486_INTLVL_MASK_1 0x2000 /**< Mask for interrupt level 1.  */
	#define I486_INTLVL_MASK_0 0x0000 /**< Mask for interrupt level 0.  */
	/**@}*/

#ifndef _ASM_FILE_

	#include <arch/core/i486/pmio.h>
	#include <nanvix/const.h>
	#include <stdint.h>

	/**
	 * @brief Initializes the PIC.
	 *
	 * @param offset1 Vector offset for master PIC.
	 * @param offset2 Vector offset for slave PIC.
	 */
	EXTERN void i486_pic_setup(uint8_t offset1, uint8_t offset2);

	/**
	 * @brief Masks an interrupt.
	 *
	 * @param intnum Number of the target interrupt.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int i486_pic_mask(int intnum);

	/**
	 * @see i486_pic_mask()
	 *
	 * @cond i486
	 */
	static inline int interrupt_mask(int intnum)
	{
		return (i486_pic_mask(intnum));
	}
	/**@endcond*/

	/**
	 * @brief Unmasks an interrupt.
	 *
	 * @param intnum Number of the target interrupt.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int i486_pic_unmask(int intnum);

	/**
	 * @see i486_pic_unmask()
	 *
	 * @cond i486
	 */
	static inline int interrupt_unmask(int intnum)
	{
		return (i486_pic_unmask(intnum));
	}
	/**@endcond*/

	/**
	 * @brief Acknowledges an interrupt.
	 *
	 * @param intnum Number of the target interrupt.
	 */
	static inline void i486_pic_ack(int intnum)
	{
		if (intnum >= 8)
			i486_output8(PIC_CTRL_SLAVE, PIC_EOI);

		i486_output8(PIC_CTRL_MASTER,PIC_EOI);
	}

	/**
	 * @see i486_pic_ack()
	 *
	 * @cond i486
	 */
	static inline void interrupt_ack(int intnum)
	{
		i486_pic_ack(intnum);
	}
	/**@endcond*/

	/**
	 * @brief Sets the interrupt level of the calling core.
	 *
	 * @param newlevel New interrupt level.
	 *
	 * @returns The old interrupt level.
	 */
	EXTERN int i486_pic_lvl_set(int newlevel);

	/**
	 * @see i486_pic_lvl_set()
	 *
	 * @cond i486
	 */
	static inline int interrupt_level_set(int newlevel)
	{
		return (i486_pic_lvl_set(newlevel));
	}
	/**@endcond*/

#endif /* _ASM_FILE_ */

/**@}*/

#endif /* ARCH_I486_8259_H_ */

