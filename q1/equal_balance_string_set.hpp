#ifndef equal_balance_string_set_hpp
#define equal_balance_string_set_hpp

#include "string_set.hpp"


struct EqualBalanceStringSet
    : public UnbalancedStringSet
{

    EqualBalanceStringSet()
    {
				
    }

    void optimise() override
    {
        m_root=tree_rebuild_balanced(m_root);
    }
};

#endif
