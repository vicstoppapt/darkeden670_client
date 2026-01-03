//-----------------------------------------------------------------------------
// DebugInfo.h
//-----------------------------------------------------------------------------
// CMessageArray를 통한..
// Debug정보를 표시해주는가?
//-----------------------------------------------------------------------------

#ifndef	__DEBUGINFO_H__
#define	__DEBUGINFO_H__

	#ifdef _DEBUG
//		#define	OUTPUT_DEBUG
	#else
//		#define	OUTPUT_DEBUG
	#endif

	#ifdef	OUTPUT_DEBUG
		
		//------------------------------------------
		// g_DebugMessage
		//------------------------------------------		
		#include "CMessageArray.h"

		extern CMessageArray*	g_pDebugMessage;
				

	//#endif


	//#ifdef	_DEBUG
		#include <Windows.h>
		#include <WinBase.h>
		#include <stdio.h> 
		#include <stdarg.h>

		extern char	g_StringBuffer[256];

		//------------------------------------------
		// debug message
		//------------------------------------------
		#define	DEBUG_MESSAGE(debugMessage)					\
			{												\
				va_list		vl;								\
				va_start(vl, debugMessage);					\
				vsprintf(g_StringBuffer, debugMessage, vl);	\
				va_end(vl);									\
				OutputDebugString(g_StringBuffer);			\
			}
		
//		void* PASCAL operator new( unsigned int cb, LPCSTR lpszFileName, int nLine);
//		void PASCAL operator delete(void *p, LPCSTR lpszFileName, int nLine);
		//void PASCAL operator delete [] (void *p, LPCSTR lpszFileName, int nLine);
		
// 		#define	DEBUG_NEW			new (__FILE__, __LINE__)

		
		#define	DEBUG_ADD( message )		\
				if (g_pDebugMessage!=NULL)	\
					g_pDebugMessage->Add( message );

		void	DEBUG_ADD_FORMAT(const char* format, ...);		
			
			
	// debug가 아닌 경우..
	#else
		#define	DEBUG_MESSAGE(debugMessage)	((void)0)
		
		#define	DEBUG_ADD( message )		((void)0)

		inline void	DEBUG_ADD_FORMAT(const char* format, ...) {}
			

//		#define	DEBUG_NEW			new			
	#endif	


#endif