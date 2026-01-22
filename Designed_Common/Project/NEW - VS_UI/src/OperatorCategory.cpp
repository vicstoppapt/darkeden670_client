#include "client_PCH.h"
#include "VS_UI_GameCommon.h"
#include "OperatorCategory.h"
#include "OperatorOption.h"
#include "VS_UI_widget.h"
#include "VS_UI.h"
#include "UIDialog.h"
#include "MGameStringTable.h"

#if __CONTENTS(__ITEM_SHOW)
#include "ClientFunction.h"
#include <sstream>
#endif //__ITEM_SHOW

int COperatorCategorySimpleCommand:: m_saveSelectIndexFirst = -1;
int COperatorCategorySimpleCommand:: m_saveSelectIndexSecond = -1;
int COperatorCategorySimpleCommand:: m_saveSelectIndexText = -1;

#if __CONTENTS(__ITEM_SHOW)
int COperatorCategoryShowItemSetting:: m_saveSelectIndexItemClass = -1;
int COperatorCategoryShowItemSetting:: m_saveSelectIndexItemType = -1;

using namespace std;
#endif //__ITEM_SHOW

//-----------------------------------------------------------------------------
// COperatorCategory
//
//-----------------------------------------------------------------------------
COperatorCategory::COperatorCategory(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: m_CategoryName(categoryName), m_pParentWindow(parentWindow), CRect(position)
{

}


//-----------------------------------------------------------------------------
// COperatorCategoryUtility
//
//-----------------------------------------------------------------------------
COperatorCategoryUtility::COperatorCategoryUtility(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: COperatorCategory(categoryName, parentWindow, position)
{
	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Init();

	CPoint ptButton(15, 15);
	
//	m_pC_button_group->Add(new C_VS_UI_EVENT_PUSH_BUTTON(CRect(CPoint(ptButton.x, ptButton.y), CSize(200, 30)),
//		EID_RELOAD_INFO_FILE, this, "Á¤º¸ÆÄÀÏ ¸ðµÎ ´Ù½Ã ÀÐ±â"));

//	ptButton.y += 40;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bSlideScreenShot,
		"½½¶óÀÌµå ½ºÅ©¸°¼¦ È°¼ºÈ­ (Shift+Drag: ¿µ¿ª¼±ÅÃ)"));

}


COperatorCategoryUtility::~COperatorCategoryUtility()
{

	DeleteNew(m_pC_button_group);
}


void COperatorCategoryUtility::Start()
{

}


void COperatorCategoryUtility::Finish()
{
	
}


void COperatorCategoryUtility::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	C_VS_UI_EVENT_STRING_BUTTON* pStringButton = dynamic_cast<C_VS_UI_EVENT_STRING_BUTTON*>(p_button);
	
	if(pStringButton)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pStringButton->Show(showOffset);
	}
}


void COperatorCategoryUtility::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}


void COperatorCategoryUtility::Run(id_t id)
{
//	switch(id)
//	{
// 	case EID_RELOAD_INFO_FILE:
// 		gpC_base->SendMessage(UI_RELOAD_INFO_FILE);
// 		break;
//	}
}


void COperatorCategoryUtility::Process()
{
	m_pC_button_group->Process();
}


void COperatorCategoryUtility::Show()
{
	m_pC_button_group->Show();
}


bool COperatorCategoryUtility::MouseControl(UINT message, int _x, int _y)
{
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}


//-----------------------------------------------------------------------------
// COperatorCategoryShowInfo
//
//-----------------------------------------------------------------------------
COperatorCategoryShowInfo::COperatorCategoryShowInfo(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: COperatorCategory(categoryName, parentWindow, position)
{
	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Init();

	CPoint ptButton(15, 15);
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowModifyHP, "ÉúÃüÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowModifyEXP, "¾­ÑéÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowCreatureInfo, "¹ÖÎïÐÅÏ¢ÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowImageObjectInfo, "µØÍ¼Í¼ÏñÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowAddEffect, "Ð§¹ûÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowSkillRange, "¼¼ÄÜ·¶Î§"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bShowModifyRANKEXP, "½×¼¶¾­ÑéÏÔÊ¾"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bRecordCharName, "½ÇÉ«Ãû×Ö¼ÇÂ¼"));

		ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bCanRootingGhost, "ÒþÉí"));

}


