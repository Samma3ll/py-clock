import time, signal, serial
from datetime import datetime
import psutil
import GPUtil


SLEEP_SECONDS = 1

def ctrl_c_handler(signal, frame):
    print('Goodbye!')
    exit()

def UpdateTime(dial1, dial2, dial3):
    sendString = "%d,%d,%d,\n" % (dial1, dial2, dial3)
    print ("%d,%d,%d,\n" % (dial1, dial2, dial3))
    ser.write(sendString.encode())

def main():

    global ser
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=10)

    #exit()
    while True:
        #UpdateGauges(cpu_usage(), memory_usage(), gpu_usage(), gpu_mem())
        #UpdateGauges(100, 100, 100, 100)
        now = datetime.now()
        current_time_h = now.strftime("%H")
        time_h = int(current_time_h)
        current_time_m = now.strftime("%M")
        time_m = int(current_time_m)
        current_time_s = now.strftime("%S")
        time_s = int(current_time_s)
        UpdateTime(time_h, time_m, time_s)
        time.sleep(SLEEP_SECONDS)
    exit()


if __name__ == '__main__':
    signal.signal(signal.SIGINT, ctrl_c_handler)
    main()