# Tof_Distance
# 视频：https://www.bilibili.com/video/BV1Fj421X7hX/
Air001 mcu的tof测距
## 硬件工程
https://oshwhub.com/hbk444/tofdistance
## 外壳模型工程
https://makerworld.com/zh/models/187504#profileId-206552
## 拼装方式
* 1.先焊接ic部分
* 2.烧录固件
* 3.焊接屏幕
* 4.焊接电池
* 5.摆放方式 屏幕 电池 pcb （电池在屏幕和pcb中间夹着）
## 主要硬件ic 评估你是否愿意复刻 总成本大致在30-40元
* AIR001
* SSD1306
* TP4056
* VL53L1X（模块）
* 1117-3.3
* 402030 200毫安电池
## 开发sdk
* 基于Arduino
* Air001 开发文档：https://wiki.luatos.com/chips/air001/Air001-Arduino.html

## 烧录！
* air001需要拉高boot进入烧录模式
* 将boot io 于3.3v连接 后上电 通过ttl进行烧录