COperatorCategoryShowInfo::~COperatorCategoryShowInfo()
{
	DeleteNew(m_pC_button_group);
}


void COperatorCategoryShowInfo::Start()
{

}


void COperatorCategoryShowInfo::Finish()
{
	
}


void COperatorCategoryShowInfo::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	C_VS_UI_EVENT_STRING_BUTTON* pStringButton = dynamic_cast<C_VS_UI_EVENT_STRING_BUTTON*>(p_button);
	
	if(pStringButton)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pStringButton->Show(showOffset);
	}
}


void COperatorCategoryShowInfo::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}


void COperatorCategoryShowInfo::Run(id_t id)
{

}


void COperatorCategoryShowInfo::Process()
{
	m_pC_button_group->Process();
}


void COperatorCategoryShowInfo::Show()
{
	m_pC_button_group->Show();
}


bool COperatorCategoryShowInfo::MouseControl(UINT message, int _x, int _y)
{
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}



//-----------------------------------------------------------------------------
// COperatorCategoryGameSetting
//
//-----------------------------------------------------------------------------
COperatorCategoryGameSetting::COperatorCategoryGameSetting(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: COperatorCategory(categoryName, parentWindow, position)
{
	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Init();

	CPoint ptButton(15, 15);
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bHideAttachEffect, "Òþ²Ø¸½¼ÓÐ§¹û"));

	ptButton.y += 25;
	m_pC_button_group->Add(new C_VS_UI_EVENT_CHECK_BUTTON(ptButton,
		-1, this, &g_pOperatorOption->bHideSpeechBalloon, "Speech Balloon"));
}


COperatorCategoryGameSetting::~COperatorCategoryGameSetting()
{
	DeleteNew(m_pC_button_group);
}


void COperatorCategoryGameSetting::Start()
{

}


void COperatorCategoryGameSetting::Finish()
{
	
}


void COperatorCategoryGameSetting::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	C_VS_UI_EVENT_STRING_BUTTON* pStringButton = dynamic_cast<C_VS_UI_EVENT_STRING_BUTTON*>(p_button);
	
	if(pStringButton)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pStringButton->Show(showOffset);
	}
}


void COperatorCategoryGameSetting::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}


void COperatorCategoryGameSetting::Run(id_t id)
{

}


void COperatorCategoryGameSetting::Process()
{
	m_pC_button_group->Process();
}


void COperatorCategoryGameSetting::Show()
{
	m_pC_button_group->Show();
}


bool COperatorCategoryGameSetting::MouseControl(UINT message, int _x, int _y)
{
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}
//////////////////////////////////////////////////////////////////////////
//¿î¿µÀÚ °£´Ü ¸í·É¾î
//////////////////////////////////////////////////////////////////////////

