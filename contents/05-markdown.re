= 軽量マークアップ言語 Markdown

//abstract{
  @<code>{Markdown}(マークダウン)は、文書を記述するための軽量マークアップ言語の一つです。
  「書きやすくて読みやすいプレーンテキストとして記述した文書を、妥当なHTML文書へと変換できるフォーマット」として、ジョン・グルーバーやアーロン・スワーツにより作成されました。

  Markdownの記法の多くは、電子メールにおいてプレーンテキストを装飾する際の慣習から着想を得ています。
//}

//makechaptitlepage[toc=on]

== Markdownの特徴

//sideimage[markdown][40mm][sep=5mm,side=R]{
  文書作成等に広く用いられている Markdown をご紹介いたします。記法については様々なサイトで解説されていますが、ここでは比較的良くまとまっているウィキペディア等を参考にご案内します。
//}

 * 簡潔な記法のため 容易に学習できる
 * テキストベースで使い回しも容易
 * 様々な活用が可能
 ** メモ書きに
 ** ブログ投稿に
 ** スライド作成にも

== 段落
段落は1つ以上の連続したテキストで、空行によって分けられます。
通常の段落をスペースやタブで字下げ(インデント)してはなりません。

//list[][Markdown]{
  これは段落です。2つの文があります。

  これは別の段落です。ここにも2つの文があります。
//}

== 改行
テキストに挿入された改行は、最終的な結果から取り除かれます。
強制的に改行したい場合は、行末に2つのスペースを挿入すればよいです。

== テキストの装飾
以下のように記すことで、テキストを装飾できます。
@<code>{*} や @<code>{_} などの記号の前後には、半角スペースが必要です。

//list[][Markdown]{
  *強調*

  _斜体_

  **強い強調**

  __太字__

  ~~打ち消し線~~
//}

