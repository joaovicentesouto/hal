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

#ifndef ARCH_CORE_K1B_MMU_H_
#define ARCH_CORE_K1B_MMU_H_

/**
 * @addtogroup k1b-core-mmu MMU
 * @ingroup k1b-core
 *
 * @brief Memory Management Unit
 */
/**@{*/

	/* Must comme first. */
	#define __NEED_K1B_ELF
	#define __NEED_MEMORY_TYPES

	#include <arch/core/k1b/elf.h>
	#include <arch/core/k1b/types.h>
	#include <nanvix/klib.h>
	#include <errno.h>
	#include <stdint.h>

	/**
	 * @name Page Shifts and Masks
	 */
	/**@{*/
	#if defined(__ioddr__) || defined(__ioeth__)
		#define K1B_HUGE_PAGE_SHIFT 16                  /**< Huge Page Shift   */
	#elif defined(__node__)
		#define K1B_HUGE_PAGE_SHIFT 15                  /**< Huge Page Shift   */
	#endif
	#define K1B_PAGE_SHIFT      12                      /**< Page Shift        */
	#define K1B_PGTAB_SHIFT     22                      /**< Page Table Shift  */
	#define K1B_PAGE_MASK       (~(K1B_PAGE_SIZE - 1))  /**< Page Mask         */
	#define K1B_PGTAB_MASK      (~(K1B_PGTAB_SIZE - 1)) /**< Page Table Mask   */
	/**@}*/

	/**
	 * @name Size of Pages and Page Tables
	 */
	/**@{*/
	#define K1B_HUGE_PAGE_SIZE (1 << K1B_HUGE_PAGE_SHIFT) /**< Huge Page Size (in bytes)            */
	#define K1B_PAGE_SIZE  (1 << K1B_PAGE_SHIFT)          /**< Page Size (in bytes)                 */
	#define K1B_PGTAB_SIZE (1 << K1B_PGTAB_SHIFT)         /**< Page Table Size (in bytes)           */
	#define K1B_PTE_SIZE   4                              /**< Page Table Entry Size (in bytes)     */
	#define K1B_PDE_SIZE   4                              /**< Page Directory Entry Size (in bytes) */
	/**@}*/

	/**
	 * @name Page Shifts
	 */
	/**@{*/
	#define PAGE_SHIFT  K1B_PAGE_SHIFT  /**< Page Shift       */
	#define PGTAB_SHIFT K1B_PGTAB_SHIFT /**< Page Table Shift */
	#define PAGE_MASK   K1B_PAGE_MASK   /**< Page Mask        */
	#define PGTAB_MASK  K1B_PGTAB_MASK  /**< Page Table Mask  */
	/**@}*/

	/**
	 * @name Size of Pages and Page Tables
	 */
	/**@{*/
	#define PAGE_SIZE  K1B_PAGE_SIZE  /**< Page Size                 */
	#define PGTAB_SIZE K1B_PGTAB_SIZE /**< Page Table Size           */
	#define PTE_SIZE   K1B_PTE_SIZE   /**< Page Table Entry Size     */
	#define PDE_SIZE   K1B_PDE_SIZE   /**< Page Directory Entry Size */
	/**@}*/

	/**
	 * @brief Initializes the MMU.
	 */
	extern void k1b_mmu_setup(void);

