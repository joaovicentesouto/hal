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

#include <arch/core/or1k/core.h>
#include <arch/core/or1k/tlb.h>
#include <arch/cluster/or1k/mmio.h>
#include <arch/cluster/or1k/memory.h>
#include <nanvix/const.h>
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
PUBLIC int or1k_mmio_write8(vaddr_t vaddr, uint8_t value)
{
	paddr_t paddr; /* Physical address. */

	/*
	 * Check if MMU is enabled and if so, use vaddr,
	 * otherwise, use paddr.
	 */
	if (or1k_mfspr(OR1K_SPR_SR) & (OR1K_SPR_SR_DME | OR1K_SPR_SR_IME))
	{
		/* Virtual address. */
		*((volatile uint8_t *) (vaddr)) = value;
	}

	/* Physical address. */
	else
	{
		paddr = or1k_pagewalk(vaddr) +
			(vaddr - (vaddr & OR1K_PAGE_MASK));
		
		*((volatile uint8_t *) (paddr)) = value;
	}

	return (0);
}

/**
 * @brief Writes an 8-bit string to a memory-mapped i/o device.
 *
 * @param vaddr Target virtual address.
 * @param str   8-bit string.
 *
 * @returns Upon successful completion, zero is returned. Upon
 * failure, a negative error code is returned instead.
 */
PUBLIC int or1k_mmio_write8s(vaddr_t vaddr, const uint8_t *str)
{
	paddr_t paddr; /* Physical address. */

	/*
	 * Check if MMU is enabled and if so, use vaddr,
	 * otherwise, use paddr.
	 */
	if (or1k_mfspr(OR1K_SPR_SR) & (OR1K_SPR_SR_DME | OR1K_SPR_SR_IME))
	{
		/* Virtual address. */
		for (int i = 0; str[i] != '\0'; i++)
			*((volatile uint8_t *) (vaddr + i)) = str[i];
	}
	
	/* Physical address. */
	else
	{
		paddr = or1k_pagewalk(vaddr) +
			(vaddr - (vaddr & OR1K_PAGE_MASK));

		/* Virtual address. */
		for (int i = 0; str[i] != '\0'; i++)
			*((volatile uint8_t *) (paddr + i)) = str[i];	
	}

	return (0);
}

/**
 * @brief Reads an 8-bit value from a memory-mapped i/o device.
 *
 * @param vaddr  Target virtual address.
 * @param valuep Target store location for 8-bit value.
 *
 * @returns Upon successful completion, zero is returned. Upon
 * failure, a negative error code is returned instead.
 */
PUBLIC int or1k_mmio_read8(vaddr_t vaddr, uint8_t *valuep)
{
	paddr_t paddr; /* Physical address. */

	/*
	 * Check if MMU is enabled and if so, use vaddr,
	 * otherwise, use paddr.
	 */
	if (or1k_mfspr(OR1K_SPR_SR) & (OR1K_SPR_SR_DME | OR1K_SPR_SR_IME))
	{
		/* Virtual address. */
		*valuep = *((volatile uint8_t *) (vaddr));
	}

	/* Physical address. */
	else
	{
		paddr = or1k_pagewalk(vaddr) +
			(vaddr - (vaddr & OR1K_PAGE_MASK));
		
		*valuep = *((volatile uint8_t *) (paddr));
	}

	return (0);
}

/**
 * @brief Reads an 8-bit string from a memory-mapped i/o device.
 *
 * @param vaddr Target virtual address.
 * @param strp  Target store location for 8-bit string.
 *
 * @returns Upon successful completion, zero is returned. Upon
 * failure, a negative error code is returned instead.
 */
PUBLIC int or1k_mmio_read8s(vaddr_t vaddr, uint8_t **strp)
{
	paddr_t paddr; /* Physical address. */
	uint8_t *str;  /* String pointer.   */
	uint8_t chr;   /* Current byte.     */
	int i;         /* Loop index.       */

	str = *strp;
	/*
	 * Check if MMU is enabled and if so, use vaddr,
	 * otherwise, use paddr.
	 */
	if (or1k_mfspr(OR1K_SPR_SR) & (OR1K_SPR_SR_DME | OR1K_SPR_SR_IME))
	{
		/* Virtual address. */
		while (TRUE)
		{
			chr = *((volatile uint8_t *) (vaddr + i));
			if (chr == '\0')
				break;

			*str = chr;
			str++;
			i++;
		}
	}
	
	/* Physical address. */
	else
	{
		paddr = or1k_pagewalk(vaddr) +
			(vaddr - (vaddr & OR1K_PAGE_MASK));

		/* Virtual address. */
		while (TRUE)
		{
			chr = *((volatile uint8_t *) (paddr + i));
			if (chr == '\0')
				break;

			*str = chr;
			str++;
			i++;
		}
	}

	return (0);
}
