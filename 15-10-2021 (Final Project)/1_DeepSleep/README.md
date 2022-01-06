## Deep Sleep

- Microcontroller falls into 'deep sleep' after 5 seconds.
- Deep Sleep mode helps in energy conservation.
- Deep Sleep mode in ESP32 cuts processes with **major energy consumption**, while preserves the parts which can help it wakeup
with a trigger event. 
- *Ultra Low Power (ULP)* co-processor functions in deep sleep mode,
whereas Wi-Fi and CPU are non functional.