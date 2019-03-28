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

#ifndef NANVIX_CONST_H_
#define NANVIX_CONST_H_

/**
 * @defgroup kernel Nanvix Kernel
 */

/**
 * @addtogroup kernel-consts Kernel Constants
 * @ingroup kernel
 */
/**@{*/

	/**
	 * @name Scope Constants
	 */
	/**@{*/
	#define PUBLIC         /**< Global scope       */
	#define PRIVATE static /**< File scope.        */
	#define EXTERN extern  /**< Defined elsewhere. */
	/**@}*/

	/**
	 * @brief Places object in a binary section.
	 *
	 * @param x Target binary section.
	 */
	#define SECTION(x) __attribute__((section(x)))

	/**
	 * @brief Overrides a symbol.
	 */
	#define OVERRIDE __attribute__((weak))

	/**
	 * @brief Casts an inline function.
	 */
	#define INLINE __atribute__((inline))

	/**
	 * @brief Casts a function  with no return.
	 */
	#define NORETURN __attribute__((noreturn))

	/**
	 * @brief Aligns an object at a boundary.
	 *
	 * @param x Boundary.
	 */
	#define ALIGN(x) __attribute__((aligned(x)))

	/**
	 * @brief Packs a structure
	 *
	 * @param x Boundary.
	 */
	#define PACK __attribute__((packed))

	/**
	 * @name Logical Constants
	 */
	/**@{*/
	#define FALSE 0 /**< False. */
	#define TRUE  1 /**< True.  */
	/**@}*/

	#define __need_size_t
	#define __need_ssize_t
	#define __need_NULL
	#include <decl.h>

/**@}*/

#endif /* NANVIX_CONST_H_ */
