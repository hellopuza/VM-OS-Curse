#ifndef DICTIONARY_CORRECTOR_H
#define DICTIONARY_CORRECTOR_H

#include "Dictionary/Dictionary.h"
#include "TextEditor.h"
#include "Informer.h"

namespace puza {

class Corrector final
{
public:
    Corrector(size_t dict_num = DICTIONARY_NUM_);

    void setMode(int mode);
    bool load(const char* filename);
    bool process(const char* filename);

    enum CorrectionModes
    {
        NO_OUTPUT,
        WITH_OUTPUT,
        NO_CORRECTION,
    };

    static const size_t DICTIONARY_NUM_ = 20;
    static const size_t MIN_WORD_LEN_ = 2;

private:
    void parseText();

    HashTable<size_t, Dictionary> dicts_;
    TextEditor text_;
    Informer info_;
    std::string info_output_;
    int process_mode_;
};

} // namespace puza

#endif // DICTIONARY_CORRECTOR_H