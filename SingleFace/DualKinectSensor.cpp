//------------------------------------------------------------------------------

#include "StdAfx.h"
#include "DualKinectSensor.h"
#include <math.h>


DualKinectSensor::DualKinectSensor()
{
   
}

KinectSensor::~KinectSensor()
{
    Release();
}