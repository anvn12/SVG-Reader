# YÊU CẦU 1:
- translate(x,y)
- rotate(d)
- scale(d) hoặc scale(x,y)

# YÊU CẦU 2: Bổ sung đối tượng đường bất kì - đối tượng Path của SVG.
- Các đường thẳng: lệnh moveto (M), lineto (L, H, V) và closepath (Z)
- Đường cong Bezier bậc 3 (Cubic Bézier Curve): lệnh curveto (C)
- Lệnh moveto (M) đi đến 1 điểm với tọa độ x, y.
- Lệnh lineto (L, H, V) nhận input là 1 điểm, vẽ đường thẳng từ điểm hiện tại đến điểm input. Điểm hiện tại có thể là điểm đã moveto, hoặc là điểm đích cuối sau khi thực hiện các lệnh vẽ khác. H, V vẽ các đường nằm ngang hay thẳng đứng.
- Lệnh closepath (Z) vẽ đường thẳng từ điểm cuối đến điểm đầu tiên của Path.
- Lệnh curveto (C) nhận 3 điểm input, và vẽ đường cong bậc 3 qua 4 điểm: điểm hiện tại + 3 điểm input.

# YÊU CẦU 3: Bổ sung cấu trúc phức hợp - đối tượng Group của SVG.
- stroke
- stroke-width
- stroke-opacity
- fill
- fill-opacity
- transform