== 見出し
HTMLの見出しは、テキストの前にいくつかの @<code>{#} を置くことで作ることができます。

//list[][Markdown]{
  # レベル1の見出し (=h1)
  ## レベル2の見出し (=h2)
  ### レベル3の見出し (=h3)
  #### レベル4の見出し (=h4)
  ##### レベル5の見出し (=h5)
  ###### レベル6の見出し (=h6)
//}

@<code>{h1} と @<code>{h2} は、以下のようにも書けます。

//list[][Markdown]{
  レベル1の見出し (=h1)
  =====================

  レベル2の見出し (=h2)
  ---------------------
//}

== 箇条書き

=== 順序付箇条書き
番号は自動で振られるので、全て @<code>{1. 項目} とすれば良いです。

//list[][Markdown]{
  1. 順序付きリストのアイテム
    1. 順序付きリストのサブアイテム その壱
    1. 順序付きリストのサブアイテム その弐
    1. 順序付きリストのサブアイテム その参
  1. 順序付きリストの別のアイテム
    1. 順序付きリストのサブアイテム その壱
    1. 順序付きリストのサブアイテム その弐
  1. 順序付きリストの別のアイテム
  1. 順序付きリストの別のアイテム
  1. 順序付きリストの別のアイテム
//}

=== 順不同箇条書き

@<code>{-(ハイフン)} @<code>{*(アスタリスク)} どちらの記号も使えます。結果は同じになります。

//list[][Markdown]{
  - 順不同リストアイテム
      - サブアイテムはタブもしくは4つのスペースで字下げ(インデント)する
  - 順不同リストの別のアイテム

  * 順不同しリストアイテム
      * サブアイテムはタブもしくは4つのスペースで字下げ(インデント)する
  * 順不同リストの別のアイテム
//}

== 引用
@<code>{>} を行頭に付けることで、引用文になります。

//list[][Markdown]{
  宮沢賢治 ポラーノの広場 より引用
  > 　あのイーハトーヴォのすきとおった風、夏でも底に冷たさをもつ青いそら、
  > うつくしい森で飾られたモリーオ市、郊外のぎらぎらひかる草の波
  >
  > 　またそのなかでいっしょになったたくさんのひとたち、
  > ファゼーロとロザーロ、羊飼のミーロや、顔の赤いこどもたち、
  > 地主のテーモ、山猫博士のボーガント・デストゥパーゴなど、
  > いまこの暗い巨きな石の建物のなかで考えていると、
  > みんなむかし風のなつかしい青い幻燈のように思われます。
  > では、わたくしはいつかの小さなみだしをつけながら、
  > しずかにあの年のイーハトーヴォの五月から十月までを書きつけましょう。
//}

== 水平線
一行の中に、3つ以上の @<code>{-(ハイフン)} や @<code>{*(アスタリスク)} @<code>{_(アンダースコア)}だけを並べると水平線が作られます。

ハイフンやアスタリスクの間には空白を入れられます。
次の例はすべて水平線になります。

//list[][Markdown]{
  * * *

  ***

  *****

  - - -

  ---------------------------------------
//}

== リンク
リンクは次のように記述できます。

//list[][Markdown]{
  [リンクのテキスト](リンクのURL)
//}

これは、HTML に変換すると次のようになります。

//list[][HTML]{
  <a href="リンクのURL">リンクのテキスト</a>
//}

URLが長かったり、良く使うリンクには名前を付けることもできます。

//list[][Markdown]{
  [リンクテキスト][名前]
  [名前]:URL
//}

使うときには、次のように使います。

//list[][Markdown]{
  [名前][]
//}

=== ページ内リンク

次のように書くと、ページ内リンクを作成できます。
//list[][Markdown]{
  [ポラーノの広場](#ポラーノの広場)
  [坊ちゃん](#坊ちゃん)
  [高瀬舟](#高瀬舟)

  # ポラーノの広場
  　あのイーハトーヴォのすきとおった風、夏でも底に冷たさをもつ青いそら、うつくしい森で飾られたモリーオ市、郊外のぎらぎらひかる草の波

  　またそのなかでいっしょになったたくさんのひとたち、ファゼーロとロザーロ、羊飼のミーロや、顔の赤いこどもたち、地主のテーモ、山猫博士のボーガント・デストゥパーゴなど、いまこの暗い巨きな石の建物のなかで考えていると、みんなむかし風のなつかしい青い幻燈のように思われます。では、わたくしはいつかの小さなみだしをつけながら、しずかにあの年のイーハトーヴォの五月から十月までを書きつけましょう。

  # 坊ちゃん
  親譲りの無鉄砲で小供の時から損ばかりしている。小学校に居る時分学校の二階から飛び降りて一週間ほど腰を抜かした事がある。なぜそんな無闇をしたと聞く人があるかも知れぬ。別段深い理由でもない。新築の二階から首を出していたら、同級生の一人が冗談に、いくら威張っても、そこから飛び降りる事は出来まい。弱虫やーい。と囃したからである。小使に負ぶさって帰って来た時、おやじが大きな眼をして二階ぐらいから飛び降りて腰を抜かす奴があるかと云ったから、この次は抜かさずに飛んで見せますと答えた。

  # 高瀬舟
  高瀬舟は京都の高瀬川を上下する小舟である。徳川時代に京都の罪人が遠島を申し渡されると、本人の親類が牢屋敷へ呼び出されて、そこで暇乞をすることを許された。それから罪人は高瀬舟に載せられて、大阪へ廻されることであつた。それを護送するのは、京都町奉行の配下にゐる同心で、此同心は罪人の親類の中で、主立つた一人を大阪まで同船させることを許す慣例であつた。これは上へ通つた事ではないが、所謂大目に見るのであつた、默許であつた。
//}

== 画像
次のように記述することで、画像を掲載できます。

//list[][Markdown]{
  ![代替テキスト](画像のURL)
//}

これを、HTML に変換すると、次のようになります。

//list[][HTML]{
  <img src="画像のURL" alt="代替テキスト">
//}

== 表
表は次のように書きます。

//list[][Markdown]{
  | Left align | Center align | Right align |
  |:-----------|:------------:|------------:|
  | Apple      |    Apple     |       Apple |
  | Banana     |    Banana    |      Banana |
  | Cherry     |    Cherry    |      Cherry |
//}

== コード
プログラムコードを掲載したい場合もあります。
コードを含める場合、3つずつの @<code>{```(バッククオート)}でコード全体をくくります。
開始を表すバッククオートの3つ目に続けて、任意で言語名を明記することができます。

例えば、 @<code>{Ruby} のプログラムコードの場合には、次のように書けます。

//list[][Markdown]{
  ``` ruby
     puts "Hello world"
  ```
//}

== チェックボックス
一部の環境とはなりますが、チェックボックスを作成することもできます。

//list[][Markdown]{
  - [ ] タスク1
  - [x] タスク2
//}

== 注釈
注釈を書くこともできます。注釈は、 @<code>{^(ハット)} の後に 数字を記します。
@<B>{インターネット・プロトコル・スイート} という技術用語に注釈を付けてみます。

//list[][Markdown]{
  インターネットとは、「インターネット・プロトコル・スイート」[^1]を使用し、
  複数のコンピュータネットワークを相互接続した、地球規模の情報通信網のことである。

  [^1]: TCP/IPプロトコル・スイート とも呼ばれる、標準化された通信規約のこと。
//}

== HTML
本文中に、一部の @<code>{html} タグを記述することもできます。

//list[][Markdown]{
  <figcaption>図1 りんご</figcaption>
//}

////blankline
Markdownは、そのまま文章として読んでも見やすく、また記法も簡単です。
少ない学習量で習得することができ、ちょっとしたメモ書きから、ブログの投稿やスライドの作成など様々な分野で使われています。是非、ご利用下さい。