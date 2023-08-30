#ifndef COLOR_H
#define COLOR_H

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

struct colorAlpha{
	color RGB;
	float A;
	int isPremultiplied;
};

////////////////////////////////////////////////////////////////////////////////
// Macro Default Macros
////////////////////////////////////////////////////////////////////////////////

#define R_DEF 1.0
#define G_DEF 0.0
#define B_DEF 1.0
#define ALPHA_DEF 1.0
#define COLOR_ZERO color(0.0)
#define COLOR_ONE color(1.0)
#define PREMULT_DEF 1
#define COLOR_DEF color(R_DEF, G_DEF, B_DEF)
#define COLORALPHA_DEF {COLOR_DEF, ALPHA_DEF, PREMULT_DEF}
#define COLORALPHA_ZERO {color(0.0), 0.0, 0}

////////////////////////////////////////////////////////////////////////////////
// Input Macros
////////////////////////////////////////////////////////////////////////////////

#define COLOR_SPLIT_INPUTS 								 							\
    color inputRGB = COLOR_DEF [[ string label = "Color" ]], 							\
    float inputA = ALPHA_DEF [[ string label = "A" ]], 		 							\
    int useSplitInputs = 0 									 							\
    [[ 														 							\
		string label = "Use Split Inputs", 					 							\
    	string widget = "checkbox" 							 							\
	]], 													 							\
    float inputR = R_DEF [[ string label = "R" ]], 			 							\
    float inputG = G_DEF [[ string label = "G" ]], 			 							\
    float inputB = B_DEF [[ string label = "B" ]], 			 							\
    int premultiplyOutput = 1 								 							\
    [[ 														 							\
		string label = "Premultiply Output", 				 							\
    	string help = "Normally this is on. All RGBA structs are assumed premultipled." \
	]]

////////////////////////////////////////////////////////////////////////////////
// Input Tag Macros
////////////////////////////////////////////////////////////////////////////////

#define COLOR_TAG_INPUTS(TAG)        \
	color inputRGB_##TAG = COLOR_DEF \
	[[ 								 \
		string page = "color "#TAG,  \
		string label = "Color "#TAG, \
	]], 							 \
	float inputA_##TAG = ALPHA_DEF   \
	[[ 								 \
		string page = "color "#TAG,  \
		string label = "Alpha "#TAG, \
	]]

// inputRGBA is defined as inputRGBA_##TAG##_ so that when COLOR_ALPHA_TAG_INPPUTS_GET(TAG) is 
// called it can serve as an intermediary variable and the result variable the user will reference 
// is inputRGBA_##TAG. Which is a bit clearer to read at the shader level
#define COLOR_ALPHA_TAG_INPUTS(TAG)                								\
	colorAlpha inputRGBA_##TAG##_ = COLORALPHA_DEF 								\
	[[ 											   								\
		string page = "color "#TAG, 			   								\
		string label = "Color Alpha "#TAG, 		   								\
	]], 										   								\
    COLOR_TAG_INPUTS(TAG), 						   								\
	int premultiplyInput_##TAG = 1 				   								\
	[[ 											   								\
		string page = "color "#TAG, 			   								\
		string label = "Premultiply Input "#TAG,   								\
		string help = "Whether layer inputRGB is premultiplied by layer inputA" \
	]]

#define COLOR_ALPHA_TAG_INPUTS_GET(TAG)                                  \
    colorAlpha inputRGBA_##TAG;                                          \
    if (isconnected(inputRGBA_##TAG##_))                                 \
        inputRGBA_##TAG = inputRGBA_##TAG##_;                            \
    else                                                                 \
    {                                                                    \
        inputRGBA_##TAG.RGB = inputRGB_##TAG;                            \
        inputRGBA_##TAG.A = inputA_##TAG;                                \
        inputRGBA_##TAG.isPremultiplied = 0;                             \
    }                                                                    \
    if (!inputRGBA_##TAG.isPremultiplied && premultiplyInput_##TAG)      \
        Premultiply(inputRGBA_##TAG);                                    \
    else if (inputRGBA_##TAG.isPremultiplied && !premultiplyInput_##TAG) \
        Unpremultiply(inputRGBA_##TAG)

////////////////////////////////////////////////////////////////////////////////
// Output Macros
////////////////////////////////////////////////////////////////////////////////

#define COLOR_OUTPUTS                 \
	output color resultRGB = COLOR_ZERO, \
	output float resultR = 0.0, \
	output float resultG = 0.0, \
	output float resultB = 0.0

#define COLOR_OUTPUTS_SET   \
    resultR = resultRGB[0]; \
    resultG = resultRGB[1]; \
    resultB = resultRGB[2]

#define COLOR_ALPHA_OUTPUTS                         \
	output colorAlpha resultRGBA = COLORALPHA_ZERO, \
	output color resultRGB = color(0.0), 			\
	output float resultR = 0.0, 					\
	output float resultG = 0.0, 					\
	output float resultB = 0.0, 					\
	output float resultA = 0.0

#define COLOR_ALPHA_OUTPUTS_SET    \
    resultRGB = resultRGBA.RGB;    \
    resultR = resultRGBA.RGB[0];   \
    resultG = resultRGBA.RGB[1];   \
    resultB = resultRGBA.RGB[2];   \
    resultA = resultRGBA.A

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

void Premultiply(output colorAlpha RGBA)
{
	if (!RGBA.isPremultiplied)
    {
        RGBA.RGB *= RGBA.A;
        RGBA.isPremultiplied = 1;
    }
}

void Unpremultiply(output colorAlpha RGBA)
{
    if (RGBA.isPremultiplied)
    {
        RGBA.RGB /= RGBA.A;
        RGBA.isPremultiplied = 0;
    }
}

#endif // COLOR_H