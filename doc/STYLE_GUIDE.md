# apettit OSL Style Guide
This style guide is to lay out the specific style used by apettit while writing OSL shaders and their accompanying python & bat scripts. It largely follows widely accepted C style guides with a few paritculars in the use of macros and OSL metadata.

## General
- Lines of code are ```80``` characters long
- Case:
    - Variables will use camel case: ```newVar```
    - Constants will use snake case will all caps: ```NEW_VAR```
    - Methods will use pascal case: ```NewMethod```
- Block Statements:
    - Shader ```()``` and ```{}``` will always be on their own lines
    - Block statements using ```{}``` will use a new line for each ```{``` or ```}```
    - Block statments with a single line do not use ```{}```
    - Example:
    ```
    if (!useSplitInputs)
        resultRGBA.RGB = inputRGB;
    else 
    {
        resultRGBA.RGB[0] = inputR;
        resultRGBA.RGB[1] = inputG;
        resultRGBA.RGB[2] = inputB;
    }
    ```
- Headers:
    - Headers are placed alphabetically where you can
    - Global structs, methods, and macros are found in a header file found in ```src/lib```
    - Must include ```ShaderAPI.h``` for every shader
- Variables:
    - For clarity all output parameters will use the suffix ```result```
    - Generally most input parameters will use the suffix ```input```
    - Input/output parameters or operations that will be used across many shaders are packaged as macros. Though not traditionally the best way in  a C language, this supports OSL best

## Macros
- General:
    - All macros are organized in a header file found in ```src/lib```
    - Macros are to be kept at one line whenever possible. Else the macro definition is two begin on line two
    - ```Output``` variables will all be set to ```0.0``` or its equivalent
- Global Constants:
    - Though not normally encourgaed, all global constants will be defined in macros to better support OSL
    - ```_DB``` suffix is used to indicate default values for easy debugging
    - ```_ZERO``` suffix is used to indicate a struct or other data type with  ```0``` values
- Newlines:
    - ```\``` used to indicate newlines will be tabbed to the same location for better readability, unless the macro is only two lines. If so, then use a single space between any code and ```\```
- Parameters:
    - Macro parameters that are considered constant in the scope of the macro are to be CAPS
- Example:
```
#define FLOAT_DB 1.0
#define FLOAT_TAG_INPUTS(TAG) \
    FLOAT("", inputF_##TAG, FLOAT_DB, string label = "Float "#TAG)
#define FLOAT_OUTPUTS                 \
    OUT_FLOAT(resultF, 0.0),          \
    OUT_FLOAT(invertF, (1 - resultF))
```
- Wrappers:
    - Macros can serve as a wrapper to call functions that only uses variables defined in the scope of another macro
- Example:
```
void Color_Set_Outputs(colorAlpha resultRGBA, output color resultRGB,
                       output float resultR, output float resultG,
                       output float resultB, output float resultA)
{
    resultRGB = resultRGBA.RGB;
    resultR = resultRGBA.RGB[0];
    resultG = resultRGBA.RGB[1];
    resultB = resultRGBA.RGB[2];
    resultA = resultRGBA.A;
}

#define COLOR_ALPHA_OUTPUTS_SET              \
    Color_Set_Outputs(resultRGBA, resultRGB, \
                      resultR, resultG,      \
                      resultB, resultA)
```

## Metadata
- Always begin metadata definitions on a new line
- Organized alphabetically, except for additional widget sub-metadata
- If a single metadata variable is used include metadata on one line, else use a new line for each ```[[``` and ```]]```
- Example:
```
string alphaMixType = "A"
[[ 
    int connectable = 0, 
    string label = "Alpha Mix", 
    string widget = "popup",
    string options = "A|Mix|B"
]],
float mixValue = 0.5
[[ string label = "Mix Value" ]]
```

## Python & Bat
- Python and Bat files follow no special syntax at this time
