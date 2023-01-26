#include "stringutils.h"

StringUtils::StringUtils()
{

}

QString StringUtils::toTitle(QString s) {
    int i = 0;
    while (i < s.size()) {
        if (s[i].isLetter()) {
            s[i] = s[i].toUpper();
            ++i;
            while (i < s.size() && s[i].isLetter()) {
                s[i] = s[i].toLower();
                ++i;
            }
        } else {
            ++i;
        }
    }
    return s;
}
