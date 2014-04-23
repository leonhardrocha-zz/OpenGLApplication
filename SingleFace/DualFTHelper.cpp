//------------------------------------------------------------------------------
// <copyright file="DualFTHelper.cpp" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

#include "StdAfx.h"
#include "DualFTHelper.h"
#include "Visualize.h"

#ifdef SAMPLE_OPTIONS
#include "DualOptions.h"
#else
PVOID _dualopt = NULL;
#endif

DualFTHelper::DualFTHelper()
{
    m_pFaceTracker = 0;
    m_hWnd = NULL;
    m_pFTResult = NULL;
    m_colorImage = NULL;
    m_depthImage = NULL;
    m_ApplicationIsRunning = false;
    m_LastTrackSucceeded = false;
    m_CallBack = NULL;
    m_XCenterFace = 0;
    m_YCenterFace = 0;
    m_hFaceTrackingThread = NULL;
    m_DrawMask = TRUE;
    m_depthType = NUI_IMAGE_TYPE_DEPTH;
    m_depthRes = NUI_IMAGE_RESOLUTION_INVALID;
    m_bNearMode = TRUE;
    m_bFallbackToDefault = FALSE;
    m_colorType = NUI_IMAGE_TYPE_COLOR;
    m_colorRes = NUI_IMAGE_RESOLUTION_INVALID;
	m_bSeatedSkeletonMode = true;
}

DualFTHelper::~DualFTHelper()
{
    Stop();
}

BOOL DualFTHelper::SubmitFraceTrackingResult(IFTResult* pResult)
{
    if (pResult != NULL && SUCCEEDED(pResult->GetStatus()))
    {
        if (m_CallBack)
        {
            (*m_CallBack)(m_CallBackParam);
        }

        if (m_DrawMask)
        {
            FLOAT* pSU = NULL;
            UINT numSU;
            BOOL suConverged;
            m_pFaceTracker->GetShapeUnits(NULL, &pSU, &numSU, &suConverged);
            POINT viewOffset = {0, 0};
            FT_CAMERA_CONFIG cameraConfig;

            if (m_KinectSensorPresent)
            {
                m_pKinectSensor->GetVideoConfiguration(&cameraConfig);
            }
            else
            {
                cameraConfig.Width = 640;
                cameraConfig.Height = 480;
                cameraConfig.FocalLength = 500.0f;
            }
            IFTModel* ftModel;
            HRESULT hr = m_pFaceTracker->GetFaceModel(&ftModel);
            if (SUCCEEDED(hr))
            {
                hr = VisualizeFaceModel(m_colorImage, ftModel, &cameraConfig, pSU, 1.0, viewOffset, pResult, 0x00FFFF00);
                ftModel->Release();
            }
        }
    }
    return TRUE;
}

// We compute here the nominal "center of attention" that is used when zooming the presented image.
void DualFTHelper::SetCenterOfImage(IFTResult* pResult)
{
    float centerX = ((float)m_colorImage->GetWidth())/2.0f;
    float centerY = ((float)m_colorImage->GetHeight())/2.0f;
    if (pResult)
    {
        if (SUCCEEDED(pResult->GetStatus()))
        {
            RECT faceRect;
            pResult->GetFaceRect(&faceRect);
            centerX = (faceRect.left+faceRect.right)/2.0f;
            centerY = (faceRect.top+faceRect.bottom)/2.0f;
        }
        m_XCenterFace += 0.02f*(centerX-m_XCenterFace);
        m_YCenterFace += 0.02f*(centerY-m_YCenterFace);
    }
    else
    {
        m_XCenterFace = centerX;
        m_YCenterFace = centerY;
    }
}

// Get a video image and process it.


DWORD WINAPI DualFTHelper::FaceTrackingStaticThread(PVOID lpParam)
{
    DualFTHelper* context = static_cast<DualFTHelper*>(lpParam);
    if (context)
    {
        return context->FaceTrackingThread();
    }
    return 0;
}



HRESULT DualFTHelper::GetCameraConfig(FT_CAMERA_CONFIG* cameraConfig)
{
	return m_KinectSensorPresent ? m_pKinectSensor->GetVideoConfiguration(cameraConfig) : E_FAIL;
}

