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

#ifndef CORE_I486_H_
#define CORE_I486_H_

	/**
	 * @addtogroup i486-core i486 Core
	 * @ingroup cores
	 */

	#ifndef __NEED_CORE_I486
		#error "i486 core not required"
	#endif

	#include <arch/core/i486/8253.h>
	#include <arch/core/i486/8259.h>
	#include <arch/core/i486/cache.h>
	#include <arch/core/i486/core.h>
	#include <arch/core/i486/excp.h>
	#include <arch/core/i486/int.h>
	#include <arch/core/i486/mmu.h>
	#include <arch/core/i486/pmio.h>
	#include <arch/core/i486/spinlock.h>
	#include <arch/core/i486/tlb.h>
	#include <arch/core/i486/trap.h>
	#include <arch/core/i486/upcall.h>

/**
 * @cond i486
 */

	/* Feature Declaration */
	#define CORE_SUPPORTS_PMIO 1

/**@}*/

#endif /* CORE_I486_H_ */

