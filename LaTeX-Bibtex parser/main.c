
#include <stdio.h>
#include <string.h>
#include <regex.h>



int main ()
{
    char * source = "(cite)";
    char * regexString = "The initial SA approaches were designed to increase the system resolution enlarging the size of the SA using a moving transducer. For example, an aircraft was used to carry an antenna in synthetic aperture radar (SAR) applications cite{Moreira2013}, or a single ultrasonic probe operating in pulse/echo mode, moved using a mechanical scanner, was used in the SAFT applied for NDT using bulk cite{Ylitalo1994} and Lamb waves cite{Sicard2004,Dobie2013}.";
    size_t maxMatches = 2;
    size_t maxGroups = 3;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    unsigned int m;
    char * cursor;
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Could not compile regular expression.\n");
        return 1;
    };
    
    m = 0;
    cursor = source;
    for (m = 0; m < maxMatches; m ++)
    {
        if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
            break;  // No more matches
        
        unsigned int g = 0;
        unsigned int offset = 0;
        for (g = 0; g < maxGroups; g++)
        {
            if (groupArray[g].rm_so == (size_t)-1)
                break;  // No more groups
            
            if (g == 0)
                offset = groupArray[g].rm_eo;
            
            char cursorCopy[strlen(cursor) + 1];
            strcpy(cursorCopy, cursor);
            cursorCopy[groupArray[g].rm_eo] = 0;
            printf("Match %u, Group %u: [%2u-%2u]: %s\n",
                   m, g, groupArray[g].rm_so, groupArray[g].rm_eo,
                   cursorCopy + groupArray[g].rm_so);
        }
        cursor += offset;
    }
    
    regfree(&regexCompiled);
    
    return 0;
}
