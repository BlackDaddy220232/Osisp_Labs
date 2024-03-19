#include"dirwalk.h"
int compare_wrapper(const void *a, const void *b) {
    const struct dirent **dir_a = (const struct dirent **)a;
    const struct dirent **dir_b = (const struct dirent **)b;
    return compare(dir_a, dir_b);
}

int compare(const struct dirent **a, const struct dirent **b) {
    return strcoll((*a)->d_name, (*b)->d_name);
}

void print_entry(const char *path, int options) {
    struct stat statbuf;

    if (stat(path, &statbuf) == -1) {
        fprintf(stderr, "Cannot access file: %s\n", path);
        return;
    }

    int is_dir = S_ISDIR(statbuf.st_mode);
    int is_link = S_ISLNK(statbuf.st_mode);
    int is_file = S_ISREG(statbuf.st_mode);

    if(((options & 4) && is_file)||((options & 2) && is_dir)||((options & 1) && is_link))
    {
        printf("%s\n", path);
    }
}

void dirwalk(const char *dir, int options) {
    struct dirent **namelist;
    int count = scandir(dir, &namelist, NULL, NULL);

    if (count == -1) {
        fprintf(stderr, "Cannot open directory: %s\n", dir);
        return;
    }

    if (options & 8) {
        qsort(namelist, count, sizeof(struct dirent *), compare_wrapper);
    }

    for (int i = 0; i < count; i++) {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", dir, namelist[i]->d_name);

        if (strcmp(namelist[i]->d_name, ".") == 0 || strcmp(namelist[i]->d_name, "..") == 0) {
            free(namelist[i]);
            continue;
        }

        print_entry(path, options);

        if (namelist[i]->d_type == DT_DIR) {
            dirwalk(path, options);
        }

        free(namelist[i]);
    }

    free(namelist);
}
void process_options(int argc, char *argv[], char **dir, int *options) {
    int c;

    while ((c = getopt_long(argc, argv, "ldfs", NULL, NULL)) != -1) {
        switch (c) {
            case 'l':
                *options |= 1; // Установить опцию символических ссылок
                break;
            case 'd':
                *options |= 2; // Установить опцию каталогов
                break;
            case 'f':
                *options |= 4; // Установить опцию файлов
                break;
            case 's':
                *options |= 8; // Установить опцию сортировки
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        *dir = argv[optind];
    } else {
        *dir = "./"; // Установка текущей директории по умолчанию
    }
}