COperatorCategorySimpleCommand::COperatorCategorySimpleCommand(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: COperatorCategory(categoryName, parentWindow, position)
	, m_pfirstCommand(NULL), m_psecondCommand(NULL), m_ptextList(NULL), m_pC_button_group(NULL)
{
	ivfstream file;
	//¾ÕÂÊ¿¡ ¿Ã¼ö ÀÖ´Â ¸í·É¾î
	file.open("Operator\\firstCommand.txt", 0);

	char tempstring[256];

	if(file.is_open())
	{
		while(!file.eof())
		{
			file.getline(tempstring, 256);
			m_firstCommand.push_back(tempstring);
		}
		file.close();
	}
	
	//µÚÂÊ¿¡ ¿Ã¼ö ÀÖ´Â ¸í·É¾î
	file.open("Operator\\secondCommand.txt", 0);
	if(file.is_open())
	{
		while(!file.eof())
		{
			file.getline(tempstring, 256);
			m_secondCommand.push_back(tempstring);
		}
		file.close();
	}
	
	//¸í·É¾î µÚ¿¡ µé¾î°¥ text
	file.open("Operator\\textList.txt", 0);
	if(file.is_open())
	{
		while(!file.eof())
		{
			file.getline(tempstring, 256);
			m_textList.push_back(tempstring);
		}
		file.close();
	}

	CRect firstListBOX(CPoint(5, 5), CSize(position.Width()/2 - 5, position.Height()/3 - 5));
	
	CRect secondListBOX(CPoint(position.Width()/2 + 5, 5), CSize(position.Width()/2 - 5, position.Height()/3 - 5));

	CRect thirdListBOX(CPoint(5, position.Height()/3 + 5), CSize(position.Width() - 10, position.Height() * 2 / 3 - 35));

	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Init();


	m_pfirstCommand = new C_VS_UI_LISTBOX(m_firstCommand, firstListBOX, -1, this, &gpC_base->m_chatting_pi);
	m_psecondCommand = new C_VS_UI_LISTBOX(m_secondCommand, secondListBOX, -1, this, &gpC_base->m_chatting_pi);
	m_ptextList = new C_VS_UI_LISTBOX(m_textList, thirdListBOX, -1, this, &gpC_base->m_chatting_pi);
	m_pC_button_group->Add(m_pfirstCommand);
	m_pC_button_group->Add(m_psecondCommand);
	m_pC_button_group->Add(m_ptextList);
	m_pC_button_group->Add(new C_VS_UI_EVENT_PUSH_BUTTON(CRect(CPoint(25,482), CSize(position.Width()/5, position.Height()/20)),
		1 , this, "ÊäÈëµ½ÁÄÌì¿ò"));
	m_pC_button_group->Add(new C_VS_UI_EVENT_PUSH_BUTTON(CRect(CPoint(165,482), CSize(position.Width()/5, position.Height()/20)),
		2 , this, "Çå¿ÕÑ¡Ôñ"));

	m_pfirstCommand->SetSelectListIndex(m_saveSelectIndexFirst);
	m_psecondCommand->SetSelectListIndex(m_saveSelectIndexSecond);
	m_ptextList->SetSelectListIndex(m_saveSelectIndexText);
}

COperatorCategorySimpleCommand::~COperatorCategorySimpleCommand()
{
	if(m_pfirstCommand)
		m_saveSelectIndexFirst = m_pfirstCommand->GetSelectListIndex();

	if(m_psecondCommand)
		m_saveSelectIndexSecond = m_psecondCommand->GetSelectListIndex();

	if(m_ptextList)
		m_saveSelectIndexText = m_ptextList->GetSelectListIndex();

	DeleteNew(m_pC_button_group);
}

void
COperatorCategorySimpleCommand::Start()
{
}

void
COperatorCategorySimpleCommand::Finish()
{
}

void
COperatorCategorySimpleCommand::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	C_VS_UI_EVENT_STRING_BUTTON* pStringButton = dynamic_cast<C_VS_UI_EVENT_STRING_BUTTON*>(p_button);
	C_VS_UI_LISTBOX* pListString = dynamic_cast<C_VS_UI_LISTBOX*>(p_button);
	
	if(pStringButton)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pStringButton->Show(showOffset);
	}
	if(pListString)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pListString->Show(showOffset);
	}

}
void
COperatorCategorySimpleCommand::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{
}

void
COperatorCategorySimpleCommand::Run(id_t id)
{

	std::string finalstring ="";

	switch(id)
	{
	case 1:
		if(m_pfirstCommand->GetSelectListString(m_pfirstCommand->GetSelectListIndex()))
		{
			finalstring += m_pfirstCommand->GetSelectListString(m_pfirstCommand->GetSelectListIndex());
			finalstring += " ";
		}
		if(m_psecondCommand->GetSelectListString(m_psecondCommand->GetSelectListIndex()))
		{
			finalstring += m_psecondCommand->GetSelectListString(m_psecondCommand->GetSelectListIndex());
			finalstring += " ";
		}
		if(m_ptextList->GetSelectListString(m_ptextList->GetSelectListIndex()))
		{
			finalstring += m_ptextList->GetSelectListString(m_ptextList->GetSelectListIndex());
		}
		if(finalstring.size()<=256)
		{
			gC_vs_ui.SetInputString(finalstring.c_str());
		}
		else
		{
#ifdef __GAME_CLIENT__			
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_CANNOT_USE].GetString());
#endif
		}
		
		break;

	case 2:	
		m_pfirstCommand->SetSelectListIndex(-1);
		m_psecondCommand->SetSelectListIndex(-1);
		m_ptextList->SetSelectListIndex(-1);
		break;
	}
}

