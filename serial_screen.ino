#include <Adafruit_GFX.h>    // 导入Adafruit_GFX库
#include <Adafruit_ST7789.h> // 导入ST7789库

// 定义引脚（注意：这是显示屏上印刷的引脚名称，并非标准命名）
#define TFT_DC 12
#define TFT_RES 13 // RST 引脚
#define TFT_SDA 14 // MOSI 引脚
#define TFT_SCL 15 // SCK 引脚

// 定义变量
int x = 0;         // x 坐标
int y = 0;         // y 坐标
int i = 0;         // rgb数组的索引
uint8_t rgb[3] = {0, 0, 0}; // 临时存放 RGB 值

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_DC, TFT_RES, TFT_SDA, TFT_SCL); // 定义屏幕

void setup() {
  Serial.begin(2000000); // 设置波特率（Arduino IDE 的串口监视器最大值）
  tft.init(240, 240);  // 初始化显示屏
  tft.fillScreen(ST77XX_BLACK); // 填充屏幕为黑色
  tft.setRotation(0);  // 旋转显示屏方向
  pinMode(13, OUTPUT); // 设置主板指示灯引脚模式
  digitalWrite(13, LOW); // 指示灯灭
}

void loop() {
  if (Serial.available() > 0) { // 串口有内容时执行
    rgb[i] = Serial.read(); // 读取一字节，即0-255，一个颜色通道
    i++; // 索引值加一
    if (i == 3) { // 当 RGB 三通道都获取后执行
      i = 0; // 重置索引
      tft.drawPixel(x, y, tft.color565(rgb[0], rgb[1], rgb[2])); // 在指定坐标画指定颜色的点
      x++; // x 坐标加一
      if (x >= tft.width()) { // 当新 x 坐标超过屏幕宽度时执行
        x = 0; // 重置 x 坐标
        y++; // y 坐标加一
        if (y >= tft.height()) { // 当新 y 坐标超过屏幕高度时执行
          // 重置坐标，为下一次绘图做准备
          x = 0;
          y = 0;
        }
      }
    }
  }
}
