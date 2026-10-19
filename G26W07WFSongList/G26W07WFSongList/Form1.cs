using Microsoft.EntityFrameworkCore;

namespace G26W07WFSongList {

    // 디자이너가 Form1을 찾으려면 Form1이 파일의 첫 번째 클래스여야 한다.
    // (Song, AppDbContext를 위에 두면 디자이너에서 오류가 난다 -> 아래로 옮김)
    public partial class Form1 : Form {
        //private List<Song> _songs = [];
        private AppDbContext _db = new AppDbContext();

        public Form1() {
            InitializeComponent();

            _db.Database.EnsureCreated();

            // Songs 테이블이 비어있으면 초기 데이터 추가
            if (!_db.Songs.Any()) {
                List<Song> initialSongs = [
                    new("Blue Hour", "LUNA8", 5),
                    new("도깨비불 (Ghostfire)", "X-CROSS", 4),
                    new("Spicy Love", "Cherry Bomb", 5),
                    new("신기루 (Mirage)", "ONE-WAY", 3),
                    new("Hypnotized", "NEXUS", 4),
                    new("첫사랑 법칙 (First Love Rule)", "Pureum", 5),
                    new("Black Out", "Viper", 4),
                    new("한여름 밤의 꿈 (Midsummer)", "SOLO", 5),
                    new("Cyberpunk", "GLITCH", 4),
                    new("별자리 (Constellation)", "Aura", 3),
                    new("Bad Boy, Good Girl", "TRIGGER", 5),
                    new("소리쳐 (Shout Out)", "ZEAL", 4),
                    new("Velvet Dress", "Siren", 5),
                    new("그림자놀이 (Shadow)", "ECLIPSE", 4),
                    new("Neon City", "Beat Runners", 3),
                    new("비밀정원 (Secret)", "Fairy Tale", 5),
                    new("Crash Landing", "Sledge", 4),
                    new("눈이 부시게 (Blinding)", "DAWN", 5),
                    new("Wildfire", "ASHE", 4),
                    new("시간을 달려서 (Time Warp)", "Nova", 4)
                ];

                _db.Songs.AddRange(initialSongs);
                _db.SaveChanges();
            }

            //var filteredSongs = _db.Songs
            //    .Where(s => s.Rating >= 4)
            //    .OrderByDescending(s => s.Rating);

            //foreach (var song in filteredSongs) {
            //    listSong.Items.Add(song);
            //}

            LoadSongs();
        }

        private void OnAdd(object sender, EventArgs e) {
            string title = txtTitle.Text.Trim();
            string artist = txtArtist.Text.Trim();

            if (title.Length == 0 || artist.Length == 0) {
                MessageBox.Show("제목과 가수를 모두 입력하세요.");
                return;
            }

            // TryParse: 숫자로 못 바꾸면 예외 대신 false를 돌려준다 (out으로 결과를 받음)
            if (!int.TryParse(txtRating.Text, out int rating) || rating < 1 || rating > 5) {
                MessageBox.Show("평점은 1~5 사이의 숫자로 입력하세요.");
                txtRating.SelectAll();
                txtRating.Focus();
                return;
            }

            // Id는 넘기지 않는다 -> DB가 AUTOINCREMENT로 부여
            var song = new Song(title, artist, rating);

            _db.Songs.Add(song);        // 메모리에만 반영
            _db.SaveChanges();          // 실제로 songs.db에 기록

            LoadSongs();                // 화면 갱신

            txtTitle.Clear();
            txtArtist.Clear();
            txtRating.Clear();
            txtTitle.Focus();
        }

        // ListBox에서 선택이 바뀔 때마다 불린다.
        // is not Song song  -> Song 타입인지 검사하면서 맞으면 song 변수를 바로 만든다 (패턴 매칭)
        private void OnChanged(object sender, EventArgs e) {
            if (listSong.SelectedItem is not Song song) {
                txtSelected.Clear();
                btnDelete.Enabled = false;      // 고를 게 없으면 삭제 버튼을 잠근다
                return;
            }

            txtSelected.Text = song.ToString();
            btnDelete.Enabled = true;
        }

        private void OnDelete(object sender, EventArgs e) {
            if (listSong.SelectedItem is not Song song)
                return;

            var result = MessageBox.Show(
                $"{song.ToString()}\n\n노래를 삭제할까요?",
                "삭제 확인",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (result != DialogResult.Yes)     // 되돌릴 수 없으니 한 번 더 확인
                return;

            _db.Songs.Remove(song);
            _db.SaveChanges();

            LoadSongs();

            txtSelected.Clear();
            btnDelete.Enabled = false;
        }

        // 목록을 다시 채우는 일을 함수 하나로 모았다.
        // 노래를 추가/삭제한 뒤에도 이 함수만 부르면 화면이 갱신된다.
        private void LoadSongs() {
            listSong.Items.Clear();     // 비우지 않으면 부를 때마다 중복 추가된다

            var songs = _db.Songs
                //.Where(s => s.Rating >= 4)
                .OrderByDescending(s => s.Rating)
                .ToList();

            foreach (var song in songs)
                listSong.Items.Add(song);
        }
    }

    public record Song(string Title, string Artist, int Rating) {
        // 이름이 Id면 EF Core가 Primary Key로 인식한다.
        // set 대신 init -> DB가 값을 넣는 것은 허용하고, 이후 수정은 막는다.
        public int Id { get; init; }

        public override string ToString() => $"{Title} - [{Artist}] (⭐{Rating})";
    }

    public class AppDbContext : DbContext {
        public DbSet<Song> Songs { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder) {
            // songs.db 파일로 저장
            optionsBuilder.UseSqlite("Data Source=songs.db");
        }
    }
}
