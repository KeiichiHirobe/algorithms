## k番目の考え方

### 2分探索
`xが小さい方からk番目`

は以下と同値

`x以下がkコ以上であるようなxの最小値`

xのとり得る範囲を2分探索して求めることができる

ref: https://atcoder.jp/contests/abc294/submissions/39973241

### 場合の数
`xが小さい方からk番目`

は以下と同値

1. `x-1以下がkコ未満`
1. `x以下がkコ未満ではない`

ここで、f(x)をx以下がkコ未満である場合の数とすると、xが小さい方からk番目の場合の数は

f(x-1) - f(x)

となる。

ref: https://atcoder.jp/contests/abc295/submissions/40060066

