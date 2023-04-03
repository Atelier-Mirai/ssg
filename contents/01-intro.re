= 導入

//abstract{
  ウェブサイトを作成する際、少し大きなサイトになると、ヘッダーやフッターなど、共通する部品を纏めて楽に管理したくなります。また、素の @<code>{HTML} や @<code>{CSS} で、構築するのは辛くなりますので、@<code>{Slim} や @<code>{Sass} など、より効率的な言語を使いたくなるものです。こういったときに活躍するのが、@<B>{「静的サイトジェネレータ(生成機)」}です。

  静的サイトジェネレータとして知られる多くのシステムがありますが、ここでは、 @<code>{Ruby} @<fn>{ruby} ベースでとても使いやすい、@<code>{Middleman} をご紹介いたします。
//}

//makechaptitlepage[toc=on]

//footnote[ruby][@<code>{Ruby} とは、@<B>{まつもとゆきひろ} さんが考案した、柔軟性に富む優れた書き味で人気のプログラミング言語です。 @<href>{https://www.ruby-lang.org/ja/, オブジェクト指向スクリプト言語 Ruby}]



== 作成例のご紹介

//image[mizubasho][][width=75%,border=on]

持統天皇の御製「春過ぎて夏來にけらし　白妙の衣干すてふ　天の香具山」。百人一首でもよく知られています。当時の奈良を偲ぶ蓮の花咲くヒーローイメージが目を引きます。

尾瀬の「水芭蕉」を謳った唱歌「夏の思い出」を紹介しています。 @<fn>{mizubasho}

//footnote[mizubasho][水芭蕉は里芋科の多年草で、尾瀬を始め日本各地で群生しています。静的サイトジェネレータとして紹介する@<ruby>{Middleman,ミドルマン}に因み、「み」から始まる花として選びました。]

//blankline

== 静的サイトジェネレータの利便性

作成例に相応しく簡潔に、「ヘッダー、ナビゲーションメニュー、コンテンツ、フッター」から成り立っています。

慣れている方であれば、HTMLで文書構造を、CSS で配置と装飾を、JavaScript で動的表現をと、書き下してすぐに完成させられることと思います。

そしてこのような簡潔なウェブサイトであっても、各ページのHTMLやCSSは多数の行数となり、管理が大変になります。「ヘッダー」一つの修正であっても、全ページの更新が必要ですし、長大なHTML / CSSから目的の箇所を見いだすのも至難の業となります。

「ヘッダー」「ナビゲーションメニュー」など、個々の部品ごとに、HTML や CSS を管理できたらどうでしょうか。とっても楽に管理できるのではないでしょうか。

また、素の @<code>{HTML} は @<code>{<h1></h1>} などと開始タグや終了タグが煩わしく、@<code>{CSS} も @<code>{h1 { font-size: 48px; \} h1 a { text-decoration: none; \}} と個々の要素ごとに記述するのも大変です。

このような状況を解決するのが「静的サイトジェネレータ」です。

== @<ruby>{Middleman,ミドルマン}のご紹介

静的サイトジェネレータとして知られる多くのシステムがありますが、ここでは、 @<code>{Ruby} @<fn>{ruby} ベースでとても使いやすい、@<code>{Middleman} をご紹介いたします。

@<code>{middleman} とは、「周旋人」「仲人」「媒介者」という意味です。
「ヘッダー」「ナビゲーションメニュー」など部品ごとに、素の @<code>{HTML} や @<code>{CSS} に代えて、@<code>{Slim} や @<code>{Sass} で書いたソースコードを、完成形の @<code>{HTML}ファイルに変換、取り持ってくれます。

== コード例の紹介

=== ヘッダー
ヘッダー部分を @<code>{HTML} に代えて @<code>{Slim} で記述しています。開始タグや終了タグが取れ、CSSライクにクラス名の記述もでき、すっきりしています。

//list[][_header.slim]{
  header
    a.rainbow.gradation.text href="index.html" 水芭蕉
  nav
    ul
      li
        a href="#omoide"
          i.fa-brands.fa-envira.fa-lg.fa-fw
          | 夏の思い出
//}

@<code>{CSS} に代えて @<code>{SCSS} で記述しています。「入れ子」にしたり変数名も使用できます。
//list[][_header.scss]{
  header  {
    font-size: clamp(48px, 12vw, 54px);
    font-weight: bold;

    a {
      color: inherit;
      text-decoration: none;
    }

    @media (min-width: 768px) {
      justify-self: start;
    }
  }
