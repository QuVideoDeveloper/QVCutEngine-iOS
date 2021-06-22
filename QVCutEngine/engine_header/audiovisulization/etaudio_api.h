﻿#ifndef _ETAUDIO_API_H_
#define	_ETAUDIO_API_H_

#include "amcomdef.h"
#include "etaudioanalysiscomdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ETAUDIO_LIB_EXPORTS
	#define ETAUDIO_DLL_API	__declspec(dllexport)
#else
	#ifdef ETAUDIO_LIB_EXPORTS
		#define ETAUDIO_DLL_API	__declspec(dllimport)
	#else
		#define ETAUDIO_DLL_API 
	#endif
#endif

ETAUDIO_DLL_API MRESULT AA_Init(AA_INIT_PARAM * pInitParam,MHandle * pAAHandle,MTChar * szTemplateFilePath,FunAudioAnalysisCB pFunCB, MVoid * pUserData);

//看一下target的类型，可能有多个，返回的内部的内存，请勿修改
ETAUDIO_DLL_API MRESULT AA_PeekTargetTypeArray(MHandle hIns,AnaTargetType ** ppArrayType,MDWord & dwCount);


ETAUDIO_DLL_API MVoid AA_Uninit(MHandle hIns);


//Result 获取的是内部的数据，调用后会锁住(防止冲突)，无论是否获取到了值都需要解锁
ETAUDIO_DLL_API MRESULT AA_GetAnalysisResult(MHandle hIns,MDWord dwTimeStamp, MDWord dwTargetIdx, AA_RESULT ** ppAAResult);


ETAUDIO_DLL_API MVoid AA_UnLockResult(MHandle hIns,MDWord dwTargetIdx);

//目前即使是多Target,步长也必须一致的
ETAUDIO_DLL_API MInt32 AA_GetTimeWindowWidth(MHandle hIns);


/*
 * 从json文件得到Onset点信息
 * @param pszResFile,json文件路径
 * @param pAudioRange,audio 文件时间范围
 * @param pdwCount，Onset点数量
 * @param ppOnsetRes,Onset点时间位置
 * @return 成功返回QVET_ERR_NONE,否则返回错误码
 */
ETAUDIO_DLL_API MRESULT AA_GetOnsetDetectResult(MTChar* pszResFile,AMVE_POSITION_RANGE_TYPE* pAudioRange,MDWord* pdwCount,MFloat** ppOnsetRes); 

/*
 * 从json文件得到tempo点信息
 * @param pszResFile,json文件路径
 * @param pAudioRange,audio 文件时间范围
 * @param pdwCount，tempo点数量
 * @param ppOnsetRes,tempo点时间位置
 * @return 成功返回QVET_ERR_NONE,否则返回错误码
 */
ETAUDIO_DLL_API MRESULT AA_GetTempoDetectResult(MTChar* pszResFile,AMVE_POSITION_RANGE_TYPE* pAudioRange,MDWord* pdwCount,MFloat** ppTempoRes); 

#ifdef __cplusplus
}
#endif

#endif