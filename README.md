Painting_Board_Program
===

TERM
---

2017.10.31 ~ 2017.11.7

Program
----

**0. Take Input**

row size, col size, and image.

---

**1. Query1: RESIZE**

* arg1 = 0: 2X Magnification

![image](https://user-images.githubusercontent.com/30820487/50946130-6ec04b00-14db-11e9-80d3-25ae6dfce8fb.png)

*arg1 = 1: 2X Reduction

![image](https://user-images.githubusercontent.com/30820487/50946174-97484500-14db-11e9-8d22-5cbd98116038.png)

---

**2. Query2: ROTATE**

* arg2 = 0: 90 degree

* arg2 = 1: 180 degree

* arg2 = 2: 270 degree

---

**3. Query3: FLIP**

* arg3 = 0: flip horizontally

* arg3 = 1: flip vertically

---

**4. Query4: COPY AND PASTE**

Take x1, y1, c_h, c_w, x2, y2.

Copy the vertical length (c_h) and the horizontal length (c_w) at the (x1,y1) coordinates of the original image.

Paste the result of the copy to (x2,y2) coordinates.

![image](https://user-images.githubusercontent.com/30820487/50946476-df1b9c00-14dc-11e9-87de-1b37a6532248.png)

---

**5. Query5: FILL**

Take x, y, color

Change all the pixels that are adjacent to (x,y) and same color with (x,y) coordinates into a given color.

![image](https://user-images.githubusercontent.com/30820487/50946580-6f59e100-14dd-11e9-82e3-731589dd042e.png)
