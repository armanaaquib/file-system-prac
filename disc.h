#ifndef __DISC_H_
#define __DISC_H_

void write_to_disc(int offset, char *buffer, int size);
void read_from_disc(int offset, char *buffer, int size);

#endif