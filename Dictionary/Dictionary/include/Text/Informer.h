#ifndef TEXT_INFORMER_H
#define TEXT_INFORMER_H

#include <vector>
#include <string>

namespace puza {

class Informer final
{
public:
    Informer(size_t max_words_num);
    Informer(const Informer& obj) = delete;
    Informer(Informer&& obj) noexcept = delete;
    ~Informer() = default;

    Informer& operator=(const Informer &obj) = delete;
    Informer& operator=(Informer&& obj) noexcept = delete;

    void appendWord(const std::string& word);
    void clearText();
    void setMessage(const std::string& message);
    std::string getOutput() const;

private:
    std::vector<std::string> text_;
    std::string message_;
    size_t max_words_num_;
};

} // namespace puza

#endif // TEXT_INFORMER_H