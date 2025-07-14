# matterRemembered

Matter, Remembered is a large-scale breathing lamp installation that makes the environmental impact of U.S. material consumption something you can see, feel, and even interact with.

Built from recycled duct tape, salvaged wooden dowels, and New York City “Thank you” bags, the piece visualizes U.S. material footprint data (1970–2024) as light and breath — growing more urgent as consumption increases.

Presented at NYU’s ITP Spring Show 2025.

✨ Concept

This project explores memory, materiality, and resilience through the lens of discarded materials. The translucent lampshade preserves the printed graphics of HDPE bags, creating a glowing surface layered with history and light.

Visitors can turn the lamp on and off with a ghostlike hand gesture, thanks to an embedded APDS-9960 sensor. As the LEDs breathe in and out, their rhythm accelerates in proportion to U.S. consumption data — turning statistics into something visceral.

A journal at the base of the lamp, Identity Crisis: Duct Tape, imagines what duct tape might say if it could speak about the lives it’s patched together.

🧰 Materials & Tools

Structure: Recycled wooden dowels, reused duct tape
Shade: Woven and heat-fused HDPE plastic bags
Sensors & Electronics:
APDS-9960 proximity sensor
WS2812B addressable LEDs
Arduino Uno
Software:
Arduino IDE
Custom C++ code (in /code/ folder)
Data:
Global Material Flows Database (U.S. material footprint 1970–2024)
📂 Repository Structure

/code           → Arduino sketch & libraries
/images         → Installation and process photos
/journal        → *Identity Crisis: Duct Tape* journal scans
/README.md      → This file

🚀 How to Run

Open the sketch in /code/ with Arduino IDE.
Connect your Arduino Uno and upload the code.
Wire the APDS-9960 sensor and WS2812B LEDs according to the schematic in /code/schematic.png.
Power the lamp and interact with the sensor to turn it on/off. The LEDs will animate based on the mapped data.

📖 License

This project is open source under the MIT License. Feel free to adapt, remix, or build upon it — and don’t forget to credit the duct tape.

