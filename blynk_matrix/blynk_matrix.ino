#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>


#define PIN 26
#define NUMPIXELS 64


// Флаг показывающий режим работы - 0 - свечение, 1 - мигание
int flag = 0;
// Флаг показывающий состояние светодиодов - 0 - горят, 1 - выключены
int neopixel_status = 0;
// таймер
unsigned long timer = 0;
// флаг показывающий, какую картинку включать
int image = 1;

// Инициализация светодиодной ленты
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// AUTH TOKEN из приложения Blynk
char auth[] = "";

// Данные для подклчения к Wi-Fi сети
char ssid[] = "";
char pass[] = "";

// Глобальные переменные, отвечающие за цвет
int R = 100, G = 100, B = 100;

// Функция, окрашивающаяя всю матрицу в один цвет
void color(int R, int G, int B) {
    for (int i = 0; i < NUMPIXELS; i++) pixels.setPixelColor(i, pixels.Color(R, G, B));
    pixels.show();
}

// Функция по отрисовке разноцветного смайлика
void draw_smile() {
    color(0, 0, 0);
    int circle[] = {2, 3, 4, 5, 9, 14, 16, 23, 24, 31, 32, 39, 40, 47, 49, 54, 58, 59, 60, 61};
    int eyes[] = {18, 21};
    int mouth[] = {42, 45, 51, 52};

    for (int i = 0; i < 20; i++) {
        pixels.setPixelColor(circle[i], pixels.Color(0, 50, 150));
    }
    for (int i = 0; i < 2; i++) {
        pixels.setPixelColor(eyes[i], pixels.Color(0, 150, 50));
    }
    for (int i = 0; i < 4; i++) {
        pixels.setPixelColor(mouth[i], pixels.Color(150, 0, 0));
    }
    pixels.show();
}

// Функция по отрисовке сердечка заданного цвета
void draw_heart(int R, int G, int B) {
    color(0, 0, 0);
    int heart[] = {9, 10, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
                   37, 38, 39, 41, 42, 43, 44, 45, 46, 50, 51, 52, 53, 59, 60};
    for (int i = 0; i < 40; i++) {
        pixels.setPixelColor(heart[i], pixels.Color(R, G, B));
    }
    pixels.show();
}


// Обработчик виртуального пина V2. Изменение положения слайдера - изменяет изображения
BLYNK_WRITE(V2)
{
    image = param.asInt();
    select_image(image);
}

// Обработчик виртуального пина V1. В переменную флаг записывается положение кнопки
BLYNK_WRITE(V1)
{
    flag = param.asInt();
}

/* Обработчик виртуального пина V0. В соответствующие переменные отвечающие за составление цвета
 * Записываются полученные значение, а затем отрисовывается картинка.
 */
BLYNK_WRITE(V0)
{
    R = param[0].asInt();
    G = param[1].asInt();
    B = param[2].asInt();
    select_image(image);
}

// Функция отрисовывающая картинку, в зависимости от номера
void select_image(int type) {
    switch (type) {
        case 1:
            draw_heart(R, G, B);
            break;
        case 2:
            draw_smile();
            break;
    };
}

void setup() {
    Blynk.begin(auth, ssid, pass); // Подключение к Blynk-серверу
    pixels.begin(); // Инициализация светодиодов
    select_image(image); // отображение значения по умолчанию (белое сердечко)
}


void loop() {
    Blynk.run();
    if (flag != 0) {
        if (timer == 0) {
            if (neopixel_status == 0) {
                neopixel_status = 1;
                color(0, 0, 0);
                timer = millis();
            } else {
                neopixel_status = 0;
                select_image(image);
                timer = millis();
            }
        } else if (millis() - timer > 1000) {
            if (neopixel_status == 0) {
                neopixel_status = 1;
                color(0, 0, 0);
                timer = millis();
            } else {
                neopixel_status = 0;
                select_image(image);
                timer = millis();
            }
        }
    }

}
