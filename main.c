#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int main(void)
{
  int fd0 = aOpen("a.txt", ARW_MODE);
  aWrite(fd0, "In computing, a file system or filesystem (often abbreviated to fs) controls how data is stored and retrieved. Without a file system, data placed in a storage medium would be one large body of data with no way to tell where one piece of data stops and the next begins. By separating the data into pieces and giving each piece a name, the data is easily isolated and identified. Taking its name from the way paper-based data management system is named, each group of data is called a file. The structure and logic rules used to manage the groups of data and their names is called a file system. There are many different kinds of file systems. Each one has different structure and logic, properties of speed, flexibility, security, size and more. Some file systems have been designed to be used for specific applications. For example, the ISO 9660 file system is designed specifically for optical discs. File systems can be used on numerous different types of storage devices that use different kinds of media. As of 2019, hard disk drives have been key storage devices and are projected to remain so for the foreseeable future.[1] Other kinds of media that are used include SSDs, magnetic tapes, and optical discs. In some cases, such as with tmpfs, the computer's main memory (random-access memory, RAM) is used to create a temporary file system for short-term use. Some file systems are used on local data storage devices;[2] others provide file access via a network protocol (for example, NFS,[3] SMB, or 9P clients). Some file systems are virtual, meaning that the supplied files (called virtual files) are computed on request (such as procfs and sysfs) or are merely a mapping into a different file system used as a backing store. The file system manages access to both the content of files and the metadata about those files. It is responsible for arranging storage space; reliability, efficiency, and tuning with regard to the physical storage medium are important design considerations.\n", 1994);
  aWrite(fd0, "Despite the ubiquity of APFS volumes in today's Macs and the format's 2016 introduction, third-party repair utilities continue to have notable limitations in supporting APFS volumes, due to Apple's delayed release of complete documentation. According to Alsoft, the maker of DiskWarrior, Apple's 2018 release of partial APFS format documentation has delayed the creation of a version of DiskWarrior that can safely rebuild APFS disks.[32] Competing products, including MicroMat's TechTool and Prosoft's Drive Genius, are expected to increase APFS support as well. Paragon Software Group has published a software development kit under the 4-Clause BSD License that supports read-only access of APFS drives.[33] An independent read-only open source implementation by Joachim Metz, libfsapfs, is released under GNU Lesser General Public License v3. It has been packaged into Debian and Ubuntu software repositories.[34] Both are command-line tools that do not expose a normal filesystem driver interface. There is a Filesystem in Userspace (FUSE) driver for Linux called apfs-fuse with read-only access.[35] An APFS for Linux project is working to integrate APFS support into the Linux kernel.", 1190);

  int fd1 = aOpen("b.txt", ARW_MODE);
  aWrite(fd1, "file2 content", 13);

  char *buffer = calloc(3500, 1);

  aResetOffset(fd1);
  aRead(fd1, buffer, 13);
  printf("%s\n", buffer);
  aClose(fd1);

  aResetOffset(fd0);
  aRead(fd0, buffer, 3184);
  printf("%s\n", buffer);
  aClose(fd0);

  fd0 = aOpen("a.txt", AW_MODE);
  aWrite(fd0, "over written content", 20);
  aClose(fd0);

  fd1 = aOpen("b.txt", ARW_MODE);
  aWrite(fd1, "Since macOS High Sierra, all devices with flash storage are automatically converted to APFS.[25] FileVault volumes are also converted. As of macOS Mojave, Fusion Drives and hard disk drives are also upgraded on installation.[26] The primary user interface to upgrade does not present an option to opt out of this conversion, and devices formatted with the High Sierra version of APFS will not be readable in previous versions of macOS.[25] Users can disable APFS conversion by using the installer's startosinstall utility on the command line and passing --converttoapfs NO. An experimental version of APFS, with some limitations, is available in macOS Sierra through the command line diskutil utility. Among these limitations, it does not perform Unicode normalization while HFS+ does,[28] leading to problems with languages other than English.[29] Drives formatted with Sierra’s version of APFS may also not be compatible with future versions of macOS or the final version of APFS, and the Sierra version of APFS cannot be used with Time Machine, FileVault volumes, or Fusion Drives.", 1084);
  aWrite(fd1, "file2 content2", 14);

  int fd2 = aOpen("c.txt", AW_MODE);
  aWrite(fd2, "Hello World!", 12);
  aClose(fd2);

  fd0 = aOpen("a.txt", AR_MODE);
  fd1 = aOpen("b.txt", AR_MODE);
  fd2 = aOpen("c.txt", AR_MODE);

  char *buff1 = calloc(3500, 1);
  aRead(fd0, buff1, 3184);
  printf("%s\n", buff1);

  char *buff2 = calloc(1500, 1);
  aRead(fd1, buff2, 1111);
  printf("%s\n", buff2);

  char *buff4 = calloc(50, 1);
  aRead(fd2, buff4, 12);
  printf("%s\n", buff4);

  aClose(fd0);
  aClose(fd1);
  aClose(fd2);

  return 0;
}
