# ติดตั้งและอัปโหลดโปรแกรม

หน้านี้สำหรับคนที่ต้องการนำซอร์สโค้ดใน GitHub ไปลงเครื่องของตัวเอง โครงงานกำหนดสภาพแวดล้อมเป็น **Arduino UNO R4 WiFi** บน PlatformIO และใช้ไลบรารี **LiquidCrystal_I2C** ตาม [platformio.ini](https://github.com/BankTQMA/Bakuduino/blob/main/platformio.ini)

## สิ่งที่ต้องเตรียม

- บอร์ด Arduino UNO R4 WiFi และสาย USB ที่ส่งข้อมูลได้
- เครื่องคอมพิวเตอร์ที่ใช้เปิด Visual Studio Code กับส่วนขยาย PlatformIO IDE หรือมี PlatformIO Core
- อุปกรณ์ตามหน้า [อุปกรณ์และวงจร](hardware.md)
- อินเทอร์เน็ตในครั้งแรกที่ PlatformIO ต้องดาวน์โหลดแพลตฟอร์มและไลบรารี

หากใช้ VS Code สามารถติดตั้ง PlatformIO IDE จากหน้าส่วนขยายได้ตาม [คู่มือ PlatformIO อย่างเป็นทางการ](https://docs.platformio.org/en/latest/integration/ide/vscode.html)

## เปิดโปรเจกต์

1. ดาวน์โหลดหรือ clone [repository Bakuduino](https://github.com/BankTQMA/Bakuduino)
2. เปิดโฟลเดอร์โครงงานใน VS Code โดยเลือกโฟลเดอร์ที่มี `platformio.ini`
3. รอ PlatformIO เตรียม environment `uno_r4_wifi` และไลบรารีที่ระบุในไฟล์ตั้งค่า
4. เชื่อมบอร์ดกับคอมพิวเตอร์ แล้วเลือกพอร์ตของบอร์ดถ้าระบบไม่ตรวจให้อัตโนมัติ
5. กด **Build** เพื่อคอมไพล์ ตรวจข้อความผิดพลาด แล้วกด **Upload** เพื่ออัปโหลด

ปุ่ม Build และ Upload อยู่ในแถบ PlatformIO ของ VS Code ตาม [คู่มือ PlatformIO IDE](https://docs.platformio.org/en/latest/integration/ide/vscode.html)

### ใช้คำสั่งแทนปุ่ม

เปิดเทอร์มินัลในโฟลเดอร์ที่มี `platformio.ini` แล้วใช้คำสั่งต่อไปนี้:

```bash
pio run -e uno_r4_wifi
pio run -e uno_r4_wifi -t upload
```

คำสั่งแรกคอมไพล์ environment ของบอร์ดในโครงงาน คำสั่งที่สองคอมไพล์และอัปโหลด ดูรูปแบบคำสั่งได้ใน [PlatformIO Quick Start](https://docs.platformio.org/en/latest/core/quickstart.html)

## หลังอัปโหลด

เมื่อเครื่องทำงาน จอจะขึ้นข้อความรอเริ่มเกมแล้วรอการกดปุ่มหนึ่งครั้ง ใน [เฟิร์มแวร์ที่อยู่บน GitHub ขณะจัดทำเอกสาร](https://github.com/BankTQMA/Bakuduino/blob/main/src/ModuleSpiral.h) ข้อความบรรทัดแรกยังเป็น **SIGNAL DECODER** และบรรทัดถัดไปเป็น **PRESS ANY KEY** ส่วนชื่อเกมในคู่มือคือ **Simon Says**

กดปุ่มใดก็ได้หนึ่งครั้งเพื่อเริ่ม แล้วสังเกตว่าสัญลักษณ์ ด่าน เวลา และเสียงปรากฏตามปกติ ถ้าจอไม่แสดงผล ให้ตรวจไฟเลี้ยง สาย I²C และ address `0x27` ก่อน

## Serial Monitor สำหรับผู้พัฒนา

โค้ดส่งข้อมูลโจทย์และคำตอบของด่านออกทาง Serial ที่ความเร็ว **9600 baud** เพื่อช่วยตรวจพฤติกรรมระหว่างพัฒนา ค่านี้อยู่ใน [platformio.ini](https://github.com/BankTQMA/Bakuduino/blob/main/platformio.ini) และฟังก์ชันพิมพ์คำตอบอยู่ใน [ModuleStar.h](https://github.com/BankTQMA/Bakuduino/blob/main/src/ModuleStar.h)

ระหว่างเล่นจริง ควรปิดหน้าต่าง Serial Monitor หรือหันออกจากสายตาผู้เล่น เพราะข้อความนี้เปิดเผยคำตอบ

## เมื่อ Build หรือ Upload ไม่สำเร็จ

| อาการ | จุดที่ควรตรวจ |
| --- | --- |
| ไม่พบ `LiquidCrystal_I2C.h` | ตรวจการเชื่อมต่ออินเทอร์เน็ตและบรรทัด `lib_deps` ใน `platformio.ini` |
| เลือกบอร์ดไม่ตรง | environment ต้องเป็น `uno_r4_wifi` ตามไฟล์ตั้งค่า |
| Upload ไม่พบพอร์ต | ตรวจสาย USB พอร์ตที่เลือก และปิดโปรแกรมอื่นที่กำลังใช้พอร์ต |
| Upload ผ่านแต่จอไม่แสดง | ตรวจการต่อจอและ address I²C `0x27` |
| เสียงหรือปุ่มไม่ตรง | ตรวจการเชื่อมต่อ D2–D5 และ D8 ตามหน้า [อุปกรณ์และวงจร](hardware.md) |

หากแก้ชื่อไฟล์ โครงสร้างโฟลเดอร์ หรือชนิดบอร์ด โปรดตรวจ [platformio.ini](https://github.com/BankTQMA/Bakuduino/blob/main/platformio.ini) และ [ซอร์สโค้ดหลัก](https://github.com/BankTQMA/Bakuduino/blob/main/src/main.cpp) ให้ตรงกัน

