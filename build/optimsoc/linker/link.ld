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

OUTPUT_FORMAT("elf32-or1k")
ENTRY(_do_start)

BOOT_ADDR = 0;

SECTIONS
{
	. = BOOT_ADDR;

	EXCEPTIONS = .;

	KSTART_CODE = .;

	/* Kernel code section. */
	.bootstrap : AT(ADDR(.bootstrap))
	{
		*hooks.o
		*boot_code.o
	}

	. = ALIGN(8192);

	/* Kernel code section. */
	.text : AT(ADDR(.text))
	{
		*(.text)
	}

	KSTART_DATA = ALIGN(8192);

	/* Initialized kernel data section. */
	.data ALIGN(8192) : AT(ADDR(.data))
	{
		*boot_data.o
		*(.rodata)
		*(.data)
	}

	/* Uninitialized kernel data section. */
	.bss : AT(ADDR(.bss))
	{
		*(.bss)
	}

	. =ALIGN(8192);

	KDATA_END = .;

	/* Discarded. */
	/DISCARD/ :
	{
		*(.comment)
		*(.note)
	}
}
