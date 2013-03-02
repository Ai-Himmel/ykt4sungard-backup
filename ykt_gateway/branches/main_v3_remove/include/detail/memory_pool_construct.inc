// this file is auto-generated. DO NOT modify this file manually.
             // Copyright Kingstargroup 2006 
            // Author: люЁи 
template<typename T0>
T* alloc(T0& arg0)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0);

}
template<typename T0>
T* alloc(const T0& arg0)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0);

}
template<typename T0,typename T1>
T* alloc(T0& arg0,T1& arg1)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1);

}
template<typename T0,typename T1>
T* alloc(const T0& arg0,const T1& arg1)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1);

}
template<typename T0,typename T1,typename T2>
T* alloc(T0& arg0,T1& arg1,T2& arg2)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2);

}
template<typename T0,typename T1,typename T2>
T* alloc(const T0& arg0,const T1& arg1,const T2& arg2)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2);

}
template<typename T0,typename T1,typename T2,typename T3>
T* alloc(T0& arg0,T1& arg1,T2& arg2,T3& arg3)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2,arg3);

}
template<typename T0,typename T1,typename T2,typename T3>
T* alloc(const T0& arg0,const T1& arg1,const T2& arg2,const T3& arg3)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2,arg3);

}
template<typename T0,typename T1,typename T2,typename T3,typename T4>
T* alloc(T0& arg0,T1& arg1,T2& arg2,T3& arg3,T4& arg4)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2,arg3,arg4);

}
template<typename T0,typename T1,typename T2,typename T3,typename T4>
T* alloc(const T0& arg0,const T1& arg1,const T2& arg2,const T3& arg3,const T4& arg4)
{
TM lock(mutex_);
if(!lock.locked())return NULL;
return object_pool_.construct(arg0,arg1,arg2,arg3,arg4);

}
