#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device

struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short type;  // Type of file 1- dir, 2 -file 3- executable
  short nlink; // Number of links to file
  uint64 size; // Size of file in bytes
};