void
COperatorCategorySimpleCommand::Process()
{
	m_pC_button_group->Process();
}

void
COperatorCategorySimpleCommand::Show()
{
	m_pC_button_group->Show();
}
	
bool
COperatorCategorySimpleCommand::MouseControl(UINT message, int _x, int _y)
{
	m_pC_button_group->MouseControl(message, _x, _y);
	return true;
}

#if __CONTENTS(__ITEM_SHOW)
//-----------------------------------------------------------------------------
// COperatorCategoryShowItemSetting
// Cheon-Iljea 2008.7.17
//-----------------------------------------------------------------------------
COperatorCategoryShowItemSetting::COperatorCategoryShowItemSetting(LPCTSTR categoryName, Window* parentWindow, const CRect& position)
	: COperatorCategory(categoryName, parentWindow, position)
	, m_pItemClassListBox(NULL), m_pItemTypeListBox(NULL)
{
	m_RectList = position;
	m_find_str = "";

	// ¹è°æ
	CRect rc_ItemClassListBOX(CPoint(5, 5), CSize(position.Width()/2 - 5, position.Height() - 10));
	CRect rc_ItemTypeListBOX(CPoint(position.Width()/2 + 5, 5), CSize(position.Width()/2 - 10, position.Height() - 10));

	m_pItemClassListBox = new C_VS_UI_LISTBOX(m_ItemClassListBox, rc_ItemClassListBOX, -1, this, &gpC_base->m_chatting_pi);
	m_pItemTypeListBox = new C_VS_UI_LISTBOX(m_ItemTypeListBox, rc_ItemTypeListBOX, -1, this, &gpC_base->m_chatting_pi);

	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Init();

	m_pC_button_group->Add(m_pItemClassListBox);
	m_pC_button_group->Add(m_pItemTypeListBox);
	int i;
	for( i=0;i<MAX_ITEM_CLASS;i++)
	{
		ostringstream ostr;
		ostr<<i<<". "<<ITEM_SHOW_NAME[i];

		m_pItemClassListBox->AddString(ostr.str());
	}
	m_pItemClassListBox->AddString("<<Çå¿Õ±³°ü>");
	m_pItemClassListBox->AddString("");
	m_pItemClassListBox->AddString("create by rallser");
	m_pItemClassListBox->AddString("");

	int item_size = (*g_pItemTable)[0].GetSize();
	
	for(i=0;i<item_size;i++)
	{
		ostringstream ostr;
		ostr<<0<<"-"<<i<<". "
			<<(*g_pItemTable)[0][i].HName.GetString()<<"("
			<<(*g_pItemTable)[0][i].EName.GetString()<<")";
	
		m_pItemTypeListBox->AddString(ostr.str());
	}

	m_find_mark_str = "This Class! ¢Ñ ";
	m_find_mark_str_size = m_find_mark_str.size();

	m_pItemClassListBox->SetSelectListIndex(0);
	m_pItemTypeListBox->SetSelectListIndex(m_saveSelectIndexItemType);
}

COperatorCategoryShowItemSetting::~COperatorCategoryShowItemSetting()
{
	if(m_pItemClassListBox)
		m_saveSelectIndexItemClass = m_pItemClassListBox->GetSelectListIndex();
	if(m_pItemTypeListBox)
		m_saveSelectIndexItemType = m_pItemTypeListBox->GetSelectListIndex();

	DeleteNew(m_pC_button_group);
	gC_vs_ui.SetInputString("");
}


void COperatorCategoryShowItemSetting::Start()
{
	
}

void COperatorCategoryShowItemSetting::Finish()
{
	
}

void COperatorCategoryShowItemSetting::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	C_VS_UI_LISTBOX* pListString = dynamic_cast<C_VS_UI_LISTBOX*>(p_button);

	if(pListString)
	{
		CPoint showOffset(TopLeft());
		showOffset.x += GetParentWindowPtr()->x;
		showOffset.y += GetParentWindowPtr()->y;
		pListString->Show(showOffset);
	}
}

void COperatorCategoryShowItemSetting::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

void COperatorCategoryShowItemSetting::Run(id_t id)
{
}


void COperatorCategoryShowItemSetting::Process()
{
	m_pC_button_group->Process();
}

