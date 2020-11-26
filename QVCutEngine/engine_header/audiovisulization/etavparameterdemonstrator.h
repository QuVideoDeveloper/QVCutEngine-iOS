﻿#ifndef ET_AV_PARAMETER_DEMONSTRATOR_H
#define	ET_AV_PARAMETER_DEMONSTRATOR_H



#include "etaudioanalysiscomdef.h"
#include "etwin32gdiagent.h"
#include <vector>

typedef struct __tagAVPD_INIT_PARAMETER
{
	MDWord dwDuration;
	MTChar *pszAVAudioSrc;
	MFloat  fOnsetThreshHold;  //onset thresh hold 0.01~0.99
	MDWord  dwOnsetMode; //Onset mode,0~14
	MDWord dwOnsetGap; //Onset gap,ms
}AVPD_INIT_PARAMETER;

class CQVETAVParameterDemonstrator
{
public:
	CQVETAVParameterDemonstrator();
	virtual ~CQVETAVParameterDemonstrator();

public:
	MRESULT Init(AVPD_INIT_PARAMETER *pInitParam);
	MRESULT DrawParameter(MDWord dwTimeStamp, MBITMAP *pBmp/*in,out*/);

protected:
	MVoid	Uninit();

	MRESULT InitAudioAnalyzer();
	MRESULT InitGDI();

	MRESULT ConstructAASpectrumTarget(AA_PROCEDURE_TARGET *pTarget);
	MRESULT ConstructAAVolumeTarget(AA_PROCEDURE_TARGET *pTarget);	
	MRESULT ConstructAAOnsetTarget(AA_PROCEDURE_TARGET *pTarget);	
	MRESULT ConstructAATempoTarget(AA_PROCEDURE_TARGET *pTarget);

	MRESULT DrawParameter4Spectrum(MDWord dwTimeStamp, MBITMAP *pBmp/*in, out*/);
	MRESULT DrawParameter4Volume(MDWord dwTimeStamp, MBITMAP *pBmp/*in, out*/);
	MRESULT DrawParameter4Onset(MDWord dwTimeStamp, MBITMAP *pBmp/*in, out*/);	
	MRESULT DrawParameter4Tempo(MDWord dwTimeStamp,MBITMAP* pBmp/*in, out*/);



protected:
	MRESULT PreparePointList(MDWord dwCnt);
	MRESULT PrepareOTPList(MDWord dwCapacity);//如果就有list里有内容，重新准备后要copy一下
	MRESULT OrgnizeOTPData(MDWord dwCurTime);

	MRESULT PrepareTMPList(MDWord dwCapacity);
	MRESULT OrgnizeTMPData(MDWord dwCurTime);
	
	static MRESULT CreateGDIHandle(MBITMAP *pBmp/*in*/, MHandle* pHDC, MHandle* pHBITMAP);
	static MVoid DestoryGDIHandle(MHandle HDC, MHandle HBTIMAP, MHandle H);
	static inline MRESULT DrawLine(MHandle hDC, MPOINT startPt, MPOINT endPt);
	static inline MFloat  MapLenth(MFloat fValue, MFloat fMin, MFloat fMax, MFloat mapMaxLength);
	
private:
	AA_INIT_PARAM 	m_AAInitParam;
	MV2AUDIOINFO	m_AudioInfo;
	MHandle m_hAA;
	MDWord  m_dwAudioLength;
	MTChar	m_szAVAudioSrc[AMVE_MAXPATH];
	AA_RESULT *m_pAAResList;
	QWin32GDIAgent *m_pGDIAgent;
	MVoid	*m_PtList;/*win32 POINT struct*/
	MDWord	m_dwPtCnt;

	//Onset有关的数据列表
	MLong	*m_pOTPList; //Onset Time Post
	MDWord	m_dwOTPListCapacity; //Onset Time Post
	MDWord  m_dwOTPDataCnt; 

    //Tempo有关的数据列表
    MLong   *m_pTMPList; //Tempo Time Post
    MDWord m_dwTMPListCapacity; //Tempo Time POst
    MDWord m_dwTMPDataCnt;
	
	std::vector<MDWord> m_OnsetPosVec;
	MFloat m_fOnsetThreshHold;
	MDWord m_dwOnsetMode;
	MDWord m_dwOnsetGap;

};

#endif
