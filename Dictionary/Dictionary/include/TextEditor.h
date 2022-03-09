#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <vector>
#include <string>

namespace puza {

class TextEditor final
{
public:
    TextEditor() = default;
    ~TextEditor() = default;

    bool load(const char* filename);
    void save(const char* filename) const;

    class iterator;

    void replace(const iterator& it, const std::string& str);

    iterator begin() const;
    iterator end() const;

private:
    std::string file_content_;
};

class TextEditor::iterator
{
public:
    iterator(size_t position, const TextEditor* text_ed);
    iterator& operator++();
    iterator operator++(int);
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

#endif // TEXTEDITOR_H