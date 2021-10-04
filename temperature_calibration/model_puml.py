import numpy as np
import matplotlib.pyplot as plt
from typing import List

TMP116_CAL_ATTEMPTS_TOTAL = 3

TMP116_CAL_CYCLE_PERIOD_SEC = 60

TMP116_CAL_DATA_COLLECTION_PERIOD_SEC = 15

START_TIME_S = 0

MEASUREMENT_TIME = 0.8

WIDTH = 800

if __name__ == '__main__':
    cal_start_times_s = np.arange(
        TMP116_CAL_ATTEMPTS_TOTAL) * TMP116_CAL_CYCLE_PERIOD_SEC + START_TIME_S

    cal_times = []

    cal_time_offsets = np.arange(TMP116_CAL_DATA_COLLECTION_PERIOD_SEC)
    for i in cal_start_times_s:
        for j in cal_time_offsets:
            cal_times.append(i + j)

    span = max(cal_times) - min(cal_times)
    print(cal_times)

    with open('model.puml', 'w') as fstream:
        fstream.write('@startuml Temperature Calibration Timeline\n')
        fstream.write(f'scale {1} as {int(WIDTH / span)} pixels\n')
        fstream.write('concise "Activity" as SF\n')
        for cal_time in cal_times:
            fstream.write(f'@{cal_time}\n')
            fstream.write('SF is Measure\n')
            
            fstream.write(f'@{cal_time + MEASUREMENT_TIME}\n')
            fstream.write('SF is {-}\n')
        fstream.write('@enduml\n')
