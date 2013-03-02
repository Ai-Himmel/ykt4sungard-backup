#ifndef _SMARTPOOL_H_
#define _SMARTPOOL_H_
/*! @file
 *	模块名:			一卡通通用前置机
 *	文件名: 		smartpool.h
 *	文件实现功能:	智能资源池
 *	作者:	汤成
 *	版本:	V1.0
 *	备注:
 定义一套智能资源池与智能资源池指针。
 1. 目标是自动管理资源池的资源，资源使用完成后，自动释放资源。
 2. 申请的资源不能 delete 。
 3. 智能指针被拷贝后，多个智能指针使用的仍是同一个资源。
 4. 对于智能指针 sp , if(sp) ... if(!sp) ... 都是可以的，它将会判断资源申请成功
 5. 对于智能指针sp , &sp 操作不会返回对资源的地址，而是智能指针的地址
 6. 不要试图调用ResourcePool的Return()方法，该方法由智能指针调用
*/
#ifdef _MSC_VER
#pragma once
#endif

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/pool/object_pool.hpp>
#include <list>


template <class T,class ThreadModel,class CheckPolicy>
class KSG_Memory_Pool_Allocator : public CheckPolicy
{
private:
	boost::object_pool<T> object_pool_;
	typedef typename ThreadModel TM;

	typename TM::MutexType mutex_;
public:
	KSG_Memory_Pool_Allocator()
	{}
	KSG_Memory_Pool_Allocator(const KSG_Memory_Pool_Allocator &rhs)
	{}

	void free(T *p)
	{
L_TEST_AGAIN:
{
		TM lock(mutex_);
		if(!lock.locked())
			goto L_TEST_AGAIN;
		if(object_pool_.is_from(p))
	{
			OnDeleteCheck(p);
			object_pool_.destroy(p);
	}
		}
	}
	T* alloc()
	{
		TM lock(mutex_);
		if(!lock.locked())
			return NULL;
		T* ret = object_pool_.construct();
		OnNewCheck(ret);
		return ret;
	}
#include "detail/memory_pool_construct.inc"

	void OnInit()
	{}
	void OnDelete()
	{}
	bool is_empty()
{
		return false;
		}
	};


template <class T,class ThreadModel,class Creator>
class KSG_Resource_Pool_Allocator
{
private:
	typedef std::list<T*> Res_Ptr_List_Type;
	typedef typename ThreadModel TM;
	Res_Ptr_List_Type ptr_list_;
	typename TM::MutexType mutex_;
	typename Creator creator_;
public:
	KSG_Resource_Pool_Allocator()
	{}
	KSG_Resource_Pool_Allocator(const KSG_Resource_Pool_Allocator &rhs)
	{}
	void OnInit()
	{
		int i = creator_.get_max();
		while(i-->0)
		{
			T* p = creator_.create_new();
			if(p)
				ptr_list_.push_back(p);
		}
	}
	void OnDelete()
	{
		Res_Ptr_List_Type::iterator i;
		for(i = ptr_list_.begin();i != ptr_list_.end();++i)
		{
			T* p = *i;
			if(p)
				creator_.delete_one(p);
	}
		ptr_list_.clear();
	}
	void free(T* p)
	{
L_TEST_AGAIN:
		{
		TM lock(mutex_);
			if(!lock.locked())
			goto L_TEST_AGAIN;
		ptr_list_.push_back(p);
	}
		}

	T* alloc()
	{
		TM lock(mutex_);
		if(!lock.locked())
			return NULL;
		if(ptr_list_.empty())
			return NULL;
		T* p = ptr_list_.front();
		ptr_list_.pop_front();
		return p;
		}

	bool is_empty()
	{
		return s_ptr_list_.empty()
	}
};


template <class T,class Allocator>
class KSG_SmartPool
{
public:
	typedef boost::shared_ptr<T> SmartPtr;
	typedef SmartPtr SmartObject;
private:
	typedef typename Allocator AP;
	AP allocator_;
	SmartPtr new_obj(T* p)
	{
		if(!p)
	{
			SmartPtr res = SmartPtr(p);
			return res;
	}
		SmartPtr res(p,std::bind1st(std::mem_fun(AP::free),&allocator_));
		return res;
	}
public:
	KSG_SmartPool()
	{
		//	
	}
	void Init()
	{
		allocator_.OnInit();
	}
	~KSG_SmartPool()
		{
		allocator_.OnDelete();
	}
	SmartPtr Alloc()
	{
		T * ret = allocator_.alloc();
		return new_obj(ret);
	}
#include "detail/smart_ptr_construct.inc"

};

#endif // _SMARTPOOL_H_

