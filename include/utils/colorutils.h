/**
 * @file colorutils.h
 * @brief Set of macros containing ANSI color escape codes
 *
 */

#ifndef UTILS_COLOR_H
#define UTILS_COLOR_H
#define COLOR_RESET "\033[0m"

#define COLOR_BLACK  "\033[0;30m"
#define COLOR_RED    "\033[0;31m"
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE   "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN   "\033[0;36m"
#define COLOR_WHITE  "\033[0;37m"

#define COLOR_BLACK_BOLD  "\033[1;30m"
#define COLOR_RED_BOLD    "\033[1;31m"
#define COLOR_GREEN_BOLD  "\033[1;32m"
#define COLOR_YELLOW_BOLD "\033[1;33m"
#define COLOR_BLUE_BOLD   "\033[1;34m"
#define COLOR_PURPLE_BOLD "\033[1;35m"
#define COLOR_CYAN_BOLD   "\033[1;36m"
#define COLOR_WHITE_BOLD  "\033[1;37m"

#define COLOR_BLACK_UNDERLINED  "\033[4;30m"
#define COLOR_RED_UNDERLINED    "\033[4;31m"
#define COLOR_GREEN_UNDERLINED  "\033[4;32m"
#define COLOR_YELLOW_UNDERLINED "\033[4;33m"
#define COLOR_BLUE_UNDERLINED   "\033[4;34m"
#define COLOR_PURPLE_UNDERLINED "\033[4;35m"
#define COLOR_CYAN_UNDERLINED   "\033[4;36m"
#define COLOR_WHITE_UNDERLINED  "\033[4;37m"

#define COLOR_BLACK_BRIGHT  "\033[0;90m"
#define COLOR_RED_BRIGHT    "\033[0;91m"
#define COLOR_GREEN_BRIGHT  "\033[0;92m"
#define COLOR_YELLOW_BRIGHT "\033[0;93m"
#define COLOR_BLUE_BRIGHT   "\033[0;94m"
#define COLOR_PURPLE_BRIGHT "\033[0;95m"
#define COLOR_CYAN_BRIGHT   "\033[0;96m"
#define COLOR_WHITE_BRIGHT  "\033[0;97m"

#define COLOR_BLACK_BOLD_BRIGHT  "\033[1;90m"
#define COLOR_RED_BOLD_BRIGHT    "\033[1;91m"
#define COLOR_GREEN_BOLD_BRIGHT  "\033[1;92m"
#define COLOR_YELLOW_BOLD_BRIGHT "\033[1;93m"
#define COLOR_BLUE_BOLD_BRIGHT   "\033[1;94m"
#define COLOR_PURPLE_BOLD_BRIGHT "\033[1;95m"
#define COLOR_CYAN_BOLD_BRIGHT   "\033[1;96m"
#define COLOR_WHITE_BOLD_BRIGHT  "\033[1;97m"

#define COLOR_BLACK_BACKGROUND  "\033[40m"
#define COLOR_RED_BACKGROUND    "\033[41m"
#define COLOR_GREEN_BACKGROUND  "\033[42m"
#define COLOR_YELLOW_BACKGROUND "\033[43m"
#define COLOR_BLUE_BACKGROUND   "\033[44m"
#define COLOR_PURPLE_BACKGROUND "\033[45m"
#define COLOR_CYAN_BACKGROUND   "\033[46m"
#define COLOR_WHITE_BACKGROUND  "\033[47m"

#define COLOR_BLACK_BACKGROUND_BRIGHT  "\033[0;100m"
#define COLOR_RED_BACKGROUND_BRIGHT    "\033[0;101m"
#define COLOR_GREEN_BACKGROUND_BRIGHT  "\033[0;102m"
#define COLOR_YELLOW_BACKGROUND_BRIGHT "\033[0;103m"
#define COLOR_BLUE_BACKGROUND_BRIGHT   "\033[0;104m"
#define COLOR_PURPLE_BACKGROUND_BRIGHT "\033[0;105m"
#define COLOR_CYAN_BACKGROUND_BRIGHT   "\033[0;106m"
#define COLOR_WHITE_BACKGROUND_BRIGHT  "\033[0;107m"

#endif // UTILS_COLOR_H
