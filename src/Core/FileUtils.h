#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

class FileUtils
{
public:
    static bool FindDir(const char *name, const char *path = ".");
    static void CreateDir(const char *name, const char *path = ".");
    static char *GetEnv(const char *name);
    static void SetEnv(const char *name, const char *value);
    static void UnsetEnv(const char *name);
    void SetFile(char * ciao, int parm);

    static const std::string CurrentDateTime();
};


#endif // FILEUTILS_H

