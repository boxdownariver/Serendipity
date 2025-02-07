#include <string>
#include <vector>

#ifndef menu_lines_struct
#define menu_lines_struct
struct MenuLines {
	std::string menuName;
	std::vector<std::string> menuLines;
	std::string storeName = "Serendipity Booksellers";
};
#endif

#ifndef make_menu
#define make_menu
int makeMenu(MenuLines &);
#endif