HRESULT DualFTHelper::Init(HWND hWnd, FTHelperCallBack callBack, PVOID callBackParam, 
                       NUI_IMAGE_TYPE depthType, NUI_IMAGE_RESOLUTION depthRes, BOOL bNearMode, BOOL bFallbackToDefault, NUI_IMAGE_TYPE colorType, NUI_IMAGE_RESOLUTION colorRes, BOOL bSeatedSkeletonMode)
{
    if (!hWnd || !callBack)
    {
        return E_INVALIDARG;
    }
    m_hWnd = hWnd;
    m_CallBack = callBack;
    m_CallBackParam = callBackParam;
    m_ApplicationIsRunning = true;
    m_depthType = depthType;
    m_depthRes = depthRes;
    m_bNearMode = bNearMode;
    m_bFallbackToDefault = bFallbackToDefault;
    m_bSeatedSkeletonMode = bSeatedSkeletonMode;
    m_colorType = colorType;
    m_colorRes = colorRes;
    m_hFaceTrackingThread = CreateThread(NULL, 0, FaceTrackingStaticThread, (PVOID)this, 0, 0);
    return S_OK;
}


HRESULT DualFTHelper::Stop()
{
    m_ApplicationIsRunning = false;
    if (m_hFaceTrackingThread)
    {
        WaitForSingleObject(m_hFaceTrackingThread, 1000);
    }
    m_hFaceTrackingThread = 0;
    return S_OK;
}

int DualFTHelper::StartFaceTracker()
{
	FT_CAMERA_CONFIG videoConfig;
    FT_CAMERA_CONFIG depthConfig;
    FT_CAMERA_CONFIG* pDepthConfig = NULL;

	if (m_KinectSensorPresent)
    {        
        m_pKinectSensor->GetVideoConfiguration(&videoConfig);
        m_pKinectSensor->GetDepthConfiguration(&depthConfig);
        pDepthConfig = &depthConfig;
        m_hint3D[0] = m_hint3D[1] = FT_VECTOR3D(0, 0, 0);
    }
    else
    {
		WCHAR errorText[MAX_PATH];
		ZeroMemory(errorText, sizeof(WCHAR) * MAX_PATH);
		wsprintf(errorText, L"Could not initialize the %s Kinect sensor; \n", m_pKinectSensor == &m_FirstKinectSensor ? "first" : "second");
		MessageBoxW(m_hWnd, errorText, L"Face Tracker Initialization Error\n", MB_OK);
		return 1;
    }

	// Try to start the face tracker.
    m_pFaceTracker = FTCreateFaceTracker(_dualopt);
    if (!m_pFaceTracker)
    {
        MessageBoxW(m_hWnd, L"Could not create the face tracker.\n", L"Face Tracker Initialization Error\n", MB_OK);
        return 2;
    }

    HRESULT hr = m_pFaceTracker->Initialize(&videoConfig, pDepthConfig, NULL, NULL); 
    if (FAILED(hr))
    {
        WCHAR path[512], buffer[1024];
        GetCurrentDirectoryW(ARRAYSIZE(path), path);
        wsprintf(buffer, L"Could not initialize face tracker (%s). hr=0x%x", path, hr);

        MessageBoxW(m_hWnd, /*L"Could not initialize the face tracker.\n"*/ buffer, L"Face Tracker Initialization Error\n", MB_OK);

        return 3;
    }

    hr = m_pFaceTracker->CreateFTResult(&m_pFTResult);
    if (FAILED(hr) || !m_pFTResult)
    {
        MessageBoxW(m_hWnd, L"Could not initialize the face tracker result.\n", L"Face Tracker Initialization Error\n", MB_OK);
        return 4;
    }

    // Initialize the RGB image.
    m_colorImage = FTCreateImage();
    if (!m_colorImage || FAILED(hr = m_colorImage->Allocate(videoConfig.Width, videoConfig.Height, FTIMAGEFORMAT_UINT8_B8G8R8X8)))
    {
        return 5;
    }

    if (pDepthConfig)
    {
        m_depthImage = FTCreateImage();
        if (!m_depthImage || FAILED(hr = m_depthImage->Allocate(depthConfig.Width, depthConfig.Height, FTIMAGEFORMAT_UINT16_D13P3)))
        {
            return 6;
        }
    }

	return 0;
}


