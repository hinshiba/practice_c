Cの

char str[] = "aa" "bb";

は
str == "aabb"である

## _Generic関係

### dbglogへ

- 単純にdbglog(i, getfmt(i))
  - _Genericが後で評価されるのか知らんけど無理だった
- コンマ演算子の利用を試みた
  - sprintf しかし宣言が式ではなく文なので失敗
    - `printf((sprintf((char buf[100]), "%s is set: %s\n", #i, getfmt(i)), buf),#)`
  - printfを3つ使えば行ける
    - ;と何が違うのか
- トークン連結演算子##であれこれ

### inputsへ
- そもそも可変長から取り出すときに、castするのでx
- 単一入力なら代入したいので出る番なし