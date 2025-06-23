# Cách chia file
## File không được thay đổi
- targetver.h 
- rapidxml.hpp 
- stdafx.cpp


## Sử dụng stdafx.h
- Có include thư viện gì thì include trong cái stdafx.h trước
- Sau đó include cái thư viện đó trong cái file .h cần thêm
- Trong file .cpp, làm:
	-	#include "stdafx.h"
	-	#include "cái file .h"

- Mục đích của cái này là tăng tốc thời gian combine.


# Các bước đọc file
1. Parse cái svg (bỏ mấy cái <> của xml)
2. Sau khi lọc cái svg -> bỏ vô mấy cái class
3. Dùng đồ họa vẽ nó lên

# Giai thich vài hàm của windows.h
WINMAIN: chỗ chứa như hàm main

wndclass: là chỗ của mấy cái kiểu như nút bấm, chức năng này kia
hwnd: chỉ tạo ra cái màn hình không có chức năng -> cần có cái showwindow, updatewindow...



#
[x] SVGReader cần thêm chỗ chứa shape; có biến chứa có code, hàm đọc xml bỏ vô đây luôn
[ ] Cần renderer class để render riêng (vẽ SVGShape, ): mục đích là khi mở rộng thêm vẽ hình gì thì có thể thêm vào đây

[ ] Gom chung thuộc tính svg về svgshape: mục đích để tái sử dụng code


[ ] Them giải thích OOP (chỗ nào là inherit, abstrac, ...)


[ ] Bat lai cai WM_CLOSE sau khi code xong



taskkill /F /IM SVG-Reader.exe