/**@}*/

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond k1b
 */

	/**
	 * @name Exported Constants
	 */
	/**@{*/
	#define KPAGE_SIZE  K1B_HUGE_PAGE_SIZE /**< @ref K1B_PAGE_SIZE   */
	#define PAGE_SIZE   K1B_PAGE_SIZE      /**< @ref K1B_PAGE_SIZE   */
	#define PGTAB_SIZE  K1B_PGTAB_SIZE     /**< @ref K1B_PGTAB_BIT   */
	#define PTE_SIZE    K1B_PTE_SIZE       /**< @ref K1B_PTE_SIZE    */
	#define PDE_SIZE    K1B_PDE_SIZE       /**< @ref K1B_PDE_SIZE    */
	#define PAGE_SHIFT  K1B_PAGE_SHIFT     /**< @ref K1B_PAGE_SHIFT  */
	#define PGTAB_SHIFT K1B_PGTAB_SHIFT    /**< @ref K1B_PGTAB_SHIFT */
	#define PAGE_MASK   K1B_PAGE_MASK      /**< @ref K1B_PAGE_MASK   */
	#define PGTAB_MASK  K1B_PGTAB_MASK     /**< @ref K1B_PGTAB_MASK  */
	#define PADDR_BIT   K1B_PADDR_BIT      /**< @ref K1B_PADDR_BIT   */
	#define VADDR_BIT   K1B_VADDR_BIT      /**< @ref K1B_VADDR_BIT   */
	#define PADDR_BYTE  K1B_PADDR_BYTE     /**< @ref K1B_PADDR_BYTE  */
	#define VADDR_BYTE  K1B_VADDR_BYTE     /**< @ref K1B_VADDR_BYTE  */
	/**@}*/

	/**
	 * @name Exported Types
	 */
	/**@{*/
	#define __frame_t /**< @ref frame_t */
	#define __paddr_t /**< @ref paddr_t */
	#define __vaddr_t /**< @ref vaddr_t */
	/**@}*/

	/**
	 * @name Exported Variables
	 */
	/**@{*/
	#define __root_pgdir   /**< @ref root_pgdir   */
	#define __kernel_pgtab /**< @ref kernel_pgtab */
	#define __kpool_pgtab  /**< @ref kpool_pgtab  */
	/**@}*/

	/**
	 * @brief Exported Functions
	 */
	/**@{*/
	#define __pde_clear_fn       /**< pde_clear()       */
	#define __pde_frame_get_fn   /**< pde_frame_get()   */
	#define __pde_frame_set_fn   /**< pde_frame_set()   */
	#define __pde_get_fn         /**< pde_get()         */
	#define __pde_is_present_fn  /**< pde_is_present()  */
	#define __pde_is_user_fn     /**< pde_is_user()     */
	#define __pde_is_write_fn    /**< pde_is_write()    */
	#define __pde_present_set_fn /**< pde_present_set() */
	#define __pde_user_set_fn    /**< pde_user_set()    */
	#define __pde_write_set_fn   /**< pde_write_set()   */
	#define __pte_clear_fn       /**< pte_clear()       */
	#define __pte_frame_get_fn   /**< pte_frame_get()   */
	#define __pte_frame_set_fn   /**< pte_frame_set()   */
	#define __pte_get_fn         /**< pte_get()         */
	#define __pte_is_present_fn  /**< pte_is_present()  */
	#define __pte_is_user_fn     /**< pte_is_user()     */
	#define __pte_is_write_fn    /**< pte_is_write()    */
	#define __pte_present_set_fn /**< pte_present_set() */
	#define __pte_user_set_fn    /**< pte_user_set()    */
	#define __pte_write_set_fn   /**< pte_write_set()   */
	/**@}*/

	/**
	 * @brief Page Frame number.
	 */
	typedef uint32_t frame_t;

	/**
	 * @brief Page directory entry.
	 */
	struct pde
	{
		unsigned present  :  1; /**< Present in memory? */
		unsigned writable :  1; /**< Writable page?     */
		unsigned user     :  1; /**< User page?         */
		unsigned          :  2; /**< Reserved.          */
		unsigned accessed :  1; /**< Accessed?          */
		unsigned          :  1; /**< Unused             */
		unsigned          :  2; /**< Reserved.          */
		unsigned          :  3; /**< Unused.            */
		unsigned frame    : 20; /**< Frame number.      */
	};

	/**
	 * @brief Page table entry.
	 */
	struct pte
	{
		unsigned present  :  1; /**< Present in memory? */
		unsigned writable :  1; /**< Writable page?     */
		unsigned user     :  1; /**< User page?         */
		unsigned          :  2; /**< Reserved.          */
		unsigned accessed :  1; /**< Accessed?          */
		unsigned          :  1; /**< Unused             */
		unsigned          :  2; /**< Reserved.          */
		unsigned          :  3; /**< Unused.            */
		unsigned frame    : 20; /**< Frame number.      */
	};

	/**
	 * @brief Clears a page directory entry.
	 *
	 * @param pde Target page directory entry.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_clear(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		kmemset(pde, 0, PTE_SIZE);

		return (0);
	}

	/**
	 * @brief Sets the frame of a page table.
	 *
	 * @param pde Page directory entry of target page table.
	 * @param frame Frame number.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_frame_set(struct pde *pde, frame_t frame)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		/* Invalid frame. */
		if (frame > ~(frame_t)((1 << (VADDR_BIT - PAGE_SHIFT)) - 1))
			return (-EINVAL);

		pde->frame = frame;

		return (0);
	}

	/**
	 * @brief Sets/clears the present bit of a page table.
	 *
	 * @param pde Page directory entry of target page table.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_present_set(struct pde *pde, int set)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		pde->present = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the present bit of a page table is set.
	 *
	 * @param pde Page directory entry of target page table.
	 *
	 * @returns If the present bit of the target page table is set,
	 * non zero is returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_is_present(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		return (pde->present);
	}

	/**
	 * @brief Gets the frame number of a page directory entry.
	 *
	 * @param pde Target page directory entry.
	 *
	 * @returns The frame number of the target page directory entry.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline frame_t pde_frame_get(struct pde *pde)
	{
		return (pde->frame);
	}

	/**
	 * @brief Sets/clears the write bit of a page table.
	 *
	 * @param pde Page directory entry of target page table.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int  pde_write_set(struct pde *pde, int set)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		pde->writable = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the write bit of a page table is set.
	 *
	 * @param pde Page directory entry of target page table.
	 *
	 * @returns If the write bit of the target page table is set, non
	 * zero is returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_is_write(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		return (pde->writable);
	}

	/**
	 * @brief Sets/clears the user bit of a page table.
	 *
	 * @param pde Page directory entry of target page table.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_user_set(struct pde *pde, int set)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		pde->user = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the user bit of a page table is set.
	 *
	 * @param pde Page directory entry of target page table.
	 *
	 * @returns If the user bit of the target page table is set, non
	 * zero is returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pde_is_user(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		return (pde->user);
	}

	/**
	 * @brief Clears a page table entry.
	 *
	 * @param pte Target page table entry.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_clear(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		kmemset(pte, 0, PTE_SIZE);

		return (0);
	}

	/**
	 * @brief Sets/clears the present bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_present_set(struct pte *pte, int set)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		pte->present = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the present bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 *
	 * @returns If the present bit of the target page, non zero is
	 * returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_is_present(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->present);
	}

	/**
	 * @brief Sets the frame of a page.
	 *
	 * @param pte   Page table entry of target page.
	 * @param frame Frame number.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_frame_set(struct pte *pte, frame_t frame)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		/* Invalid frame. */
		if (frame > ~(frame_t)((1 << (VADDR_BIT - PAGE_SHIFT)) - 1))
			return (-EINVAL);

		pte->frame = frame;

		return (0);
	}

	/**
	 * @brief Gets the frame linked to page.
	 *
	 * @param pte   Page table entry of target page.
	 *
	 * @returns Number of the frame that is linked to the target page.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline frame_t pte_frame_get(struct pte *pte)
	{
		return (pte->frame);
	}

	/**
	 * @brief Sets/clears the write bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_write_set(struct pte *pte, int set)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		pte->writable = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the write bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 *
	 * @returns If the write bit of the target page, non zero is
	 * returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_is_write(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->writable);
	}

	/**
	 * @brief Sets/clears the user bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 * @param set Set bit?
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_user_set(struct pte *pte, int set)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		pte->user = (set) ? 1 : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the user bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 *
	 * @returns If the user bit of the target page, non zero is
	 * returned. Otherwise, zero is returned instead.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline int pte_is_user(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->user);
	}

	/**
	 * @brief Gets the page table index of a page.
	 *
	 * @param vaddr Target virtual address.
	 *
	 * @returns Returns the page table index of the page that lies at
	 * address @p vaddr.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline unsigned pte_idx_get(vaddr_t vaddr)
	{
		return (((unsigned)(vaddr) & (K1B_PGTAB_MASK^K1B_PAGE_MASK)) >> K1B_PAGE_SHIFT);
	}

	/**
	 * @brief Gets the page directory index of a page.
	 *
	 * @param vaddr Target virtual address.
	 *
	 * @returns Returns the page directory index of the page that lies
	 * at address @p vaddr.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline unsigned pde_idx_get(vaddr_t vaddr)
	{
		return ((unsigned)(vaddr) >> K1B_PGTAB_SHIFT);
	}

	/**
	 * @brief Gets a page directory entry.
	 *
	 * @param pgdir Target page directory.
	 * @param vaddr  Target virtual address.
	 *
	 * @returns The requested page directory entry.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline struct pde *pde_get(struct pde *pgdir, vaddr_t vaddr)
	{
		/* Invalid page directory. */
		if (pgdir == NULL)
			return (NULL);

		return (&pgdir[pde_idx_get(vaddr)]);
	}

	/**
	 * @brief Gets a page table entry.
	 *
	 * @param pgtab Target page table.
	 * @param vaddr Target virtual address.
	 *
	 * @returns The requested page table entry.
	 *
	 * @author Pedro Henrique Penna
	 */
	static inline struct pte *pte_get(struct pte *pgtab, vaddr_t vaddr)
	{
		/* Invalid page table. */
		if (pgtab == NULL)
			return (NULL);

		return (&pgtab[pte_idx_get(vaddr)]);
	}

/**@endcond**/

#endif /* ARCH_CORE_K1B_MMU_H_ */

