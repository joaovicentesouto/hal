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

#ifndef CLUSTER_OR1K_MMIO_H_
#define CLUSTER_OR1K_MMIO_H_

/**
 * @addtogroup or1k-core-io Memory-Mapped I/O
 * @ingroup or1k-core
 *
 * @brief Memory-Mapped I/O
 */
/**@{*/

	#define __NEED_MEMORY_TYPES
	#include <arch/core/or1k/types.h>
	#include <sys/types.h>
	#include <stdint.h>

	/**
	 * @brief Writes an 8-bit value to a memory-mapped i/o device.
	 *
	 * @param vaddr Target virtual address.
	 * @param value 8-bit value.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int or1k_mmio_write8(vaddr_t vaddr, uint8_t value);

	/**
	 * @brief Writes an 8-bit string to a memory-mapped i/o device.
	 *
	 * @param vaddr Target virtual address.
	 * @param str   8-bit string.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int or1k_mmio_write8s(vaddr_t vaddr, const uint8_t *str);

	/**
	 * @brief Reads an 8-bit value from a memory-mapped i/o device.
	 *
	 * @param vaddr  Target virtual address.
	 * @param valuep Target store location for 8-bit value.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int or1k_mmio_read8(vaddr_t vaddr, uint8_t *valuep);

		/**
	 * @brief Reads an 8-bit string from a memory-mapped i/o device.
	 *
	 * @param vaddr Target virtual address.
	 * @param strp  Target store location for 8-bit string.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int or1k_mmio_read8s(vaddr_t vaddr, uint8_t **strp);

/**@}*/

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond or1k
 */

	/**
	 * @name Provided Functions
	 */
	/**@{*/
	#define __mmio_write8_fn  /**< or1k_mmio_write8()  */
	#define __mmio_write8s_fn /**< or1k_mmio_write8s() */
	#define __mmio_read8_fn   /**< or1k_mmio_read8()   */
	#define __mmio_read8s_fn  /**< or1k_mmio_read8s()  */
	/**@}*/

	/**
	 * @see or1k_mmio_write8().
	 */
	static inline int mmio_write8(vaddr_t vaddr, uint8_t value)
	{
		return (or1k_mmio_write8(vaddr, value));
	}

	/**
	 * @see or1k_mmio_write8s().
	 */
	static inline int mmio_write8s(vaddr_t vaddr, const uint8_t *str)
	{
		return (or1k_mmio_write8s(vaddr, str));
	}

	/**
	 * @see or1k_mmio_read8().
	 */
	static inline int mmio_read8(vaddr_t vaddr, uint8_t *valuep)
	{
		return (or1k_mmio_read8(vaddr, valuep));
	}

	/**
	 * @see or1k_mmio_read8s().
	 */
	static inline int mmio_read8s(vaddr_t vaddr, uint8_t **strp)
	{
		return (or1k_mmio_read8s(vaddr, strp));
	}

/**@endcond*/

#endif /* CLUSTER_OR1K_MMIO_H_ */
