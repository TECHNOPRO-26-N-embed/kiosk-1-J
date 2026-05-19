# 実装すべき関数一覧と役割

## 1. ユーザー認証・管理
- `int authenticate_user(const char* user_id);`
  - ユーザーIDの認証を行う。

## 2. 書籍貸出・返却管理
- `int checkout_book(const char* user_id, const char* book_id, const char* date);`
  - 指定ユーザーによる書籍の貸出処理。ユーザーIDと書籍IDの整合性チェック、貸出情報のCSV保存。
- `int return_book(const char* user_id, const char* book_id, const char* date);`
  - 指定ユーザーによる書籍の返却処理。ユーザーIDと書籍IDの整合性チェック、返却情報のCSV保存。
- `int can_user_borrow_book(const char* user_id, const char* book_id);`
  - 書籍が貸出可能か（在庫が1冊以上あること）、かつ指定ユーザーがその書籍を借りられるかを判定。

## 3. 延滞・料金計算
- `int calculate_late_fee(const char* checkout_date, const char* return_date);`
  - 貸出日と返却日から延滞料金を計算。
- `int calculate_rental_fee(const char* book_id);`
  - 書籍ごとの貸出料金を計算。

## 4. 書籍・ユーザー情報管理
- `int load_books_from_csv(const char* csv_path);`
  - 書籍情報をCSVから読み込む。
- `int load_users_from_csv(const char* csv_path);`
  - ユーザー情報をCSVから読み込む。
- `int save_checkout_log(const char* user_id, const char* book_id, const char* date, const char* action);`
  - 貸出・返却操作のログをCSVに保存。
- `int is_valid_book_id(const char* book_id);`
  - 書籍IDが登録済みかどうかを判定。

## 5. 在庫管理
- `int get_book_stock(const char* book_id);`
  - 書籍の在庫数を取得。

## 6. ポイント・会員管理（オプション）
- `int add_user_point(const char* user_id, int points);`
  - ユーザーにポイントを付与。
- `int get_user_point(const char* user_id);`
  - ユーザーのポイントを取得。

## 7. その他
- `void print_error(const char* message);`
  - エラーメッセージの表示。
- `void print_log(const char* message);`
  - 操作ログの表示。

## 8. 通知機能
- `void notify_due_date(const char* user_id, const char* book_id, const char* due_date);`
  - 返却期限の1日前に、指定ユーザーに通知を送信する。

---

各関数は要件定義書の機能要件・非機能要件に基づき設計されています。

---

# 画面遷移（テキスト形式）

【ユーザーID入力（ログイン画面）】
├─ ユーザーID入力・認証
└─ 認証成功 → 【メインメニュー】

【メインメニュー】
├─ 1. 書籍貸出 → 【書籍貸出画面】
│ ├─ 書籍ID入力
│ ├─ 貸出可否判定・結果表示
│ ├─ 料金計算・支払い
│ ├─ 貸出確定・CSV保存
│ └─ メインメニューへ戻る
├─ 2. 書籍返却 → 【書籍返却画面】
│ ├─ 書籍ID入力
│ ├─ 返却可否判定・延滞料金表示
│ └─ メインメニューへ戻る
├─ 3. 在庫照会 → 【在庫照会画面】
│ ├─ 書籍ID入力
│ ├─ 在庫数表示
│ └─ メインメニューへ戻る
├─ 4. ログ参照 → 【操作ログ画面】
│ ├─ ログ一覧表示
│ └─ メインメニューへ戻る
└─ 0. ログアウト → 【ユーザーID入力（ログイン画面）】

※ ポイント・会員管理機能がある場合は、メインメニューに追加可能

---

# 必要なデータ一覧

| 情報の名前 | 内容や説明 | 例 |
|---|---|---|
| ユーザーID | 紙で発行された利用者識別子。ログイン、貸出・返却の本人確認に使用。 | U000123 |
| ユーザー名 | ユーザーIDに紐づく利用者名。画面表示やログ確認時の識別に使用。 | 山田太郎 |
| 書籍ID | 書籍を一意に識別するID。CSVで事前登録されたIDのみ有効。 | B001245 |
| 書籍名 | 書籍のタイトル情報。画面表示や検索結果表示に使用。 | 吾輩は猫である |
| 在庫数 | 同一書籍IDの貸出可能冊数。1冊以上で貸出可否判定に利用。 | 3 |
| 貸出日 | 書籍を貸し出した日付。返却期限、延滞判定に使用。 | 2026-05-19 |
| 返却日 | 書籍を返却した日付。延滞料金計算に使用。 | 2026-05-27 |
| 返却期限日 | 貸出日から7泊8日ルールで算出する期限日。 | 2026-05-26 |
| 貸出料金 | 書籍貸出時に発生する基本料金。支払い処理対象。 | 300 |
| 延滞料金 | 返却期限超過時に発生する追加料金。 | 200 |
| 支払い金額 | 貸出料金と必要に応じた延滞料金の合計。 | 500 |
| 貸出状態 | 書籍の現在状態（貸出中/返却済/在庫あり）を管理。 | 貸出中 |

---

# CSV保存形式定義

## 1. ユーザーマスタCSV（users.csv）

CSV形式（ヘッダー）:
ユーザーID,ユーザー名,利用可否
CSV行例:
000101,山田太郎,1

## 2. 書籍マスタCSV（books.csv）

CSV形式（ヘッダー）:
書籍ID,書籍名,貸出料金,在庫冊数,書籍登録日
CSV行例:
B000201,C言語を学ぼう！,300,3,2026-05-19

## 3. 貸出・返却履歴CSV（transactions.csv）

CSV形式（ヘッダー）:
貸出状況,ユーザーID,書籍ID,書籍名,支払料金,貸出日,返却期間,返却日,延滞料金
CSV行例:
返却済,000101,B000201,C言語を学ぼう！,700,5/15,5/23,5/26,500