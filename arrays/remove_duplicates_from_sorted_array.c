int removeDuplicates(int* nums, int numsSize)
{
	int slow;
	int duplicates;
	int i;

	slow = 0;
	i = 0;
	while (i < numsSize)
	{
		duplicates = 1;
		while (i + duplicates < numsSize && nums[i] == nums[i + duplicates])
			duplicates++;
		nums[slow] = nums[i];
		slow++;
		i += duplicates;
	}
	return slow;
}