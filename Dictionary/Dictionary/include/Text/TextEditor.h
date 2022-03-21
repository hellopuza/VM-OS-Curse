#ifndef TEXT_TEXTEDITOR_H
#define TEXT_TEXTEDITOR_H

#include <vector>
#include <string>

namespace puza {

class TextEditor final
{
public:
    TextEditor() = default;
    TextEditor(const TextEditor& obj) = delete;
    TextEditor(TextEditor&& obj) noexcept = delete;
    ~TextEditor() = default;

    TextEditor& operator=(const TextEditor &obj) = delete;
    TextEditor& operator=(TextEditor&& obj) noexcept = delete;

    bool load(const char* filename);
    void save(const char* filename) const;

    class iterator;

    void replace(iterator& it, const std::string& str);

    iterator begin() const;
    iterator end() const;

private:
    std::string file_content_;
};

class TextEditor::iterator
{
public:
    iterator(size_t position, const TextEditor* text_ed);
    iterator& next();
    bool operator==(const iterator& obj) const;
    bool operator!=(const iterator& obj) const;
    iterator& operator*();

    size_t current_position() const;
    std::string current_word() const;
    std::string current_section() const;

private:
    size_t begin_pos_;
    size_t end_word_pos_;
    size_t end_section_pos_;
    const TextEditor* text_ed_;
};

} // namespace puza

#endif // TEXT_TEXTEDITOR_H