#include "Client_PCH.h"
#include "BGMManager.h"
#include "ACriticalSection.h"
#include "VorbisSound.h"
#include <process.h>

#include <assert.h>

#ifdef Assert
#	undef assert
#	define assert Assert
#endif

// BGMManager Instance
namespace
{
	BGMManager s_BGMManager;
}


unsigned int WINAPI MusicUpdateThreadProc(void *arg)
{	
	BGMManager *pBGMManager = static_cast<BGMManager*>(arg);

	for(;;)
	{
		//50ms씩 슬리프
		Sleep(50);
		
		// Thread를 끝낸다.
		if(!pBGMManager->IsInit())
		{
			break;	
		}

		synchronized(*pBGMManager->m_pMusicUpdateCS)
		{
			VorbisSound* pVorbisSound = pBGMManager->m_pVorbisSound;

			if(pVorbisSound)
			{
				//스트림이 초당 5번 업데이트되도록 정적 카운터를 사용한다.
				//더 사용하면 낭비가 된다.		
				if( ( pBGMManager->m_nStreamUpdateCount++ ) % 4 == 1 )
				{			
					pBGMManager->m_pVorbisSound->ServiceBuffer();
				}
			}
		}
	}	
	
	return 0;
}


BGMManager::BGMManager()
{
	m_pMusicUpdateCS		= NULL;
	m_pVorbisSound			= NULL;
	m_hUpdateThread			= NULL;

	m_nStreamUpdateCount	= 0;
	m_bInit					= false;
}


BGMManager::~BGMManager()
{
	Destory();
}


bool BGMManager::Init(LPDIRECTSOUND directSound)
{
	Destory();

	m_pMusicUpdateCS	= new ACriticalSection;
	m_pVorbisSound		= new VorbisSound;
	m_pVorbisSound->Init(directSound);

	DWORD	dwChildThreadID;

	m_hUpdateThread = (HANDLE)_beginthreadex(NULL,
											0,
											MusicUpdateThreadProc,
											this,
											0,
											(unsigned int *)&dwChildThreadID);

	SetThreadPriority(m_hUpdateThread, THREAD_PRIORITY_BELOW_NORMAL);

	m_nStreamUpdateCount = 0;
	m_bInit	= true;

	return true;
}


bool BGMManager::Destory()
{
	// 일단 배경음악 중지하고 시작하자
	if(m_pVorbisSound)
	{
		m_pVorbisSound->Stop();
	}

	//--------------------------------------------
	// thread 중지
	//--------------------------------------------
	m_bInit = false;

	if(m_hUpdateThread)
	{
		// Thread가 끝나기를 3초간 기다려준다.
		if(WaitForSingleObject(m_hUpdateThread, 3000) == WAIT_TIMEOUT)
		{
			// 3초나 기다렸는데 안끝나면 걍 죽인다. -_-;
			TerminateThread(m_hUpdateThread, 0);
		}

		CloseHandle(m_hUpdateThread);

		m_hUpdateThread = NULL;
	}

	SAFE_DELETE(m_pVorbisSound);
	SAFE_DELETE(m_pMusicUpdateCS);

	return true;
}


bool BGMManager::PlayMusic(LPCTSTR fileName)
{
	if(!m_pVorbisSound)
	{
		assert("BGMManager::PlayMusic() : vorbis sound not init" && FALSE);
		return false;
	}

	synchronized(*m_pMusicUpdateCS)
	{
		m_pVorbisSound->Stop();
		
		if(!m_pVorbisSound->Open(fileName))
		{
			return false;
		}
		
		if(!m_pVorbisSound->Play())
		{
			return false;
		}
	}

	return true;
}


bool BGMManager::StopMusic()
{
	if(!m_pVorbisSound)
	{
		assert("BGMManager::StopMusic() : vorbis sound not init" && FALSE);
		return false;
	}

	synchronized(*m_pMusicUpdateCS)
	{
		m_pVorbisSound->Stop();
	}

	return true;
}


void BGMManager::SetVolume(int volume)
{
	if(!m_pVorbisSound)
	{
		assert("BGMManager::SetVolume() : vorbis sound not init" && FALSE);
		return;
	}

	synchronized(*m_pMusicUpdateCS)
	{
		m_pVorbisSound->SetVolume(volume);
	}
}


int BGMManager::GetVolume()
{
	if(!m_pVorbisSound)
	{
		assert("BGMManager::GetVolume() : vorbis sound not init" && FALSE);
		return -1;
	}

	synchronized(*m_pMusicUpdateCS)
	{
		return m_pVorbisSound->GetVolume();
	}

	return -1;
}