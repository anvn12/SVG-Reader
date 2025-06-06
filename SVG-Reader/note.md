# Cách chia file
header file thì nhét vô stdafx.h
targetver.h để nhét đúng cái thư viện cho các phiên bản windows (10,11,7,8,...)


rapidxml.hpp là thư viện để đọc file SVG (xml), KO THAY ĐỔI cái này

mấy cái này đang vẽ bằng windows.h, chưa có thư viện gdi+


# Các bước đọc file
1. Parse cái svg (bỏ mấy cái <> của xml)
2. Sau khi lọc cái svg -> bỏ vô mấy cái class
3. Dùng đồ họa vẽ nó lên