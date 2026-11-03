#ifndef FILE_H
#define FILE_H    // again written so no one can add it two times by mistake in main file.c

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