void COperatorCategoryShowItemSetting::Show()
{
	m_pC_button_group->Show();

	const char *Find_Str = gC_vs_ui.GetNewInputString();
	char find_str[256];
	if(Find_Str!=NULL)
	{
		strcpy(find_str,Find_Str);
		delete (char *)Find_Str;
		Find_Str = NULL;
	}
	else
	{
		strcpy(find_str,"");
	}

	// ¹®ÀÚ¿­ »èÁ¦ÇØÁÖ±â
	string find_str_delete = "°Ë»ö¾î";
	string find_str_str	= find_str;

	if( lstrlen("°Ë»ö¾î¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä.")!=find_str_str.size() )
	{
		if( find_str_delete.size()!=0 && find_str_str.find(find_str_delete.c_str()) != std::string::npos )
		{
			if(lstrlen("°Ë»ö¾î¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä.")<find_str_str.size())
			{
				string str = &find_str_str[find_str_str.size()-1];
				gC_vs_ui.SetInputString(str.c_str());
				strcpy(find_str,str.c_str());
			}
			else
			{
				gC_vs_ui.SetInputString("");
				strcpy(find_str,"");
			}
		}
	}
	
	ShowItem_Find(find_str);
}

bool COperatorCategoryShowItemSetting::MouseControl(UINT message, int _x, int _y)
{
	m_pC_button_group->MouseControl(message, _x, _y);
	
	CPoint ptLocalMouse(_x , _y );
//	if(!m_RectList.PtInRect(ptLocalMouse))
//		message = M_LEFTBUTTON_UP; // ½ºÅ©·Ñ¹Ù ½ºÅ©·Ñ ÇÏ¸é¼­ ¹ÛÀ¸·Î ²ø¾î³»¸é ¸¶¿ì½º¶¼µµ °è¼Ó ½ºÅ©·Ñ µÇ´Â°Å °íÄ¥·Á°íÇß´ø°Í.

	bool ClassList_bt = m_pItemClassListBox->MouseControl(message, _x, _y);
	bool TypeList_bt = m_pItemTypeListBox->MouseControl(message, _x, _y);
	
	bool bClickMessage = (message==M_LEFTBUTTON_DOWN||message==M_LB_DOUBLECLICK);
	
	if(!ClassList_bt&&bClickMessage&&m_pItemClassListBox->GetSelectListIndex()<m_pItemClassListBox->ListNodeMax()&&m_pItemClassListBox->GetSelectListIndex()<=MAX_ITEM_CLASS||m_pItemClassListBox->GetSelectListIndex()==MAX_ITEM_CLASS+2)
	{
		m_pItemTypeListBox->DelListNodeAll();
		
		if(m_pItemClassListBox->GetSelectListIndex()==MAX_ITEM_CLASS)
		{
			gpC_base->SendMessage(UI_ITEM_SHOW_AND_CLEAR_ITEM, 0, 0);
		}
		else
		{
			char src_str[20];
			if(m_pItemClassListBox->IsFindStringOK())
			{
				char mark_str[256];
				string _find_str;

				strcpy(mark_str,m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()));
				_find_str = mark_str;

				// find mark..
				if( m_find_mark_str.size()!=0 && _find_str.find(m_find_mark_str.c_str()) != std::string::npos )
					sscanf(&mark_str[m_find_mark_str_size],"%s",src_str);
				else
					sscanf(m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()),"%s",src_str);
			}
			else
			{
				sscanf(m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()),"%s",src_str);
			}

			int Class_Num = atoi(src_str);
		
			int item_size = (*g_pItemTable)[Class_Num].GetSize();
	
			for(int i=0;i<item_size;i++)
			{
				ostringstream ostr;
				ostr<<Class_Num<<"-"<<i<<". "
					<<(*g_pItemTable)[Class_Num][i].HName.GetString()<<"("
					<<(*g_pItemTable)[Class_Num][i].EName.GetString()<<")";
	
				m_pItemTypeListBox->AddString(ostr.str());
			}
			m_pItemTypeListBox->SetSelectListIndex(-1);
		}
	}
	
	// create item..
	if(!TypeList_bt&&bClickMessage&&m_pItemTypeListBox->GetSelectListIndex()!=-1&&m_pItemTypeListBox->GetSelectListIndex()<m_pItemTypeListBox->ListNodeMax())
	{
		char src_str[20];
		sscanf(m_pItemTypeListBox->GetSelectListString(m_pItemTypeListBox->GetSelectListIndex()),"%s",src_str);

		int Class_Num = atoi(src_str);
		char* ptr = src_str;
		for(;(ptr!=NULL&&*ptr!=45);ptr++); ptr++;
		int Type_Num = atoi(ptr);

		gpC_base->SendMessage(UI_ITEM_SHOW_AND_CREATE_ITEM, Class_Num, Type_Num);
	}

	return true;
}

