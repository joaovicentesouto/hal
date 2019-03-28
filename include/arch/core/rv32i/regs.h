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


#ifndef ARCH_CORE_RV32I_REGS_H_
#define ARCH_CORE_RV32I_REGS_H_

	#ifndef __NEED_CORE_REGS
		#error "do not include this file"
	#endif

/**
 * @addtogroup rv32i-core-regs Registers
 * @ingroup rv32i-core
 *
 * @brief Registers
 */
/**@{*/

	/**
	 * @name Machine Cause Register (mcause)
	 */
	/**@{*/
	#define RV32I_MCAUSE_INT   0x80000000ul /**< Interrupt? */
	#define RV32I_MCAUSE_CAUSE 0x000000fful /**< Trap Cause */
	/**@}*/

/**@}*/

#endif /* ARCH_CORE_RV32I_REGS_H_ */