//}

=== レイアウトファイル

ウェブサイトの各ページの構造は、ほぼ共通しています。
そのため、枠組みとなるレイアウトファイルを用意し、コンテンツ部分のみを流し込めるようにすると、開発効率が上がります。

以下の例をご覧ください。

//list[][]{
doctype html
html
  head
    meta charset="utf-8"
    title = current_page.data.title || "水芭蕉"
    meta content="width=device-width" name="viewport"


    / ファビコン & アップルタッチアイコン
    = favicon_tag 'favicon.ico'
    = favicon_tag 'apple-touch-icon-180x180.png',
             rel: 'apple-touch-icon', sizes: '180x180', type:  'image/png'

    / 検索エンジン用の紹介文
    meta content="夏の思い出 水芭蕉を謳います" name="description"

    / スタイルシートやスクリプトファイルを読み込む
    = stylesheet_link_tag "style"
    = javascript_include_tag "site"

  body
    / 部分ファイル _header.slim を読み込む
    = partial 'header'

    / この = yield が、index.html.slim等、各々の内容に置き換えられる
    = yield

    / 部分ファイル _footer.slim を読み込む
    = partial 'footer'
//}

@<code>{<head>}タグには、ウェブページの設定事項いろいろを記述していきますが、文字コードやビューポートなど概ね全てのページに共通しています。

また、@<code>{<body>}タグに書かれる事柄も、「ヘッダー」や「フッター」など各ページで共通するコードに関しては @<code>{= partial 'header'} と、先に紹介した 部分ファイル @<file>{_header.slim} を呼び出し、描画するようにすると、変更があった際の修正も容易で、また他のサイトを作成する際にも使い回しが利くなどの利点が得られます。

@<code>{= yield} は、各ページの「コンテンツ」に置換されます。
トップページであれば、@<file>{index.html.slim} を、お問い合わせページであれば、@<file>{contact.html.slim} を書くことのみに集中できます。


=== トップページ

作成例のトップページは「ヘッダー、ナビゲーションメニュー、コンテンツ、フッター」から成り立っています。

この中の「ヘッダー、ナビゲーションメニュー、フッター」に関しては、全てのページに共通する部分として、レイアウトファイルで既に描画していますので、トップページでは、「コンテンツ」部分のみを集中して書くことができます。

コンテンツは、ヒーローイメージと夏の思い出という記事部分に別れています。
纏めて書くこともできますが、部品ごとに分けると管理もしやすく見通しも良くなりますので、詳細は二つの部分ファイル @<file>{_hero.slim} と @<file>{_omoide.slim} に書き、それぞれを呼び出し、描画するようにします。

//clearpage

//list[][index.html.slim]{
  / ヒーローイメージ
  = partial 'hero'

  / 夏の思い出
  = partial 'omoide'
//}

//list[][_hero.slim]{
  .hero
    figure
      = image_tag "kaguyama.webp", alt: "藤原宮と蓮、天香久山"
    h1
      span.lefted.text.ml-3
        = link_to "持統天皇", "https://ja.wikipedia.org/wiki/持統天皇",
                              class: "gold gradation text"

      span.lefted.silver.gradation.glow.text 春過ぎて
      span.lefted.silver.gradation.glow.text 夏來にけらし　白妙の
      span.centered.silver.gradation.glow.text 衣干すてふ　天の香具山

    = javascript_include_tag "glow-text.js"
//}

//list[][_omoide.slim]{
  section.omoide#omoide
    h2.gold.title 夏の思い出
    article
      p
        | 夏が来れば　思い出す
        br
        | はるかな尾瀬　とおい空

    figure.rotate-3.frame.gallery
      = link_to "images/oze_mizubasho.webp", title: "梅雨前に訪れた尾瀬の風景" do
        = image_tag "oze_mizubasho.webp", alt: "尾瀬と水芭蕉"
      figcaption
        | 梅雨前に訪れた尾瀬の風景
//}

以上、簡単ではありましたが、静的サイトジェネレータ「@<ruby>{Middleman,ミドルマン}」を使ってのウェブサイト作成方法がイメージできたのではないでしょうか。

//blankline
大まかな全体像をご紹介したところで、次章以降でより詳細をご案内して参ります。
