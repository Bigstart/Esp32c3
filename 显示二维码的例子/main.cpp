#include <Arduino.h>
#include "qrcode.h"

void setup() {
    Serial.begin(921600);
    while (!Serial);

    // 要编码的文本
    const char *qrData = "WIFI:T:WPA;S:DESKTOP-0EVJM2M 9604;P:00001111;;";

    // 配置选项，使用默认配置
    esp_qrcode_config_t cfg = ESP_QRCODE_CONFIG_DEFAULT();
    cfg.max_qrcode_version = 39; // 21是240x240的二维码版本号
    // 生成并显示二维码
    esp_err_t err = esp_qrcode_generate(&cfg, qrData);
    if (err != ESP_OK) {
        Serial.println("Failed to generate QR Code");
    }
}

void loop() {
    // 你的循环代码
}
