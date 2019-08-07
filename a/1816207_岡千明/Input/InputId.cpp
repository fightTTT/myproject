#include <type_traits>
#include "InputId.h"

INPUT_ID begin(INPUT_ID)
{
	return INPUT_ID::LEFT;
}

INPUT_ID end(INPUT_ID)
{
	return INPUT_ID::MAX;
}

INPUT_ID operator++(INPUT_ID & key)
{
	// std::underlying_type<Z>::type(Z)	—ñ‹“Œ^‚ÌŒ^‚ğæ“¾‚µ·¬½Ä‚·‚é
	return key = INPUT_ID(std::underlying_type<INPUT_ID>::type(key) + 1);
}

INPUT_ID operator*(INPUT_ID & key)
{
	return key;
}