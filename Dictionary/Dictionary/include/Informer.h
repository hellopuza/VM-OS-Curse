#ifndef INFORMER_H
#define INFORMER_H

#include <vector>
#include <string>

namespace puza {

class Informer final
{
public:
    Informer(size_t max_words_num);

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

#endif // INFORMER_H