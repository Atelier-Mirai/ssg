= 進化した HTML記述言語 Slim

//abstract{
  @<code>{Slim} は、HTML を簡単に書けるように進化した言語です。
  @<href>{https://github.com/slim-template/slim/blob/master/README.jp.md,公式サイト} をもとに簡単にご紹介いたします。
//}

//makechaptitlepage[toc=on]


== @<code>{Slim} の 特徴

@<code>{Slim} @<fn>{koushiki} は 不可解にならない程度に view の構文を本質的な部品まで減らすことを目指したテンプレート言語です。標準的な HTML テンプレートからどれだけのものを減らせるか、検証するところから始まりました。

多くの人が @<code>{Slim} に興味を持ったことで、機能的で柔軟な構文に成長しました。

//image[slim][][width=80%]


 * すっきりした構文
 ** 閉じタグの無い短い構文 (代わりにインデントを用いる)
 ** 閉じタグを用いた HTML 形式の構文
 ** 設定可能なショートカットタグ  @<br>{} デフォルトでは @<code>{#} は @<code>{<div id="...">} に、@<code>{.} は @<code>{<div class="...">} に展開されます。
 * 安全性
 ** デフォルトで自動 HTML エスケープ
 * 柔軟な設定
 * プラグインを用いた拡張性
 * 高性能
 ** ERB に匹敵するスピード

//footnote[koushiki][@<href>{http://slim-lang.com}]

== イントロダクション

=== Slim とは?

Slim は 高速、軽量なテンプレートエンジンです。
Slim の核となる構文は、「この動作を行うために最低限必要なものは何か。」との考えによって導かれています。

=== なぜ Slim を使うのか?
 * Slim によって メンテナンスが容易な限りなく最小限のテンプレートを作成でき、正しい文法の HTML が書けることを保証します。
 * Slim の構文は美しく、テンプレートを書くのがより楽しくなります。Slim は主要なフレームワークで互換性があるので、簡単に始めることができます。
 * Slim のアーキテクチャは非常に柔軟なので、構文の拡張やプラグインを書くことができます。

=== どうやって使い始めるの？

Slim を gem としてインストールすることによって、使い始めることができます。
(Middleman を使う場合は、Middleman 内で、Gemfile に書いていますので、以下の操作は不要です。)

//terminal[][]{
  gem install slim
//}

あなたの @<file>{Gemfile} に @<code>{gem "slim"} と書いてインクルードするか, ファイルに @<code>{require "slim"} と書く必要があります。これだけです! 後は拡張子に @<file>{.slim} を使うだけで準備完了です。

=== 構文例

Slim テンプレートがどのようなものか簡単な例を示します:

//list[][Slimの例]{
doctype html
html
  head
    title Slim のファイル例
    meta name="keywords" content="template language"
    meta name="author" content=author
    link rel="icon" type="image/png" href=file_path("favicon.png")
    javascript:
      alert('Slim は javascript の埋め込みに対応しています!')

  body
    h1 マークアップ例

    #content
      p このマークアップ例は Slim の典型的なファイルがどのようなものか示します。

    == yield

    - if items.any?
      table#items
        - for item in items
          tr
            td.name  = item.name
            td.price = item.price
    - else
      p アイテムが見つかりませんでした。いくつか目録を追加してください。
        ありがとう!

    div id="footer"
      == render 'footer'
      | Copyright &copy; #{@year} #{@author}
//}

=== 字下げ(インデント)について
字下げ(インデント)の深さはあなたの好みで選択できます。マークアップを入れ子にするには最低1つのスペースによる字下げ(インデント)が必要なだけです。

== ラインインジケータ

=== テキスト

@<code>{|(パイプ)}を使うと、Slim はパイプよりも深く字下げされた全ての行をコピーします。

//list[][slim]{
  body
    p
      |
        一行目
        二行目
        三行目
//}

//list[][html]{
  <body><p>一行目 二行目 三行目</p></body>
//}


改行を入れたい場合、次のように書けます。

//list[][slim]{
body
  p
    | 一行目
    br
    | 二行目
    br
    | 三行目
//}

//list[][html]{
  <body><p>一行目<br>二行目<br>三行目</p></body>
//}

=== インライン HTML

HTML タグを直接 Slim の中に書くことができます。Slim では、閉じタグを使った HTML タグ形式や HTML と Slim を混ぜてテンプレートの中に書くことができます。


//list[][slim]{
<html>
  head
    title Example
  <body>
    - if articles.empty?
    - else
      table
        - articles.each do |a|
          <tr><td>#{a.name}</td><td>#{a.description}</td></tr>
  </body>
</html>
//}

=== 制御コード @<code>{-}


@<code>{-(ダッシュ)} は制御コードを意味します。制御コードの例としてループと条件文があります。@<code>{end} は @<code>{-} の後ろに置くことができません。ブロックは字下げ(インデント)によってのみ定義されます。
複数行にわたる Ruby のコードが必要な場合、行末にバックスラッシュ @<code>{\\} を追加します。

//list[][slim]{
body
  - if articles.empty?
    | 在庫なし
//}

=== 出力 @<code>{=}

@<code>{=(イコール)}はバッファに追加する出力を生成する Ruby コードの呼び出しを Slim に命令します。Ruby のコードが複数行にわたる場合、例のように行末にバックスラッシュを追加します。

//list[][slim]{
= javascript_include_tag \
   "jquery",
   "application"
//}


行末・行頭にスペースを追加するために修飾子の @<code>{>} や @<code>{<} がサポートされています。

 * @<code>{=>} は末尾のスペースを伴った出力をします。 末尾のスペースが追加されることを除いて、単一の等合 (@<code>{=}) と同じです。
 * @<code>{=<} は先頭のスペースを伴った出力をします。先頭のスペースが追加されることを除いて、単一の等号 (@<code>{=}) と同じです。

=== HTML エスケープを伴わない出力 @<code>{==}

単一のイコール (@<code>{=}) と同じですが、@<code>{escape_html} メソッドを経由しません。 末尾や先頭のスペースを追加するための修飾子 @<code>{>} と @<code>{<} はサポートされています。

 * @<code>{==>} は HTML エスケープを行わずに、末尾のスペースを伴った出力をします。末尾のスペースが追加されることを除いて、二重等号 (@<code>{==}) と同じです。
 * @<code>{==<} は HTML エスケープを行わずに、先頭のスペースを伴った出力をします。先頭のスペースが追加されることを除いて、二重等号 (@<code>{==}) と同じです。

=== コードコメント @<code>{/} と HTML コメント @<code>{/!}

コードコメントにはスラッシュを使います。スラッシュ以降は最終的なレンダリング結果に表示されません。コードコメントには @<code>{/} を、html コメントには @<code>{/!} を使います。

//list[][slim]{
body
  p
    / この行は表示されません。
      この行も表示されません。
    /! html コメントとして表示されます。
//}

//list[][html]{
<body><p><!--html コメントとして表示されます。--></p></body>
//}

== HTML タグ

=== <!DOCTYPE> 宣言

doctype キーワードを使うことで、DOCTYPE を生成できます。

//list[][slim]{
doctype html
//}

//list[][html]{
<!DOCTYPE html>
//}

=== 行頭・行末にスペースを追加する (@<code>{<}, @<code>{>})

@<code>{a} タグの後に @<code>{>} を追加することで、末尾にスペースを追加するよう Slim に強制することができます。

//list[][slim]{
  a> href="url1" リンク1
  a> href="url2" リンク2
//}

@<code>{<} を追加することで先頭にスペースを追加できます。

//list[][slim]{
  a< href="url1" リンク1
  a< href="url2" リンク2
//}

これらを組み合わせて使うこともできます。

//list[][slim]{
  a<> href="url" リンク
//}

=== インラインタグ

タグをよりコンパクトにインラインにしたくなることがあるかもしれません。


//list[][slim]{
ul
  li.first: a href="/a" A リンク
  li: a href="/b" B リンク
//}

可読性のために、属性を囲むこともできます。

//list[][slim]{
ul
  li.first: a[href="/a"] A リンク
  li: a[href="/b"] B リンク
//}

=== テキストコンテンツ
タグと同じ行で開始するか、入れ子にするか、どちらかを選択できます。

//list[][slim]{
body
  h1 id="headline" ようこそ
//}

//list[][slim]{
body
  h1 id="headline"
    | ようこそ
//}

=== 動的コンテンツ (@<code>{=} と @<code>{==})

同じ行で呼び出すか、入れ子にすることができます。
Rubyコードにより、page_headline を定義している場合に使います。


//list[][slim]{
body
  h1 id="headline" = page_headline
//}

//list[][slim]{
body
  h1 id="headline"
    = page_headline
//}

=== 属性
タグの後に直接属性を書きます。通常の属性記述にはダブルクォート @<code>{"} か シングルクォート @<code>{'} を使わなければなりません (引用符で囲まれた属性)。

//list[][slim]{
a href="http://slim-lang.com" title='Slim のホームページ' Slim のホームページへ
//}

引用符で囲まれたテキストを属性として使えます。

==== 属性の囲み
区切り文字が構文を読みやすくするのであれば、三種類の括弧(@<code>{{...\}}、@<code>{(...)}、@<code>{[...]}) で属性を囲むことができます。

//list[][slim]{
body
  h1(id="logo") = page_logo
  h2[id="tagline" class="small tagline"] = page_tagline
//}

属性を囲んだ場合、属性を複数行にわたって書くことができます。
//list[][slim]{
h2[id="tagline"
   class="small tagline"] = page_tagline
//}

==== 引用符で囲まれた属性

例は、次のようになります。

//list[][slim]{
a href="http://slim-lang.com" title='Slim のホームページ' Slim のホームページへ
//}

引用符で囲まれたテキストを属性として使えます。

//list[][slim]{
a href="http://#{url}" #{url} へ
//}

==== Ruby コードを用いた属性
@<code>{=} の後に直接 Ruby コードを書きます。コードにスペースが含まれる場合,
@<code>{(...)} の括弧でコードを囲まなければなりません。ハッシュを@<code>{{...\}} に、配列を @<code>{[...]} に書くこともできます。

//list[][slim]{
body
  table
    - for user in users
      td id="user_#{user.id}" class=user.role
        a href=user_action(user, :edit) Edit #{user.name}
        a href=(path_to_user user) = user.name
//}

==== 真偽値属性
属性値の @<code>{true}、@<code>{false} や @<code>{nil} は真偽値として
評価されます。属性を括弧で囲む場合、属性値の指定を省略することができます。

//list[][slim]{
input type="text" disabled="disabled"
input type="text" disabled=true
input(type="text" disabled)

input type="text"
input type="text" disabled=false
input type="text" disabled=nil
//}

=== ショートカット

==== ID ショートカット @<code>{#} と class ショートカット @<code>{.}

@<code>{id} と @<code>{class} の属性を次のショートカットで指定できます。

//list[][slim]{
body
  h1#headline
    = page_headline
  h2#tagline.small.tagline
    = page_tagline
  .content
    = show_content
//}

これは次に同じです

//list[][slim]{
body
  h1 id="headline"
    = page_headline
  h2 id="tagline" class="small tagline"
    = page_tagline
  div class="content"
    = show_content
//}

== テキストの展開
Ruby の標準的な展開方法を使用します。テキストはデフォルトで html エスケープされます。

//list[][slim]{
body
  h1 ようこそ #{current_user.name} ショーへ。
//}

== 埋め込みエンジン
slim中に、cssなども記述できます。

例を以下に挙げます。

//list[][slim]{
  css:
    body: {
      background: yellow;
    }

  scss class="myClass":
    $color: #f00;
    body { color: $color; }

  markdown:
    #Header
      #{"Markdown"} からこんにちは!
      2行目!
//}


レンダリング結果は、次のようになります。

//list[][html]{
  <style type="text/css">body{background: yellow}</style>
  <style class="myClass" type="text/css">body{color:red}</style>
  <h1 id="header">Header</h1>
  <p>Markdown からこんにちは! 2行目!</p>
//}

@<code>{Ruby, JavaScript, CSS, SCSS, Markdown} 形式を使用することができます。

//table[tbl1][]{
フィルタ	必要な gems	説明
-----------------
ruby:	なし	Ruby コードを埋め込むショートカット
javascript:	なし	javascript コードを埋め込み、script タグで囲む
css:	なし	css コードを埋め込み、style タグで囲む
scss:	sass	scss コードを埋め込み、style タグで囲む
markdown:	redcarpet @<br>{}discount @<br>{} kramdown	Markdown をコンパイルし、テキスト中の @<code>{#{variables\}} を展開
//}

== Slim の設定

=== 構文ハイライト
様々なテキストエディタのためのプラグインがあります。

 * @<href>{https://github.com/slim-template/language-slim,Atom用language-slimパッケージ}

=== テンプレート変換

有志の方により、gem ファイルが公開されていますので、それを用いると、html と slim を相互変換できます。

==== htmlファイルからslimファイルへ変換

//terminal[][]{
$ html2slim index.html index.html.slim
//}

ブラウザから変換できるサイト @<href>{https://html2slim.herokuapp.com/} もございます。

==== slimファイルからhtmlファイルへ変換

//terminal[][]{
$ slimrb -p index.html.slim > index.html
//}
