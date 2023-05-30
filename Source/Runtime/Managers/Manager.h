#pragma once

template<typename M>
class Manager
{
    inline static M* instance = nullptr;
	
public:
    static M*& Instance()
    {
        if (!instance)
        {
            instance = new M();
        }
		
        return instance;
    }
};