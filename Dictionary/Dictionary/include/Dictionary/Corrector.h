#ifndef DICTIONARY_CORRECTOR_H
#define DICTIONARY_CORRECTOR_H

#include "Dictionary/Dictionary.h"
#include "Text/TextEditor.h"
#include "Text/Informer.h"

namespace puza {

class Corrector final
{
public:
    Corrector(size_t dict_num = DICTIONARY_NUM_);
    Corrector(const Corrector& obj) = delete;
    Corrector(Corrector&& obj) noexcept = delete;
    ~Corrector() = default;

    Corrector& operator=(const Corrector &obj) = delete;
    Corrector& operator=(Corrector&& obj) noexcept = delete;

    void setMode(int mode);
    void setParallel(bool parallel);
    bool load_text(const char* filename);
    bool load_data(const char* filename);
    bool save_data(const char* filename) const;
    bool process(const char* filename);

    enum CorrectionModes
    {
        NO_OUTPUT,
        WITH_OUTPUT,
        NO_CORRECTION,
    };

    static const size_t DICTIONARY_NUM_ = 24;
    static const size_t MIN_WORD_LEN_ = 2;
    static const size_t MAX_LEV_DIST_ = 2;
    static const size_t INFORMER_WORDS_NUM_ = 5;

private:
    void parseText();
    void updateOutput(const std::vector<std::string>& best_words, TextEditor::iterator* text_it);

    HashTable<size_t, Dictionary> dicts_;
    TextEditor text_;
    Informer info_;
    std::string info_output_;
    int process_mode_ = NO_CORRECTION;
    bool parallel_processing_ = false;
};

} // namespace puza

#endif // DICTIONARY_CORRECTOR_H