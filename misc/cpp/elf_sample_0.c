#include <fcntl.h> // for open
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> // for close

void main(int argc, char **argv) {
  Elf *elf;
  Elf_Scn *scn = NULL;
  GElf_Shdr shdr;
  Elf_Data *data;
  int fd, ii, count;

  elf_version(EV_CURRENT);

  fd = open(argv[1], O_RDONLY);
  elf = elf_begin(fd, ELF_C_READ, NULL);

  while ((scn = elf_nextscn(elf, scn)) != NULL) {
    gelf_getshdr(scn, &shdr);
    if (shdr.sh_type == SHT_SYMTAB) {
      /* found a symbol table, go print it. */
      break;
    }
  }

  data = elf_getdata(scn, NULL);
  count = shdr.sh_size / shdr.sh_entsize;

  /* print the symbol names */
  for (ii = 0; ii < count; ++ii) {
    GElf_Sym sym;
    gelf_getsym(data, ii, &sym);
    printf("%s\n", elf_strptr(elf, shdr.sh_link, sym.st_name));
  }
  elf_end(elf);
  close(fd);
}

// Printing the ELF Symbol Table
// ./a.out <elf binary>
// gcc elf_sample_0.c -l elf
// clang-format elf_sample_0.c -i
