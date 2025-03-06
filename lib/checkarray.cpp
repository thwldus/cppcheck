# include "checkarray.h"

# include "token.h"
# include "astutils.h"
# include "valueflow.h"

# include <iostream>
# include <string>


//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
    CheckArray instance;
}

// CWE ids used:
static const CWE CWE129(129U);  // Improper Validation of Array Index

//---------------------------------------------------------------------------



void CheckArray::uncheckedIndex()
{
    std::cout << "indexvalid Testing...\n";
}
