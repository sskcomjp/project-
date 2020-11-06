import sensor
import image
import lcd
import KPU as kpu
import json
import time
#from modules import ws2812
from machine import UART
from fpioa_manager import fm

#シリアル通信設定
fm.register(35, fm.fpioa.UART1_TX, force=True)
fm.register(34, fm.fpioa.UART1_RX, force=True)
uart = UART(UART.UART1,115200 ,8,0,0, timeout=1000, read_buf_len=409)
serial_judg=0


lcd.init()
#カメラ設定
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(True) # カメラ上下反転
sensor.run(1)



#YOLO初期化
task = kpu.load(0x300000) # you need put model(face.kfpkg) in flash at address 0x300000
#task = kpu.load("/sd/kmodel/model.kmodel")

anchor = (0.57273, 0.677385, 1.87446, 2.06253, 3.33843, 5.47434, 7.88282, 3.52778, 9.77052, 9.162828)
a = kpu.init_yolo2(task, 0.5, 0.3, 5, anchor)


while(True):
    distance = 0;
    distance_judg=255;
    #width=0
    img = sensor.snapshot()
    #img = img.resize(224,224)
    #img.pix_to_ai()

    code = kpu.run_yolo2(task, img)







    if code:

        uart.write('6')


        for i in code:


                data = json.loads(json.dumps(i)) #座標データを取得
                x_Coordinate = data['x']
                y_Coordinate = data['y']
                width = data['w']
                height = data['h']
                print('幅',end='')
                print(width,end='')
                print('高さ',end='')
                print(height-30)
                #print(i)

                #距離計測
                distance=round(3.5-0.024*width,2)
                if(distance<0):
                   if(distance<-0.3):
                      distance=distance+1.4
                   distance=round(abs(distance),2)





                distance_judg=distance
                print(distance_judg,end='')
                print('m')


                #シリアル通信 距離によってシリアル通信で送る値を変える
                if distance_judg<0.9:
                    uart.write ('1')

                elif distance_judg<1.5:
                    uart.write ('2')

                elif distance_judg<=2:
                    uart.write ('3')
                #print(i.rect())
                #img = img.resize(224,224)
                #a = img.draw_circle(224,224,20,fill=True)

                a = img.draw_rectangle(i.rect())


    else:

        uart.write('7')



    time.sleep(5)






UART.deinit ()
#b = class_ws2812.set_led(0,(0,0,0))
#b = class_ws2812.display()

a = kpu.deinit(task)
