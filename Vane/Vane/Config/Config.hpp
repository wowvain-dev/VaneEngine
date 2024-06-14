#pragma once

#include <mutex>
#include <array>
#include <string>


#include "CVar.hpp"

namespace Vane {
class Config {
private:
    static Config *s_Instance;
    static std::mutex s_Mutex;



public:
    Config(Config &other) = delete;
    void operator =(const Config &) = delete;

    static Config *GetInstance();


    CVarString m_resourcePath{"resource_path", "Resources"};

    /**
     * \brief Use the Filesystem to read the file, then call ProcessFile to parse
     * the file and set the configuration variables
     * 
     * \param filePath of the configuration file
     */
    void Read(const std::string_view &filePath);

    /**
     * \brief Process the content passed in by removing the comments,
     * ignoring whitespace (keeps string whitespace in values, not keys), check
     * for valid lines, set the CVar values
     * 
     * \param contentBuffer what will be processed into the CVars
     */
    void ProcessFile(const char *contentBuffer);

    void SetVal(const std::string &key, const std::string_view &value);
    std::vector<std::string_view> GetCommands() const;

protected:
    ~Config() = default;

private:
    Config() = default;
    class CVarRegistry cvarsRegistry;

    /**
     * \brief Removes comments (any characters followed by '#') and
     * carriage returns ('\r')
     * 
     * \param line a mutable string
     */
    void RemoveComments(std::string* line) const;

    /**
     * \brief Checks if the line is valid, doesn't have multiple equal signs
     * 
     * \param line should be a single line (only 1 carriage return)
     * \return true if the line is valid
     * \return false if the line has errors
     */
    bool OnlyWhitespace(const std::string_view &line) const;

    /**
     * \brief Checks if the line is valid, doesn't have multiple equal signs
     * 
     * \param line should be a single line (only 1 carriage return)
     * \return true if the line is valid
     * \return false if the line has errors
     */
    bool ValidLine(const std::string_view &line) const;

    /**
     * \brief Extracts the key from the string (key is before the '=')
     * 
     * \param key passed by reference value of the key
     * \param sepPos position of the '=' in the line 
     * \param line the string which holds key/value pair
     */
    void ExtractKey(std::string *key, const u_size &sepPos,
                    const std::string_view line);

    /**
     * \brief Extracts the value from the string (value is after '=')
     * 
     * \param value passed by reference value of the value
     * \param sepPos position of the '=' in the line
     * \param line the string which holds key/value pair
     */
    void ExtractValue(std::string *value, const u_size &sepPos,
                      const std::string_view line);
};
};
