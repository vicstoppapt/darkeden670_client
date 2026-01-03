//────────────────────────────────────────────────────────────────
//	2007 10 04							by zzi
//			Nowcom CDN과 International 버전의 구분을 위한 헤더추가.
//			> __USE_NOWCDN__ 을 정의할 경우, Nowcdn을 통한 패치버전
//			> _INTERNATIONAL_VERSION_ 을 정의할 경우, 모든 문자열이 영문으로 출력되며,
//				현재, 계정생성과 고객센터 버튼은 비활성 되어 있다. 이 부분은, 추후에 해당 URL이 오픈되어야 할 때 수정되어야 한다.
//				수정할 곳은.. ScreenObejct의 초기화시, bButtonEnable 멤버 초기화 부분을 수정하면 된다.
//────────────────────────────────────────────────────────────────
#ifndef _UPDATERVERSIONCONTROL_H_
#define _UPDATERVERSIONCONTROL_H_

//#define __USE_NOWCDN__
#define _INTERNATIONAL_VERSION_
#define __CHINESE__//by viva
//#define __ENGLISH__
#endif