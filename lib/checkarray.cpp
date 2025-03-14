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
    // std::cout << "indexvalid Testing...\n";
    logChecker("CheckArray::uncheckedIndex");

    for (const Token *tok = mTokenizer->tokens(); tok; tok = tok->next()){
        if(tok->str() != "[")
            continue;
        const Token* array = tok->astOperand1();
        while (Token::Match(array, ".|::"))
            array = array->astOperand2();
        if (!array || ((!array->variable() || array->variable()->nameToken() == array) && array->tokType() != Token::eString))
            continue; 
    
        std::vector<const Token*> indexTokens;
        for (const Token* tok2 = tok; tok2 && tok2->str() == "["; tok2 = tok2->next()) {
            if (!tok2->astOperand2()) {
                indexTokens.clear();
                break;
            }
            indexTokens.push_back(tok2->astOperand2());
        }
        if (indexTokens.empty()) {
            continue;
        }

        // indexTokens 정보 출력
        for (const Token* idx : indexTokens) {
            bool b = false;
            try {
                std::stoi(idx->str()); 
                b = true;
            } catch (const std::invalid_argument& e) {  
                // 정수로 변환할 수 없는 문자열의 경우
                // b = false로 유지
            } catch (const std::out_of_range& e) { 
                // 정수 범위를 벗어난 경우 
            }
            if (!b){   
                // std::cout << "________________\n\n";
                // std::cout << " ▶  검사 배열 인덱스 변수 정보:\n" ;
                // std::cout << "  - 인덱스: " << idx->index() << " (위치: " << idx->linenr() << "번째 줄)\n";
            
                // Checking
                bool indexCheck = false;
                for (const Token *ctok = mTokenizer->tokens(); ctok != idx; ctok = ctok->next()) {
                    // std::cout << ctok->index() << "\n";
                    if (ctok->str() != idx->str())
                        continue;
                    std::string nextStr = ctok->next()->str();
                    if (nextStr == "==" ||
                        nextStr == "!=" ||
                        nextStr == "<" ||
                        nextStr == "<=" ||
                        nextStr == ">" ||
                        nextStr == ">=") {
                            indexCheck = true;
                    } 
                }
                if (!indexCheck) {
                    // std::cout << "CWE-129 error detection: " << idx->str() <<"\n";
                    uncheckedIndexError(tok);
                }
            }
        }
    }

}

void CheckArray::uncheckedIndexError(const Token* tok)
{
    // severity, id, msg 등 필요 시 추가 조정
    reportError(tok, Severity::error, "uncheckedArrayIndex", 
        "Index variable in array used without proper validation", CWE129, Certainty::normal);
}