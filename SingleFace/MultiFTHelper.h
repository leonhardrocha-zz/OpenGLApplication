//------------------------------------------------------------------------------
// <copyright file="FTHelper.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once
#pragma warning(disable:4786)
#include <FaceTrackLib.h>
#include "KinectSensor.h"
#include <vector>
#include <queue>
#include <map>

typedef void (*FTHelperCallBack)(PVOID lpParam);

class SensorAlignmentComparison
{
  bool isDecreasing;
public:
  SensorAlignmentComparison(const bool& revparam=false)
    {isDecreasing=revparam;}
  bool operator() (const KinectSensor* lhs, const KinectSensor* rhs) const
  {
    if (isDecreasing) return (lhs->m_smallestDistance > rhs->m_smallestDistance);
    else return (lhs->m_smallestDistance < rhs->m_smallestDistance);
  }
};

class MultiFTHelper;

typedef std::pair<KinectSensor*,MultiFTHelper*> TrackerPair;
typedef std::map<KinectSensor*,MultiFTHelper*, SensorAlignmentComparison> TrackerMap;




class MultiFTHelper
{
	
public:
	MultiFTHelper();
	MultiFTHelper(MultiFTHelper* parent);
    ~MultiFTHelper();
	HRESULT Init(HWND hWnd, NUI_IMAGE_TYPE depthType, NUI_IMAGE_RESOLUTION depthRes, BOOL bNearMode, BOOL bFallbackToDefault, NUI_IMAGE_TYPE colorType, NUI_IMAGE_RESOLUTION colorRes, BOOL bSeatedSkeletonMode,FTHelperCallBack callBack, PVOID callBackParam);
	HRESULT Stop();
	HRESULT GetTrackerResult();
	int StartFaceTracker();
	void SwapKinectSensor();
	void CheckCameraInput();
	IFTResult* GetResult()      { return(m_pFTResult);}
    BOOL IsKinectPresent()      { return(m_KinectSensorPresent);}
    IFTImage* GetColorImage()   { return(m_colorImage);}
    float GetXCenterFace()      { return(m_XCenterFace);}
    float GetYCenterFace()      { return(m_YCenterFace);}
    void SetDrawMask(BOOL drawMask) { m_DrawMask = drawMask;}
    BOOL GetDrawMask()          { return(m_DrawMask);}
    IFTFaceTracker* GetTracker() { return(m_pFaceTracker);}
    HRESULT GetCameraConfig(FT_CAMERA_CONFIG* cameraConfig);
	TrackerPair GetBestTracker();

	FTHelperCallBack     m_CallBack;
    LPVOID               m_CallBackParam;
	HANDLE               m_hFaceTrackingThread;

	protected:

	KinectSensor*               m_pKinectSensor;
	MultiFTHelper*				master;
	IFTFaceTracker*             m_pFaceTracker;
    IFTResult*                  m_pFTResult;
    IFTImage*                   m_colorImage;
    IFTImage*                   m_depthImage;
    FT_VECTOR3D                 m_hint3D[2]; 

	bool						m_KinectSensorPresent;
    float                       m_XCenterFace;
    float                       m_YCenterFace;

	TrackerMap validSensors;

	HWND                 m_hWnd;
	bool                 m_LastTrackSucceeded;
	bool                 m_ApplicationIsRunning;

    BOOL                 m_DrawMask;
    NUI_IMAGE_TYPE       m_depthType;
    NUI_IMAGE_RESOLUTION m_depthRes;
    BOOL                 m_bNearMode;
    BOOL                 m_bFallbackToDefault;
    BOOL                 m_bSeatedSkeletonMode;
    NUI_IMAGE_TYPE       m_colorType;
    NUI_IMAGE_RESOLUTION m_colorRes;

    BOOL SubmitFraceTrackingResult(IFTResult* pResult);
    void SetCenterOfImage(IFTResult* pResult);
    DWORD WINAPI FaceTrackingThread();

    static DWORD WINAPI FaceTrackingStaticThread(PVOID lpParam);
	
};

