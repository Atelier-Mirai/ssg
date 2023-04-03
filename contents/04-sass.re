= 構文的に優れたスタイルシート Sass

//abstract{
ウェブサイトを作成する際、少し規模が大きくなると、通常のHTMLでの記述が困難となるのと同様、CSS もより書きやすくなるよう、その能力の向上が求められます。
こういった用途に応えて開発されたのが、 @<B>{Sass} です。
@<B>{Sass} は、Syntactically Awesome Style Sheets の略で、「構文的に優れたスタイルシート」の意味です。
//}

//makechaptitlepage[toc=on]


== @<code>{Sass} の特徴

@<B>{Sass} の @<href>{https://sass-lang.com/, 公式サイト} と、その使い方を詳細に解説されているサイト @<href>{https://www.webdesignleaves.com/pr/css/css_basic_08.html, Web Design Leaves} より適宜引用しつつ使用法などをご紹介します。

//image[sass][][width=80%]

まず公式サイトには、次のように案内されています。

//quote{
  スーパーパワーを持ったCSS。
  Sassは、世界で最も成熟した、安定した、強力なプロフェッショナルグレードのCSS拡張言語です。

  Sassは、すべてのバージョンのCSSと完全に互換性があります。私たちはこの互換性を重要視しており、利用可能なあらゆるCSSライブラリをシームレスに使用することができます。

  Sassは、他のどのCSS拡張言語よりも多くの機能と能力を誇っています。Sassのコアチームは、他の言語に追いつくだけでなく、先を行くために絶え間ない努力を続けています。
  Sassは約15年間、コアチームによって積極的にサポートされてきました。業界では、Sassが最高のCSS拡張言語として何度も選ばれています。

  Sassは、いくつかのハイテク企業と何百人もの開発者からなるコンソーシアムによって積極的にサポートされ、開発されています。
//}

それでは、特徴を見ていきましょう。

 * 一行コメント @<code>{//} が使える。
 * 変数が使える。
 * 入れ子(ネスト)ができる。
 * スタイルファイルを分けて管理できる。
 * ミックスイン（部品の再利用）ができる。
 ** メディアクエリの記述が楽である。
 * 演算ができる。
 ** 幅や高さなどの四則演算ができる。
 ** 色の演算もできる。
 * オリジナル関数の定義もできる。


== Sass の形式
@<code>{Sass} には、 @<code>{Sass形式} と @<code>{SCSS形式} があります。

//list[][Sass形式]{
  body
    font-family: Helvetica, sans-serif
    color:       #333
//}

//list[][SCSS形式]{
  body {
    font-family: Helvetica, sans-serif;
    color: #333;
  }
//}

どちらも同じルールセットの宣言になります。どちらの記法を採用するかは慣れや好みです。
#@# が、@<code>{SCSS}記法が使われることが多い印象があります。

@<code>{Sass形式} では、@<code>{{\}}や、@<code>{;}を取り除き、よりすっきりとさせており、簡潔さを追求した記法となっています。

@<code>{SCSS形式} は従来のCSSと同じ記法です。CSS形式で書かれたスタイルシートは、そのままSCSS形式としても解釈することができ、また学習コストも低いため、SCSS形式が多く使われています。

== 一行コメントを使う
CSS では、コメントとして、範囲コメント @<code>{/* */} のみが、使用可能でした。

@<code>{Sass} では、一行コメント @<code>{//} が使えます。
Atom など、主なエディタでは、複数行選択し、@<code>{Command + /} で、全てコメントにすることができます。
この一行コメントは、@<code>{Sass} から @<code>{CSS} に コンパイルされると、コメントは残りませんので、開発中の注釈・覚書などとして、活用することができます。

コンパイルされた @<code>{CSS} にコメントを残したいのであれば、従来通りの範囲コメント @<code>{/* */} を用いることができます。

== 変数

@<code>{Sass}では、「変数」を用いることができます。 @<fn>{custom_property}
//footnote[custom_property][CSSでもカスタムプロパティを使って、実現できます。]

@<code>{$font-stack}や、@<code>{$primary-color}が、変数です。
早速、使ってみましょう。

//list[][SCSS]{
  $font-stack:    Helvetica, sans-serif;
  $primary-color: #333;

  body {
    font-family: $font-stack;
    color:       $primary-color;
  }
//}

これをコンパイルすると、以下の CSS になります。

//list[][CSS]{
  body {
    font-family: Helvetica, sans-serif;
    color:       #333;
  }
//}

@<code>{$font-stack} が、 @<code>{Helvetica, sans-serif}に、@<code>{$primary-color} が、 @<code>{#333} に、置き換わっています。
スタイルを変更したくなった際には、変数の値を変更するだけで良く、またその意図するところも明確にすることができるため、開発が容易となります。

== 入れ子 その１

HTML を記述していくと、タグは抱合関係になっていきます。例えば次のようにです。

//list[][HTML]{
  <nav>
    <ul>
      <li>
        <a href="#">index.html</a>
      </li>
      <li>
        <a href="#">about.html</a>
      </li>
      <li>
        <a href="#">contact.html</a>
      </li>
    </ul>
  </nav>
//}

このような HTML に対して、スタイルを適用するとき、Sass を使うと、とても簡単に記述できます。

//list[][SCSS]{
nav {
  ul {
    margin: 0;
    padding: 0;
    list-style: none;
    li {
      display: inline-block;
      a {
        display: block;
        padding: 6px 12px;
        text-decoration: none;
      }
    }
  }
}
//}

@<code>{nav} の中に@<code>{ul}があり、@<code>{ul} の中に@<code>{li} がありと、それぞれの抱合関係が明確であり、HTMLの構造そのままに記述していけるので、とても楽にスタイルシートを書くことができます。

これをコンパイルすると、次のCSSになります。

//list[][CSS]{
nav ul {
  margin: 0;
  padding: 0;
  list-style: none;
}

nav ul li {
  display: inline-block;
}

nav ul li a {
  display: block;
  padding: 6px 12px;
  text-decoration: none;
}
//}

このように入れ子(ネスト)になっている場合、CSS では、スタイルの適用先を限定するために、 @<code>{nav ul li a} と書かなくてはなりませんでしたが、不要になり、とても円滑に記述できます。早速、活用していきましょう。

== 入れ子 その２

CSS の「擬似クラス」も楽に記述できます。@<href>{https://developer.mozilla.org/ja/docs/Web/CSS/Pseudo-classes, MDN Web Docs} には、次のように書かれています。

//quote{
  CSS の擬似クラスは、セレクタに付加するキーワードであり、選択された要素に対して特定の状態を指定します。例えば @<code>{:hover} 擬似クラスで、利用者のポインタが当たったときにボタンの色を変更することができます。@<code>{:active} 疑似クラスは、ユーザーによってアクティブ化されている要素を表します。マウスを使用する場合は、「アクティブ化」とは普通、左ボタンを押し下げたときに始まります。
//}

//list[][CSS]{
  /* 通常のリンクの色 */
  a {
    color: pink;
  }

  /* 利用者のポインタが当たっているすべてのリンク */
  a:hover {
    color: blue;
  }

  /* アクティブ化されている <a> をすべて選択します */
  a:active {
    color: red;
  }
//}

このような場合も @<code>{Sass} では簡潔に記述できます。

//list[][SCSS]{
  a {
    color: pink;

    &:hover {
      color: red;
    }

    &.active {
      color: blue;
    }
  }
//}

@<code>{&} で繋ぐことにより、纏めて書けることに着目してください。

== スタイルファイルの分割管理

少し大きなウェブサイトを作成していくと、スタイルシートは 1000行、2000行と、すぐには理解できないくらいの行数へと増えていきます。

一つの大きなスタイルシートを管理するのはとても大変です。
このため、機能ごとに個々のスタイルシートに分け、管理することで、全体の見通しも良くなります。 @<fn>{layer}

//footnote[layer][CSSでは @<code>{@import} や @<code>{@layer} を使えます。]


スタイルシートの分割管理には、いくつかの指針がありますが、ここでは分かりやすく簡潔な @<code>{FLOU(フロウ)} に従って分割した例を示します。 @<fn>{fn-import}
//footnote[fn-import][従来の@<code>{@import}に代えて@<code>{@use}や@<code>{forward}を用いるよう推奨されています。Middleman非対応のため @<code>{@import}を使っています。]

//list[][style.css.scss]{
  // リセットCSS など基盤となる部分のスタイルシート
  @import "foundation";

  // 要素の配置に関するスタイルシート
  @import "layout";

  // それぞれの部品に関するスタイルシート
  @import "object";

  // 色や間隔の設定などあると便利なスタイルシート
  @import "utility";
//}

@<file>{foundation.scss}, @<file>{layout.scss}, @<file>{object.scss}, @<file>{utility.scss} の 四つのファイルを取り込んで、一つの @<file>{style.css.scss} が出来上がります。

取り込まれる部品であることを分かりやすくするために、ファイル名の先頭に @<file>{_(アンダーバー)} を付けて、@<file>{_foundation.scss}, @<file>{_layout.scss}, @<file>{_object.scss}, @<file>{_utility.scss} とすることもあります。

一つの巨大なスタイルシートを管理するのは、とても大変ですので、機能ごと、部品ごとにファイルの分割し、管理するのがお薦めです。

== ミックスイン

CSS では、一度定義した CSS の再利用は難しいですが、Sass ではミックスインを使うことで CSS の再利用が可能になります。

ミックスインを使うとプロパティやセレクタをまとめてワンセットにしておいて、それらを読み込むことができます。
ミックスインは @<code>{@mixin} ディレクティブ(指示命令)を用いて定義し、 @<code>{@include} ディレクティブで定義したミックスインを呼び出します。
ミックスインでは @<code>{引数,ひきすう}を取ることができるので、より使い回しが柔軟にできます。
ミックスインは、 @<code>{@mixin} の後に半角スペースを置き、任意の名前で定義します。

具体的に、使い方を見ていきましょう。

//list[][SCSS]{
  // ミックスインの定義
  @mixin gray-box {
    margin:     20px 0;
    padding:    10px;
    border:     1px solid #999;
    background: #eee;
    color:      #333;
  }

  .card {
    // 定義したミックスインの呼び出し
    @include grayBox;
  }

  .photo {
    // 定義したミックスインの呼び出し
    @include grayBox;
  }
//}

これをコンパイルすると、次のようになります。

//list[][CSS]{
  .card {
    margin:     20px 0;
    padding:    10px;
    border:     1px solid #999;
    background: #eee;
    color:      #333;
  }

  .photo {
    margin:     20px 0;
    padding:    10px;
    border:     1px solid #999;
    background: #eee;
    color:      #333;
  }
//}

@<code>{card} クラスや、 @<code>{photo} クラスといった複数のクラスに、同じスタイルを適用したい場合に、同じ CSS を繰り返し 書かずに済みます。もし、一つのクラスにしか適用しないスタイルであっても、ミックスインを使うことで、意味や修正が容易となりますので、活用していきましょう。

=== 引数を使ったミックスイン

ミックスインは引数を取ることができます。引数はミックスイン名の後に括弧を書き、その括弧の中に記述します。引数が複数ある場合は、カンマで区切って記述します。

それでは、具体例を見ていきましょう。

//list[][scss]{
  // 枠線の色、幅、丸め具合を指定するミックスイン
  @mixin my-border($color, $width, $radius) {
    border: {
      color:  $color;
      width:  $width;
      radius: $radius;
    }
  }

  // 先に定義した 枠線ミックスインを取り込む
  p {
    @include my-border(blue, 1px, 3px);
  }
//}

//list[][CSS]{
  p {
    border-color:  blue;
    border-width:  1px;
    border-radius: 3px;
  }
//}

枠線の指定など、良く使いますので、このようなミックスインを定義しておき、適宜取り込むようにすると、開発効率がとても上がりますので、お薦めです。

=== 引数に初期値を設定する

引数の初期値を設定しておくと、初期値と同じ値を使用する場合は、引数を省略することができます。よく使う値があれば、初期値を設定しておくと便利です。

引数の初期値を設定するには、変数 と同じ書式 で記述します。つまり、名前は @<code>{$} から始め、 @<code>{:} で区切って値を指定します。

呼び出す際は、引数が初期値と同じ場合は、 @<code>{()} や値は省略することができます。初期値と値が異なる場合だけ、引数の値を指定します。

具体例を見ていきましょう。

//list[][SCSS]{
  // 角丸用のミックスイン
  // 初期値は 5px
  @mixin kadomaru($radius: 5px) {
    border-radius: $radius;
  }

  .foo {
    // 角丸ミックスインを取り込む
    // 引数を与えていないので 初期値の 5px が使われる
    @include kadomaru;
  }

  .bar {
    // 角丸ミックスインを取り込む
    // 引数を与えていないので 初期値の 5px が使われる
    @include kadomaru();
  }

  .baz {
    // 角丸ミックスインを取り込む
    // 引数を与えたので 10px が使われる
    @include kadomaru(10px);
  }
//}

これをコンパイルすると、次のCSSが得られます。

//list[][CSS]{
  .foo {
    border-radius: 5px;
  }

  .bar {
    border-radius: 5px;
  }

  .baz {
    border-radius: 10px;
  }
//}

=== メディアクエリへの活用

@<href>{https://www.tam-tam.co.jp/tipsnote/html_css/post10708.html, Sassの変数とmixinで変更に強いメディアクエリをつくる} という記事があります。

Sass を使うとメディアクエリが書きやすくなりますので、引用してご紹介いたします。

レスポンシブウェブデザインではメディアクエリを書くことが多くなります。通常のCSSではブレークポイントを変更したくなったときに、すでに書いてしまった箇所を直していくのはとても大変です。

Sass を使えば、変数やミックスインを使うことで一ヶ所で管理することが容易になります。

それでは、利用例を挙げて行きましょう。

//list[][SCSS]{
  // ブレークポイントの定義
  $breakpoints: (
    "tablet":  "(min-width: 481px)",
    "desktop": "(min-width: 961px)",
  ) !default;

  // メディアクエリ用のミックスイン mq の定義
  @mixin mq($bp: tablet) {
    @media #{map-get($breakpoints, $bp)} {
      @content;
    }
  }
//}

@<code>{@mixin} を呼び出すときは次のように使います。

//list[][SCSS]{
  .card {
    color: blue;

    // 引数を省略
    // 初期値の タブレット用のメディアクエリ
    // (min-width: 481px) が展開される
    @include mq() {
      color: yellow;
    }

    // 引数を指定
    // 指定した デスクトップ用のメディアクエリ
    // (min-width: 961px) が展開される
    @include mq(desktop) {
      color: red;
    }
  }
//}

これをコンパイルすると、次のCSSが得られます。

//list[][CSS]{
  .card {
    color: blue;
  }

  @media (min-width: 481px) {
    .card {
      color: yellow;
    }
  }

  @media (min-width: 961px) {
    .card {
      color: red;
    }
  }
//}

@<code>{$breakpoints} は、Sass の @<B>{マップ型変数} で書かれていますので、少し見慣れない感じもしますが、ブレークポイントの定義 をしている変数です。ブレークポイントの数値を変更したい場合や、大画面用のブレークポイントを追加したい場合など、@<code>{$breakpoints} を書き換えるのみで、対応できます。

ウェブサイトのレスポンシブ対応をするに当たってはメディアクエリは不可欠です。Sass を使うと、簡単にメディアクエリを書くことができますので、活用していきましょう。 @<fn>{fn-range}
//footnote[fn-range][Media Queries Level 4 にて、範囲指定構文が提唱されています。@<code>{@media (width <= 480px){\}} と分かりやすく書くことができます。Safari での対応が待たれるところです。]

== 数値の操作

=== 四則演算

Sass では数値型の値に計算の記号を使うことで計算をすることができます。単位を省略すると元の単位にあわせて計算されます。

早速、使用例を見ていきましょう。

//list[][SCSS]{
  .thumb {
    width:   200px - (5 * 2) - 2;
    padding: 5px + 3px;
    border:  1px * 2 solid #ccc;
  }
//}

//list[][CSS]{
  .thumb {
    width:   188px;
    padding: 8px;
    border:  2px solid #ccc;
  }
//}

幅など、それぞれのプロパティが、計算されているのが分かることと思います。
手計算して、 @<code>{width: 188px;} と算出しても良いですが、計算間違いも起こりますし、 @<code>{width: 200px - (5 * 2) - 2;} と、その導出過程を明示することで、意図も明らかになります。 @<fn>{calc}

//footnote[calc][CSS にも プロパティ値を計算するための @<code>{calc()} 関数がありますので、これを使って計算することができます。Sass では より強力かつ柔軟に演算が行えるようになっています。]


//blankline

計算で使える記号には、以下のようなものがあります。

//table[][演算子の種類][csv=on]{
演算, 記号
============
加算, @<code>{+}（プラス)
減算, @<code>{-}（ハイフン）
乗算, @<code>{*}（アスタリスク）
除算, @<code>{/}（スラッシュ）
剰余, @<code>{%}（パーセント）
//}

実際には、以下のように変数を使って計算することが多いと思います。

//list[][SCSS]{
  $main_width: 600px;
  $border_width: 2px;

  .card {
    $padding: 5px;
    width: $main_width - $padding * 2 - $border_width *2;
  }
//}

//list[][CSS]{
  .card {
    width: 586px;
  }
//}

=== 色を操作する関数

Sass で計算できるのは、数値だけではありません。 スタイルシートでよく用いる「色」も操作することができます。より明るい色にしたい、暗い色にしたいなど、そのための専用の関数が用意されています。

//table[][色を操作する関数]{
関数名	機能	実行例
-----------------
@<code>{lighten($color, $amount)}	明るい色を作成	@<code>{lighten(#800, 20%)} @<br>{} @<code>{=>} @<code>{#e00}
@<code>{darken($color, $amount)}	暗い色を作成	@<code>{darken(#800, 10%)} @<br>{} @<code>{=>} @<code>{#500}
@<code>{mix($color1, $color2, [$weight])}	中間色を作成	@<code>{mix(#f00, #00f, 25%)} @<br>{} @<code>{=>} @<code>{#3f00bf}
@<code>{saturate($color, $amount)}	彩度の高い色を作成	@<code>{saturate(#855, 20%)} @<br>{} @<code>{=>} @<code>{#9e3f3f}
@<code>{desaturate($color, $amount)}	彩度の低い色を作成	@<code>{desaturate(#855, 20%)} @<br>{} @<code>{=>} @<code>{#726b6b}
@<code>{rgba($color, $alpha)}	RGB値に透明度を指定	@<code>{rgba(blue, 0.2)} @<br>{} @<code>{=>} @<code>{rgba(0, 0, 255, 0.2)}
//}

例えば、 @<code>{color: #800; } (赤茶色) を、もう少し明るい色にしたい場合には、 @<code>{color: lighten(#800, 20%); } と書くことで、 @<code>{color: #e000} (緋色) となり、明るくなります。

様々な関数が用意されていますので、使って行きましょう。

== オリジナル関数の定義

色の操作をする関数はとても便利でした。そして、Sass では、自分で独自の関数を定義することもできます。

構文は、次の通りです。

//list[][SCSS]{
  @function 関数名($引数) {
    // 処理の記述
    @return 戻り値;
  }
//}

@<code>{@function} で関数の宣言をします。独自の関数名を命名し、(必要であれば)引数を設定します。 関数の戻り値(計算結果)は、@<code>{@return} を使って返します。

例として、大きさを変更する独自関数を作ってみましょう。

//list[][SCSS]{
  // 引数で与えられた $value の $scale 倍を返す関数
  // ($size の 初期値は 1 にしている)
  @function change-size($value, $scale: 1) {
    @return $value * $scale;
  }

  .small.card {
    // 幅を 200px の 2/3 倍 にする
    width: change-size(200px, 2/3) ;
  }

  .card {
    // 倍率の指定をしないときには 初期値の 1 が使われる
    width: change-size(200px) ;
  }

  .large.card {
    // 幅を 200px の 1.5 倍 にする
    height: change-size(200px, 1.5);
  }
//}

//list[][CSS]{
  .small.card {
    width: 133.3333333333px;
  }

  .card {
    width: 200px;
  }

  .large.card {
    width: 300px;
  }
//}

カードの大小によって、幅を変えることができました。
#@# 関数を用いることにより、定型的な処理を手作業で行うのではなく、より生産的な部分に注力することができます。始めのうちは慣れないかもしれませんが、理解して、活用していきましょう。

=== コメント
独自に定義した関数の場合、後から使う人のために、その関数がどのようなものなのか、働きや引数の型や単位の有無など使用方法が分かるようにコメントを残すようにしましょう。

ここでは、グラデーション を作成する関数を例に挙げます。 @<fn>{gradiention}

//footnote[gradiention][ここでは、自作する例を挙げましたが、@<href>{https://www.infact1.co.jp/staff_blog/webmarketing/40006/, 「簡単に美しいグラデーションを作れる便利サイト4選」}のようなサイトもございます。ご活用下さい。]

//list[][SCSS]{
  // @function gradation グラデーションの値を返す
  // @param    {Color}  $base-color 元の色
  // @param    {Number} $amount 0-100%の数値 既定値は20%
  // @return   {String} グラデーションの値を返す
  @function gradation($base-color, $amount: 20%) {
    @return linear-gradient($base-color, darken($base-color, $amount));
  }

  .card {
    background: gradation(#0f0);
  }
//}

これをコンパイルすると、次のCSSが得られます。

//list[][CSS]{
  .card {
    linear-gradient(rgb(0, 255, 0), rgb(0, 153, 0));
  }
//}

@<code>{.card}クラスの背景色が、緑のグラデーションとなりました。

//blankline

ここでは、基本的な Sass の使い方の例を取り上げましたが、他にも @<href>{https://sass-lang.com/, 公式サイト} や、@<href>{https://www.webdesignleaves.com/pr/css/css_basic_08.html, Web Design Leaves} では、様々な使い方が解説されています。より深い知識、情報が必要となった際には、きっと役立つことと思いますので、ご参考になれば幸いです。
