//------------------------------------------------------------------------------
// <copyright file="FTHelper.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#pragma once
#include <FaceTrackLib.h>
#include "FTHelper.h"

typedef void (*FTHelperCallBack)(PVOID lpParam);

class DualFTHelper
{
public:
    DualFTHelper();
    ~DualFTHelper();
	HRESULT Init(HWND hWnd, FTHelperCallBack callBack, PVOID callBackParam, 
        NUI_IMAGE_TYPE depthType, NUI_IMAGE_RESOLUTION depthRes, BOOL bNearMode, BOOL bFallbackToDefault, NUI_IMAGE_TYPE colorType, NUI_IMAGE_RESOLUTION colorRes, BOOL bSeatedSkeletonMode);
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
	
	protected:
	KinectSensor                m_FirstKinectSensor;
	BOOL                        m_FirstKinectSensorPresent;
	KinectSensor                m_SecondKinectSensor;
	BOOL                        m_SecondKinectSensorPresent;

	KinectSensor*               m_pKinectSensor;
    BOOL                        m_KinectSensorPresent;

	
    IFTFaceTracker*             m_pFaceTracker;
    HWND                        m_hWnd;
    IFTResult*                  m_pFTResult;
    IFTImage*                   m_colorImage;
    IFTImage*                   m_depthImage;
    FT_VECTOR3D                 m_hint3D[2];
    bool                        m_LastTrackSucceeded;
    bool                        m_ApplicationIsRunning;
    FTHelperCallBack            m_CallBack;
    LPVOID                      m_CallBackParam;
    float                       m_XCenterFace;
    float                       m_YCenterFace;
    HANDLE                      m_hFaceTrackingThread;
    BOOL                        m_DrawMask;
    NUI_IMAGE_TYPE              m_depthType;
    NUI_IMAGE_RESOLUTION        m_depthRes;
    BOOL                        m_bNearMode;
    BOOL                        m_bFallbackToDefault;
    BOOL                        m_bSeatedSkeletonMode;
    NUI_IMAGE_TYPE              m_colorType;
    NUI_IMAGE_RESOLUTION        m_colorRes;

    BOOL SubmitFraceTrackingResult(IFTResult* pResult);
    void SetCenterOfImage(IFTResult* pResult);
    DWORD WINAPI FaceTrackingThread();
    static DWORD WINAPI FaceTrackingStaticThread(PVOID lpParam);
};
