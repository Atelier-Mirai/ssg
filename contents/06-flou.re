= 簡潔なCSS設計 FLOU

//abstract{
  少し大きなウェブサイトになると、数百行〜数千行にも渡るスタイルシートを書くことになります。一つの巨大なスタイルシートではとても扱いにくいので、機能ごと、部品ごとに分割して管理することになりますが、どのようにスタイルシートを設計し、管理すれば良いのでしょうか。

  BEMなど様々なCSS設計思想がありますが、簡素で分かり易く使えるFLOU(フロウ) @<fn>{flou} をご紹介いたします。 @<fn>{fn-layer}

//}

//footnote[flou][@<href>{https://webnaut.jp/technology/20170407-2421/, FLOCSSを扱いきれないあなたに贈る、スリムなCSS設計の話} より、抜粋引用]

//footnote[fn-layer][CSSが本質的にグローバルスコープであるため、その対応として生まれたBEM等ですが、いまいち美しくないように感じます。全ブラウザでサポートされたカスケードレイヤーに期待しています。@<href>{https://coliss.com/articles/build-websites/operation/css/css-cascade-layers.html, CSSの新機能カスケードレイヤー「@layer」CSSをレイヤー化して扱え、今までの実装方法が大きく変わる！}]

//makechaptitlepage[toc=on]



Webの開発をやったことのある方なら誰しも、「CSSって結局どう書くのがベストなの？」という悩みを感じたことがあるでしょう。
一見簡単なCSSですが、一度書き始めるとそのあまりの自由さに、まるで大海原に放り出された赤子のような気分になってしまいます。今日はCSSの設計について考えてみましょう。

//image[flou0][][width=70%]

