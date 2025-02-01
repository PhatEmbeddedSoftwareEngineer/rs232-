# RS-232
RS-232 for Linux, FreeBSD and windows

Website: https://www.teuniz.net/RS-232/

No merge requests. If you want to report a bug, create an issue.
#
#
# Chức năng của đoạn code này như sau , 
# đoạn code này dùng để upload firmware cho ESP32 và STM32 bằng cổng UART 
# đây là 1 phần của dự án , còn phần mã của STM32 và ESP32 em không đưa thêm vào
# ở phần code RS232 này mình có thể kiểm soát hoàn toàn tốc độ upload của firmware không qua tốc độ baud rate và kiểm tra lỗi trên đường
# truyền và phản hồi lại nếu báo lỗi để gửi lại .
# 
# Dự án này được test trên PC giao tiếp uart với STM32 và ESP32 thông qua USB TTL
# 
#

 #