#include <stdio.h>
#include <winbase.h>

void main() {
	int dbport = GetPrivateProfileInt("database", "port", 143, ".\\dbsettings.ini");
}