#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int tempconv()
{
    char *Celsius = NULL;
    size_t len = 0;
    long double Fahrenheit;
    regex_t regex;
    regmatch_t match[1];
    char *p;
    // Compile the regex
    if (regcomp(&regex, "[0-9]+", REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex\n");
        return 1;
    }
    printf("Enter Celsius to Convert to Fahrenheit (or 'q' to quit): ");
    getline(&Celsius, &len, stdin);
    // Remove the newline character at the end of the input
    Celsius[strcspn(Celsius, "\n")] = 0;
    // Check if the input is "q" or "Q"
    int quit = strcmp(Celsius, "q") == 0 || strcmp(Celsius, "Q") == 0;
    switch (quit)
    {
    case 1:
        free(Celsius);
        regfree(&regex);
        return 0;
    default:
        // Find all numbers in the input string
        p = Celsius;
        while (regexec(&regex, p, 1, match, 0) == 0)
        {
            // Extract the number and convert it to a long double
            char *numstr = strndup(p + match[0].rm_so, match[0].rm_eo - match[0].rm_so);
            Fahrenheit = strtold(numstr, NULL) * 9 / 5 + 32;
            // Print the Celsius
            printf("%s Celsius is ", numstr);
            free(numstr);
            // Print the Fahrenheit value
            printf("%Lf Fahrenheit\n", Fahrenheit);
            // Move the start position to the end of the current match
            p += match[0].rm_eo;
        }
        // Recursive call
        tempconv();
    }
    return 0;
}

int main()
{
    tempconv();
}