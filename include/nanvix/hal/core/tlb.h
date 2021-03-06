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

#ifndef HAL_CORE_TLB_H_
#define HAL_CORE_TLB_H_

	/* Core Interface Implementation */
	#include <nanvix/hal/core/_core.h>

/*============================================================================*
 * Interface Implementation Checking                                          *
 *============================================================================*/

	#if (!defined(TLB_SOFTWARE) && !defined (TLB_HARDWARE))
		#error "who manages the TLB?"
	#endif

	/*
	 * Required interface for software- and hardware-managed TLBs.
	 */
	#ifndef __tlb_flush_fn
		#error "tlb_flush() not defined?"
	#endif

	/*
	 * Required interface for software-managed TLBs.
	 */
	#ifdef TLB_SOFTWARE

		/* Constants. */
		#ifndef TLB_INSTRUCTION
		#error "TLB_INSTRUCTION not defined!"
		#endif
		#ifndef TLB_DATA
		#error "TLB_DATA not defined!"
		#endif

		/* Types and Structures */
		#ifndef __tlbe_st
			#error "struct tlbe not defined?"
		#endif

		/* Functions */
		#ifndef __tlbe_vaddr_get_fn
			#error "tlb_vaddr_get() not defined?"
		#endif
		#ifndef __tlbe_paddr_get_fn
			#error "tlb_paddr_get() not defined?"
		#endif
		#ifndef __tlb_lookup_vaddr_fn
			#error "tlb_lookup_vaddr() not defined?"
		#endif
		#ifndef __tlb_lookup_paddr_fn
			#error "tlb_lookup_paddr() not defined?"
		#endif
		#ifndef __tlb_write_fn
			#error "tlb_write() not defined?"
		#endif
		#ifndef __tlb_inval_fn
			#error "tlb_inval() not defined?"
		#endif

	#endif

/*============================================================================*
 * TLB Interface                                                              *
 *============================================================================*/

/**
 * @addtogroup kernel-hal-core-tlb TLB
 * @ingroup kernel-hal-core
 *
 * @brief TLB HAL Interface
 */
/**@{*/

	#include <nanvix/const.h>

	/**
	 * @brief Casts something to a virtual address.
	 *
	 * @param x Something.
	 */
	#define VADDR(x) ((vaddr_t) (x))

	/**
	 * @brief Casts something to a physical address.
	 *
	 * @param x Something.
	 */
	#define PADDR(x) ((paddr_t) (x))

#if defined(TLB_HARDWARE)

	/**
	 * @name TLB Types
	 */
	/**@{*/
	#define TLB_INSTRUCTION 0 /**< Instruction TLB */
	#define TLB_DATA        1 /**< Data TLB        */
	/**@}*/

#endif

	/**
	 * @brief TLB entry.
	 */
	struct tlbe;

	/**
	 * @brief Gets the virtual address encoded in a TLB entry.
	 *
	 * @param tlbe Target TLB entry.
	 *
	 * @returns The virtual address encoded in the TLB entry pointed
	 * to by @p tlbe.
	 */
	EXTERN vaddr_t tlbe_vaddr_get(const struct tlbe *tlbe);

	/**
	 * @brief Gets the physical address encoded in a TLB entry.
	 *
	 * @param tlbe Target TLB entry.
	 *
	 * @returns The physical address encoded in the TLB entry pointed
	 * to by @p tlbe.
	 */
	EXTERN paddr_t tlbe_paddr_get(const struct tlbe *tlbe);

	/**
	 * @brief Lookups a TLB entry by virtual address.
	 *
	 * @param tlb_type Target TLB (D-TLB or I-TLB).
	 * @param vaddr    Target virtual address.
	 *
	 * @returns Upon successful completion, a pointer to the TLB entry
	 * that matches the virtual address @p vaddr is returned. If no
	 * TLB entry matches @p vaddr, @p NULL is returned instead.
	 */
#if !((defined(TLB_HARDWARE) && !defined(__tlb_lookup_vaddr)))
	EXTERN const struct tlbe *tlb_lookup_vaddr(int tlb_type, vaddr_t vaddr);
#else
	static const struct tlbe *tlb_lookup_vaddr(int tlb_type, vaddr_t vaddr)
	{
		((void) tlb_type);
		((void) vaddr);

		return (NULL);
	}
#endif

	/**
	 * @brief Lookups a TLB entry by physical address.
	 *
	 * @param tlb_type Target TLB (D-TLB or I-TLB).
	 * @param paddr    Target physical address.
	 *
	 * @returns Upon successful completion, a pointer to the TLB entry
	 * that matches the physical address @p paddr is returned. If no
	 * TLB entry matches @p paddr, @p NULL is returned instead.
	 */
#if !((defined(TLB_HARDWARE) && !defined(__tlb_lookup_paddr_fn)))
	EXTERN const struct tlbe *tlb_lookup_paddr(int tlb_type, paddr_t paddr);
#else
	static const struct tlbe *tlb_lookup_paddr(int tlb_type, paddr_t paddr)
	{
		((void) tlb_type);
		((void) paddr);

		return (NULL);
	}
#endif

	/**
	 * @brief Encodes a virtual address into the TLB.
	 *
	 * @param tlb_type Target TLB (D-TLB or I-TLB).
	 * @param vaddr    Target virtual address.
	 * @param paddr    Target physical address.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
#if !((defined(TLB_HARDWARE) && !defined(__tlb_write_fn)))
	EXTERN int tlb_write(int tlb_type, vaddr_t vaddr, paddr_t paddr);
#else
	static inline int tlb_write(int tlb_type, vaddr_t vaddr, paddr_t paddr)
	{
		((void) tlb_type);
		((void) vaddr);
		((void) paddr);

		return (0);
	}
#endif

	/**
	 * @brief Invalidates a virtual address in the TLB.
	 *
	 * @param tlb_type Target TLB (D-TLB or I-TLB).
	 * @param vaddr    Target virtual address.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
#if !((defined(TLB_HARDWARE) && !defined(__tlb_inval_fn)))
	EXTERN int tlb_inval(int tlb_type, vaddr_t vaddr);
#else
	static inline int tlb_inval(int tlb_type, vaddr_t vaddr)
	{
		((void) tlb_type);
		((void) vaddr);

		return (0);
	}
#endif

	/**
	 * @brief Flushes changes in the TLB.
	 *
	 * @returns Upon successful completion, zero is returned. Upon
	 * failure, a negative error code is returned instead.
	 */
	EXTERN int tlb_flush(void);

/**@}*/

#endif /* HAL_CORE_TLB_H_ */


