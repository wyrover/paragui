#ifndef PG_FACTORY_H
#define PG_FACTORY_H

#include <map>
#include <string>

#include "pgsingleton.h"

class PG_Widget;

template< class T, class PT = PG_Widget > class PG_FactoryObject {
public:
	static T* CreateObject(PT* parent) {
		return new T(parent);
	}
};

template<class H>
class PG_FactoryHolder : public PG_Singleton< PG_FactoryHolder<H> > {
public:
	
	typedef PG_Widget* (*CREATEFN)(PG_Widget* parent);
	
	template< class T, class PT > static void RegisterClass(const H& classname) {
		GetInstance().RegisterCreateFn(classname, (CREATEFN)&PG_FactoryObject<T, PT>::CreateObject);
	}
		
	template< class T > static void RegisterClass(const H& classname) {
		GetInstance().RegisterCreateFn(classname, (CREATEFN)&PG_FactoryObject<T>::CreateObject);
	}

	static PG_Widget* CreateObject(const H& classname, PG_Widget* parent = NULL) {
		CREATEFN create = GetInstance().creator_map[classname];
		
		if(create == NULL) {
			return NULL;
		}
		
		return create(parent);
	}
	
protected:
	
	inline void RegisterCreateFn(const H& classname, CREATEFN fn) {
		creator_map[classname] = fn;
	}
	
	std::map< H, PG_FactoryHolder<H>::CREATEFN > creator_map;
	
	friend class PG_Singleton< PG_FactoryHolder<H> >;
	
};

typedef PG_FactoryHolder<std::string> PG_Factory;

#endif // PG_FACTORY_H
