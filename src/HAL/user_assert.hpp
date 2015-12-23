/*
 * assert.hpp
 *
 *  Created on: Dec 22, 2015
 *      Author: pluyckx
 */

#ifndef SRC_HAL_USER_ASSERT_HPP_
#define SRC_HAL_USER_ASSERT_HPP_

void assert_handler();

inline void assert( bool test )
{
	if( !test )
	{
		assert_handler();
	}
}

#endif /* SRC_HAL_USER_ASSERT_HPP_ */
