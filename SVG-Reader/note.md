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


