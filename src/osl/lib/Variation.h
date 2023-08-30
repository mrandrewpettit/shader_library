#ifndef VARIATION_H
#define VARIATION_H

#define VARIATION_INPUTS(tag) 					   \
	float varPattern##tag = 1.0 				   \
	[[ 											   \
		string page = (#tag " Variation"), 		   \
		string label = (#tag " Pattern"), 		   \
	]], 										   \
	float varMax##tag = 1.0 					   \
	[[ 											   \
		string page = (#tag " Variation"), 		   \
		string label = (#tag " Max"), 			   \
		string help = "Value when pattern is 1.0", \
		int connectable = 0 					   \
	]], 										   \
	float varMid##tag = 1.0 					   \
	[[ 											   \
		string page = (#tag " Variation"), 		   \
		string label = (#tag " Mid"), 			   \
		string help = "Value when pattern is 0.5", \
		int connectable = 0 					   \
	]], 										   \
	float varMin##tag = 1.0 					   \
	[[ 											   \
		string page = (#tag " Variation"), 		   \
		string label = (#tag " Min"), 			   \
		string help = "Value when pattern is 0.0", \
		int connectable = 0 					   \
	]]

float Variation(float value, float min, float mid, float max, float pattern)
{
    float coords[5] = {min, min, mid, max, max};
    return value * spline("linear", pattern, coords);
}

#define VARIATION_SET(value, tag) \
    Variation(value, varMin##tag, varMid##tag, varMax##tag, varPattern##tag)

#endif // VARIATION_H