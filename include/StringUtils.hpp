#include <string>

namespace StringUtils {
	std::string toUpperCase(std::string& str) {
		int i;
		while(str[i]) {
			str[i] = toupper(str[i]);
			i++;
		}
		return str; // Function edits reference, but return it method is used differently
	}
}