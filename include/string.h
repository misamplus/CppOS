/**
 * The string simulation!
 *
 * @package CppOS
 * @since CppOS 1.05
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

size_t strlen(const char* str) {
	size_t ret = 0;
	while (str[ret] != 0) ret++;
	return ret;
}