= 静的サイトジェネレータ @<ruby>{Middleman,ミドルマン}

//abstract{
  @<B>{静的サイトを構築する使いやすいフレームワーク} それが 「@<code>{Middleman}」です。

  インストールから始まり、様々な便利な機能の紹介を、サンプルコードとともに行っていきます。
//}

//makechaptitlepage[toc=on]

== インストール
公式ガイドは、 @<href>{https://middlemanapp.com/jp/, Middleman: 作業を効率化するフロントエンド開発ツール} です。ここから抜粋、説明を加えながら、ご案内していきます。

//blankline

Middleman は RubyGems のパッケージマネージャを使って配布されます。 つまり Middleman を使うには Ruby のランタイムと RubyGems の両方が 必要だということです。

Mac 利用者の方は、以下に従い、インストールしてください。 @<fn>{windows}
//footnote[windows][Windows 利用者の方は、 @<href>{https://youtu.be/nNc5Pm4IYeE, 公式インストールビデオ} が公開されていますので、そちらをご覧ください。]

=== Command Line Tools のインストール
macOS では ソースコードのコンパイルに Xcode の Command Line Tools が必要です。

ターミナルアプリ @<fn>{iterm2} より以下のコマンドを実行します。
//footnote[iterm2][より高性能な、@<href>{https://www.iterm2.com, iTerm2} がお薦めです。]

//terminal[][]{
  $ xcode-select --install
//}

=== HomeBrew のインストール
HomeBrew @<fn>{homebrew} は、macOS（またはLinux）用パッケージマネージャーです。
//footnote[homebrew][@<href>{https://brew.sh/index_ja, homebrew}]

HomeBrew を使うと、開発に必要な様々なプログラムを簡単にインストールすることが出来ます。公式サイトを始め、使い方について書かれた様々なサイトがございますので、詳細はそちらをご覧ください。

//terminal[][]{
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
//}

=== rbenv のインストール
rbenv は、Ruby の バージョン管理を行うためのツールです。Ruby は 毎年クリスマスにメジャーバージョンが提供されます。最新版を用いることが好ましいですが、様々な事情により、以前のバージョンを使いたい場合もあります。
そこで、それぞれのプロジェクトに応じた Ruby のバージョンを仕様できるよう、rbenv をインストールします。

//terminal[][]{
  $ brew install rbenv
  $ brew install ruby-build
//}

rbenvがインストールできたら、パスを通します。「パスとは、小道、道筋、進路、通り道などの意味を持つ英単語で、ITの分野では、コンピュータ内で特定の資源の所在を表す文字列のことをパス」 @<fn>{path}と言います。 パスを通すことにより、インストールしたプログラムをコマンドラインから実行できるようになります。
//footnote[path][出典: @<href>{https://e-words.jp/w/パス.html, IT用語辞典}]

//terminal[][]{
  # シェルに bash を使っている場合
  $ echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bash_profile

  # シェルに zsh を使っている場合
  % echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.zshrc
//}

rbenv のインストールが終わったら、初期設定を行います。
//terminal[][]{
  $ rbenv init
//}

@<code>{eval "$(rbenv init -)"}を、 @<code>{~/.bash_profile} または @<code>{~/.zshrc} に追記するよう、メッセージが表示されますので、お使いのエディタで、@<code>{~/.bash_profile} または @<code>{~/.zshrc} を開き、末尾に追記します。

ここまでで、rbenv のインストールは完了です。

@<B>{一旦ターミナルを閉じて、再度開きます。}

=== Ruby のインストール

//terminal[][]{
  $ rbenv install -l
//}
と、コマンド入力すると、インストール可能な Ruby のバージョンが次のように表示されます。

//terminal[][]{
  rbenv install -l
  2.6.10
  2.7.6
  3.0.4
  3.1.2
  jruby-9.3.6.0
  mruby-3.1.0
  picoruby-3.0.0
  rbx-5.0
  truffleruby-22.2.0
  truffleruby+graalvm-22.2.0

  Only latest stable releases for each Ruby implementation are shown.
  Use 'rbenv install --list-all / -L' to show all local versions.
//}

様々な Ruby のバージョンがあることが分かります。

ここでは一番新しい @<code>{3.1.2} をインストールすることにしましょう。

//terminal[][]{
$ rbenv install 3.1.2
//}

しばらくすると、インストールが完了します。

=== RubyGems とは

//quote{
  RubyGemsは、Ruby言語用のパッケージ管理システムであり、Rubyのプログラムと（"gem" と呼ばれる）ライブラリの配布用標準フォーマットを提供している。gemを容易に管理でき、gemを配布するサーバの機能も持つ。@<fn>{fn-wikipedia}
//}
//footnote[fn-wikipedia][出典: ウィキペディア]

有志の方々により Ruby でつくられたパッケージ(=便利なプログラム) は、@<href>{https://rubygems.org, RubyGems 公式サイト} で公開されており、様々なパッケージが提供されています。

ここでは、複数の gem を用いる際に定番となっている、@<code>{Bundler} と、人気の フレームワーク @<code>{Ruby on Rails} のインストール方法をご紹介いたします。

=== Bundler のインストール

RubyGems に登録されているところによると、

//quote{
Bundlerは、必要なgemsとバージョンを正確に追跡してインストールすることで、Rubyプロジェクトに一貫した環境を提供します。
//}

とのことです。

あるプロジェクトでは、X, Y という二つの gem を使います。そして、X という gem が機能するためには、A という別のgemの特定のバージョンを必要としており、Y という gem を機能させるためには、B という別のgemの特定のバージョンを必要とするような状況を考えてみましょう。

それぞれの gem が要求するバージョンを適切に管理していくのは、プロジェクトで用いる gem が増えるに従い大変となるのが容易に想像できます。

Bundler を導入すると、適切な gem が使われるよう、バージョン管理を自動で行うことが出来ます。

Bundler 自身も gem として提供されていますので、次のコマンドでインストール出来ます。

//terminal[][]{
$ gem inistall bundler
//}

//note[]{
  @<B>{【おまけ】Ruby on Rails のインストール}

  本書では、登場しませんが、人気のウェブフレームワーク Ruby on Rails を使いたい方もいらっしゃることと思います。

//terminal[][]{
$ gem inistall rails
//}

  でインストールできます。

  Middleman と Ruby on Rails は、良く似ています。

  * 静的サイトなら Middleman
  * 動的サイトなら Ruby on Rails

  と、容易に使い分けられることでしょう。
//}


=== Middleman のインストール

#@# macOS には Ruby と RubyGems の両方がパッケージされていますが、Middleman の 依存ライブラリの一部はインストール時にコンパイルする必要があります。macOS では コンパイルに Xcode の Command Line Tools が必要です。Xcode がインストール されている場合 以下のコマンドをTerminalから実行し、Command Line Tools をインストールしてください。

#@# //terminal[][]{
#@#   $ xcode-select --install
#@# //}

準備が整いましたので、次のコマンドを実行してください。

//terminal[][]{
  $ gem install middleman
//}

これで、Middleman のインストールは完了です。
インストール後、新しいコマンドと、3つの便利な機能が追加されます。

//terminal[][]{
  # 新たに Middleman を使ったサイトを作成する。
  $ middleman init

  # コーディング中に、ブラウザで結果を確認する。
  $ middleman server

  # 公開用のサイトデータを出力する。
  $ middleman build
//}

===[column] Bundler を使って gem のバージョン管理を行っている場合

gem のバージョン依存関係を管理するために、Bundler を使う旨、お話いたしました。
Bundler を使う場合、@<file>{Gemfile} という ファイルの中に、使いたい gem の名前と、(必要があれば)そのgem のバージョン指定を書きます。そして次のコマンドにより、Gemfile に記述された gem インストールします。

//terminal[][]{
  # Bundler を使って Gemfile に記述された gem インストールする。
  $ bundle install
//}

//terminal[][]{
% bundle install
Fetching gem metadata from https://rubygems.org/............
Resolving dependencies...
Using concurrent-ruby 1.1.9
Using bundler 2.3.5
(略)
Using middleman-core 4.4.2
Using middleman 4.4.2
Using middleman-autoprefixer 3.0.0
Using middleman-livereload 3.4.7
Using middleman-minify-html 3.4.1
Installing in_threads 1.6.0
Using image_optim 0.25.0
Using image_optim_pack 0.2.3
Using middleman-imageoptim 0.3.0
Bundle complete! 8 Gemfile dependencies, 64 gems now installed.
Use `bundle info [gemname]` to see where a bundled gem is installed.
//}
とメッセージが表示されます。 @<code>{middleman 4.4.2} と表示されていますので、Middleman の バージョン 4.4.2 が使われることが確認できます。

このコマンドにより、各 gem の 依存関係を解決するよう、適切なバージョンの gem が Bundler により、インストールされ、使用する様々な gem のバージョンを記した @<file>{Gemfile.lock} というファイルが作られます。

Bundler 管理下で、Middleman を使う場合には、以下のコマンドを用います。

//terminal[][]{
  # 新たに Middleman を使ったサイトを作成する。
  $ bundle exec middleman init

  # コーディング中に、ブラウザで結果を確認する。
  $  bundle exec middleman server

  # 公開用のサイトデータを出力する。
  $  bundle exec middleman build
//}

(先頭に @<code>{ bundle exec } が付いていることに着目です。)

===[/column]

== 新しいサイトの作成

開発を始めるに Middleman が動作するプロジェクトディレクトリを作る必要があります。

 - 1. 既存ディレクトリを、Middlemanで開発できるようにする場合には、ターミナルから以下のコマンドを実行してください。

//terminal[][]{
  $ middleman init
//}

 - 2. 新規に、Middlemanで開発するディレクトリを作成する場合には、ターミナルから以下のコマンドを実行してください。

//terminal[][]{
  $ middleman init my_new_site
//}

これにより、いくつかのディレクトリとファイルが自動生成されます。

@<file>{source} ディレクトリは、ウェブサイト構築用に、slim や sass 等のソースファイルを置くディレクトリです。

@<file>{config.rb} は、Middleman の設定を行うためのファイルです。
@<file>{Gemfile}は、Middlemanが必要とする、gem(=便利なプログラム)を記述したファイルです。

== 雛型
そのままでも使えますが、より便利に使えるよう、調整した雛型を作成しましたので、ご活用下さい。

@<file>{config.rb} や @<file>{Gemfile}の設定が済んでおり、作りやすいよう @<file>{index.html} の雛形などが同梱されています。

//terminal[][]{
  $ bundle exec middleman init my_new_site -T Atelier-Mirai/mizubasho
//}

@<file>{my_new_site} というディレクトリが作られています。
以下のコマンドで、@<file>{my_new_site} ディレクトリ に移動しましょう。
//terminal[][]{
  $ cd my_new_site
//}

今後の作業は、このディレクトリ内で行っていきます。

//clearpage
== ディレクトリ構造

//list[][]{
my_middleman_site/
  +-- .gitignore             # git の対象にしたくないファイルを記述する
  +-- Gemfile                # Middlemanが必要とするgemを記述する
  +-- Gemfile.lock
  +-- config.rb              # Middleman の各種設定用ファイル
  +-- build/                 # ウェブサイト公開用のHTMLなどが
  |                            出力されているディレクトリ
  +-- data/                  # データファイルを置くと、
  |                            テンプレート内(=slim)で利用できる
  +-- helper/                # 定型的なHTMLを簡単に記述するために
  |                            自作したプログラムを置くディレクトリ
  +-- source/                # ウェブサイト用のソースファイルを置く
      +-- images/            # 画像ファイル用のディレクトリ
      +-- index.html.slim    # slimで記述したトップページのファイル。
      |                        コンパイルすると、index.htmlになる。
      +-- javascripts/       # サイトで必要なJavaScript用のディレクトリ
      ¦   +-- site.js
      +-- layouts/           # レイアウトファイル(後述)を置くディレクトリ
      ¦   +-- layout.slim
      +-- stylesheets        # スタイルシートを置くディレクトリ
          +-- style.css.scss
//}

=== 主要なディレクトリ
Middleman は特定の目的のために source, build, data と lib ディレクトリを 利用します。各ディレクトリは Middleman のルートディレクトリに 存在します。

: source ディレクトリ
  source ディレクトリには利用するテンプレートの JavaScript、CSS や画像を含む、ビルドされる ウェブサイトのソースファイルが置かれます。

: build ディレクトリ
  build ディレクトリは静的サイトのファイルがコンパイルされ出力される ディレクトリです。

: data ディレクトリ
  ローカルデータ機能によって data ディレクトリの中に YAML や JSON ファイルを作成 し、これらのファイルの情報をテンプレートの中で利用することができます。data フォルダはプロジェクトの source フォルダと同じように,プロジェクトのルートに 置かれます。詳細については ローカルデータ を確認してください。

: helper ディレクトリ
  helper ディレクトリには、Middleman によって提供されるヘルパに加え、コントローラやビューの中からアクセスできる 独自のヘルパやクラスを追加することができます。

それぞれのファイルは、次のように記述します。
(雛形を導入すると、既に記述されています。)

//list[][Gemfile]{
  source "https://rubygems.org"

  # 静的サイトジェネレータ Middleman
  gem "middleman"
  gem "webrick"

  # ベンダープリフィックスを自動付与する
  gem "middleman-autoprefixer"

  # ファイル更新の際にブラウザを再読み込みする
  gem "middleman-livereload"

  # テンプレートエンジンとしてSlimを使用する
  gem "slim"

  # HTML圧縮を行う
  gem "middleman-minify-html"

  # html_builder(DSL)用にnokogiriも入れる
  gem "nokogiri"

  # img タグに width属性, height属性を付与する為に
  gem "fastimage"
//}

//list[][config.rb]{
  # JavaScript圧縮用ライブラリを読み込む
  require "uglifier"

  # コード変更すると、自動再読み込みされる
  activate :livereload

  # 相対URLを使う
  activate :relative_assets
  set :relative_links, true

  # ベンダープリフィックスを自動的に付与する
  activate :autoprefixer do |prefix|
    prefix.browsers = "last 2 versions"
  end

  # レイアウトファイルの指定
  set :layout, "site"
  page "index.html", layout: "top"
  # page "no_layout.html", layout: false

  # ビルド時の設定
  configure :build do
    # HTML圧縮
    activate :minify_html
    # CSS圧縮
    activate :minify_css
    # JavaScript圧縮
    activate :minify_javascript,
      compressor: proc {
        ::Uglifier.new(
          mangle: { toplevel: true },
          compress: { unsafe: true },
          harmony: true
        )
      }
    # アセットファイルのURLにハッシュを追加
    activate :asset_hash
    # テキストファイルのgzip圧縮
    activate :gzip
  end

  # Slim の設定
  # set :slim, {
  #   # デバック用にhtmlをきれいにインデントし属性をソートしない
  #   # (html, css, javascript の圧縮も無効化すると、
  #   #  学習用に読みやすいHTMLが出力される )
  #   pretty: true, sort_attrs: false
  # }

  # 動的サイトの設定例
  # data.cats.each do |neko|
  #   proxy "/#{neko.name}.html", "/neko_template.html",
      locals: { neko_data: neko }, ignore: true
  # end
//}

//list[][source/layouts/site.slim]{
doctype html
html
  head
    meta charset="utf-8"
    meta name="viewport" content="width=device-width"
    title
      = current_page.data.title || "さくら商会"
    = stylesheet_link_tag "style"

  body
    = yield
//}

== 開発サイクル

=== Middleman server

Middleman は開発のスタート時点から開発コード @<fn>{development}とプロダクションコード @<fn>{production}を分離します。これにより開発中に Slim, Sass など開発に有益なツールを利用することができます。
//footnote[development][開発コードとは、作成中に用いるコードのことです。]
//footnote[production][プロダクションコードとは、最終的に出来上がってウェブサイトの公開するためのコードのことです。]

Middleman を使う時間の大半は開発サイクルになります。
コマンドラインから、プロジェクトディレクトリの中でプレビューサーバを起動してください。

//terminal[][]{
$ bundle exec middleman server
//}

このコマンドはローカルの ウェブサーバを起動します。

//terminal[][]{
$ bundle exec middleman
== The Middleman is loading
== LiveReload accepting connections from ws://192.168.0.4:35729
== View your site at "http://Mac-mini.local:4567", "http://192.168.0.4:4567"
== Inspect your site configuration at "http://Mac-mini.local:4567/__middleman"
, "http://192.168.0.4:4567/__middleman"
//}

と、表示されていれば、無事にサーバーが起動しています。

//note[]{
//terminal[][]{
(略)
== Port "4567" is in use. This should not have happened. Please start "middlem
an server" again.
bundler: failed to load command: middleman (/Users/mirai/.rbenv/versions/3.1.0
/bin/middleman)
(略)
//}
とエラーメッセージが表示されるときには、他のターミナルで既に Middleman が起動しています。他のターミナルで起動している Middleman を終了してから、再度挑戦してください。
//}

ブラウザを開き、 @<code>{http://localhost:4567/} にアクセスして下さい。
それから、@<file>{source}ディレクトリ内で、ファイルを作成や編集して下さい。プレビューウェブサーバが起動しているおかげで、ブラウザ上で編集内容を確認できます。

プレビューウェブサーバを停止したい場合には、コマンドラインから @<code>{Ctrl + C} (@<code>{CtrlキーとCキーを同時に押す})で、停止できます。

//note[]{
サーバー起動中は、このターミナルウィンドウからはコマンド入力が行えません。
Git操作等のコマンド入力は、もう一つ別のターミナルウィンドウ(タブ)を開き、
そちらのウィンドウ(タブ)から行います。
//}

=== LiveReload (自動再読込)

Middleman にはサイト内のファイルを編集するたびにブラウザを自動的にリロードする拡張機能が実装されています。
まず Gemfile に middleman-livereload を追記してください。
(雛形の @<file>{Gemfile} には既に記述済です)

//list[][Gemfile]{
  gem "middleman-livereload"
//}

続いて @<file>{config.rb} を開いて次の行を 追加してください。
(雛形の @<file>{config.rb} には既に記述済です)

//list[][config.rb]{
  activate :livereload
//}

これでページ内容に変更があると、自動的にブラウザが再読込(リロード)されます。

== ビルド & デプロイ

=== @<code>{middleman build} でサイトをビルド

静的サイトのコードを出力する準備ができたら、サイトをビルドする必要があります。
コマンドラインを使い、@<code>{middleman build} を実行してください。

//list[][]{
  $ bundle exec middleman build
//}

//note[]{
//terminal[][]{
% bundle exec middleman build
bundler: failed to load command: middleman (/Users/mirai/.rbenv/versions/3.1.2
/bin/middleman)
//}

とエラーメッセージが表示される場合には、Bundler による gem ファイルのバージョン管理が行われていない状態です。

//terminal[][]{
% bundle install
//}
として、Gemfile に記述した gem をインストールして下さい。
//}

このコマンドは @<file>{source} フォルダにあるファイル毎に静的ファイルを作ります。Slim ファイルや Sass ファイルがコンパイルされ、ファイル圧縮などの機能が実行されます。そして、ビルドが完了すると、必要なものはすべて @<file>{build} ディレクトリに用意されます。

//terminal[][]{
% bundle exec middleman build
:image_optim is deprecated. Please use `:imageoptim` instead.
YAML Exception parsing /Users/mirai/rails_projects/my_new_site/source/fruits.h
tml.slim: (<unknown>): did not find expected key while parsing a block mapping
 at line 1 column 1
      create  build/stylesheets/foundation/modern-css-reset-a537b384.css
      create  build/stylesheets/style-85d5d9f4.css
      create  build/images/tora_s-6b7d4713.jpg
      create  build/images/logo-cd6002e6.jpg
      create  build/images/sea-2adf6e5e.jpg

      create  build/images/tama-ca888398.jpg
      create  build/images/zou-3128b283.jpg
        (略)
  imageoptim  build/images/tama-ca888398.jpg (18.62% / 33KiB smaller)
  imageoptim  fixed file mode on build/images/tama-ca888398.jpg file to match
source
  imageoptim  build/images/apple-touch-icon-180x180-7af643fc.png (12.62% / 7Ki
B smaller)
  imageoptim  build/imageoptim.manifest.yml updated
  imageoptim  Total savings: 120KiB
      create  build/javascripts/magnific-popup-custom-205d8eda.js.gz (272 Byte
s smaller)
      create  build/javascripts/site-17e02c7a.js.gz (76 Bytes smaller)
      create  build/index.html.gz (5.6 KB smaller)
      create  build/kitchen_sink.html.gz (8.4 KB smaller)
      create  build/fruits.html.gz (49 Bytes smaller)
      create  build/stylesheets/foundation/modern-css-reset-a537b384.css.gz (4
15 Bytes smaller)
      create  build/stylesheets/style-85d5d9f4.css.gz (10.1 KB smaller)
        gzip  Total gzip savings: 24.9 KB
Project built successfully.
//}

とメッセージが表示されました。

@<file>{build} ディレクトリを覗いてみると、@<file>{index.html}など、お馴染のファイル達が作られていることが確認できます。

適宜、公開(デプロイ) @<fn>{deploy}してください。

//footnote[deploy][ソースコード管理に @<code>{Git} を、ウェブサイトの公開に @<code>{Netlify} を使用すると、より快適に公開できます。]

=== アセットハッシュの付与
プロダクション環境では、一般的にアセットファイル名にハッシュ文字列を付与します。
ハッシュ文字列とは何でしょうか？

ハッシュ文字列を付与しないときには、次のように出力されます。
//list[][]{
  <link href="/stylesheets/style.css" rel="stylesheet">
//}

ハッシュ文字列を付与すると、次のようになります。
//list[][]{
  <link href="/stylesheets/style-85d5d9f4.css" rel="stylesheet">
//}

@<file>{style.css}が、@<file>{style-85d5d9f4.css} となりました。この @<file>{style}のあとに付与される文字列のことを、ハッシュ文字列といいます。このハッシュ文字列は、スタイルシートが更新される都度、異なる文字列となります。そのため、(ブラウザのキャッシュ機能による)「新しいスタイルシートをウェブサイトにアップしても、見た目が変わらない」という課題を解消することができます。

ハッシュ文字列を付与するには、 @<file>{config.rb} に次のように記述します。
(雛形の @<file>{config.rb} には既に記述済です)

//list[][config.rb]{
  activate :asset_hash
//}

== Frontmatter (前付け)
@<code>{Frontmatter}は、本の前付けの意味です。
@<code>{Frontmatter} は @<code>{YAML}フォーマット(形式)でテンプレート上部に記述することができる、ページ固有の変数です。

@<code>{Frontmatter}はテンプレートの最上部に記述します。そして、行頭から行末まで 3つのハイフン @<code>{---} によって、その他の部分から分離して書きます。このブロックの中では、テンプレート内で @<code>{current_page.data} ハッシュとして使えるデータを作ることができます。
つまり、Frontmatter(前付け)の中で、@<code>{title: "大好きな果物の紹介"} と書いたハッシュデータは、 テンプレートの中で、@<code>{current_page.data.title} として取得できます。

それでは、簡単な使い方の例を紹介します。 @<file>{fruits.html.slim}を次のように書いてみます。

//list[][source/fruits.html.slim]{
---
title: "大好きな果物の紹介"

my_favorite_fruits_list:
- あけび
- かき
- さくらんぼ
---

h1 大好きな果物

ol
  - current_page.data.my_favorite_fruits_list.each do |fruit|
    li = fruit
//}

レイアウトファイル @<file>{site.slim}は、次のようになっているとします。

//list[][source/layouts/site.slim]{
doctype html
html
  head
    meta charset="utf-8"
    meta name="viewport" content="width=device-width"
    title
      = current_page.data.title || "さくら商会"
    = stylesheet_link_tag "style"

  body
    = yield
//}

そうすると、ビルドして出来上がるhtmlファイル @<file>{fruits.html} は次のようになります。

//list[][build/fruits.html]{
<!DOCTYPE html><html><head><meta charset=utf-8 /><meta content="width=device-width" name=viewport /><title>大好きな果物の紹介</title><link href="stylesheets/style-85d5d9f4.css" rel=stylesheet /></head><body><h1>大好きな果物</h1><ol><li>あけび</li><li>かき</li><li>さくらんぼ</li></ol></body></html>
//}

少しでも配信時間を速くできるように、空白等を削除して、生成されています。
出来上がったウェブサイトを公開する場合には、これは都合が良いのですが、出力された内容を確認する為に、綺麗に整形しましょう。

手作業で行っても良いのですが、@<href>{https://lab.syncer.jp/Tool/HTML-PrettyPrint/, Syncer} というサイトがありますので、これを使ってみます。

//list[][]{
<!DOCTYPE html>
<html>
<head>
  <meta charset=utf-8 />
  <meta content="width=device-width" name=viewport />
  <title>大好きな果物の紹介</title>
  <link href="stylesheets/style-85d5d9f4.css" rel=stylesheet />
</head>
<body>
  <h1>大好きな果物</h1>
  <ol>
    <li>あけび</li>
    <li>かき</li>
    <li>さくらんぼ</li>
  </ol>
</body>
</html>
//}

@<code>{Frontmatter(前付け)}と、出来上がった @<file>{fruits.html} との対応関係を見てください。個々のページによって、タイトルは異なりますが、同じレイアウトファイル(雛形)に、ページのタイトルを渡すことができています。

また、@<code>{my_favorite_fruits_list} として、好きな果物を列挙しましたが、それぞれの果物が @<code>{Ruby} 持つ強力な @<code>{each} メソッドにより取り出され、@<code>{<li>}タグに展開される点にも着目してください。もしご希望ならば、「たんかん」や「なし」など、他の果物も簡単に追加できます。

//note[]{
  先ほど紹介したアセットハッシュが付与され @<code>{<link href="stylesheets/style-85d5d9f4.css" rel=stylesheet />} となっています。
//}

== テンプレート言語

@<B>{テンプレート言語}とは、ウェブサイトの作成を簡単にするために用いられる言語のことです。@<code>{Slim}や@<code>{Sass}が有名です。
@<code>{Slim}記法で記述すると@<code>{HTML}が、@<code>{Sass}記法では@<code>{CSS}が容易に書けるようになるとともに、ページ内で変数やループを使えるようになります。

@<code>{Middleman}で使うテンプレートは、そのファイル名にテンプレート言語の拡張子を含みます。具体的には、@<code>{slim}で書かれた@<file>{index}ページは、ファイル名の@<file>{index.html}に、さらに@<code>{slim}と拡張子を付けた@<file>{index.html.slim}という名前になります。

@<file>{source}ディレクトリの直下に、@<file>{index.html.slim}を置き、ビルドすると、@<file>{build}ディレクトリに、@<file>{index.html}が出力されます。

以下に例を挙げます。

//list[][index.html.slim]{
  h1 ようこそ
  ul
    - 3.times do |num|
      li = "#{num}回目"
//}

これをビルドすると、次のようになります。

//list[][index.html]{
  <h1>ようこそ</h1>
  <ul>
    <li>1回目</li>
    <li>2回目</li>
    <li>3回目</li>
  </ul>
//}

@<code>{- 3.times do |num| } @<code>{li = "#{num\}回目"} は、 @<code>{Ruby} での繰り返しの書き方です。

== ヘルパーメソッド

テンプレートヘルパはよくある @<code>{HTML} の作業を簡単にするため、テンプレートの中で使用できるメソッドです。
基本的なメソッドのほとんどは @<code>{Ruby on Rails} のビューヘルパを利用したことのある人にはお馴染みのものです。

=== リンクヘルパ

リンクを記述する際に、リンクヘルパを使うと簡単に書くことができます。
基本的な使い方は、@<code>{link_to}メソッドに、引数として「リンク名」と「リンク先URL」を与えます。

//list[][index.html.slim]{
  = link_to "わたくしのサイト", "https://mysite.com"
//}

これをビルドすると、次のようになります。

//list[][index.html]{
  <a href="https://mysite.com">わたくしのサイト</a>
//}

@<code>{link_to}メソッドはより複雑な内容のリンクを生成できるように、ブロックをとることもできます。

//list[][index.html.slim]{
  = link_to "http://mysite.com" do
    = image_tag "mylogo.png", alt: "ロゴマーク"
    p
      | わたくしの会社へようこそ
//}

ビルドすると、次のようになります。

//list[][index.html]{
  <a href="http://mysite.com">
    <img src="/images/mylogo.png" alt="ロゴマーク">
    <p>
      わたくしの会社へようこそ
    </p>
  </a>
//}

=== メールヘルパ
リンクが簡単に作成できたように、メールを容易に送信できるようタグを作ってくれる、メールヘルパもあります。

//list[][index.html.slim]{
  = mail_to 'taro@example.com', "メール"
//}

ビルドすると、次のようになります。

//list[][index.html]{
  <a href="mailto:taro@example.com">メール</a>
//}

=== イメージヘルパ

@<file>{source/images/}ディレクトリ内の画像を表示させたい場合には、イメージヘルパを使って、次のように書くこともできます。

//list[][index.html.slim]{
  = image_tag "mylogo.png", alt: "ロゴマーク"
//}

//list[][index.html]{
  <img src="/images/mylogo.png" alt="ロゴマーク">
//}

=== アセットヘルパ

@<code>{<head>}タグ内で良く用いられるアセットヘルパとして、次の三種類があります。

: @<code>{favicon_tag}
  ファビコンを作成する際に、使うと便利なタグです。

//list[][index.html.slim]{
  = favicon_tag "favicon.ico"
  = favicon_tag "apple-touch-icon-180x180.png",
                rel:   "apple-touch-icon",
                type:  "image/png",
                sizes: "180x180"
//}

//list[][index.html]{
  <link href="images/favicon.ico" rel="icon" type="image/ico">
  <link href="images/apple-touch-icon-180x180.png" rel="apple-touch-icon" type="image/png" sizes="180x180">
//}
画像は @<code>{images} ディレクトリに置く約束ですので、 @<code>{href="images/favicon.ico"} と展開されます。画像ディレクトリのパスが変更された際にも、 @<file>{config.rb} で設定するのみで良いので、保守効率も上がります。

: @<code>{stylesheet_link_tag}
  スタイルシートを読み込む際に、使うと便利なタグです。

//list[][index.html.slim]{
  = stylesheet_link_tag "style"
//}

//list[][index.html]{
  <link href="stylesheets/style.css" rel="stylesheet">
//}
スタイルシートは @<code>{stylesheet} ディレクトリに置く約束ですので、@<code>{href="stylesheets/style.css"} と展開されます。短く簡潔に書くことが出来ます。

: @<code>{javascript_include_tag}
  スクリプトを読み込む際に、使うと便利なタグです。

//list[][index.html.slim]{
  = javascript_include_tag "site"
//}

//list[][index.html]{
  <script src="javascripts/site.js"></script>
//}
スクリプトは @<code>{javascripts} ディレクトリに置く約束ですので、@<code>{href="javascripts/site.js"} と展開されます。

#@# //note[@<code>{stylesheet_link_tag, javascript_include_tag} の使い分け]{
//note[stylesheet_link_tag, javascript_include_tag の使い分け]{
CDN @<fn>{cdn} で配信されるコードには、 @<code>{link} タグや @<code>{script} タグで書き、自分で書いたものにはヘルパタグの利用が便利です。

//list[][Magnific Popup ライブラリを使用する際の例]{
/ CDN 配信
link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/magnific-popup.js/1.1.0/magnific-popup.min.css"
script src="https://cdnjs.cloudflare.com/ajax/libs/magnific-popup.js/1.1.0/jquery.magnific-popup.min.js"

/ 自作
= stylesheet_link_tag    "magnific-popup-custom"
= javascript_include_tag "magnific-popup-custom"
//}

//footnote[cdn][@<href>{https://e-words.jp/w/CDN.html, CDN(コンテンツデリバリネットワーク)とは、Web上で送受信されるコンテンツをインターネット上で効率的に配送するために構築されたネットワーク。}]

//}


=== ページクラス

サイト階層に対応する @<code>{body} タグの @<code>{class} 属性が生成されると便利です。 @<code>{page_classes} はこれらの属性名を生成します。 @<file>{projects/rockets/saturn-v.html.slim} にページがあるとすると、レイアウトには次のように表示されます。

//list[][source/projects/rockets/saturn-v.html.slim]{
  body class=page_classes
    h1 サターンＶ型ロケット
    p 月面着陸を成し遂げたアポロ計画で使われたロケットです。
//}

//list[][build/projects/rockets/saturn-v.html]{
  <body class="projects rockets saturn-v">
    <h1>サターンＶ型ロケット</h1>
    <p>月面着陸を成し遂げたアポロ計画で使われたロケットです。</p>
  </body>
//}

これにより簡単にページに @<code>{projects} や @<code>{rockets}、@<code>{saturn-v} のスタイルを適用できます。

=== カスタム定義ヘルパ

@<code>{Middleman} によって提供されるヘルパに加え、コントローラやビューの中からアクセスできる独自のヘルパを追加できます。良く使う@<code>{html}部品があれば、生成用のヘルパを創ると便利です。

ここではカスタム定義ヘルパの例として、ISBN番号からAmazonへのリンクを生成するヘルパを作ってみます。

カスタム定義ヘルパは、 @<file>{helpers}ディレクトリに配置すると分かりやすいです。ファイル名は任意ですが、 ここでは @<file>{custom_helper.rb} として、作成します。

//list[][helpers/custom_helper.rb]{
  # Stringクラスの拡張
  class String
    def to_amazon_url
      "https://www.amazon.co.jp/dp/#{self}"
    end

    def to_image
      "#{self}.jpg"
    end
  end

  # 本を紹介するためのカスタムヘルパの定義
  def introduce(book)
    title = book.title
    desc  = book.desc
    isbn  = book.isbn
    url   = isbn.to_s.to_amazon_url
    image = isbn.to_s.to_amazon_book_image

    t = content_tag :h2, class: 'title' do title end
    i = image_tag(image)
    d = content_tag :p, class: 'desc' do desc end

    content_tag :div, class: 'book' do
      link_to url, target: '_blank' do
        (t + i + d)
      end
    end
  end
//}

カスタムヘルパが定義できましたので、実際に使ってみます。

//list[][source/books.html.slim]{
---
title: "大好きな本の紹介"

my_favorite_books_list:
- title: CSSグリッドで作る HTML5&CSS3 レッスンブック
  desc: |-
        CSSグリッドをベースにすると、Webページ制作がシンプルになります。
        本書では、サンプルを作りながらステップ・バイ・ステップで学習することにより、モバイルファーストで本格的なレスポンシブに対応した実践的なWeb制作に関する知識をひと通り得ることができるようになっています。
        これからHTML5＆CSS3を使ったWebサイトの構築を学びたい人に最適の一冊です。
  isbn: 4802611897

- title: Ruby on Rails 6 実践ガイド
  desc: |-
        本書では、1つの企業向け顧客管理システムを作る過程で、RailsによるWebアプリケーション開発の基礎知識とさまざまなノウハウを習得していきます。各章末には演習問題が設けられているので、理解度を確かめながら確実に読み進められます。
        著者が試行錯誤を繰り返した上でのベストプラクティスを提供し、読者は、実際に業務システムを構築しながらRailsのさまざまな機能、方法、作法、メソッド、テクニックを学ぶことができます。
  isbn: 4295008052
---

h1 大好きな本

- current_page.data.my_favorite_books_list.each do |book|
  = introduce(book)
//}


これをビルドすると、次のような@<code>{HTML}が出力されます。

//list[][books.html]{
<div class="book">
  <a href="https://www.amazon.co.jp/dp/4295008052" target="_blank">
    <h2 class="title">
      Ruby on Rails 6 実践ガイド
    </h2>
    <img src="http://images-jp.amazon.com/images/P/4295008052.09.LZZZZZZZ.jpg" alt="" loading="lazy">
    <p class="desc">
      本書では、1つの企業向け顧客管理システムを作る過程で、RailsによるWebアプリケーション開発の基礎知識とさまざまなノウハウを習得していきます。各章末には演習問題が設けられているので、理解度を確かめながら確実に読み進められます。 著者が試行錯誤を繰り返した上でのベストプラクティスを提供し、読者は、実際に業務システムを構築しながらRailsのさまざまな機能、方法、作法、メソッド、テクニックを学ぶことができます。
    </p>
  </a>
</div>
//}

//sideimage[rails_jissen][60mm][sep=5mm,side=R]{
  本の書名と、ISBN番号を元に取得した本の画像が表示されています。そして画像をクリックするとAmazonへ跳ぶようリンクが設定されています。

  良く使う定型的な部品を表示させるときには、カスタムヘルパを作成することも作業効率化のために役立ちますので、参考になさってください。
//}

====[column] YAML解説

先ほど、Frontmatter (前付け) の紹介の際に使った果物の例を思い出してみましょう。
果物の紹介の場合には、次のように Frontmatter(前付け) を書いていました。
//list[][]{
---
my_favorite_fruits_list:
- あけび
- かき
- さくらんぼ
---
//}

本を紹介する場合には、たくさんの行が現れてきました。
もし、本の書名だけで良ければ、次のように書くことも出来ます。

//list[][]{
---
my_favorite_books_list:
- CSSグリッドで作る HTML5&CSS3 レッスンブック
- Ruby on Rails 6 実践ガイド
---
//}

ここではより詳しい本の属性として「書名」「簡単な内容紹介」「ISBN番号」を扱いますので、

//list[][]{
---
my_favorite_books_list:
- title: Ruby on Rails 6 実践ガイド
  desc: |-
        本書では、1つの企業向け顧客管理システムを作る過程で、RailsによるWebアプリケーション開発の基礎知識とさまざまなノウハウを習得していきます。各章末には演習問題が設けられているので、理解度を確かめながら確実に読み進められます。
        著者が試行錯誤を繰り返した上でのベストプラクティスを提供し、読者は、実際に業務システムを構築しながらRailsのさまざまな機能、方法、作法、メソッド、テクニックを学ぶことができます。
  isbn: 4295008052
---
//}

と書いています。すると、

//list[][]{
- current_page.data.my_favorite_books_list.each do |book|
    li = book.title
    li = book.desc
    li = book.isbn
//}
として、それぞれの属性の値を取得、表示させることが出来ます。

@<code>{introduce} ヘルパに @<code>{book} オブジェクトを渡しているので、
@<code>{introduce} ヘルパ内で、それぞれの本を紹介するための HTML が作られることとなります。

//list[][]{
- current_page.data.my_favorite_books_list.each do |book|
  = introduce(book)
//}

====[/column]

=== @<code>{html builder}

前回は、@<code>{content_tag} を使って、カスタム定義ヘルパを作成しました。
@<code>{content_tag} は、タグの文字列を生成して返してくれるメソッドですが、入れ子になっている場合など、扱いにくいことがあります。
@<code>{Nokogiri} という、HTMLの解析や生成を行うための gem を使うと、複雑なHTMLを作成する場合にも便利ですので、使ってみます。

@<href>{https://www.oiax.jp/rails/tips/nokogiri_html_builder.html, Nokogiri::HTML::Builder} や、 @<href>{https://www.amazon.co.jp/dp/4295008052, Ruby on Rails 6 実践ガイド 黒田 努 著 p328} に、より詳しく説明がありますので、お読みください。ここでは適宜引用してご紹介いたします。

まず HTML のマークアップを簡単に行うメソッド @<code>{markup} を以下のように定義します。

//list[][helpers/html_builder.rb]{
# Ruby on Rails 6 実践ガイド 黒田 努 著 p328より引用
module HtmlBuilder
  def markup(tag_name = nil, options = {})
    root = Nokogiri::HTML::DocumentFragment.parse("")
    Nokogiri::HTML::Builder.with(root) do |doc|
      if tag_name
        doc.method_missing(tag_name, options) do
          yield(doc)
        end
      else
        yield(doc)
      end
    end
    root.to_html.html_safe
  end
end
//}

これで、@<code>{markup} メソッドが使えるようになりました。
それでは利用者一覧を表示するための「カスタム定義ヘルパ」を作成します。

//list[][helpers/custom_helper.rb]{
def table_of_users(users)
  markup do |m|
    m.table(id: 'users', class: 'ui table') do
      m.tr do
        m.th '姓'
        m.th '名'
        m.th '性別'
      end
      users.each do |u|
        attrs = {}
        attrs[:class] = 'admin' if u[:admin]
        m.tr(attrs) do
          m.td(:class => 'family_name bold') do
            m.text u[:family_name]
          end
          m.td u[:given_name]
          m.td u[:gender] == 'male' ? '男' : '女'
        end
      end
    end
  end
end
//}

カスタム定義ヘルパができましたので、それでは、使ってみましょう。
//list[][source/users.html.slim]{
---
title: "利用者一覧"

my_favorite_users_list:
- family_name: 浅倉
  given_name: 南
  gender: female
  admin: true

- family_name: 上杉
  given_name: 達也
  gender: male
  admin: false

- family_name: 上杉
  given_name: 和也
  gender: male
  admin: false
---

h1 利用者一覧

= table_of_users(current_page.data.my_favorite_users_list)
//}

これをビルドすると、次のようなHTMLが生成されます。

//list[][index.html]{
<table id="users" class="ui table">
  <tbody>
    <tr>
      <th>姓</th>
      <th>名</th>
      <th>性別</th>
    </tr>
    <tr class="admin">
      <td class="family_name bold">浅倉</td>
      <td>南</td>
      <td>女</td>
    </tr>
    <tr>
      <td class="family_name bold">上杉</td>
      <td>達也</td>
      <td>女</td>
    </tr>
    <tr>
      <td class="family_name bold">上杉</td>
      <td>和也</td>
      <td>女</td>
    </tr>
  </tbody>
</table>
//}

//sideimage[riyousha][40mm][sep=5mm,side=R]{
利用者が三人ですので、直接 slim や html を書いても手間ではありませんが、多くの利用者を表示する際にはとても役立ちます。

管理者属性(admin)を持つ浅倉南さんの行に @<code>{class="admin"} とクラス属性が付与されている点にも注目です。手作業で行うとミスが起きやすいですが、カスタムヘルパ内に書かれているので確実です。

また @<code>{<table>} タグを使って書きましたが @<code>{<ol> & <li>} タグで書き直すこととなった際にも容易に修正できます。

さらに、データファイル(後述)として作成した@<file>{users.yml}から、各利用者のデータを取得、纏めて表示する際などにも威力を発揮します。
//}

== レイアウト

レイアウト機能を使うと、ウェブサイトのそれぞれのページを囲むための共通@<code>{HTML}が使えるようになります。つまり、ウェブサイトの各ページには、 @<code>{<head>(略)</head>}や、@<code>{<header>(略)</header>}、@<code>{<footer>(略)</footer>}など、共通する「外枠」がありますが、この「外枠」を共用する機能がレイアウト機能です。

それでは、早速使ってみましょう。まずは次のようにレイアウトファイルを用意します。

//list[][source/layouts/site.slim]{
doctype html
html
  head
    meta charset="utf-8"
    meta name="viewport" content="width=device-width"
    title
      = current_page.data.title || "さくら商会"
    = stylesheet_link_tag "style"

  body
    = yield
//}

そして、各ページに固有の内容を、それぞれのファイルに記述します。
//list[][source/about.html.slim]{
h1 会社紹介
//}

//list[][source/contact.html.slim]{
h1 お問い合わせ
//}

ビルドすると、 @<file>{build} ディレクトリ以下に、@<file>{about.html}や @<file>{contact.html} が出力されます。

//list[][build/about.html]{
<html>
<head>
  <meta charset="utf-8">
  <meta content="width=device-width" name="viewport">
  <title>さくら商会</title>
  <link href="stylesheets/style.css" rel="stylesheet">
</head>

<body>
  <h1>会社紹介</h1>
</body>
</html>
//}

//list[][build/contact.html]{
<html>
<head>
  <meta charset="utf-8">
  <meta content="width=device-width" name="viewport">
  <title>さくら商会</title>
  <link href="stylesheets/style.css" rel="stylesheet">
</head>

<body>
  <h1>お問い合わせ</h1>
</body>
</html>
//}

レイアウトファイル @<file>{site.slim}の @<code>{= yield} に、 @<file>{about.html.slim}や、 @<file>{contact.html.slim} に書いた内容が差し込まれています。

素の @<code>{html} で書く際には、@<code>{<head>(略)</head>}など、各ページで共通する部分も全て、それぞれのページに記述しなければなりませんでした。
共通する部分をレイアウトファイルに纏めることで、各ページには固有の内容のみを記述すれば良くなりますので、見通しも良くなり、開発効率も上がります。

レイアウトファイルは @<file>{source/layouts/site.slim} ですが、個別ページは @<file>{source/about.html.slim} や @<file>{source/contact.html.slim} です。
@<B>{拡張子が異なる} ことに注意してください。

=== カスタムレイアウト
既定では@<code>{Middleman} は作成するウェブサイトのすべてのページに同じレイアウト(@<file>{site.slim})を適用しますが、例えばトップページとその傘下にある下層ページなど、それぞれのページが用いるレイアウトを指定したい場合があります。
#@# 複数のレイアウトを使い分けたい場合があります。
#@# どのページがどのレイアウトを使うのか指定したい場合があります。

トップページである @<file>{index.html} には、@<file>{top.slim} というレイアウトファイルを適用し、下層ページであるそれ以外のページには、@<file>{site.slim} という下層ページ用のレイアウトファイルを使うように指定するには、@<file>{config.rb} に次のように記述します。

//list[][config.rb]{
# レイアウトファイルの指定
set :layout, "site"
page "index.html", layout: "top"
//}

=== 完全なレイアウト無効化

いくつかの場合では、まったくレイアウトを使いたくない場合があります。
@<file>{config.rb} で次のように書くと、レイアウトを無効化できます。

==== 全てのページでレイアウトを適用したくない場合
//list[][config.rb]{
set :layout, false
//}

==== 特定のページ(no_layout.html)にレイアウトを適用したくない場合
//list[][config.rb]{
page 'no_layout.html', layout: false
//}

== パーシャル（部分・断片ファイル）
パーシャルはコンテンツの重複を避けるためにページ全体にわたってそのコンテンツを共有する方法です。パーシャルはページテンプレートとレイアウトで使うことができます。

ウェブサイトには、ヘッダーやナビゲーション、フッターなど複数のページで共通して使われる部分があります。また一つのページでしか用いられなくても、その記述が長くなる場合など、別ファイルに分離すると見通しがよくなります。こうした際に用いるのが「パーシャル」です。

パーシャルのファイル名は @<code>{_ (アンダースコア)}から始まります。例として @<code>{source} ディレクトリに置かれる @<file>{_footer.slim} と 名付けられた @<code>{footer} パーシャルを示します。

//list[][source/_footer.slim]{
footer
  p
    | Copyright (C) 令和四年 さくら商会 All rights reserved.
//}

こうして準備したパーシャルファイルを利用するには、 @<code>{partial} メソッドを使います。@<code>{partial} メソッドを使って既定のレイアウトにパーシャルを配置した例を次に示します。

//list[][source/layouts/site.slim]{
doctype html
html
  head
    meta charset="utf-8"
    meta name="viewport" content="width=device-width"
    title
      = current_page.data.title || "さくら商会"
    = stylesheet_link_tag "style"

  body
    = yield
    = partial "footer"
//}

//note[]{
パーシャルファイル名は @<file>{_footer.slim} と @<code>{_(アンダースコア)} が付いていますが、@<code>{partial} メソッドに使いたいパーシャルファイル名を渡す際には @<code>{= partial "footer"} と @<code>{_(アンダースコア)} は不要です。
//}

それでは次のコードを用意し、ビルドしましょう。

//list[][source/about.html.slim]{
h1 会社紹介
//}

@<file>{build} ディレクトリ以下に、会社紹介ページ @<file>{about.html} が出力されています。

//list[][build/about.html]{
<!DOCTYPE html>
<html>
<head>
  <meta charset=utf-8 />
  <meta content="width=device-width" name=viewport />
  <title>さくら商会</title>
  <link href="stylesheets/style-85d5d9f4.css" rel=stylesheet />
</head>
<body>
  <h1>会社紹介</h1>
  <footer>
    <p>Copyright (C) 令和四年 さくら商会 All rights reserved.</p>
  </footer>
</body>
</html>
//}

@<code>{= partial "footer"} の部分が @<file>{_footer.slim} で置き換えられていることが確認できます。

フッターは全てのページで使われますが、内容を更新したくなった場合は、 @<file>{_footer.slim} を編集するだけで全てのページが更新されるので、とても便利です。


== パーシャルに変数を渡す

そして、パーシャルを使い始めると、変数を渡すことで異なった呼び出しを行いたくなるかもしれません。次の方法で対応出来ます。

飼っているペットの猫たちの紹介をするウェブサイトの例を挙げてみます。

//list[][source/_cat.slim]{
  h2 = name
  = image_tag image_filename
  p = introduction
//}

//list[][source/cat.html.slim]{
  h1 猫たちの紹介

  = partial "cat",
             locals: { name: "タマ",
                       image_filename: "tama.jpg",
                       introduction: "タマです。白黒の猫です。"}

  = partial "cat",
             locals: { name: "ミケ",
                       image_filename: "mike.jpg",
                       introduction: "ミケです。茶色の猫です。"}
//}

ビルドすると、 @<file>{build} ディレクトリ以下に 次のように出力されます。

//list[][build/cats.html]{
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset=utf-8 />
    <meta content="width=device-width" name=viewport />
    <title>さくら商会</title>
    <link href="stylesheets/style.css" rel=stylesheet />
  </head>

  <body>
    <h1>猫たちの紹介</h1>

    <h2>タマ</h2>
    <img src="images/tama.jpg" alt=Tama loading=lazy />
    <p>タマです。白黒の猫です。</p>

    <h2>ミケ</h2>
    <img src="images/mike.jpg" alt=Mike loading=lazy />
    <p>ミケです。茶色の猫です。</p>

  </body>
  </html>
//}

@<file>{_cat.slim} には @<code>{h2 = name} と書かれていましたが、 出力された @<file>{cats.html} では @<code>{<h2>タマ</h2>} に置き換えられていることが確認できます。

//sideimage[tama][50mm][sep=5mm,side=R]{
  どのタグを使って猫の紹介をするのか、その形式は共通していますので、こういった場合、パーシャルファイル @<file>{_cat.slim} を使うと、同じタグの繰り返しを何度も書かずに済みます。

  そして、置き換えたい猫のデータを、@<code>{locals: { name: "タマ"\} } とハッシュ形式で渡すことで、個別に異なる猫のデータだけを必要な箇所に指し込むことが出来ます。

  使用するタグを変更したい場合にも、パーシャルファイルを編集するだけで、ページが更新されますようになり、とても便利ですので使いこなしていきましょう。
//}


== データファイル
ページのコンテンツデータを、レンダリング @<fn>{rendering} から抜き出すと便利な場合があります。

//footnote[rendering][@<href>{https://e-words.jp/w/レンダリング.html, レンダリングとは、何らかの抽象的なデータ集合を元に、一定の処理や演算を行って文字や画像や映像、音声などを生成すること。例えば、一つのウェブページに含まれる、HTMLやCSSなどによる描画内容の記述、スクリプトによる動作の記述、画像ファイルやフォントファイルなど外部のデータなどを組み合わせ、ブラウザのウィンドウ内にページ内容の描画を行うことを指す。}]

先ほど登場した「猫を紹介するページ」の例では、 @<file>{cats.html.slim}内に、個々の猫に関するデータを直接記述し、@<code>{locals: {\}} として、パーシャルファイルに渡していました。

猫が十匹二十匹と増えてくると、逐一ハッシュを記述するのも大変です。また、@<file>{index.html}の他に、もしかすると@<file>{tama.html}や@<file>{mike.html}、あるいは @<file>{タマ.html}や@<file>{ミケ.html}というページでも、猫のデータを使いたいかもしれません。 @<fn>{nippongo_url}

//footnote[nippongo_url][以前は、半角英数に限られていたURLですが、日本語も使えるようになっています。]

このような場合、猫のデータのみを別ファイルにし、必要に応じて読み出せると便利です。

@<code>{Middleman} はこういった用途のために「データファイル」機能を備えています。

データファイルは @<file>{data} ディレクトリの中に @<code>{YAML(ヤムル)}形式のデータとして作ることができ、拡張子は@<code>{yml}です。作成したならば、それぞれの@<file>{slim}ファイル内で、この情報を使うことができます。 @<file>{data} ディレクトリは、@<file>{source} ディレクトリと同じように、プロジェクトのルートに置きます。

それでは、ページのコンテンツデータ（ここでは、猫たちの紹介データ）を、@<code>{YAML(ヤムル)}形式のデータファイルに抜き出してみましょう。
@<file>{data} ディレクトリ内に @<file>{cats.yml} という名前で作成します。

//list[][data/cats.yml]{
  - name: タマ
    image_filename: tama.jpg
    introduction: タマです。白黒の猫です。
  - name: ミケ
    image_filename: mike.jpg
    introduction: ミケです。茶色の猫です。
//}

@<code>{name:} の後には、「半角スペース」を入れて、「タマ」と書きます。
@<code>{image_filename:} の前には、「半角スペース２つ」が必要です。

一般的に @<code>{YAML(ヤムル)}形式は上のように書きますが、下のように書くこともできます(@<code>{JSON(ジェイソン)}形式に良く似ているので、馴染み易いかもしれません。)

//list[][data/cats.yml]{
  [
    { name: タマ,
      image_filename: tama.jpg,
      introduction: タマです。白黒の猫です。},
    { name: ミケ,
      image_filename: mike.jpg,
      introduction: ミケです。茶色の猫です。}
  ]
//}

次の形式になっていることが読み取れるでしょうか。
//list[][]{
  [
    {一匹目の猫のデータ},
    {二匹目の猫のデータ}
  ]
//}

@<code>{[]} は、配列といい、個々のデータ(要素)を纏めたものです。
@<code>{{\}} は、「ハッシュ(連想配列、辞書)」と言います。 @<code>{name: タマ} のように、 @<code>{鍵(key): 値(value)} の形になっています。(@<code>{項目名: データ} と読むこともできます。)

@<code>{YAML(ヤムル)}形式には二種類の書き方があります。お好みでお使いください。


//blankline
用意したデータファイルは、次のように使います。

//list[][source/cats2.html.slim]{
  h1 猫たちの紹介

  - data.cats.each do |cat|
    h2 = cat.name
    = image_tag cat.image_filename
    p = cat.introduction
//}

これを、ビルドすると、 @<file>{build} ディレクトリ以下に 次のように出力されます。

//list[][build/cats2.html]{
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset=utf-8 />
    <meta content="width=device-width" name=viewport />
    <title>さくら商会</title>
    <link href="stylesheets/style.css" rel=stylesheet />
  </head>

  <body>
    <h1>猫たちの紹介</h1>

    <h2>タマ</h2>
    <img src="images/tama.jpg" alt=Tama loading=lazy />
    <p>タマです。白黒の猫です。</p>

    <h2>ミケ</h2>
    <img src="images/mike.jpg" alt=Mike loading=lazy />
    <p>ミケです。茶色の猫です。</p>

  </body>
  </html>
//}

パーシャルファイルを使った場合と全く同じになります。
@<file>{cats.html.slim} では、別に用意したパーシャルファイル @<file>{_cat.slim} へ、@<code>{locals: {\}} としてハッシュ形式でデータを渡していましたが、@<file>{cats2.html.slim} では、@<file>{_cat.slim} 相当のコードが直接 @<file>{cats2.html.slim} に書かれており、 @<file>{cats.yml} ファイルから猫データを読み込みレンダリングしています。

パーシャルファイルに引数として猫データを渡してレンダリングするのか、直接データファイルから猫データを読み取りレンダリングするのか、どちらも同じ結果が得られます。状況に応じて適宜活用してください。

===[column] Ruby 文法解説

@<file>{source/cats2.html.slim} を解説します。

@<code>{Slim} では、テンプレート中に、 @<code>{Ruby} コードを書くことができます。 @<fn>{ruby}

//footnote[ruby][@<code>{Ruby} とは、@<B>{まつもとゆきひろ} さんが考案した、柔軟性に富む優れた書き味で人気のプログラミング言語です。 @<href>{https://www.ruby-lang.org/ja/, オブジェクト指向スクリプト言語 Ruby}]

@<code>{Ruby} コードを書くときには、@<code>{- (ハイフン)}で始めます。

@<code>{data.cats} は、@<code>{Middleman} で、データファイルを読み込むための書き方です。このように書くことで、@<code>{Middleman}は、 @<file>{data}ディレクトリにある @<file>{cats.yml} から情報を読み込み、 @<code>{Ruby} コードで扱えるようにします。 @<code>{data.cats}には、「配列」と呼ばれるデータ形式で、全ての猫たちのデータが納められています。

@<code>{.each} は、@<code>{Ruby} で、配列の各々の要素（つまり一匹一匹の猫）について処理するよう、指示するコードです。

@<code>{do} は、コードブロックと呼ばれ、次に続く@<code>{Ruby}コードを実行するよう指示する構文です。

@<code>{|cat|} には、猫一匹分の全てのデータ(@<code>{name(名前)}, @<code>{image_filename(画像ファイル名)}, @<code>{introduction(紹介文)})が入っていますので、@<code>{cat.name} は、取り出した猫一匹の@<code>{name(名前)}です。(タマやミケなど、個々の猫の名前になります)

@<code>{h2 =} ですが、 @<code>{h2} は、@<code>{<h2>タグ} になります。@<code>{=} を書くことで、 @<code>{Ruby} でいろいろ処理を行った結果を、 @<code>{h2}タグの内容として出力できるので、@<code>{<h2>タマ</h2>} のようになります。

@<code>{= image_tag cat.image_filename} は、 @<code>{Middleman}で用意されている @<code>{image_tag}ヘルパを使った書き方です。@<code>{image_tag}ヘルパに引数として @<code>{cat.image_filename} を渡すと、@<code>{<img>}タグを生成してくれます。

以上で、@<file>{cats.yml} という、猫たちの紹介データを用いて、 @<code>{html}を作成できました。

//note[データと枠との分離]{
  たくさんのデータがあるときに、同じような @<code>{html}を繰り返し書かずに済むので、とっても楽です。データとそれを納める枠とを分離することで、管理が容易になります。活用していきましょう。
//}

===[/column]

== パーシャルやヘルパなど 様々な手法でのタグ生成

//sideimage[gallery][80mm][sep=5mm,side=R]{
パーシャルやヘルパ、データファイルなど様々なことを扱ってきました。
今までのまとめとして、九種類の写真ギャラリーを作成してみます。
最終的に出来上がるHTMLタグは同じものとなります。
作りやすさや分かりやすさなど、ご参考になれば幸いです。
//}

//list[][HTMLで書いた例]{
// html で書いた例
<h3>写真展 その1</h3>
<div class="gallery">
  <a href="images/tora.jpg" title="The Cleaner">
    <img src="images/tora_s.jpg">
  </a>
  <a href="images/tsuru.jpg" title="Winter Dance">
    <img src="images/tsuru_s.jpg">
  </a>
  <a href="images/zou.jpg" title="The Uninvited Guest">
    <img src="images/zou_s.jpg">
  </a>
</div>
//}
最も基本となる形です。

//list[][Slimで書いた例]{
// slim で書いた例
h3 写真展 その2
.gallery
  a href="images/tora.jpg" title="The Cleaner"
    img src="images/tora_s.jpg"
  a href="images/tsuru.jpg" title="Winter Dance"
    img src="images/tsuru_s.jpg"
  a href="images/zou.jpg" title="The Uninvited Guest"
    img src="images/zou_s.jpg"
//}
Slim 記法で簡潔に記すことが出来ました。
HTML と比較するととてもすっきりしています。

//list[][helper メソッドを使って書いた例]{
h3 写真展 その3
.gallery
  = link_to "images/tora.jpg", title: "The Cleaner"
    = image_tag "tora_s.jpg"
  = link_to "images/tsuru.jpg", title: "Winter Dance"
    = image_tag "tsuru_s.jpg"
  = link_to "images/zou.jpg", title: "The Uninvited Guest"
    = image_tag "zou_s.jpg"
//}
@<code>{link_to} や @<code>{image_tag} といったヘルパが標準で備わっています。
@<code>{Ruby on Rails} でも良く用いる書き方でお薦めです。

//list[][データを格納した配列を使って書いた例]{
h3 写真展 その4
.gallery
  - doubutsu = [ { picture: "tora",     title: "The Cleaner" },
                 { picture: "tsuru",    title: "Winter Dance" },
                 { picture: "zou",      title: "The Uninvited Guest" }]
  - doubutsu.each do |kemono|
    - picture = kemono[:picture]
    - title   = kemono[:title]
    = link_to "images/#{picture}.jpg", title: title
      = image_tag "#{picture}_s.jpg"
//}
@<code>{Ruby} は、簡潔で親しみやすく理解しやすいプログラミング言語です。 @<code>{doubutsu} 配列にそれぞれの @<ruby>{獣, けもの} の写真と文字を格納します。そして配列から一つ一つの獣をとり出し、リンクと画像を生成する基本的な @<code>{Ruby} のコードです。

//list[][パーシャルファイルに、データを渡して書いた例]{
h3 写真展 その5
.gallery
  = partial "gallery", locals: { picture: "tora",     title: "The Cleaner" }
  = partial "gallery", locals: { picture: "tsuru",    title: "Winter Dance" }
  = partial "gallery", locals: { picture: "zou",      title: "The Uninvited Guest" }
//}

//list[][_gallery.slim]{
= link_to "images/#{picture}.jpg", title: title
  = image_tag "#{picture}_s.jpg"
//}

呼び出し元では、 @<code>{= partial "gallery"} と、パーシャルファイルを表示するよう記述しています。そして、パーシャルファイルに渡す個々の獣情報を @<code>{locals: { picture: "tora", title: "The Cleaner" \}} と、ハッシュ形式で表現しています。

//list[][4, 5の併せ技]{
h3 写真展 その6
.gallery
  - doubutsu = [ { picture: "tora",     title: "The Cleaner" },
                 { picture: "tsuru",    title: "Winter Dance" },
                 { picture: "zou",      title: "The Uninvited Guest" }]

  - doubutsu.each do |kemono|
    = partial "gallery", locals: kemono
//}
データ配列から@<code>{each}メソッドにより個々の獣データを取得、パーシャルファイルに渡す例です。

//list[][データファイルを使った例]{
h3 写真展 その7
.gallery
  - data.doubutsu.each do |kemono|
    = partial "gallery", locals: kemono
//}

//list[][data/doubutsu.yml]{
- picture: tora
  title:   The Cleaner
- picture: tsuru
  title:   Winter Dance
- picture: zou
  title:   The Uninvited Guest
//}
データファイルを使った例です。コードとデータが分離され、すっきりしています。データファイルから取得したデータを、パーシャルに渡し、HTMLを生成しています。

//list[][データファイルとカスタムヘルパを使った例]{
h3 写真展 その8
.gallery
  - data.doubutsu.each do |kemono|
    = animal_photo kemono
//}

//list[][helpers/doubutsu.rb]{
def animal_photo(data)
  link_to "images/#{data.picture}.jpg", title: data.title do
    image_tag "#{data.picture}_s.jpg"
  end
end
//}
データファイルから読み取ったデータを、パーシャルではなくカスタムヘルパに渡し HTML を生成します。カスタムヘルパ内では Middleman標準の @<code>{link_to, image_tag} を使っています。

//list[][全てをカスタムヘルパで生成する例]{
h3 写真展 その9
= animals_photo
//}

//list[][helpers/doubutsu.rb]{
def animals_photo
  markup do |m|
    m.div(class: 'gallery') do
      data.doubutsu.each do |kemono|
        m.a(href: "images/#{kemono[:picture]}.jpg", title: kemono[:title]) do
          m << image_tag("#{kemono[:picture]}_s.jpg")
        end
      end
    end
  end
end
//}
データファイルからの読み込みも含めて、全てをカスタムヘルパに @<ruby>{委,ゆだ}ねた例です。 @<code>{Slim} 自体は僅か二行ととてもすっきりしました。
カスタムヘルパ内では、 @<code>{HtmlBuilder} を使って書いています。少し記法が独特ですが @<code>{content_tag} では書きにくい際に活躍します。

//blankline
以上九種類をご紹介いたしました。適宜、ご活用下さい。

== 動的ページ

@<code>{Middleman} にはテンプレートファイルと 一 対 一 の対応関係を持たない ページを生成する機能があります。この機能により、変数に応じて複数のファイルを作り出すテンプレートを使えるようになります。
該当するページはないにもかかわらず、代わって応答してくれるところから@<code>{Proxy(プロキシ・代理人)} と呼ばれます。

//blankline
具体例を挙げます。先ほどは、猫たちの紹介を、 @<file>{cats.html} の中で行いましたが、それぞれの猫の専用ページ、@<file>{タマ.html}や@<file>{ミケ.html}というページを作ることができます。
@<code>{Proxy(プロキシ・代理人)}となってくれる、猫専用ページの雛形ページを作成し、猫の名前を与えると、代理人がそれぞれのページの代わりに応答してくれる感覚になります。

この@<code>{Proxy(プロキシ・代理人)}を作るには、 @<file>{config.rb} で  @<code>{proxy} メソッドを使って、「作りたいページのパス」「使いたいテンプレートのパス」を与えます。

それでは、猫たち専用ページを作成するために、 @<file>{config.rb} を設定してみましょう。

//list[][config.rb]{
  data.cats.each do |neko|
    proxy "/#{neko.name}.html", "/neko_template.html", locals: { neko_data: neko }, ignore: true
  end
//}

一行目の @<code>{data.cats.each do |neko|}は、@<file>{cats.yml} からデータを取得します。そして取得した一匹一匹の猫データは @<code>{neko} という変数に格納されます。

二行目ですが @<code>{neko} には一匹一匹の猫データが格納されていますので、 @<code>{neko.name}で猫の名前を取り出すことができます。ですので @<code>{"/#{neko.name\}.html"} は @<code>{タマ.html} や @<code>{ミケ.html} となります。
つまり @<code>{proxy "タマ.html", "/neko_template.html"} @<code>{proxy "ミケ.html", "/neko_template.html"} と書いたのと同じことになります。

@<code>{proxy}は「代理人」ですから、ブラウザのURL欄に @<code>{https://example.com/タマ.html} と入力された際に @<file>{タマ.html} の代理人として、@<file>{neko_template.html}が代わりに応答するよう 設定しています。

そこで、代わりに応答する @<file>{neko_template.html} に 一匹一匹の猫のデータを渡してあげる必要があります。データファイル@<file>{cats.yml}から取り出した一匹一匹の猫のデータは @<code>{neko}に格納されていますので、@<code>{locals: { neko_data: neko \}} と書くことで、この@<code>{neko}を@<file>{neko_template.html} に渡せます。すると @<file>{neko_template.html} 内で 一匹一匹の猫のデータを @<code>{neko_data} という変数名で参照できるようになります。

//blankline

それでは「代理人」となる @<file>{neko_template.html.slim} の中身を見てみましょう。

//list[][source/neko_template.html.slim]{
  h2 = neko_data.name
  = image_tag neko_data.image_filename
  p = neko_data.introduction
//}

以前に登場してきたものと同じ内容です。 @<code>{neko_data}には、一匹一匹の猫のデータが入っていますので @<code>{neko_data.name} と記述し、猫の名前など、必要な情報を取り出しています。

レイアウトファイルを次のように準備して、ビルドしてみましょう。
//list[][source/layouts/site.slim]{
doctype html
html
  head
    meta charset="utf-8"
    meta name="viewport" content="width=device-width"
    title
      = current_page.data.title || "さくら商会"
    = stylesheet_link_tag "style"

  body
    = yield
//}

出力された二つのファイル @<file>{タマ.html} や @<file>{ミケ.html} は、次のようになります。

//list[][タマ.html]{
<!DOCTYPE html>
<html>
<head>
  <meta charset=utf-8 />
  <meta content="width=device-width" name=viewport />
  <title>さくら商会</title>
  <link href="stylesheets/style.css" rel=stylesheet />
</head>
<body>
  <h2>タマ</h2><img src="images/tama.jpg" alt=Tama loading=lazy />
  <p>タマです。白黒の猫です。</p>
</body>
</html>
//}

//list[][ミケ.html]{
<!DOCTYPE html>
<html>
<head>
  <meta charset=utf-8 />
  <meta content="width=device-width" name=viewport />
  <title>さくら商会</title>
  <link href="stylesheets/style.css" rel=stylesheet />
</head>
<body>
  <h2>ミケ</h2><img src="images/mike.jpg" alt=Mike loading=lazy />
  <p>ミケです。茶色の猫です。</p>
</body>
</html>
//}

//sideimage[mike][50mm][sep=5mm,side=R]{
猫の雛形ファイル @<file>{neko_template.html.slim} と、サイトのレイアウトファイル @<file>{site.slim} を元に、(猫の情報のみが異なるのみで) 二つのほとんど同じ HTML ファイルが生成されました。

人の手で同じ作業をしようとすると、労力もかかり、また間違いも起きがちです。何よりあまり愉しくありません。より創作的なことに生命力を使えるよう Middleman より機能提供されていますので、活用していきましょう。
//}

//note[変数名について]{
  @<code>{neko} という変数名やファイル名に違和感を感じた方もいらっしゃるかもしれません。一般的には @<code>{neko} に代えて @<code>{cat}が良く用いられますが、@<code>{cat} という同じ語が大量に現れることとなりますので、ここでは混乱を避け、区別する意図から @<code>{neko} としました。

  エディタ上でそれぞれの語の意味に応じて色分けされるように、ときにはローマ字の変数名を使ってみるのも区別しやすくなり良いかもしれません。
//}

== ファイルサイズ最適化
ウェブサイトを公開するときには、応答速度の改善のために、 @<code>{HTML}、@<code>{CSS}、@<code>{JavaScript}や、@<code>{画像ファイル}の圧縮を行うことが推奨されています。

@<code>{Middleman} にも、もちろんファイル最適化の為の機能が用意されており、 @<file>{Gemfile} や @<file>{config.rb} に簡単な設定を書くことで使えるようになります。(雛形を利用した場合には、既に記述済みです。)

=== HTML の 圧縮

@<code>{Middleman} で、HTML出力を圧縮するためには、公式に用意されている拡張機能 @<file>{middleman-minify-html}を用います。
@<file>{Gemfile} に次のように記述します。

//list[][Gemfile]{
  gem "middleman-minify-html"
//}

そして、ターミナルから、@<code>{bundle install} を実行します。
//terminal[][]{
  % bundle install
//}

これで、HTML出力圧縮のための @<file>{gem} ファイル、@<file>{middleman-minify-html}のインストールが完了です。

そして、@<code>{config.rb} を開いて、次のように追加します。

//list[][config.rb]{
  configure :build do
    activate :minify_html
  end
//}

これで、設定は完了です。
ビルドして出力された @<code>{HTML} ファイルを確認してみてください。スペースやタブや改行などが削除され、圧縮されていることが分かります。

=== CSS の 圧縮

CSS の圧縮はさらに簡単です。次のように @<file>{config.rb} に記述するだけで完了します。

//list[][config.rb]{
  configure :build do
    activate :minify_css
  end
//}

=== JavaScript の 圧縮

JavaScript の圧縮は少し複雑ですが、次のように @<file>{config.rb} に記述すると完了します。

//list[][config.rb]{
  require "uglifier"

  configure :build do
    activate :minify_javascript,
      compressor: proc {
        ::Uglifier.new(
          mangle: { toplevel: true },
          compress: { unsafe: true },
          harmony: true
        )
      }
  end
//}

=== 画像ファイル の 圧縮

@<href>{https://ics.media/entry/201001/,次世代画像形式のWebP、そしてAVIFへ} という記事より、引用してご紹介いたします。

//blankline
長い間、Webの静止画に関しては「写真のJPEG、ロゴやイラストのGIF、透過画像のPNG」という明確な使い分けが確立されて来ました。WebPはこのすべてを置き換えることができる次世代のフォーマットです。

#@# //quote{
#@#   WebPとは、グーグル社が開発・公開している画像ファイル形式の一つ。標準のファイル拡張子は「.webp」。Webページへ埋め込む静止画像に適した画像形式として、既存のJPEGやGIF、PNGの置き換えが可能である。
#@#   　JPEGのような写真に適した高圧縮率の非可逆圧縮方式と、GIFやPNGのような図表やイラストに適した可逆圧縮方式の両方に対応する。透過PNGのようなピクセル単位の透過度(アルファチャンネル)が非可逆圧縮でも利用でき、GIFアニメーションのような簡易なアニメーション機能(フルカラー画像や非可逆圧縮も可)にも対応する。【出典: IT用語辞典】
#@# //}


#@# 様々な画像形式が考案され、写真用の@<ruby>{JPEG,ジェイペグ}, 図やイラストのための@<ruby>{GIF,ジフ},@<ruby>{PNG,ピング}が主流となりましたが、こうした中登場したのが、次世代画像形式の@<ruby>{WebP,ウェッピー}です。

#@# //quote{
#@# //noindent
#@# 　WebPとは、グーグル社が開発・公開している画像ファイル形式の一つ。標準のファイル拡張子は「.webp」。Webページへ埋め込む静止画像に適した画像形式として、既存のJPEGやGIF、PNGの置き換えが可能である。 @<br>{}
#@# 　JPEGのような写真に適した高圧縮率の非可逆圧縮方式と、GIFやPNGのような図表やイラストに適した可逆圧縮方式の両方に対応する。透過PNGのようなピクセル単位の透過度(アルファチャンネル)が非可逆圧縮でも利用でき、GIFアニメーションのような簡易なアニメーション機能(フルカラー画像や非可逆圧縮も可)にも対応する。【出典: IT用語辞典】
#@# //}

#@# ウェブ制作会社ICSが提供する技術情報メディアがあります。HTML / CSS / JavaScriptを中心とした記事が多数掲載されています。@<ruby>{WebP,ウェッピー}について書かれた記事もございましたので、引用してご紹介いたします。 @<fn>{ics}

#@# ==== 次世代画像形式のWebP、そしてAVIFへ
==== 次世代画像形式の@<ruby>{WebP,ウェッピー}
長い間、Webの静止画に関しては「写真のJPEG、ロゴやイラストのGIF、透過画像のPNG」という明確な使い分けが確立されて来ました。WebPはこのすべてを置き換えることができる次世代のフォーマットです。

=== WebPはJPEG/GIF/PNG(APNG)をカバーする魅力的なフォーマット

WebPを使うことで、これまでは用途や画像の特徴ごとに使い分けが必要だったフォーマットの一本化が可能になります。主な特徴を簡単に紹介しましょう。

 * 高い圧縮率：同等画質のJPEGと比較して20-30%のサイズ削減（JPEGの置き換え）
 * 不可逆圧縮と透過アニメーションの併用（透過アニメーションでも画質を犠牲にしてサイズを削減できる）（GIF/PNGの置き換え）
 * 画質劣化のない可逆圧縮もサポート（GIF/PNGの置き換え）

//image[webp][][width=75%]

=== さらに次世代のフォーマット、AVIFも

  * 多様な色空間やサンプリング方式をサポート
  * WebPよりもさらに高画質でコンパクト（同じサイズでも画質が高く、JPEGに特有のブロックノイズも発生しない）
  * Amazon・Netflix・Google・Microsoft・Mozilla等の幅広い企業によるコンソーシアムが共同で開発（FacebookやAppleも後から参画）

//image[avif][][width=75%]

//blankline



#@# //footnote[ics][@<href>{https://ics.media/entry/201001/,次世代画像形式のWebP、そしてAVIFへ}]

//footnote[imagemagick][@<href>{https://imagemagick.biz/,ImageMagickの使いかた 日本語マニュアル}]


#@# //image[webp][][width=80%]
#@# //image[avif][][width=80%]


//blankline
今まで登場してきた猫たちの画像ファイルでも実験してみました。
猫のイラストは @<href>{https://www.ac-illust.com,イラストAC}より取得、横900px, 縦1200px に切り抜いたものを使いました。

//tsize[latex][|cr|cr|rr|]
//table[][jpg と webp のサイズ比較][csv=on,hline=off]{
jpg, サイズ, webp, サイズ, 減少サイズ, 減少率
-----------------------------------------------------------
tama.jpg, 79KB, tama.webp, 36KB, 43KB, 54%
mike.jpg, 88KB, mike.webp, 41KB, 47KB, 53%
//}

#@# //tsize[latex][|cr|cr|rr|]
#@# //table[][jpg と 圧縮後 のサイズ比較][csv=on,hline=off]{
#@# 圧縮前, サイズ, 圧縮後, サイズ, 減少サイズ, 減少率
#@# -----------------------------------------------------------
#@# tama.jpg, 79KB, tama.jpg, 65KB, 14KB, 18%
#@# mike.jpg, 88KB, mike.jpg, 64KB, 24KB, 27%
#@# //}

@<code>{jpg}形式から@<code>{webp}形式に変換することで、半分以下にまで小さくなりました。
#@# 一方 @<code>{imageoptim} による画像圧縮を施しても、約二、三割ほどの改善にとどまります。

//blankline
今日では 全てのブラウザが @<code>{webp}形式 に対応しています。
#@# @<code>{jpg}画像を圧縮するよりは @<code>{webp}形式に変換したほうが良いでしょう。
@<code>{ImageMagick} @<fn>{imagemagick}等のツールを導入することで、簡単に画像形式を変換することができます。ネット上でオンラインで変換してくれるサイトもございます。

画像の表示も速くなり、利用者も快適に閲覧できますので、使っていきましょう。

#@# ビルド時に画像を圧縮することも可能です。見た目はほとんど変わらず、JPG / GIF / PNG などの画像ファイルの大きさを数％から数十％小さくすることができます。
#@#
#@# 有志の方により @<code>{middleman-imageoptim} という @<file>{gem} ファイルが提供されていますのでので、使用方法をご紹介いたします。
#@#
#@# @<file>{Gemfile} に次のように記述します。
#@#
#@# //list[][Gemfile]{
#@#   gem "middleman-imageoptim"
#@# //}
#@#
#@# そして、ターミナルから、@<code>{bundle install} を実行します。
#@# //terminal[][]{
#@#   % bundle install
#@# //}
#@#
#@# これで画像圧縮のための @<file>{gem} ファイル @<file>{middleman-imageoptim}のインストールが完了します。
#@#
#@# そして @<code>{config.rb} を開いて次のように追加します。
#@#
#@# //list[][config.rb]{
#@#   configure :build do
#@#     activate :imageoptim
#@#   end
#@# //}
#@#
#@# これで、設定は完了です。
#@# ビルドして出力された @<file>{images} ディレクトリ内の画像ファイルサイズを確認してみてください。圧縮前の画像ファイルサイズに比べ、ファイルサイズが縮小されています。圧縮前後の画像ファイルをを見比べても @<small>{(ほぼ)} 見た目に変化はないことが確認できることと思います。


=== デバッグ時のオプション
通常 @<code>{Slim} で生成される @<code>{html} ファイルは、ウェブサイトに公開した際の速度改善が望めるよう、空白等を取り除きコンパクトに圧縮されています。

デバック時には、これを無効化することができます。
@<code>{Middleman}アプリケーションでは、@<code>{config.rb}中に、以下のように記述します。

//list[][config.rb]{
set :slim, {
  pretty: true, sort_attrs: false
}
//}

併せて、圧縮にかかる設定も、コメントアウトして無効化しておきましょう。
//list[][config.rb]{
configure :build do
  # HTML圧縮
  # activate :minify_html
  # CSS圧縮
  # activate :minify_css
  # JavaScript圧縮
  # activate :minify_javascript,
  #   compressor: proc {
  #     ::Uglifier.new(
  #       mangle: { toplevel: true },
  #       compress: { unsafe: true },
  #       harmony: true
  #     )
  #   }
  # イメージ圧縮
  # activate :imageoptim
  # アセットファイルのURLにハッシュを追加
  # activate :asset_hash
  # テキストファイルのgzip圧縮
  # activate :gzip
end
//}

== 画像形式の変換
画像形式を変換するにはどうしたら良いのでしょうか？
様々な手法がありますが、ここでは、簡単なコマンド操作で処理できる @<code>{ImageMagick} @<fn>{tuduri}をご紹介いたします。
//footnote[tuduri][@<code>{magic} ではなく @<code>{magick} と綴られています。一般名詞を組み合わせて、固有名詞化する際に、このような事例が時折見られます。]

@<href>{https://imagemagick.biz,Imagemagickの使い方日本語マニュアル} というサイトがあります。「日本語のマニュアルが少ない画像加工ツールImageMagickの使い方を、初心者の方にも解りやすいよう詳しく丁寧に解説している」サイトです。

インストールから、画像の拡大縮小、形式変換、色の加工など、様々な使い方が紹介されています。適宜引用抜粋しつつ、その使い方をご紹介いたします。

=== インストール

既に Mac用パッケージマネージャ HomeBrew の導入が完了しておりますので、ターミナルから以下のコマンドを入力することで、ImageMagick のインストールは完了します。

//terminal[][]{
$ brew install imagemagick
//}

=== 画像形式の変換

フォーマット変換とも呼ばれます。 @<code>{tama.jpg} という jpg形式の画像を、 @<code>{tama.webp} という webp形式の画像に変換するには、次のようにします。

まず、画像があるディレクトリに移動します。
そのためには、現在、どのディレクトリにいるのか、知る必要があります。
そのためのコマンドが @<code>{pwd} です。
//terminal[][]{
% pwd
/Users/haruka/my_new_site
//}
現在、 @<code>{/Users/haruka/my_new_site} というディレクトリにいることが分かりました。

@<code>{haruka} は、このコンピュータを利用している、ユーザ名です。 Finder アプリでは、サイドバーに、家のアイコンと共に表示されています。

@<file>{my_new_site} は、Middleman で新規作成したディレクトリ(ウェブサイト)の名前です。画像ファイルは、 @<file>{source/images/} ディレクトリにありますから、そこまで移動します。

移動するためのコマンドは、 @<code>{cd} です。
//terminal[][]{
% cd source
% cd images
//}
と入力して、ディレクトリを移動しましょう。

@<code>{pwd} コマンドで、現在いるディレクトリを確認してみます。
//terminal[][]{
% pwd
/Users/haruka/my_new_site/source/images
//}
となり、無事に移動することが出来ました。

//note[]{
ちなみに上のディレクトリに戻るには
//terminal[][]{
% cd ..
//}
と入力することで、一つ上のディレクトリに戻れます。
//}

そのディレクトリにどのようなファイルがあるか、表示するには、 @<code>{ls} コマンドを用います。
//terminal[][]{
% ls
apple-touch-icon-180x180.png    tora.jpg
favicon.ico                     (略)
//}
とたくさん表示されました。

@<file>{jpg} ファイルのみに絞って表示させるには、以下のコマンドを用います。
//terminal[][]{
% ls *.jpg
logo.jpg                tama.jpg                tsuru_s.jpg
mike.jpg                tora.jpg                (略)
//}
@<file>{tama.jpg} があることが確認できました。

それでは、見つかった @<file>{tama.jpg} を @<code>{webp} 形式に変換しましょう。

==== 一つのファイルの画像形式を変換する

//terminal[][]{
$ convert tama.jpg tama.webp
//}
これで、変換完了です。

==== 複数のファイルの画像形式を変換する
一つ一つファイル名を指定してコマンド入力して変換するのは、大変です。
纏めて変換することも出来ます。そのためには以下のコマンドを入力します。

//terminal[][]{
$ for i in *.jpg; do convert $i ${i%jpg}webp; done
//}
これで、全ての @<code>{jpg} ファイルを @<code>{webp} 形式に変換できました。

簡単なシェルコマンドについてご紹介いたしました。より詳しく学びたい方には、
巻末の参考文献「1日1問、半年以内に習得 シェル・ワンライナー160本ノック」がお薦めです。シェルコマンドを極めるための様々な技法が紹介されていますので、是非ご一読下さい。

=== 画像の拡大縮小

4k など 巨大な画像を縮小するには、以下のコマンドで行えます。

==== アスペクト比を維持
//terminal[][]{
$ convert tama_large.jpg -resize 640x480 tama_small.jpg
//}
アスペクト比が維持されるよう(画像の横幅が640pxになるか、あるいは画像の縦が480pxになるまで)、画像が縮小されます。

==== アスペクト比を無視
//terminal[][]{
$ convert tama_large.jpg -resize 640x480! tama_small.jpg
//}
サイズ指定の後に @<code>{!(感嘆符)} を付けると、アスペクト比を無視し、強制的に画像サイズを、横640px、縦480pxに縮小します。

==== アスペクト比を維持（幅のみを指定）
//terminal[][]{
$ convert tama_large.jpg -resize 640x tama_small.jpg
//}
画像の横幅のみを指定すると、画像の縦はアスペクト比が維持されるように適宜調整して縮小されます。

==== アスペクト比を維持（縦のみを指定）
//terminal[][]{
$ convert tama_large.jpg -resize x480 tama_small.jpg
//}
画像の縦のみを指定すると、画像の横はアスペクト比が維持されるように適宜調整して縮小されます。

==== パーセンテージで縮小
//terminal[][]{
$ convert tama_large.jpg -resize 25% tama_small.jpg
//}
パーセンテージを指定すると、アスペクト比が維持して縮小されます。



== 画像の遅延読み込み

一般に画像の読み込みは時間がかかるものです。写真が中心のサイトを作っている際などはなおさらです。

このために様々な仕様が規定されました。
@<code>{<img srcset="..."}  @<fn>{img}や、 @<code>{<picture><source srcset="..."} @<fn>{picture}などです。

//footnote[img][@<href>{https://developer.mozilla.org/ja/docs/Web/HTML/Element/img, <img>: 画像埋め込み要素}]

//footnote[picture][@<href>{https://developer.mozilla.org/ja/docs/Web/HTML/Element/picture,<picture>: 画像要素}]

ここでは、簡単に行える方法として、 @<code>{<img src="tama.jpg" loading="lazy">} をご紹介いたします。

//quote{
@<code>{loading} ブラウザーがどのように画像を読み込むかを示します。
//blankline

@<code>{eager} 画像が現在可視ビューポートに入っているかどうかにかかわらず、直ちに画像を読み込みます (これが既定値です)。
//blankline

@<code>{lazy} 画像がブラウザーで定義されたビューポートからの距離に達するまで、画像の読み込みを遅延させます。これは、画像が必要とされるのが合理的に確実になるまで、処理に必要なネットワークやストレージの帯域幅を使用しないようにするためです。これは一般的に、ほとんどの典型的な使用法において、コンテンツの性能を向上させることができます。
//}

全ての @<code>{<img>} タグに @<code>{loading="lazy"} が付くよう、ヘルパメソッドを用意しました。

//list[][helpers/lazy.rb]{
module Padrino
  module Helpers
    module AssetTagHelpers
      def image_tag(url, options={})
        options = { :src => image_path(url) }.update(options)
        options[:alt] ||= image_alt(url) unless url.to_s =~ /\A(?:cid|data):|\A\Z/

        # img タグに loading="lazy" を追加する
        options[:loading] ||= :lazy

        # 画像名から自動で img タグのalt属性, width属性, height属性を付与する
        # (Middleman::Extensions::AutomaticAltTags より)
        unless url.include?('://')
          options[:alt]    ||= ''
          options[:width]  ||= ''
          options[:height] ||= ''

          real_path = url.dup
          unless real_path.start_with?('/')
            real_path = File.join(config[:images_dir], real_path)
          end

          file = app.files.find(:source, real_path)

          if file && file[:full_path].exist?
            # alt 属性
            if options[:alt].empty?
              options[:alt] = File.basename(file[:full_path].to_s,'.*').capitalize!
            end

            # width属性, height属性
            if options[:width].empty? || options[:height].empty?
              w, h = FastImage.size(file[:full_path])
              options[:width]  = w
              options[:height] = h
            end
          end
        end

        tag(:img, options)
      end
    end
  end
end
//}

//list[][ソースコード slim]{
= image_tag "logo.webp"
//}

//list[][ビルド結果 html]{
<img src="images/logo.webp" alt="logo" loading="lazy" width="200px" height="100px">
//}

ブラウザでのレイアウトシフトを回避するために、@<code>{<img>} タグは @<code>{<img width="○○px" height="○○px"} と、@<code>{width} 属性、@<code>{height} 属性 の記述が求められるようになりましたので、こちらも自動で付与するようにしています。

//blankline
以上、静的サイトジェネレータ @<code>{Middleman} の使い方を紹介してきました。

少し規模が大きくなると、素の HTML や CSS を使ってウェブサイトを構築していくのは大変になります。先人の方々が効果的に開発できるよう、素晴らしい資源を提供してくださっていますので、活用していきましょう。

そしてその恵みに感謝しつつ、後世に生きる方々のために貢献できるよう、何かを残せたら仕合わせです。
