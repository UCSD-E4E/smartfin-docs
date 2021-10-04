import numpy as np
import matplotlib.pyplot as plt
from typing import List

TMP116_CAL_ATTEMPTS_TOTAL = 15

TMP116_CAL_CYCLE_PERIOD_SEC = 60

TMP116_CAL_DATA_COLLECTION_PERIOD_SEC = 5

START_TIME_S = 300

temperature_levels = [25, 20, 15, 10, 5, 15]

temperature_times_h = [0, 3, 6, 9, 12, 15, 18]

transition_time_h = 0.5
if __name__ == '__main__':
    temperature_segments: List[float] = []
    temperature_times: List[float] = []

    cal_start_times_s = np.arange(
        TMP116_CAL_ATTEMPTS_TOTAL) * TMP116_CAL_CYCLE_PERIOD_SEC + START_TIME_S

    cal_times = []

    cal_time_offsets = np.arange(TMP116_CAL_DATA_COLLECTION_PERIOD_SEC)
    for i in cal_start_times_s:
        for j in cal_time_offsets:
            cal_times.append(i + j)

    cal_times_h = np.array(cal_times) / 60 / 60

    for i in range(len(temperature_levels)):
        # start point
        temperature_segments.append(temperature_levels[i])
        temperature_times.append(temperature_times_h[i])

        # end point
        temperature_segments.append(temperature_levels[i])
        temperature_times.append(temperature_times_h[i+1] - 0.5)

    cal_temps = []
    for cal_time in cal_times_h:
        for i in range(len(temperature_levels)):
            if cal_time >= temperature_times_h[i] and \
                    cal_time < temperature_times_h[i+1] - transition_time_h:
                cal_temps.append(temperature_levels[i])
            elif cal_time >= temperature_times_h[i+1] - transition_time_h and \
                    cal_time < temperature_times_h[i+1]:
                time_interval = [temperature_times_h[i+1] - transition_time_h,
                                 temperature_times_h[i+1]]
                temp_interval = [temperature_levels[i],
                                 temperature_levels[i + 1]]
                cal_temps.append(
                    np.interp(cal_time, time_interval, temp_interval))
            else:
                pass

    plt.plot(temperature_times, temperature_segments)
    plt.scatter(cal_times_h, cal_temps)
    plt.xlabel('Time (h) since procedure start')
    plt.ylabel('Temperature (C)')
    plt.title("Temperature Calibration Plot")
    plt.grid()
    plt.savefig('temperature_plot.png')
