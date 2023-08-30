#ifndef MATH_H
#define MATH_H

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

float AngleAsUnit(float angle, string unit)
{
    return (unit == "degrees" ? radians(angle) : angle);
}

float SafeDivide(float num, float den)
{
    return (den == 0.0) ? 0.0 : (num / den);
}

float RemapFloat(float inputF,
                 float inputMin, float inputMax,
                 float outputMin, float outputMax)
{
    float scale = SafeDivide((outputMax - outputMin), (inputMax - inputMin));
    return outputMin + (clamp(inputF, inputMin, inputMax) - inputMin) * scale;
}

#endif // MATH_H