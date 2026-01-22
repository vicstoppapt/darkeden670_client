//----------------------------------------------------------------------
// CDirectMusic.h
//----------------------------------------------------------------------

#ifndef __CDIRECTMUSIC_H__
#define __CDIRECTMUSIC_H__

#include <DMusicI.h>
#include <DMusicF.h>

typedef enum DIRECTMUSIC_TYPE	
{
	DIRECTMUSIC_TYPE_HW,	// hardware midi
	DIRECTMUSIC_TYPE_SW		// microsoft software synthesizer
};

class CDirectMusic {
	public :
		CDirectMusic();
		~CDirectMusic();

		//-----------------------------------------------------------
		// Init / Release
		//-----------------------------------------------------------
		bool		Init(HWND hWnd, DIRECTMUSIC_TYPE type=DIRECTMUSIC_TYPE_SW);
		void		Release();

	
		//-----------------------------------------------------------
		// Play / Stop		Pause / Resume
		//-----------------------------------------------------------
		bool		Play(const char* filename, WORD repeat=0xFFFF);
		void		Stop();
		void		Pause();
		void		Resume();

		//-----------------------------------------------------------
		// Tempo
		//-----------------------------------------------------------
		int			GetCurrentTempo() const		{ return m_CurrentTempo; }
		int			GetOriginalTempo() const	{ return m_OriginalTempo; }
		void		SetOriginalTempo()			{ SetCurrentTempo(m_OriginalTempo); }
		void		SetCurrentTempo(int t);

		//-----------------------------------------------------------
		// Volume
		//-----------------------------------------------------------
		//void		AddVolume(long hdec);
		//void		SubVolume(long hdec);

		//-----------------------------------------------------------
		// ����
		//-----------------------------------------------------------
		bool		IsInit() const		{ return m_bInit; }
		bool		IsLoad() const		{ return m_bInit && m_bLoad; }
		bool		IsPlay() const		{ return m_bInit && m_bPlay; }
		bool		IsPause() const		{ return m_bInit && m_bLoad && !m_bPlay; }

		// port type
		bool		IsSoftwareSynth() const	{ return m_bInit && m_bSoftwareSynth; }
	
	protected :
		//-----------------------------------------------------------
		// Protected Functions
		//-----------------------------------------------------------
		bool		CreatePerformance();
		bool		CreatePort(DIRECTMUSIC_TYPE type);
		bool		CreateLoader();


	protected :
		IDirectMusic*				m_pDM;
		IDirectMusicPerformance*	m_pDMPerformance;
		IDirectMusicPort*			m_pDMPort;
		IDirectMusicLoader*			m_pDMLoader;
		IDirectMusicSegment*		m_pDMSegment;
		IDirectMusicSegmentState*	m_pDMSegmentState;	

		MUSIC_TIME					m_mtStart;
		MUSIC_TIME                  m_mtOffset;
		REFERENCE_TIME              m_rtStart;
		REFERENCE_TIME              m_rtOffset;

		bool						m_bSoftwareSynth;

		bool						m_bInit;	// �ʱ�ȭ �Ǿ��°�?
		bool						m_bLoad;	// ȭ���� Load�Ǿ��°�?
		bool						m_bPlay;	// ���� ���ΰ�?
	
		int							m_OriginalTempo;	// original ����
		int							m_CurrentTempo;		// ���� ����
		//long						m_MasterVolume;
};


extern CDirectMusic		g_DXMusic;


#endif

