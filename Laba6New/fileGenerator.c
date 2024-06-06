#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define JULIAN_DAY_START 15020.0

struct index_s
{
    double time_mark;
    uint64_t recno;
};

double random_double(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double generate_time_mark(double max_julian_date)
{
    double integerDayPart = JULIAN_DAY_START + rand() % ((int)max_julian_date - (int)JULIAN_DAY_START);
    double fractional_day = random_double(0.0, 0.999999);
    return integerDayPart + fractional_day;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Неверные параметры");
        return EXIT_FAILURE;
    }

    size_t amountOfRecords = atoi(argv[1]);
    amountOfRecords = ((amountOfRecords + 255) / 256) * 256;
    char *filename = argv[2];

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    srand(getpid());
    for (size_t i = 0; i < amountOfRecords; i++)
    {
        struct index_s record = {
            .time_mark = generate_time_mark(60435),
            .recno = i + 1};
        printf("%ld : %lf\n", record.recno, record.time_mark);
        fwrite(&record, sizeof(struct index_s), 1, file);
    }

    fclose(file);

    printf("Файл с %zu записями был сгенерирован успешно: %s\n", amountOfRecords, filename);

    return EXIT_SUCCESS;
}