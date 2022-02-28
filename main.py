import serial
import signal
import time
from datetime import datetime

SLEEP_SECONDS = 1


def ctrl_c_handler(signal, frame):
    print('Goodbye!')
    exit()


def UpdateChar(d1, d2, d3, d4, d5, d6, d7, d8):
    sendString = "%d,%d,%d,%d,%d,%d,%s,%s,\n" % (d1, d2, d3, d4, d5, d6, d7, d8)
    print ("%d,%d,%d,%d,%d,%d,%s,%s,\n" % (d1, d2, d3, d4, d5, d6, d7, d8))
    ser.write(sendString.encode())


def main():
    global ser
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=10)

    while True:
        now = datetime.now()
        time_c = now.strftime("%H%M%S")
        time_list = []
        time_list[:] = time_c
        #print (time_list)
        # time_h = int(current_time_h)
        # current_time_m = now.strftime("%M")
        # time_m = int(current_time_m)
        # current_time_s = now.strftime("%S")
        # time_s = int(current_time_s)

        segment = {1: '', 2: '', 3: '', 4: '', 5: '', 6: '', 7: '', 8: ''}
        s = 1
        for i in time_list:
            segment[s] = i
            s += 1
        print (segment)

        d1 = int(segment[1])
        d2 = int(segment[2])
        d3 = int(segment[3])
        d4 = int(segment[4])
        d5 = int(segment[5])
        d6 = int(segment[6])
        d7 = (segment[7])
        d8 = (segment[8])

        UpdateChar(d1, d2, d3, d4, d5, d6, d7, d8)
        time.sleep(SLEEP_SECONDS)
    exit()


if __name__ == '__main__':
    signal.signal(signal.SIGINT, ctrl_c_handler)
    main()
