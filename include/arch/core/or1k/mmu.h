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

#ifndef ARCH_CORE_OR1K_MMU_H_
#define ARCH_CORE_OR1K_MMU_H_

/**
 * @addtogroup or1k-core-mmu MMU
 * @ingroup or1k-core
 *
 * @brief Memory Management Unit
 */
/**@{*/

#ifndef _ASM_FILE_

	#define __NEED_MEMORY_TYPES
	#include <arch/core/or1k/types.h>

	#include <nanvix/klib.h>
	#include <errno.h>
	#include <stdint.h>

#endif /* _ASM_FILE_ */

	/**
	 * @name Page Shifts and Masks
	 */
	/**@{*/
	#define OR1K_PAGE_SHIFT  13                       /**< Page Shift        */
	#define OR1K_PGTAB_SHIFT 24                       /**< Page Table Shift  */
	#define OR1K_PAGE_MASK   (~(OR1K_PAGE_SIZE - 1))  /**< Page Mask         */
	#define OR1K_PGTAB_MASK  (~(OR1K_PGTAB_SIZE - 1)) /**< Page Table Mask   */
	#define OR1K_PPN_SHIFT   10                       /**< Page Number shift */
	/**@}*/

	/**
	 * @name Size of Pages and Page Tables
	 */
	/**@{*/
	#define OR1K_PAGE_SIZE  (1 << OR1K_PAGE_SHIFT)  /**< Page Size                 */
	#define OR1K_PGTAB_SIZE (1 << OR1K_PGTAB_SHIFT) /**< Page Table Size           */
	#define OR1K_PTE_SIZE   4                       /**< Page Table Entry Size     */
	#define OR1K_PDE_SIZE   4                       /**< Page Directory Entry Size */
	#define OR1K_PT_SIZE    4096                    /**< Page table size           */
	#define OR1K_PT_SHIFT   10                      /**< Page table shift          */
	/**@}*/

	/**
	 * Page table entry constants.
	 */
	#define OR1K_PT_CC  0x1         /* Cache Coherency.       */
	#define OR1K_PT_CI  0x2         /* Cache Inhibit.         */
	#define OR1K_PT_WBC 0x4         /* Write-Back Cache.      */
	#define OR1K_PT_WOM 0x8         /* Weakly-Ordered Memory. */
	#define OR1K_PT_A   0x10        /* Accesed.               */
	#define OR1K_PT_D   0x20        /* Dirty.                 */
	#define OR1K_PT_PPI 0x1C0       /* Page Protection Index. */
	#define OR1K_PT_L   0x200       /* Last.                  */
	#define OR1K_PT_PPN 0xFFFFFC00  /* Physical Page Number.  */

	/**
	 * Page table new fields.
	 */
	#define OR1K_PT_PRESENT OR1K_PT_CI  /* Present in memory. */

	/**
	 * Page Protection Index, offset.
	 */
	#define OR1K_PT_PPI_OFFSET   0x6   /* PPI offset. */

	/**
	 * Page Protection Index, data.
	 */
	#define OR1K_PT_PPI_USR_RD   0x40  /* Supervisor Read/Write, User: Read.       */
	#define OR1K_PT_PPI_USR_WR   0x80  /* Supervisor Read/Write, User: Write.      */
	#define OR1K_PT_PPI_USR_RDWR 0xC0  /* Supervisor Read/Write, User: Read/Write. */

	/**
	 * Page Protection Index, instruction.
	 */
	#define OR1K_PT_PPI_USR_EX   0x80  /* User Execute.       */
	#define OR1K_PT_PPI_SPV_EX   0x40  /* Supervisor Execute. */

#ifndef _ASM_FILE_

	/**
	 * @brief Initializes the MMU.
	 */
	EXTERN void or1k_mmu_setup(void);

	/**
	 * @brief Enables the MMU.
	 */
	EXTERN void or1k_enable_mmu(void);
	
	/**
	 * @brief Enables the MMU.
	 */
	EXTERN paddr_t or1k_pagewalk(vaddr_t vaddr);

