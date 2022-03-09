#include "TextEditor.h"

#include <fstream>
#include <sstream>

namespace puza {

bool TextEditor::load(const char* filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file_content_ = buffer.str();
    }
    else
    {
        return false;
    }

    return true;
}

void TextEditor::save(const char* filename) const
{
    std::ofstream out(filename);
    out << file_content_;
}

void TextEditor::replace(const iterator& it, const std::string& str)
{
    file_content_.replace(it.current_position(), str.length(), str);
}

TextEditor::iterator TextEditor::begin() const
{
    size_t pos = 0;
    while ((pos < file_content_.length()) && (!isalpha(file_content_[pos])))
    {
        pos++;
    }
    if (pos == file_content_.length())
    {
        pos = 0;
    }
    return iterator(pos, this);
}

TextEditor::iterator TextEditor::end() const
{
    size_t pos = file_content_.length() - 1;
    while ((pos > 0) && !(isalpha(file_content_[pos]) && !isalpha(file_content_[pos - 1])))
    {
        pos--;
    }
    return iterator(pos, this);
}

TextEditor::iterator::iterator(size_t position, const TextEditor* text_ed) :
    begin_pos_(position), text_ed_(text_ed)
{
    end_word_pos_ = begin_pos_;
    while ((end_word_pos_ < text_ed_->file_content_.length()) && (isalpha(text_ed_->file_content_[end_word_pos_])))
    {
        end_word_pos_++;
    }
    end_word_pos_--;

    end_section_pos_ = end_word_pos_ + 1;
    while ((end_section_pos_ < text_ed_->file_content_.length()) && (!isalpha(text_ed_->file_content_[end_section_pos_])))
    {
        end_section_pos_++;
    }
    end_section_pos_--;
}

TextEditor::iterator& TextEditor::iterator::operator++()
{
    if (end_section_pos_ == text_ed_->file_content_.length() - 1)
    {
        return *this;
    }

    end_word_pos_ = begin_pos_ = end_section_pos_ + 1;
    while ((end_word_pos_ < text_ed_->file_content_.length()) && (isalpha(text_ed_->file_content_[end_word_pos_])))
    {
        end_word_pos_++;
    }
    end_word_pos_--;

    end_section_pos_ = end_word_pos_ + 1;
    while ((end_section_pos_ < text_ed_->file_content_.length()) && (!isalpha(text_ed_->file_content_[end_section_pos_])))
    {
        end_section_pos_++;
    }
    end_section_pos_--;

    return *this;
}

TextEditor::iterator TextEditor::iterator::operator++(int)
{
    iterator retval = *this;
    ++(*this);
    return retval;
}

bool TextEditor::iterator::operator==(const iterator& obj) const
{
    return (begin_pos_ == obj.begin_pos_);
}

bool TextEditor::iterator::operator!=(const iterator& obj) const
{
    return !(*this == obj);
}

TextEditor::iterator& TextEditor::iterator::operator*()
{
    return *this;
}

size_t TextEditor::iterator::current_position() const
{
    return begin_pos_;
}

std::string TextEditor::iterator::current_word() const
{
    return text_ed_->file_content_.substr(begin_pos_, end_word_pos_ - begin_pos_ + 1);
}

std::string TextEditor::iterator::current_section() const
{
    return text_ed_->file_content_.substr(begin_pos_, end_section_pos_ - begin_pos_ + 1);
}

} // namespace puza