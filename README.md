# ESP32C3-WS2812B-Digital-Clock
A digital clock built using ESP32C3 and WS2812B LEDs. This project demonstrates how to control a WS2812B LED matrix to display a colorful and accurate digital clock.

Features

Real-time digital clock display

Fully addressable WS2812B LEDs

Customizable colors and animations

Easy to replicate with ESP32C3

Hardware

Microcontroller: ESP32C3

LEDs: WS2812B (addressable RGB LEDs)

Power supply: 5V (depends on number of LEDs)

LED Matrix Segment Mapping

The LED digits are controlled in pairs, and each pair corresponds to a segment of the 7-segment display. The mapping is as follows:

Segment	LED Index
G	{0, 1}
B	{2, 3}
A	{4, 5}
F	{6, 7}
E	{8, 9}
D	{10, 11}
C	{12, 13}

Each digit is constructed using these segments in the standard 7-segment configuration. Adjust your code if your LED wiring is different.

Software

Written in Arduino (or ESP-IDF if applicable)

Uses the FastLED library to control WS2812B LEDs

Timekeeping handled via RTC or NTP (depending on your setup)

GitHub

Full project, including code and schematics: https://github.com/ufukcicekdev/ESP32C3-WS2812B-Digital-Clock