#endif /* _ASM_FILE_ */

/**@}*/

/*============================================================================*
 * Exported Interface                                                         *
 *============================================================================*/

/**
 * @cond or1k
 */

	/**
	 * @name Exported Constants
	 */
	/**@{*/
	#define KPAGE_SIZE  OR1K_PAGE_SIZE   /**< @ref OR1K_PAGE_SIZE   */
	#define PAGE_SIZE   OR1K_PAGE_SIZE   /**< @ref OR1K_PAGE_SIZE   */
	#define PGTAB_SIZE  OR1K_PGTAB_SIZE  /**< @ref OR1K_PGTAB_BIT   */
	#define PTE_SIZE    OR1K_PTE_SIZE    /**< @ref OR1K_PTE_SIZE    */
	#define PDE_SIZE    OR1K_PDE_SIZE    /**< @ref OR1K_PDE_SIZE    */
	#define PAGE_SHIFT  OR1K_PAGE_SHIFT  /**< @ref OR1K_PAGE_SHIFT  */
	#define PGTAB_SHIFT OR1K_PGTAB_SHIFT /**< @ref OR1K_PGTAB_SHIFT */
	#define PAGE_MASK   OR1K_PAGE_MASK   /**< @ref OR1K_PAGE_MASK   */
	#define PGTAB_MASK  OR1K_PGTAB_MASK  /**< @ref OR1K_PGTAB_MASK  */
	#define PADDR_BIT   OR1K_PADDR_BIT   /**< @ref OR1K_PADDR_BIT   */
	#define VADDR_BIT   OR1K_VADDR_BIT   /**< @ref OR1K_VADDR_BIT   */
	#define PADDR_BYTE  OR1K_PADDR_BYTE  /**< @ref OR1K_PADDR_BYTE  */
	#define VADDR_BYTE  OR1K_VADDR_BYTE  /**< @ref OR1K_VADDR_BYTE  */
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