DWORD WINAPI DualFTHelper::FaceTrackingThread()
{
     // Try to get the Kinect camera to work
    
	
	HRESULT hr1 = m_FirstKinectSensor.Init(m_depthType, m_depthRes, m_bNearMode, m_bFallbackToDefault, m_colorType, m_colorRes, m_bSeatedSkeletonMode);
	m_FirstKinectSensorPresent = SUCCEEDED(hr1);

	HRESULT hr2 = m_SecondKinectSensor.Init(m_depthType, m_depthRes, m_bNearMode, m_bFallbackToDefault, m_colorType, m_colorRes, m_bSeatedSkeletonMode);
	m_SecondKinectSensorPresent = SUCCEEDED(hr2);

	m_pKinectSensor = m_FirstKinectSensorPresent ? &m_FirstKinectSensor : &m_SecondKinectSensor;
	m_KinectSensorPresent = m_FirstKinectSensorPresent || m_FirstKinectSensorPresent;
	
	
    int trackerInitResult = StartFaceTracker();
	if (trackerInitResult > 0)
	{
		return trackerInitResult;
	}

    SetCenterOfImage(NULL);
	m_LastTrackSucceeded = false;
    while (m_ApplicationIsRunning)
    {
        CheckCameraInput();
        InvalidateRect(m_hWnd, NULL, FALSE);
        UpdateWindow(m_hWnd);
		if (!m_LastTrackSucceeded)
		{
			SwapKinectSensor();
		}
        Sleep(16);	
    }

    m_pFaceTracker->Release();
    m_pFaceTracker = NULL;

    if(m_colorImage)
    {
        m_colorImage->Release();
        m_colorImage = NULL;
    }

    if(m_depthImage) 
    {
        m_depthImage->Release();
        m_depthImage = NULL;
    }

    if(m_pFTResult)
    {
        m_pFTResult->Release();
        m_pFTResult = NULL;
    }
    m_pKinectSensor->Release();
    return 0;
}

HRESULT DualFTHelper::GetTrackerResult()
{
	HRESULT hrFT = E_FAIL;
    if (m_KinectSensorPresent && m_pKinectSensor->GetVideoBuffer())
    {
        HRESULT hrCopy = m_pKinectSensor->GetVideoBuffer()->CopyTo(m_colorImage, NULL, 0, 0);
        if (SUCCEEDED(hrCopy) && m_pKinectSensor->GetDepthBuffer())
        {
            hrCopy = m_pKinectSensor->GetDepthBuffer()->CopyTo(m_depthImage, NULL, 0, 0);
        }
        // Do face tracking
        if (SUCCEEDED(hrCopy))
        {
            FT_SENSOR_DATA sensorData(m_colorImage, m_depthImage, m_pKinectSensor->GetZoomFactor(), m_pKinectSensor->GetViewOffSet());

            FT_VECTOR3D* hint = NULL;
            if (SUCCEEDED(m_pKinectSensor->GetClosestHint(m_hint3D)))
            {
                hint = m_hint3D;
            }
            if (m_LastTrackSucceeded)
            {
                hrFT = m_pFaceTracker->ContinueTracking(&sensorData, hint, m_pFTResult);
            }
            else
            {
                hrFT = m_pFaceTracker->StartTracking(&sensorData, NULL, hint, m_pFTResult);
            }

        }
    }

	return hrFT;
}

void DualFTHelper::SwapKinectSensor()
{
	if(m_pKinectSensor == &m_FirstKinectSensor && m_SecondKinectSensorPresent)
	{
		m_pKinectSensor = &m_SecondKinectSensor;
		return;
	}

	if(m_pKinectSensor == &m_SecondKinectSensor && m_FirstKinectSensorPresent)
	{
		m_pKinectSensor = &m_FirstKinectSensor;
		return;
	}
}

// Get a video image and process it.
void DualFTHelper::CheckCameraInput()
{
    HRESULT hrFT = GetTrackerResult();
    m_LastTrackSucceeded = SUCCEEDED(hrFT) && SUCCEEDED(m_pFTResult->GetStatus());
    if (m_LastTrackSucceeded)
    {
        SubmitFraceTrackingResult(m_pFTResult);
    }
    else
    {
        m_pFTResult->Reset();
    }
    SetCenterOfImage(m_pFTResult);
}