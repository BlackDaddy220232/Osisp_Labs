#include"dirwalk.h"

int main(int argc, char *argv[]) {
    char *dir;
    int options = 0; // Default options: выводить все (каталоги, файлы, символические ссылки)

    process_options(argc, argv, &dir, &options);
    dirwalk(dir, options);

    return 0;
}