== どんな設計があるの？
CSS設計 について調べてみると、OOCSS、SMACSS、FLOCSSなど、いろいろな設計思想があることがわかります。

 * OOCSS  @<href>{https://www.slideshare.net/stubbornella/object-oriented-css, Slide Share – Object Oriented CSS}
 * SMACSS @<href>{https://smacss.com/, SMACSS}
 * FLOCSS @<href>{https://github.com/hiloki/flocss, GitHub – FLOCSS}

FLOCSSを例に見てみましょう。概観としては、

 * Foundation
 * Layout
 * Object

の三つがあって、さらにObjectの中に、

 * Component
 * Project
 * Utility

があり、これらにCSSを分類して書くという設計となっています。

FLOCSSの設計に従うことで、

  * CSSがコンポーネント化されるので使いまわしや修正に強くなり、
  * MindBEMdingのネーミングルールによってクラスの役割が明確化され、
  * 全体として管理のしやすいソースコードが出来上がる

というメリットを得られます。
とはいえ、「ハイハイ、これに従って書けばいいのね」と書き始めたのも束の間、ほとんどの人は思うことでしょう。

  * 「このパーツってComponentとProjectのどっちだ…」
  * 「Utility使いまくらないと全然レイアウト実現できない…」
  * 「Layoutに書くこと少なすぎ…」

多くのWebサイト制作では、FLOCSSのポテンシャルを生かしきれずに、そのメリットがなんだかよくわからないままCSSを書いていくことになってしまいがちです。

相当大規模なプロジェクトならまだしも、ページ数の知れているWebサイトなんかではここまで巨大な設計図を引かなくても、うまいこと組み立てられそうですよね。

ということで、FLOCSSのいいところどりをした、よりスリムな設計「FLOU」を考えてみることにしましょう。

== F、L、O、Uの4つに分けよう

基本のアーキテクチャとしては、Foundation、Layout、Object、Utilityの4つに分けましょう。

例えばこんな組み方にしたいとき、

//image[flou1][][width=60%]{
//}

それぞれの役割は、図にするとこのようになります。

//image[flou2][][width=75%]{
//}

F、L、O、U、の4つが、Webページに必要な要素を過不足なく担当できているのがわかると思います。具体的なコーディングルールは、下記のような感じです。

=== Foundation
 * CSSリセットなど、すべてのベースとなるCSS
 * 基本的にコードは追加しない
 * foundation.scssに記述

//list[A Modern CSS Reset -モダンブラウザ用のCSSリセット][modern-css-reset.css]{
  /* Box sizing rules */
  *,
  *::before,
  *::after {
    box-sizing: border-box;
  }

  /* Remove default margin */
  body, h1, h2, h3, h4, p, figure, blockquote, dl, dd {
    margin: 0;
  }

  /* Remove list styles on ul, ol elements with a list role, which suggests default styling will be removed */
  ul[role="list"],
  ol[role="list"] {
    list-style: none;
  }

  /* Set core root defaults */
  html:focus-within {
    scroll-behavior: smooth;
  }

  /* Set core body defaults */
  body {
    min-height: 100vh;
    text-rendering: optimizeSpeed;
    line-height: 1.5;
  }

  /* A elements that don't have a class get default styles */
  a:not([class]) {
    text-decoration-skip-ink: auto;
  }

  /* Make images easier to work with */
  img,
  picture {
    max-width: 100%;
    display: block;
  }

  /* Inherit fonts for inputs and buttons */
  input,
  button,
  textarea,
  select {
    font: inherit;
  }

  /* Remove all animations and transitions for people that prefer not to see them */
  @media (prefers-reduced-motion: reduce) {
    html:focus-within {
     scroll-behavior: auto;
    }
    *,
    *::before,
    *::after {
      animation-duration: 0.01ms !important;
      animation-iteration-count: 1 !important;
      transition-duration: 0.01ms !important;
      scroll-behavior: auto !important;
    }
  }
//}

=== Layout
 * パーツの配置や、ラッパーとしての幅や高さなどを決定するクラス
 * layout.scssに記述

//list[][]{
  .justify-left {
    display: grid;
    justify-content: flex-start;
  }

  .justify-right {
    display: grid;
    justify-content: flex-end;
  }

  .justify-center {
    display: grid;
    justify-content: center;
  }
//}

=== Object
 * ページをまたいで使われる各種パーツを定義するクラス
 * そのパーツ内で常に同様の振る舞いをするものに関してのみスタイルを定義
 * object.scssに記述

//list[][]{
  .boxA {
    width: 100px;
    height: 100px;
    color: red;
  }

  .boxB {
    width: 200px;
    height: 200px;
    color: green;
  }
//}

=== Utility
 * 調整用のクラス
 * margin、padding、font-size、colorなどを付与するのに使用
 * 他種類のパーツ間の空き調整や、パーツとして認められないような、自由な振る舞いをする要素に対してはこちらのクラスを使用
 * utility.scssに記述

//list[][]{
  .mt10 { margint-top: 10px; }
  .mt20 { margint-top: 20px; }
  .mt30 { margint-top: 30px; }
//}

この設計を、F、L、O、Uの頭文字をとって、ここでは便宜的にFLOUと呼ぶことにします。

== FLOU設計のメリットは？
さて、このFLOUの設計を使うとどんなハッピーなことがあるのでしょうか。

=== レイアウトが劇的に楽
//sideimage[flou3][55mm][sep=5mm, side=R]{
  まず言えるのが、「モジュールの配置に関していちいちCSSを考える必要がなくなる」ということです。
  Layoutに適切なクラスを用意しておくことによって、モジュール（Object）たちを柔軟に、かつスピーディーに配置していくことが可能になります。
  例えば、CSS Gridを使ったLayoutクラスを使えば、右の図のように柔軟にモジュールを配置できます。
//}

#@# //image[flou3][][width=67%]{
#@# //}

//list[][index.html]{
  <div class="justify-left">
    <div class="box"></div>
    <div class="box"></div>
  </div>

  <div class="justify-center">
    <div class="box"></div>
    <div class="box"></div>
  </div>

  <div class="justify-right">
    <div class="box"></div>
    <div class="box"></div>
  </div>

  <div class="justify-left direction-row">
    <div class="box"></div>
    <div class="box"></div>
  </div>

  <div class="justify-center direction-row">
    <div class="box"></div>
    <div class="box"></div>
  </div>

  <div class="justify-right direction-row">
    <div class="box"></div>
    <div class="box"></div>
  </div>
//}

//list[][layout.scss]{
  .justify-left {
    display:         grid;
    grid-auto-flow:  column;
    justify-content: start;
  }

  .justify-center {
    display:         grid;
    grid-auto-flow:  column;
    justify-content: center;
  }

  .justify-right {
    display:         grid;
    grid-auto-flow:  column;
    justify-content: end;
  }

  .direction-row {
    display:        grid;
    grid-auto-flow: row;
  }

  .box {
    display:    inline;
    width:      50px;
    height:     50px;
    margin:     5px;
    background: red;
  }
//}

ここで使っている @<code>{.justify-left} などのクラスは、子要素に依存しないレイアウトのクラスとなるので、どんなモジュールに対しても使い回すことができます。 @<fn>{dependence}

//footnote[dependence][依存を完全に0にしているわけではありません。]

また、配置のためのクラス以外にも、

//list[][layout.scss]{
  .w25  { width:   25%; }
  .w50  { width:   50%; }
  .w100 { width:  100%; }
  .h25  { height:  25%; }
  .h50  { height:  50%; }
  .h100 { height: 100%; }
//}

のように、ラッパーの幅や高さを指定したりするLayoutクラスを用意しておくのも強力です。
このように、レイアウトに関する記述をLayoutクラスとして切り出し、使い回すことで、Object内で定義するモジュールを柔軟に配置することができるようになります。

=== CSSの見通しが良くなる

FLOUを使う二つ目の利点として、「ファイル全体の見通しが良くなる」というものがあります。
例えば、

//list[][object.scss]{
.boxA {
  width:      100px;
  height:     100px;
  color:      #ff0000;
  margin-top: 20px;
}

.boxB {
  width:      200px;
  height:     200px;
  color:      #00ff00;
  margin-top: 20px;
}

.textA {
  color:       #ff0000;
  font-weight: bold;
  margin-top:  20px;
}
//}

とするよりは、

//list[][utility.scss]{
  .mt20 {
    margin-top: 20px;
  }
//}

//list[][object.scss]{
  .boxA {
    width:  100px;
    height: 100px;
    color:  #ff0000;
  }

  .boxB {
    width:  200px;
    height: 200px;
    color:  #00ff00;
  }

  .textA {
    color:       #ff0000;
    font-weight: bold;
  }
//}

として、各モジュールにhtml上で

//list[][index.html]{
  <div class="boxA mt20">
    boxA
  </div>
//}

のように @<code>{.mt20} を付与する方が、全体の見通しが良くなります。

//blankline

ここでは、単に

  * それぞれのモジュールに対する記述が減ったので見やすくなった。

ということに加えて、

  * それぞれのモジュールにとって本質的でない記述が減った。

ということも重要です。

//blankline

上の例で記述されていた @<code>{margin-top: 20px;} は他のモジュールとの関係を定義するのに必要なだけであって、それぞれのモジュールには直接的には関係がない記述です。

このように、モジュール自体が他のモジュールとの関係に関するプロパティを持っていると、想定してなかったモジュールの組み合わせによって、「上の空きが大きすぎる」や「横並びになってくれない」などの不具合が生じかねません。

一方 FLOUの設計であれば モジュール(Object) 配置(Layout) 調整(Utility)を分けたことで、

  * モジュールのデザイン修正をしたい場合は Object クラスをいじって、
  * 配置に関しては Layout クラスの変更で対応し、
  * モジュール間の空きなどを調整したい場合は Utility クラスを変更すればよい。

ということになるので、仕様の変更に強くなります。

オブジェクトの修正でない、例えばレイアウトの変更や、数px単位の微妙な空き調整なんかは、結局html上でのクラスの付け替え作業になるので、他のページへの影響をケアする必要がなくなるというのも嬉しいところです。

== FLOUで書くときのポイントは？
FLOUでは、どの粒度でモジュールを切り出すかがポイントです。
理想的な切り出し方は、

 * できるだけ小さい単位で切り出す
 * しかし、常にセットで使うものに関しては一つのモジュールにまとめる

というところです。

//clearpage

//sideimage[flou4][60mm][sep=5mm,side=R]{
  例えば、こんな部品を作るとします。
//}

//sideimage[flou5][60mm][sep=5mm,side=R]{
この場合は、フォームとボタンとで一塊のモジュールとして切り出すのではなく、それぞれ別々の部品として切り出す方が良いでしょう。
//}

#@# 例えば、こんな部品を作るとします。
#@# //image[flou4][][width=50%]{
#@# //}
#@#
#@# この場合は、フォームとボタンとで一塊のモジュールとして切り出すのではなく、それぞれ別々の部品として切り出す方が良いでしょう。
#@# //image[flou5][][width=50%]{
#@# //}

なぜなら、もし「やっぱりこのページだけはフォームとボタンを縦並びに変更したい」となったときに、セットで切り出していた場合は、

  * 従来の「フォームとボタンが横並びのモジュール」に加えて、
  * 新規の「フォームとボタンを縦並びのモジュール」をCSSファイルに追加する

ということになりますが、別々で切り出していれば、

  * html上で、子要素を横並びにするLayoutクラスから @<br>{}子要素を縦並びにするLayoutクラスに変更する

という対応だけで済み、モジュールのパターン（今回で言う「フォーム」と「ボタン」）をCSS上で増やすことなくデザインが実現できるからです。

このように、モジュールはできるだけ小さい単位で管理し、配置に関しては Layoutクラスと Utilityクラス に任せることで、CSSの肥大化を抑えることができるのです。

とはいえ、もちろん「このパーツはどんな場面でも一緒に使う」と言い切れるものに関しては、一緒で管理するのが良いでしょう。

== まとめ

CSSの設計 に関しては、SMACSS や FLOCSSなどのオブジェクト指向の設計に従うことで、メンテナンス性に優れたコードを書くことができます。

しかし、どの粒度でオブジェクトを切り出すのか、またオブジェクト以外のクラスはどう扱うかなどはサイトの特性によってまちまちなので、「どんなサイトにでも使える万能な設計手法」というものは存在しません。

そんなときは、今回ご紹介したミニマムな設計である「FLOU」をベースに最適解を模索し、自己流の設計としてアレンジしてみてはいかがでしょうか！

//clearpage

===[column] Sass による実装例
FLOUは次の4つの層で構成されます。

 - 1. Foundation - reset / normalize / base...
 - 2. Layout     - justify-left / center / right...
 - 3. Object     - header/main/sidebar/footer...
 - 4. Utility    - margin / padding ...

//blankline

次は Sassを採用した場合の例です。

//list[][SassによるFLOUの実装例]{
  ├── foundation
  ├── layout
  ├── object
  │   ├── _footer.scss
  │   ├── _header.scss
  │   ├── _main.scss
  │   └── _sidebar.scss
  └── utility
       ├── _margin.scss
       ├── _padding.scss
       ├── _size.scss
       └── _text.scss
//}

モジュール単位でファイルを分割することによって、ページ単位またはプロジェクト単位でのモジュールの追加・削除の管理が容易になっています。

@<code>{style.css.scss}など、個々のスタイルシートの例を挙げます。

//list[][style.css.scss]{
  // FLOUの設計思想に従い、サイト全体で使うスタイルシートを取り込む
  @import "foundation/foundation";
  @import "layouts/layout";
  @import "objects/object";
  @import "utilities/utility";
//}

//clearpage

//list[][foundation.scss]{
  // リセットCSSなど、すべての基盤となるスタイルシート

  // A modern CSS reset
  @import "modern-css-reset";

  // font-family の指定
  $font-family: "Helvetica Neue",
                Arial,
                "Hiragino Kaku Gothic ProN",
                "Hiragino Sans", Meiryo,
                sans-serif;
  html { font-family: $font-family !important; }
//}

//list[][layout.scss]{
  // 部品の配置や、ラッパーとしての幅や高さなどを決定するクラス

  // 左寄せ指定
  .lefted.text {
    text-align: left !important;
  }
//}

//list[][object.scss]{
  // ページを跨いで使われる各種部品を定義するクラス
  @import 'footer';
  @import 'header';
//}

//list[][utility.scss]{
  // 間隔や色など、各種調整用のクラス
  @import "margin";
  @import "padding";
//}

===[/column]
