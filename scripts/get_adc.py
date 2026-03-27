import time
import serial
import matplotlib.pyplot as plt

def read_value(ser):
    while True:
        try:
            line = ser.readline().decode('ascii').strip()
            if line:
                value = float(line)
                return value
        except:
            continue

def main():
    port_name = 'COM4'
    
    ser = serial.Serial(port=port_name, baudrate=115200, timeout=0.0)
    
    if ser.is_open:
        print(f"Порт {ser.name} открыт")
    else:
        print(f"Порт {ser.name} закрыт")
        return
    
    measure_temperature_C = []
    measure_voltage_V = []
    measure_ts = []
    
    start_ts = time.time()
    
    try:
        print("\nНачинаю сбор данных...")
        print("Нажми Ctrl+C для остановки и построения графика\n")
        
        while True:
            ts = time.time() - start_ts
            
            ser.write("get_adc\n".encode('ascii'))
            voltage_V = read_value(ser)
            
            ser.write("get_temp\n".encode('ascii'))
            temp_C = read_value(ser)
            
            measure_ts.append(ts)
            measure_voltage_V.append(voltage_V)
            measure_temperature_C.append(temp_C)
            
            print(f"{voltage_V:.3f} V | {temp_C:.1f} °C | {ts:.2f} с")
            
            time.sleep(0.1)
            
    except KeyboardInterrupt:
        print("\n\nСбор данных остановлен. Строю график...")
        
    finally:
        ser.close()
        print("Порт закрыт")
        
        if len(measure_ts) > 0:
            plt.figure(figsize=(10, 8))
            
            plt.subplot(2, 1, 1)
            plt.plot(measure_ts, measure_voltage_V, 'b-', linewidth=1)
            plt.title('График зависимости напряжения от времени')
            plt.xlabel('время, с')
            plt.ylabel('напряжение, В')
            plt.grid(True)
            
            plt.subplot(2, 1, 2)
            plt.plot(measure_ts, measure_temperature_C, 'r-', linewidth=1)
            plt.title('График зависимости температуры от времени')
            plt.xlabel('время, с')
            plt.ylabel('температура, °C')
            plt.grid(True)
            
            plt.tight_layout()
            plt.show()
        else:
            print("Нет данных для построения графика")

if __name__ == "__main__":
    main()