bool COperatorCategoryShowItemSetting::ShowItem_Find(string find_str)
{
	if(m_pItemClassListBox->ListNodeMax()==0 || m_pItemTypeListBox->ListNodeMax()==0)
		return false;

	if(m_find_str.size()==find_str.size())
	{
		if( find_str.size()==0 || find_str.size()>30 || (find_str.size()!=0 && m_find_str.find(find_str.c_str()) != std::string::npos) )
			return false;
	}

	m_find_str = find_str;
	m_pItemClassListBox->DelListNodeAll();
	int i;
	for(i=0;i<MAX_ITEM_CLASS;i++)
	{
		ostringstream ostr;
		string _str;

		//////////////////////////////////////////////////////////////////////////
		// ItemType Find.. ij-ch
		int item_size = (*g_pItemTable)[i].GetSize();
		m_pItemTypeListBox->DelListNodeAll();

		for(int j=0;j<item_size;j++)
		{
			ostringstream ostr;
			ostr<<i<<"-"<<j<<". "
				<<(*g_pItemTable)[i][j].HName.GetString()<<"("
				<<(*g_pItemTable)[i][j].EName.GetString()<<")";

			m_pItemTypeListBox->AddString(ostr.str());
		}

		m_pItemTypeListBox->SetFindString(find_str);
		m_pItemTypeListBox->SetSelectListIndex(-1);
		//////////////////////////////////////////////////////////////////////////

		ostr<<i<<". "<<ITEM_SHOW_NAME[i];
		_str = ostr.str();

		if( m_pItemTypeListBox->IsFindStringOK())
		{
			ostr.str("");
			ostr<<m_find_mark_str<<i<<". "<<ITEM_SHOW_NAME[i];
		}
		
		m_pItemClassListBox->AddString(ostr.str());
	}
	m_pItemClassListBox->AddString("<<Çå¿Õ±³°ü>>");
	m_pItemClassListBox->AddString("");
	m_pItemClassListBox->AddString("create by rallser");
	m_pItemClassListBox->AddString("");
	
	m_pItemClassListBox->SetFindString(m_find_mark_str);

	// ¼±ÅÃµÈ ¾ÆÀÌÅÛ Å¸ÀÔ¸®½ºÆ®
	//////////////////////////////////////////////////////////////////////////
	char src_str[20];
	if(m_pItemClassListBox->IsFindStringOK())
	{
		char mark_str[256];
		string _find_str;

		strcpy(mark_str,m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()));
		_find_str = mark_str;

		// find mark..
		if( m_find_mark_str.size()!=0 && _find_str.find(m_find_mark_str.c_str()) != std::string::npos )
			sscanf(&mark_str[m_find_mark_str_size],"%s",src_str);
		else
			sscanf(m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()),"%s",src_str);
	}
	else
	{
		sscanf(m_pItemClassListBox->GetSelectListString(m_pItemClassListBox->GetSelectListIndex()),"%s",src_str);
	}

	//////////////////////////////////////////////////////////////////////////
	int Class_Num = atoi(src_str);

	int item_size = (*g_pItemTable)[Class_Num].GetSize();
	m_pItemTypeListBox->DelListNodeAll();

	for(i=0;i<item_size;i++)
	{
		ostringstream ostr;
		ostr<<Class_Num<<"-"<<i<<". "
			<<(*g_pItemTable)[Class_Num][i].HName.GetString()<<"("
			<<(*g_pItemTable)[Class_Num][i].EName.GetString()<<")";
	
		m_pItemTypeListBox->AddString(ostr.str());
	}
	return true;
}
#endif //__ITEM_SHOW
