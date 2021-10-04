#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdarg.h>

#define TMP116_CAL_ATTEMPTS_TOTAL_VAL 8
#define TMP116_CAL_CYCLE_PERIOD_SEC_VAL 4
#define TMP116_CAL_DDATA_COLLECTION_PERIOD_SEC_VAL 2

typedef enum SF_TMP_CAL_NVRAM
{
    TMP116_CAL_ATTEMPTS_TOTAL,
    TMP116_CAL_CYCLE_PERIOD_SEC,
    TMP116_CAL_DDATA_COLLECTION_PERIOD_SEC,
    BOOT_BEHAVIOR,
    SF_TMP_CAL_NVRAM__NELEMS
}SF_TMP_CAL_NVRAM_e;
typedef enum BOOT_BEHAVIOR_
{
    BOOT_BEHAVIOR_NORMAL=0,
    BOOT_BEHAVIOR_TMP_CAL_START=1,
    BOOT_BEHAVIOR_TMP_CAL_CONTINUE=2,
    BOOT_BEHAVIOR_TMP_CAL_END=3,
    BOOT_BEHAVIOR_UPLOAD_REATTEMPT=4,
    BOOT_BEHAVIOR_NOT_SET=255
} BOOT_BEHAVIOR_e;

typedef enum STATES_
{
    STATE_NULL          = 0x0000,
    STATE_DEEP_SLEEP    = 0x0001,
    STATE_SESSION_INIT  = 0x0002,
    STATE_DEPLOYED      = 0x0003,
    STATE_UPLOAD        = 0x0004,
    STATE_CLI           = 0x0005,
    STATE_MFG_TEST      = 0x0006,
    STATE_TMP_CAL       = 0x0007,
    STATE_CHARGE        = 0x0008
}STATES_e;

typedef enum SLEEP_MODE_
{
    SLEEP_MODE_DEEP
}SLEEP_MODE_e;

uint32_t SF_TMP_CAL_NVRAM_data[SF_TMP_CAL_NVRAM__NELEMS];
uint8_t SF_TMP_CAL_NVRAM_init[SF_TMP_CAL_NVRAM__NELEMS] = {0};
int64_t start_ms = 0;

int NVRAM_get(SF_TMP_CAL_NVRAM_e id, uint32_t* pVar);
int NVRAM_set(SF_TMP_CAL_NVRAM_e id, uint32_t val);
void setBootBehavior(BOOT_BEHAVIOR_e boot_behavior);
BOOT_BEHAVIOR_e getBootBehavior(void);
STATES_e TmpCal_run(void);
int64_t millis(void);
void setStartMs(void);
void SystemSleep(SLEEP_MODE_e mode, long seconds);
int SF_OSAL_printf(const char* fmt, ...);

int main(int argc, char const *argv[])
{
    STATES_e state;
    setStartMs();
    printf("Temperature Cal Demo\n");
    setBootBehavior(BOOT_BEHAVIOR_NORMAL);

    NVRAM_set(TMP116_CAL_ATTEMPTS_TOTAL, TMP116_CAL_ATTEMPTS_TOTAL_VAL);
    NVRAM_set(TMP116_CAL_CYCLE_PERIOD_SEC, TMP116_CAL_CYCLE_PERIOD_SEC_VAL);
    NVRAM_set(TMP116_CAL_DDATA_COLLECTION_PERIOD_SEC, TMP116_CAL_DDATA_COLLECTION_PERIOD_SEC_VAL);
    printf("Start at %lu\n", millis());
    state = TmpCal_run();
    printf("Finished in state %d\n", state);
    return 0;
}

int NVRAM_get(SF_TMP_CAL_NVRAM_e id, uint32_t* pVar)
{
    if(SF_TMP_CAL_NVRAM_init[id])
    {
        // Initialized
        *pVar = SF_TMP_CAL_NVRAM_data[id];
        return 0;
    }
    return 1;
}
int NVRAM_set(SF_TMP_CAL_NVRAM_e id, uint32_t val)
{
    SF_TMP_CAL_NVRAM_data[id] = val;
    SF_TMP_CAL_NVRAM_init[id] = 1;
}
void setBootBehavior(BOOT_BEHAVIOR_e boot_behavior)
{
    NVRAM_set(BOOT_BEHAVIOR, boot_behavior);
}

BOOT_BEHAVIOR_e getBootBehavior(void)
{
    uint32_t var;
    if(NVRAM_get(BOOT_BEHAVIOR, &var))
    {
        setBootBehavior(BOOT_BEHAVIOR_NORMAL);
        return BOOT_BEHAVIOR_NORMAL;
    }
    return (BOOT_BEHAVIOR_e) var;
}

STATES_e TmpCal_run(void)
{
    uint32_t burstIdx = 0;
    uint32_t burstLimit;
    int64_t burstStart;
    int64_t nextBurst;
    int64_t burstEnd;
    uint32_t burstTime;

    if(NVRAM_get(TMP116_CAL_ATTEMPTS_TOTAL, &burstLimit))
    {
        return STATE_CLI;
    }
    if(NVRAM_get(TMP116_CAL_CYCLE_PERIOD_SEC, &burstTime))
    {
        return STATE_CLI;
    }
    for(burstIdx = 0; burstIdx < burstLimit; burstIdx++)
    {
        burstStart = millis();
        SF_OSAL_printf("Burst %u at %ld\n", burstIdx, burstStart);
        nextBurst = burstStart + burstTime * 1e3;
        // start burst
        // end burst
        burstEnd = millis();
        SystemSleep(SLEEP_MODE_DEEP, (nextBurst - burstEnd) / 1e3);
    }
    return STATE_CLI;
}

int64_t millis(void)
{
    struct timeval now;
    uint64_t ms;
    gettimeofday(&now, NULL);
    ms = now.tv_sec * 1e3;
    ms += now.tv_usec / 1e3;
    return ms - start_ms;
    
}
void setStartMs(void)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    start_ms = now.tv_sec * 1e3;
    start_ms += now.tv_usec / 1e3;
}

void SystemSleep(SLEEP_MODE_e mode, long seconds)
{
    int64_t startTime = millis();
    int64_t endTime = startTime + seconds * 1e3;
    while(millis() < endTime)
    {

    }
}

char SF_OSAL_printfBuffer[1024];

int SF_OSAL_printf(const char* fmt, ...)
{
    va_list vargs;
    int nBytes = 0;
    va_start(vargs, fmt);
    nBytes = vsnprintf(SF_OSAL_printfBuffer, 1024, fmt, vargs);
    va_end(vargs);
    printf(SF_OSAL_printfBuffer);
    return nBytes;
}