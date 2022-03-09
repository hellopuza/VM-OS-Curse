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

    bool load(const char* filename);
    bool parse(const char* filename);

    static const size_t DICTIONARY_NUM_ = 20;
    static const size_t MIN_WORD_LEN_ = 2;

private:
    void correct(const TextEditor::iterator& text_it);

    HashTable<size_t, Dictionary> dicts_;
    TextEditor text_;
    Informer info_;
};

} // namespace puza

#endif // DICTIONARY_CORRECTOR_H