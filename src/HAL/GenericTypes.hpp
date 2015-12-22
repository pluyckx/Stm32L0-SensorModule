/*
 * GenericTypes.hpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_GENERICTYPES_HPP_
#define SRC_HAL_GENERICTYPES_HPP_

namespace stm32
{

enum class Status
{
	Clear = 0u, Off = Clear, Disabled = Clear, NotReady = Clear, False = Clear,

	Set = 1u,
	On = Set, Enabled = Set, Requested = Set, Ready = Set, True = Set
};

}
;

#endif /* SRC_HAL_GENERICTYPES_HPP_ */
