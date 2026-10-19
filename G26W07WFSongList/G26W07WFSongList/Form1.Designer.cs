namespace G26W07WFSongList
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            listSong = new ListBox();
            txtTitle = new TextBox();
            txtArtist = new TextBox();
            txtRating = new TextBox();
            btnAdd = new Button();
            txtSelected = new TextBox();
            btnDelete = new Button();
            txtFilter = new TextBox();
            SuspendLayout();
            //
            // txtFilter
            //
            txtFilter.Location = new Point(0, 12);
            txtFilter.Name = "txtFilter";
            txtFilter.PlaceholderText = "제목 또는 가수 검색";
            txtFilter.Size = new Size(760, 31);
            txtFilter.TabIndex = 7;
            txtFilter.TextChanged += OnFilterChanged;
            //
            // listSong
            //
            listSong.FormattingEnabled = true;
            listSong.Location = new Point(0, 55);
            listSong.Name = "listSong";
            listSong.Size = new Size(760, 579);
            listSong.TabIndex = 0;
            listSong.SelectedIndexChanged += OnChanged;
            listSong.DoubleClick += OnYouTube;
            //
            // txtTitle
            //
            txtTitle.Location = new Point(0, 647);
            txtTitle.Name = "txtTitle";
            txtTitle.PlaceholderText = "제목";
            txtTitle.Size = new Size(300, 31);
            txtTitle.TabIndex = 1;
            //
            // txtArtist
            //
            txtArtist.Location = new Point(306, 647);
            txtArtist.Name = "txtArtist";
            txtArtist.PlaceholderText = "가수";
            txtArtist.Size = new Size(220, 31);
            txtArtist.TabIndex = 2;
            //
            // txtRating
            //
            txtRating.Location = new Point(532, 647);
            txtRating.MaxLength = 1;
            txtRating.Name = "txtRating";
            txtRating.PlaceholderText = "평점";
            txtRating.Size = new Size(60, 31);
            txtRating.TabIndex = 3;
            //
            // btnAdd
            //
            btnAdd.Location = new Point(598, 645);
            btnAdd.Name = "btnAdd";
            btnAdd.Size = new Size(162, 35);
            btnAdd.TabIndex = 4;
            btnAdd.Text = "추가";
            btnAdd.UseVisualStyleBackColor = true;
            btnAdd.Click += OnAdd;
            //
            // txtSelected
            //
            txtSelected.Enabled = false;
            txtSelected.Location = new Point(0, 691);
            txtSelected.Name = "txtSelected";
            txtSelected.PlaceholderText = "삭제를 위해 선택된 노래";
            txtSelected.ReadOnly = true;
            txtSelected.Size = new Size(592, 31);
            txtSelected.TabIndex = 5;
            txtSelected.TabStop = false;
            //
            // btnDelete
            //
            btnDelete.Enabled = false;
            btnDelete.Location = new Point(598, 689);
            btnDelete.Name = "btnDelete";
            btnDelete.Size = new Size(162, 35);
            btnDelete.TabIndex = 6;
            btnDelete.Text = "삭제";
            btnDelete.UseVisualStyleBackColor = true;
            btnDelete.Click += OnDelete;
            //
            // Form1
            //
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(772, 755);
            Controls.Add(listSong);
            Controls.Add(txtTitle);
            Controls.Add(txtArtist);
            Controls.Add(txtRating);
            Controls.Add(btnAdd);
            Controls.Add(txtSelected);
            Controls.Add(btnDelete);
            Controls.Add(txtFilter);
            Name = "Form1";
            Text = "애창곡";
            ResumeLayout(false);
        }

        #endregion

        private ListBox listSong;
        private TextBox txtTitle;
        private TextBox txtArtist;
        private TextBox txtRating;
        private Button btnAdd;
        private TextBox txtSelected;
        private Button btnDelete;
        private TextBox txtFilter;
    }
}
