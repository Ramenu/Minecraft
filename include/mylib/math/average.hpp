#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <cstddef>

#if 0
	/* Calculates the weighted average given an array of numbers and a weight. Note: Only one weight can be passed. */
	template<typename T> inline T getWeightedAverage(T&& weight, T* nums)
	{
		size_t arrSize {sizeof(nums)/sizeof(nums[0])}; // Length of the array
		float sumOfWeight {weight * arrSize}, sumWithWeight {};
		for (size_t i {}; i < arrSize; i++)
			sumWithWeight += nums[i] * weight; 
		return sumWithWeight / sumOfWeight;
	}
#endif

#endif // AVERAGE_HPP
