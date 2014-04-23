//------------------------------------------------------------------------------
// <copyright file="DualKinectSensor.h" company="Udesc">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include <FaceTrackLib.h>
#include <NuiApi.h>
#include "KinectSensor.h"

class DualKinectSensor
{
public:
    DualKinectSensor();
    ~DualKinectSensor();
private:
	KinectSensor leftKinectSensor;
	KinectSensor rightKinectSensor;
};
