#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char timestamp[32];
    float cpu_usage;
    long total_mem_kb;
    long free_mem_kb;
    long uptime_sec;
} SystemStats;

void get_timestamp(char *buffer) {
    time_t now = time(NULL);
    strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

float get_cpu_usage() {
    return 15.5;   // placeholder for now
}

void print_stats(SystemStats *stats) {
    float mem_percent = (float)stats->free_mem_kb / stats->total_mem_kb * 100.0;

    printf("[%s] CPU: %.2f%% | Memory: %ld KB free / %ld KB total (%.1f%%) | Uptime: %ld sec\n",
           stats->timestamp, stats->cpu_usage,
           stats->free_mem_kb, stats->total_mem_kb, mem_percent,
           stats->uptime_sec);
}

int main() {
    SystemStats stats;

    printf("Linux System Monitor (Ctrl+C to stop)\n\n");

    while (1) {
        get_timestamp(stats.timestamp);
        stats.cpu_usage = get_cpu_usage();

        FILE *fp = fopen("/proc/meminfo", "r");
        char line[256];
        if (fp) {
            while (fgets(line, sizeof(line), fp)) {
                if (strncmp(line, "MemTotal:", 9) == 0)
                    sscanf(line + 9, "%ld", &stats.total_mem_kb);
                if (strncmp(line, "MemFree:", 8) == 0)
                    sscanf(line + 8, "%ld", &stats.free_mem_kb);
            }
            fclose(fp);
        }

        fp = fopen("/proc/uptime", "r");
        if (fp) {
            fscanf(fp, "%ld", &stats.uptime_sec);
            fclose(fp);
        }

        print_stats(&stats);     // Correct: pass address with &

        FILE *log = fopen("sysmon.log", "a");
        if (log) {
            fprintf(log, "[%s] CPU: %.2f%% | Mem: %ld/%ld KB | Uptime: %ld sec\n",
                    stats.timestamp, stats.cpu_usage,
                    stats.free_mem_kb, stats.total_mem_kb, stats.uptime_sec);
            fclose(log);
        }

        sleep(2);
    }

    return 0;
}
