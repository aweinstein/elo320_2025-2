#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long time;
    float power;
} data;

int main(void)
{
    FILE *fp;
    char line[128];
    data *records = NULL;
    size_t count = 0;
    size_t capacity = 0;

    fp = fopen("data_power_64040.csv", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Skip header line
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "File is empty or unreadable\n");
        fclose(fp);
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        long t;
        float p;

        // Try to parse two values from each line
        if (sscanf(line, "%ld,%f", &t, &p) == 2) {
            // Resize array if necessary
            if (count >= capacity) {
                capacity = (capacity == 0) ? 10 : capacity * 2;
                data *tmp = realloc(records, capacity * sizeof(data));
                if (tmp == NULL) {
                    perror("Memory allocation failed");
                    free(records);
                    fclose(fp);
                    return 1;
                }
                records = tmp;
            }
            records[count].time = t;
            records[count].power = p;
            count++;
        }
    }

    fclose(fp);

    // Print first 10 and last 10 data points to confirm reading
    printf("First 10 data points:\n");
    for (size_t i = 0; i < 10; i++) {
        printf("time: %ld, power: %.3f\n", records[i].time, records[i].power);
    }
    printf("Last 10 data points:\n");
    for (size_t i = count - 10; i < count; i++) {
        printf("time: %ld, power: %.3f\n", records[i].time, records[i].power);
    }

    free(records);
    return 0;
}