#ifndef _ASM_FILE_

	/**
	 * @brief Frame number.
	 */
	typedef uint32_t frame_t;

	/**
	 * @brief Page directory entry.
	 */
	struct pde
	{
		unsigned frame      : 22; /* Frame number.          */
		unsigned last       :  1; /* Last PTE.              */
		unsigned ppi        :  3; /* Page protection index. */
		unsigned dirty      :  1; /* Dirty?                 */
		unsigned accessed   :  1; /* Accessed?              */
		unsigned wom        :  1; /* Weakly-Ordered Memory. */
		unsigned wbc        :  1; /* Write-Back Cache.      */
		unsigned present    :  1; /* Present in memory.     */
		unsigned cc         :  1; /* Cache Coherency.       */
	};

	/**
	 * @brief Page table entry.
	 */
	struct pte
	{
		unsigned frame      : 22; /* Frame number.          */
		unsigned last       :  1; /* Last PTE.              */
		unsigned ppi        :  3; /* Page protection index. */
		unsigned dirty      :  1; /* Dirty?                 */
		unsigned accessed   :  1; /* Accessed?              */
		unsigned wom        :  1; /* Weakly-Ordered Memory. */
		unsigned wbc        :  1; /* Write-Back Cache.      */
		unsigned present    :  1; /* Present in memory.     */
		unsigned cc         :  1; /* Cache Coherency.       */
	};

	/**
	 * Kernel code and data addresses.
	 */
	EXTERN unsigned KSTART_CODE;
	EXTERN unsigned KSTART_DATA;

	/**
	 * @brief Clears a page directory entry.
	 *
	 * @param pde Target page directory entry.
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
	 */
	static inline int pde_write_set(struct pde *pde, int set)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		pde->ppi = (set) ? (OR1K_PT_PPI_USR_RDWR >> OR1K_PT_PPI_OFFSET)
			: (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET);

		return (0);
	}

	/**
	 * @brief Asserts if the write bit of a page table is set.
	 *
	 * @param pde Page directory entry of target page table.
	 *
	 * @returns If the write bit of the target page table is set, non
	 * zero is returned. Otherwise, zero is returned instead.
	 */
	static inline int pde_is_write(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		return (pde->ppi == (OR1K_PT_PPI_USR_RDWR >> OR1K_PT_PPI_OFFSET));
	}

	/**
	 * @brief Sets/clears the user bit of a page table.
	 *
	 * @param pde Page directory entry of target page table.
	 * @param set Set bit?
	 */
	static inline int pde_user_set(struct pde *pde, int set)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		pde->ppi = (set) ? (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET) : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the user bit of a page table is set.
	 *
	 * @param pde Page directory entry of target page table.
	 *
	 * @returns If the user bit of the target page table is set, non
	 * zero is returned. Otherwise, zero is returned instead.
	 */
	static inline int pde_is_user(struct pde *pde)
	{
		/* Invalid PDE. */
		if (pde == NULL)
			return (-EINVAL);

		return (pde->ppi & (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET));
	}

	/**
	 * @brief Clears a page table entry.
	 *
	 * @param pte Target page table entry.
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
	 */
	static inline int pte_is_present(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->present);

		return (0);
	}

	/**
	 * @brief Sets the frame of a page.
	 *
	 * @param pte   Page table entry of target page.
	 * @param frame Frame number.
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
	 */
	static inline int pte_write_set(struct pte *pte, int set)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		pte->ppi = (set) ? (OR1K_PT_PPI_USR_RDWR >> OR1K_PT_PPI_OFFSET)
			: (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET);

		return (0);
	}

	/**
	 * @brief Asserts if the write bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 *
	 * @returns If the write bit of the target page, non zero is
	 * returned. Otherwise, zero is returned instead.
	 */
	static inline int pte_is_write(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->ppi == (OR1K_PT_PPI_USR_RDWR >> OR1K_PT_PPI_OFFSET));
	}

	/**
	 * @brief Sets/clears the user bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 * @param set Set bit?
	 */
	static inline int pte_user_set(struct pte *pte, int set)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		pte->ppi = (set) ? (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET) : 0;

		return (0);
	}

	/**
	 * @brief Asserts if the user bit of a page.
	 *
	 * @param pte Page table entry of target page.
	 *
	 * @returns If the user bit of the target page, non zero is
	 * returned. Otherwise, zero is returned instead.
	 */
	static inline int pte_is_user(struct pte *pte)
	{
		/* Invalid PTE. */
		if (pte == NULL)
			return (-EINVAL);

		return (pte->ppi & (OR1K_PT_PPI_USR_RD >> OR1K_PT_PPI_OFFSET));
	}

	/**
	 * @brief Gets the page table index of a page.
	 *
	 * @param vaddr Target virtual address.
	 *
	 * @returns Returns the page table index of the page that lies at
	 * address @p vaddr.
	 */
	static inline unsigned pte_idx_get(vaddr_t vaddr)
	{
		return (((unsigned)(vaddr) & (OR1K_PGTAB_MASK^OR1K_PAGE_MASK)) >> OR1K_PAGE_SHIFT);
	}

	/**
	 * @brief Gets the page directory index of a page.
	 *
	 * @param vaddr Target virtual address.
	 *
	 * @returns Returns the page directory index of the page that lies
	 * at address @p vaddr.
	 */
	static inline unsigned pde_idx_get(vaddr_t vaddr)
	{
		return ((unsigned)(vaddr) >> OR1K_PGTAB_SHIFT);
	}

	/**
	 * @brief Gets a page directory entry.
	 *
	 * @param pgdir Target page directory.
	 * @param vaddr  Target virtual address.
	 *
	 * @returns The requested page directory entry.
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
	 */
	static inline struct pte *pte_get(struct pte *pgtab, vaddr_t vaddr)
	{
		/* Invalid page table. */
		if (pgtab == NULL)
			return (NULL);

		return (&pgtab[pte_idx_get(vaddr)]);
	}

#endif /* _ASM_FILE_ */

/**@endcond*/

#endif /* ARCH_CORE_OR1K_MMU_H_ */
