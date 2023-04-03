= 基本的な ショートカット & コマンド

//abstract{
GUI によるマウス操作は直感的ですぐに習得できます。そして良く使う操作は、特定のキー入力の組み合わせで実現できるように用意された「ショートカットキー」を使うと速くて楽にできるようになります。またコマンド操作が出来ることも生産性向上に繋がります。

習得したい基本的なショートカットとコマンドのご紹介です。是非、お役立てください。
//}

== Mac の為の ショートカット

=== 入力ソース切替
//table[][]{
キーバインド	動作
-----------------
Ctrl + Space	日本語入力と英数入力を切替
//}

=== ファイル操作
//table[][]{
キーバインド	動作	意味
-----------------
Command + O	ファイルを開く	Open 開く
Command + S	ファイルを保存する	Save 保存する
//}

=== テキスト編集
//table[][]{
キーバインド	動作	意味
-----------------
Command + Z	元に戻す	.
Command + X	切り取り	.
Command + C	コピー	Copy
Command + V	貼付	.
Command + A	全選択	All
Ctrl + H	カーソルの左の文字を削除	.
Ctrl + D	カーソルの右の文字を削除	Delete
Ctrl + K	カーソル以降を切り取り	Kill line
Ctrl + T	カーソル前後の文字を入替	Transpose 転置
//}

=== カーソル移動
//table[][]{
キーバインド	動作	意味
-----------------
Ctrl + F	カーソルを右へ移動	Forward 先へ進んで
Ctrl + B	カーソルを左へ移動	Backward 後方へ
Ctrl + P	カーソルを上へ移動	Previous 以前の行へ
Ctrl + N	カーソルを下へ移動	Next 次の行へ
Ctrl + A	カーソルを行頭へ移動	Ahead 前方へ
Ctrl + E	カーソルを行末へ移動	End 行末へ
//}

== Atom の為の ショートカット
//table[][]{
キーバインド	動作	意味
-----------------
Shift + Command + D	行の複製	Duplicate
Shift + Ctrl + K	行の削除	Kill line
Command + /	コメントアウト	.
Ctrl + F	検索（ファイル内)	Find 見つけ出す
Shift + Ctrl + F	検索（プロジェクト内)	Find 見つけ出す
Ctrl + G	任意行へカーソルを移動	Go
Command + ]	インデントを追加	.
Command + [	インデントを削除	.
Command + K →	画面分割	.
Command + W	画面を閉じる	Window close
Shift + Ctrl + P	コマンドパレット	Pallet
Shift + Command + C	色を選択	pigments
//}


== 基本的なコマンド一覧

=== ls (LiSt)
//table[][カレントディレクトリにあるファイルやディレクトリを表示]{
コマンド	意味
-----------------
ls	ファイルやディレクトリを表示
ls -l	ファイルやディレクトリを詳細表示
ls -a	ファイルやディレクトリを表示(隠しファイル含む)
ls -la	ファイルやディレクトリを詳細表示(隠しファイル含む)
//}

//clearpage

=== cd (Change Directory)
//table[][カレントディレクトリを移動]{
コマンド	意味
-----------------
cd source	sourceディレクトリに移動
cd ~/	ホームディレクトリに移動
ls ..	親ディレクトリに移動
//}

=== pwd (Print Working Directory)
//table[][カレントディレクトリを表示]{
コマンド	意味
-----------------
pwd	カレントディレクトリを表示
//}

=== touch
//table[][タイムスタンプ更新や空ファイル作成]{
コマンド	意味
-----------------
touch index.html	index.html ファイルを作成
//}

=== mkdir (MaKe DIRectory)
//table[][新しいディレクトリを作成]{
コマンド	意味
-----------------
mkdir stylesheets	stylesheets ディレクトリを作成
//}

=== mv (MoVe)
//table[][ファイル名変更や移動]{
コマンド	意味
-----------------
mv master.css style.css	master.cssからstyle.cssにファイル名変更
mv style.css stylesheets	style.cssをstylesheetsディレクトリに移動
//}

//clearpage

=== cp (CoPy)
//table[][ファイルをコピーする]{
コマンド	意味
-----------------
cp master.css style.css	master.cssをstyle.cssにコピー
cp style.css stylesheets	style.cssをstylesheetsディレクトリにコピー
cp -r stylesheets /tmp/	stylesheetsディレクトリを/tmp/ディレクトリに @<br>{}再帰的(Recursive)にコピー
//}

=== rm (ReMove)
//table[][ファイル削除]{
コマンド	意味
-----------------
rm master.css	master.cssを削除
rm -rf stylesheets	stylesheetsディレクトリを削除(要注意)
//}

=== open
//table[][ターミナルからFinderでファイルを開く]{
コマンド	意味
-----------------
open .	カレントディレクトリをFinderで開く
open ~/	ホームディレクトリFinderで開く
atom ./	カレントディレクトリをAtomで開く(参考)
//}

=== source
//table[][ファイル内のコマンドを現在のシェルで実行]{
コマンド	意味
-----------------
source ~/.zshrc	~/.zshrc を読み込み 設定を反映する
//}

//clearpage

=== history
//table[][コマンド履歴を表示]{
コマンド	意味
-----------------
history	コマンド履歴を表示
!7	履歴7番のコマンドを実行
Command + P	直前のコマンドを表示 Enterで実行
//}

=== cat (conCATenate)
//table[][ファイル内容表示及び連結]{
コマンド	意味
-----------------
cat a.txt	内容を表示
cat -n a.txt	行番号付きで内容を表示
cat a.txt b.txt > c.txt	結合してc.txtに書込
//}

//blankline
//blankline
//blankline

====[column] 金の延棒クイズ 【解答】

最後までお読みくださり、ありがとうございます。金の延棒クイズの解答です。
//blankline

//sideimage[gold_table2][35mm][sep=5mm,side=R]{
２回鋏を入れて、金の延棒を１と２と４の大きさに分割します。

一日目のお支払いには、１の延棒を渡します。

二日目のお支払いには、２の延棒を渡して、先に渡した１の延棒は返してもらいます。

三日目のお支払いには、１の延棒も渡します。

四日目のお支払いには、大きな４の延棒を渡し、２と１の延棒は返してもらいます。

五日目のお支払いには、１の延棒も渡します。

六日目のお支払いには、２の延棒を渡して、先に渡した１の延棒は返してもらいます。

七日目のお支払いには、全ての延棒を渡します。

//}
//blankline

延棒の有無を @<code>{0} と @<code>{1} で表すと二進数と対応しています。

意外なところに潜む二進数。探してみてくださいね。
