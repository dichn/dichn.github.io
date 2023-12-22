#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  elf_version(EV_CURRENT);
  int fd = open("/home/dichen/src/sinfonie/cpp/hello", O_RDONLY);
  Elf *elf;
  elf = elf_begin(fd, ELF_C_READ, NULL);
  size_t phnum;
  elf_getphdrnum(elf, &phnum);
  printf("phnum: %zu \n", phnum);
  // no idea what's this class used for.
  int class = gelf_getclass(elf);
  for (size_t i = 0; i < phnum; ++i) {
    GElf_Phdr phdr_mem;
    GElf_Phdr *phdr = gelf_getphdr(elf, i, &phdr_mem);
    printf("phdr->p_type: %zu \n", phdr->p_type);
    if (phdr->p_type == PT_DYNAMIC) {
      printf("Whoa, it's PT_DYNAMIC segment\n");
      Elf_Data *data =
          elf_getdata_rawchunk(elf, phdr->p_offset, phdr->p_filesz, ELF_T_DYN);

      int dyn_idx = 0;
      for (;; ++dyn_idx) {
        GElf_Dyn dyn_mem;
        /* Dynamic section entry.  */
        GElf_Dyn *dyn = gelf_getdyn(data, dyn_idx, &dyn_mem);
        if (dyn->d_tag == DT_NULL)
          break;
        if (dyn->d_tag == DT_SYMTAB) {
          printf("Hey, it's DT_SYMTAB section\twith d_tag: %d\n", dyn->d_tag);
          unsigned int nsyms =
              data->d_size /
              (class == ELFCLASS32 ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym));
          // the above sym number seems wrong
          printf("[Not sure] Oh, you might have %u symbols, but how can I show "
                 "them.\n",
                 nsyms);
          // TODO/Q how to get data/symbol
        }
        if (dyn->d_tag == DT_GNU_HASH) {
          printf("Hey, it's DT_GNU_HASH section\twith d_tag: %d\n", dyn->d_tag);
          // TODO/Q how to get data/symbol
        }
        if (dyn->d_tag == DT_SYMENT) {
          printf("Hey, it's DT_SYMENT section\twith d_tag: %d\n", dyn->d_tag);
          // TODO/Q how to get data/symbol
        }
      }
      printf("[Trust me] Dynamic section contains %d entries \n ", dyn_idx + 1);
    }
  }
  elf_end(elf);
  close(fd);
  return 0;
}

// gcc print_phdr.c -l elf -o print_phdr

// -D --use-dynamic       Use the dynamic section info when displaying symbols
// how to show the symbols in dynamic section
//
