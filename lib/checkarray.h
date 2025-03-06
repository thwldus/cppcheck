//---------------------------------------------------------------------------
#ifndef checkarrayH
#define checkarrayH
//---------------------------------------------------------------------------

#include "check.h"  
#include "tokenize.h"

class ErrorLogger;
class Settings;

class CPPCHECKLIB CheckArray : public Check {
public:
    /** This constructor is used when registering the CheckClass */
    CheckArray() : Check(myName()) {}

private:
    CheckArray(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    : Check(myName(), tokenizer, settings, errorLogger) {}

    /** @brief Run checks against the normal token list */
    void runChecks(const Tokenizer &tokenizer, ErrorLogger *errorLogger) override {
        CheckArray checkArray(&tokenizer, &tokenizer.getSettings(), errorLogger);
        
        checkArray.uncheckedIndex();
    }

    void uncheckedIndex();

    void getErrorMessages(ErrorLogger *errorLogger, const Settings *settings) const override {
        CheckArray c(nullptr, settings, errorLogger);
    }

    static std::string myName() {
        return "Array";
    }

    std::string classInfo() const override {
        return "Unchecked Array"; 
    }

};
//---------------------------------------------------------------------------
#endif // checkarrayH