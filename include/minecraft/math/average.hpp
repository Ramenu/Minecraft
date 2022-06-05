#ifndef MC_AVERAGE_HPP
#define MC_AVERAGE_HPP

#include <span>

#if 0
	/* Calculates the weighted average given an array of numbers and a weight. Note: Only one weight can be passed. */
	template<typename T> T getWeightedAverage(T weight, std::span<T> nums)
	requires (std::is_arithmetic_v<T>)
	{
		T sumOfWeight {weight * nums.size()}, sumWithWeight {};
		for (const auto&i: nums)
			sumWithWeight += nums[i] * weight; 
		return sumWithWeight / sumOfWeight;
	}
#endif

#endif // MC_AVERAGE_HPP
