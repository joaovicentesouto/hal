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

#ifndef ARCH_CORE_RV32I_INT_H_
#define ARCH_CORE_RV32I_INT_H_

/**
 * @addtogroup rv32i-core-int Interrupts
 * @ingroup rv32i-core
 *
 * @brief Interrupt Interface
 */
/**@{*/

	/* Must come first. */
	#define __NEED_IVT
	#define __NEED_CONTEXT

	#include <arch/core/rv32i/context.h>
	#include <arch/core/rv32i/ivt.h>

	/**
	 * @name Interrupts
	 */
	/**@{*/
	#define RV32I_INT_SWINT_USER       0 /**< User Software Interrupt       */
	#define RV32I_INT_SWINT_KERNEL     1 /**< Supervisor Software Interrupt */
	#define RV32I_INT_SWINT_RESERVED   2 /**< Reserved                      */
	#define RV32I_INT_SWINT_MACHINE    3 /**< Machine Software Interrupt    */
	#define RV32I_INT_TIMER_USER       4 /**< User Timer Interrupt          */
	#define RV32I_INT_TIMER_KERNEL     5 /**< Supervisor Timer Interrupt    */
	#define RV32I_INT_TIMER_RESERVED   6 /**< Reserved                      */
	#define RV32I_INT_TIMER_MACHINE    7 /**< Machine Timer Interrupt       */
	#define RV32I_INT_EXTERN_USER      8 /**< User External Interrupt       */
	#define RV32I_INT_EXTERN_KERNEL    9 /**< Supervisor External Interrupt */
	#define RV32I_INT_EXTERN_RESERVED 10 /**< Reserved                      */
	#define RV32I_INT_EXTERN_MACHINE  11 /**< Machine External Interrupt    */
	#define RV32I_INT_RESERVED        12 /**< Reserved                      */
	/**@}*/

	/**
 * @brief High-level interrupt dispatcher.
	 *
	 * @param num Interrupt request.
	 * @param ctx Interrupted execution context.
	 */
	extern void rv32i_do_int(int num, const struct context *ctx);

	/**
	 * @brief Enables interrupts.
	 *
	 * Enables all interrupts in the underlying core.
	 */
	static inline void rv32i_int_enable(void)
	{
	}

	/**
	 * @brief Disables interrupts.
	 *
	 * Disables all interrupts in the underlying core.
	 */
	static inline void rv32i_int_disable(void)
	{
	}

	/**
	 * @brief Sets a handler for a interrupt.
	 *
	 * @param num     Number of the target interrupt.
	 * @param handler Hardware interrupt handler.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	extern int rv32i_int_handler_set(int num, void (*handler)(int));

/**@}*/

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond rv32i
 */

	/**
	 * @name Exported Constants
	 */
	/**@{*/
	#define _INTERRUPTS_NUM RV32I_INT_NUM  /**< @ref RV32I_INT_NUM  */
	/**@}*/

	/**
	 * @name Exported Functions
	 */
	/**@{*/
	#define __interrupts_disable    /**< interrupts_disable()    */
	#define __interrupts_enable     /**< interrupts_enable()     */
	#define __interrupt_set_handler /**< interrupt_set_handler() */
	/**@}*/

	/**
	 * @see rv32i_int_enable().
	 */
	static inline void interrupts_enable(void)
	{
		rv32i_int_enable();
	}

	/**
	 * @see rv32i_int_disable().
	 */
	static inline void interrupts_disable(void)
	{
		rv32i_int_disable();
	}

	/**
	 * @see rv32i_int_handler_set().
	 */
	static inline int interrupt_set_handler(int num, void (*handler)(int))
	{
		return (rv32i_int_handler_set(num, handler));
	}

/**@endcond*/

#endif /* ARCH_CORE_RV32I_INT_H_ */
