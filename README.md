# miniRT

42 の `miniRT` 課題をベースにした、MiniLibX 製のレイトレーサーです。
`.rt` ファイルでシーンを定義し、球・平面・円柱を Phong ライティング、影、反射、屈折、カラーマップ、法線マップ、スカイボックス付きで描画します。

## 主な機能

- オブジェクト: 球体 `sp`、平面 `pl`、円柱 `cy`
- ライト: 環境光 `A`、複数の点光源 `L`
- カメラ: 位置、向き、水平 FOV の指定
- シェーディング: 拡散反射、鏡面反射、影
- 材質: `GLASS`、`IRON`、`SILVER`、`WOOD`、`WATER`
- 光学表現: 反射、屈折
- テクスチャ: カラーマップ `C:"..."`、法線マップ `N:"..."`
- 背景: スカイボックス `sk`

## ビルド

```sh
make
```

実行ファイル `miniRT` が生成されます。

MiniLibX を使うため、Linux では X11 関連ライブラリが必要です。macOS では XQuartz など、X11 が使える環境を用意してください。

## 実行

```sh
./miniRT scenes/example.rt
```

描画サイズは `inc/ft_mlx.h` の `WIDTH` / `HEIGHT` で定義されています。現在は `1024 x 1024` です。

終了方法:

- `ESC`
- ウィンドウを閉じる

## シーンファイルの書き方

シーンは `.rt` ファイルに 1 行 1 要素で記述します。
各値はスペース区切り、ベクトルや RGB はカンマ区切りです。

```rt
A 0.1 255,255,255
C 0,2,-8 0,0,1 70
L 0,5,-3 0.8 255,255,255
sp 0,1,3 2.0 255,80,80 GLASS
pl 0,0,0 0,1,0 180,180,180 WOOD C:"tex/stone_color.jpg" N:"tex/stone_normal.jpg"
```

### 共通の値

| 種類 | 形式 | 範囲・補足 |
| --- | --- | --- |
| 座標 | `x,y,z` | 例: `0,1.5,-3` |
| 正規化ベクトル | `x,y,z` | 各成分は `-1.0` から `1.0`、長さは `1` |
| RGB | `r,g,b` | 各成分は `0` から `255` |
| 光量比 | `ratio` | `0.0` から `1.0` |
| FOV | `degree` | `0` から `180` |

コメント行は parser 側で扱っていないため、`.rt` には書かないでください。

### 基本要素

| ID | 書式 | 説明 |
| --- | --- | --- |
| `A` | `A <ratio> <rgb>` | 環境光。シーン内で 1 回だけ指定できます。 |
| `C` | `C <position> <orientation> <fov>` | カメラ。シーン内で 1 回だけ指定できます。 |
| `L` | `L <position> <ratio> <rgb>` | 点光源。複数指定できます。 |
| `sk` | `sk C:"<path>"` | スカイボックス。画像を背景として使います。 |

### オブジェクト

| ID | 書式 |
| --- | --- |
| `sp` | `sp <center> <diameter> <rgb> [material] [textures...]` |
| `pl` | `pl <point> <normal> <rgb> [material] [textures...]` |
| `cy` | `cy <center> <axis> <diameter> <height> <rgb> [material] [textures...]` |

例:

```rt
sp 0,1,3 2.0 255,0,0 IRON
pl 0,0,0 0,1,0 120,120,120 WOOD C:"tex/bricks_color.png"
cy -2,0,4 0,1,0 1.0 3.0 80,120,255 SILVER
```

## 材質

材質は RGB の後ろに任意で指定できます。省略した場合は `WOOD` として扱われます。

| 材質 | 特徴 |
| --- | --- |
| `GLASS` | 強い鏡面反射と屈折 |
| `IRON` | 強めの鏡面反射 |
| `SILVER` | 強い完全反射 |
| `WOOD` | 弱めの鏡面反射 |
| `WATER` | 反射と屈折 |

## テクスチャ

テクスチャは材質の後ろ、または材質を省略した場合は RGB の後ろに続けて指定できます。

```rt
sp 0,0,3 1.0 255,255,255 IRON C:"tex/earth_color.png" N:"tex/earth_normal.png"
pl 0,0,0 0,1,0 255,255,255 C:"tex/wall.png"
```

| 指定 | 内容 |
| --- | --- |
| `C:"<path>"` | カラーマップ |
| `N:"<path>"` | 法線マップ |

画像の読み込みには `stb_image` を使っています。リポジトリ内の `tex/` には、サンプルシーンで使う画像が入っています。

## サンプルシーン

```sh
./miniRT scenes/pokemon_master.rt
./miniRT scenes/refraction.rt
./miniRT scenes/texturemap.rt
./miniRT scenes/skystar.rt
```

### `scenes/futuristic_space.rt`

<img width="793" alt="futuristic_space" src="https://github.com/user-attachments/assets/e9a201d6-81c6-45fb-8bd8-49cb290ed2dd" />

### `scenes/pokemon_master.rt`

<img width="780" alt="pokemon_master" src="https://github.com/user-attachments/assets/3290a560-eafd-492e-88c3-77a73bfdaa8a" />

### `scenes/refraction.rt`

<img width="796" alt="refraction" src="https://github.com/user-attachments/assets/c3108d22-afad-4e51-98f9-0eb330f1c064" />

### `scenes/texturemap.rt`

<img width="796" alt="texturemap" src="https://github.com/user-attachments/assets/7fb5ce50-2a7f-482a-bc84-2440b7cc66a4" />

## 開発用コマンド

```sh
make clean
make fclean
make re
make memory
```

- `clean`: オブジェクトファイルを削除
- `fclean`: オブジェクトファイルと `miniRT` を削除
- `re`: 再ビルド
- `memory`: AddressSanitizer 付きでビルド
