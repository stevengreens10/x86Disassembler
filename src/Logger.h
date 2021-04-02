#include <iostream>
#include <string>

class Logger {
public:

    explicit Logger(std::ostream &out, const std::string &delim = "[%]") : m_out(&out),
                                                                           m_delim(delim) {}

    template<typename H, typename... Args>
    void print(const std::string &format, const H &head, const Args &... tail) {
        auto newFormat = doPrint(format, head);
        if (newFormat.length() > 0) {
            print(newFormat, tail...);
        }
    }

    template<typename T>
    void print(const std::string &format, const T &nextArg) {
        auto newFormat = doPrint(format, nextArg);
        *m_out << newFormat;
    }

    void print(const std::string &msg) {
        *m_out << msg;
    }


    friend std::ostream& operator<<(std::ostream& os, const Logger& point);

private:
    std::ostream *m_out;
    const std::string m_delim;

    template<typename T>
    std::string doPrint(const std::string &format, const T &arg) {
        int idx = format.find(m_delim);
        std::string substr;
        std::string newFormat;
        if (idx != std::string::npos) {
            substr = format.substr(0, idx);
            newFormat = format.substr(idx + m_delim.length(), format.length());
        } else {
            substr = format;
            newFormat = "";
        }

        *m_out << substr;
        if (idx != std::string::npos) {
            *m_out << arg;
        }

        return newFormat;
    }

};

std::ostream &operator<<(std::ostream &os, const Logger &point) {
    return os << "Logger";
}
