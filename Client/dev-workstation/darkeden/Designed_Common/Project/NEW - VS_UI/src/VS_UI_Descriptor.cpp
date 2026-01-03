// VS_UI_Descriptor.cpp

#include "client_PCH.h"
#include "VS_UI_Descriptor.h"

DescriptorManager	g_descriptor_manager;

//----------------------------------------------------------------------------
// Operations
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// DescriptorManager::DescriptorManager
//
// 
//-----------------------------------------------------------------------------
DescriptorManager::DescriptorManager()
{
}

//-----------------------------------------------------------------------------
// DescriptorManager::~DescriptorManager
//
// 
//-----------------------------------------------------------------------------
DescriptorManager::~DescriptorManager()
{
	DESCRIBED_UNIT * data;
	for (int i=0; i < Size(); i++)
		if (Data(i, data))
			delete data;
}

//-----------------------------------------------------------------------------
// DescriptorManager::Set
//
// 
//-----------------------------------------------------------------------------
void	DescriptorManager::Set(id_t id, int x, int y, void * void_ptr, long left, long right, bool add, int z_order)
{
	if (!add && !m_DescMap.empty()) // doing?
		return;

	DESCRIBED_UNIT * data;
	for (int i=0; i < Size(); i++)
		if (Data(i, data))
			if (data->id == id)
			{
				assert(!gpC_base->m_p_DDSurface_back->IsLock());
				data->fp_rect_calculator(data->fp_show, x, y, void_ptr, left, right, z_order);
				return;
 			}
}
const DescriptorManager::DESC*	DescriptorManager::GetDesc(void* void_ptr) const
{
	DescMap::const_iterator iter = m_DescMap.begin();
	DescMap::const_iterator endIter = m_DescMap.end();
	for(; iter != endIter; ++iter)
	{
		const DESC& desc = iter->second;
		if(desc.m_fp_show_param.void_ptr == void_ptr)
			return &desc;
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// DescriptorManager::Unset
//
// 
//-----------------------------------------------------------------------------
//void	DescriptorManager::Unset()
//{
//	m_fp_show = NULL;
//}

//-----------------------------------------------------------------------------
// DescriptorManager::Unset 
//
// by sigi
// 
// NULL인 경우는 그냥 UnSet
//-----------------------------------------------------------------------------
void	DescriptorManager::Unset(void* pPtr)
{
	if (pPtr==NULL)
	{
		m_DescMap.clear();
		return;
	}

	DescMap::iterator iter = m_DescMap.begin();
	DescMap::iterator endIter = m_DescMap.end();
	for(; iter != endIter; ++iter)
	{		
		const DESC& desc = iter->second;
		if(desc.m_fp_show_param.void_ptr == pPtr)
		{
			m_DescMap.erase(iter);
			break;
		}
	}
}


//-----------------------------------------------------------------------------
// DescriptorManager::Show
//
// 
//-----------------------------------------------------------------------------
void	DescriptorManager::Show()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	DescMap::iterator iter = m_DescMap.begin();
	DescMap::iterator endIter = m_DescMap.end();
	for(; iter != endIter; ++iter)
	{
		DESC& desc = iter->second;
		if (desc.m_fp_show)
			desc.m_fp_show(desc.m_fp_show_param.rect, desc.m_fp_show_param.void_ptr, desc.m_fp_show_param.left, desc.m_fp_show_param.right);
	}
}

//-----------------------------------------------------------------------------
// DescriptorManager::AddDescribedUnit
//
// 
//-----------------------------------------------------------------------------
void	DescriptorManager::AddDescribedUnit(id_t id, void (*fp_rect_calculator)(void (*fp_show)(Rect, void *, long, long), int, int, void *, long, long, int), void (*fp_show)(Rect, void *, long, long), bool bl_immediate)
{
	// same id?
	DESCRIBED_UNIT * data;
	for (int i=0; i < Size(); i++)
		if (Data(i, data))
			if (data->id == id)
				return;

	DESCRIBED_UNIT * p_unit = new DESCRIBED_UNIT;

	p_unit->bl_immediate = bl_immediate;
	p_unit->fp_rect_calculator = fp_rect_calculator;
	p_unit->fp_show = fp_show;
	p_unit->id = id;

	Add(p_unit);
}

//-----------------------------------------------------------------------------
// DescriptorManager::RectCalculationFinished
//
// 
//-----------------------------------------------------------------------------
void	DescriptorManager::RectCalculationFinished(void (*fp_show)(Rect, void *, long, long), Rect rect, void * void_ptr, long left, long right, int z_order)
{
	DESC desc;
	desc.m_fp_show = fp_show;
	desc.m_fp_show_param.void_ptr = void_ptr;
	desc.m_fp_show_param.rect = rect;
	desc.m_fp_show_param.left = left;
	desc.m_fp_show_param.right = right;
	m_DescMap.insert(DescMap::value_type(z_order, desc));
}