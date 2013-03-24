#include "BasicMath.h"

const float BasicMath::PI = acos( -1.0 );

float BasicMath::radians( float a )
{
  return a * PI / 180.f;
}

float BasicMath::threeMax( float one, float two, float three )
{
  if (one > two)
  {
    return (one > three) ? one : three;
  }
  else
  {
    return (two > three) ? two : three;
  }
}

float BasicMath::threeMin( float one, float two, float three )
{
  if ( one < two )
  {
    return (one < three) ? one : three;
  }
  else
  {
    return (two < three) ? two : three;
  }
}

