# mini_RT

引数は以下のような感じ
```
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 0,0,-3 0.6
sp 0,0,10 7 0,0,255
```

-> Camera(C)視点、Light(L)光源からSphere(S)を見る

①open, read, close...などでファイルを受け取って解釈する

②計算して表示

---

Sphereについてはplaygroundのコードを参照
他にPlane（平面）, Cylinder（円筒）の実装が必要

赤色の球の表示はできたが、複数のオブジェクトの表示をするためには、
それぞれをループで回して視点に最も近い物体を使う↓

![alt text](image.png)

今は物体と色の構造体(t_color)が分離してしまっているため、MultipleShapes以降では
物体の構造体に色の情報を入れる必要がある。データ構造の整理が必要そう

計画はissuesを使ってやろうかな

<img width="831" alt="image" src="https://github.com/user-attachments/assets/4b733f28-8856-45fc-b147-a59a54414b9c" />


=====>　案1の方が確かにいい気もしてきた
