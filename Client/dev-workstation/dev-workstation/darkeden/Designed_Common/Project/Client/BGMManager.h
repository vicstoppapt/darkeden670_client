#ifndef __BGMMANAGER_H__
#define	__BGMMANAGER_H__

#include <dsound.h>
#include "TSingleton.h"

class ACriticalSection;
class VorbisSound;

//----------------------------------------------------------------------
// BGMManager
//----------------------------------------------------------------------
class BGMManager : public TSingleton<BGMManager>
{
public:
	BGMManager();
	~BGMManager();

	bool	Init(LPDIRECTSOUND directSound);
	bool	Destory();

	bool	IsInit()	{ return m_bInit;	}

	bool	PlayMusic(LPCTSTR fileName);
	bool	StopMusic();

	void	SetVolume(int volume);
	int		GetVolume();

	// Thread Proc
	friend unsigned int WINAPI MusicUpdateThreadProc(void *arg);

private:
	ACriticalSection	*m_pMusicUpdateCS;
	VorbisSound			*m_pVorbisSound;

	HANDLE				m_hUpdateThread;
	int					m_nStreamUpdateCount;

	bool				m_bInit;
};


#endif


