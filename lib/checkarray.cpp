# include "checkarray.h"

# include "token.h"
# include "astutils.h"
# include "valueflow.h"

# include <iostream>
# include <string>


//---------------------------------------------------------------------------

// CWE ids used:
static const CWE CWE129(129U);  // Improper Validation of Array Index

//---------------------------------------------------------------------------



void CheckArray::uncheckedIndex()
{
    std::cout << "indexvalid Testing...\n";
}
