/*
 * MIT License
 *
 * Copyright(c) 2018 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
 *              2018 Davidson Francis     <davidsondfgl@gmail.com>
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

#ifndef CLUSTER_K1B_CPU_H_
#define CLUSTER_K1B_CPU_H_

	/* Cluster Interface Implementation */
	#include <arch/cluster/k1b/_k1b.h>

/**
 * @addtogroup k1b-cluster-cpu k1b Cluster CPU
 * @ingroup k1b-cluster
 */
/**@{*/

	/**
	 * @brief Number of cores in cluster.
	 */
	#ifdef __k1io__
		#define K1B_NUM_CORES 4
	#else
		#define K1B_NUM_CORES 16
	#endif

	/**
	 * @brief Gets the number of cores.
	 *
	 * The k1b_cpu_get_num_cores() gets the number of cores in the
	 * underlying k1b processor.
	 *
	 * @returns The the number of cores in the underlying processor.
	 */
	static inline int k1b_cpu_get_num_cores(void)
	{
		return (K1B_NUM_CORES);
	}

/**@}*/

/*============================================================================*
 * Provided Interface                                                         *
 *============================================================================*/

/**
 * @cond k1b
 */

	/**
	 * @name Provided Interface
	 */
	/**@{*/
	#define __hal_cpu_get_num_cores /**< hal_cpu_get_num_cores() */
	/**@}*/

	/**
	 * @brief Number of cores in a cluster.
	 */
	#define HAL_NUM_CORES K1B_NUM_CORES

	/**
	 * @see k1b_cpu_get_num_cores().
	 */
	static inline int hal_cpu_get_num_cores(void)
	{
		return (k1b_cpu_get_num_cores());
	}

/**@endcond*/

#endif /* CLUSTER_K1B_CPU_H_ */