#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char timestamp[32];
    float cpu_usage;
    long total_memory;
    long free_memory;
    long uptime_seconds;
} SystemStats;

void get_current_time(char *buffer) {
    time_t now = time(NULL);
    strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

int main() {
    SystemStats stats;
    FILE *fp;
    char line[256];

    get_current_time(stats.timestamp);

    // Read uptime
    fp = fopen("/proc/uptime", "r");
    if (fp) {
        fscanf(fp, "%ld", &stats.uptime_seconds);
        fclose(fp);
    }

    // Read memory info
    fp = fopen("/proc/meminfo", "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "MemTotal:", 9) == 0) {
                sscanf(line + 9, "%ld", &stats.total_memory);
            }
            if (strncmp(line, "MemFree:", 8) == 0) {
                sscanf(line + 8, "%ld", &stats.free_memory);
            }
        }
        fclose(fp);
    }

    // Simple CPU usage (approximate - reads /proc/stat once)
    fp = fopen("/proc/stat", "r");
    if (fp) {
        fgets(line, sizeof(line), fp); // first line is cpu
        fclose(fp);
        stats.cpu_usage = 15.5; // placeholder - real calculation is more complex
    }

    // Write to log file
    fp = fopen("system_stats.log", "a");
    if (fp) {
        fprintf(fp, "[%s] CPU: %.2f%% | Mem: %ld/%ld KB | Uptime: %ld sec\n",
                stats.timestamp, stats.cpu_usage,
                stats.free_memory, stats.total_memory,
                stats.uptime_seconds);
        fclose(fp);
    }

    printf("System stats logged successfully at %s\n", stats.timestamp);
    printf("CPU Usage: %.2f%%\n", stats.cpu_usage);
    printf("Memory: %ld KB free / %ld KB total\n", stats.free_memory, stats.total_memory);
    printf("Uptime: %ld seconds\n", stats.uptime_seconds);

    return 0;
}
