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
            SuspendLayout();
            //
            // listSong
            //
            listSong.FormattingEnabled = true;
            listSong.Location = new Point(0, 0);
            listSong.Name = "listSong";
            listSong.Size = new Size(760, 579);
            listSong.TabIndex = 0;
            //
            // txtTitle
            //
            txtTitle.Location = new Point(0, 592);
            txtTitle.Name = "txtTitle";
            txtTitle.PlaceholderText = "제목";
            txtTitle.Size = new Size(300, 31);
            txtTitle.TabIndex = 1;
            //
            // txtArtist
            //
            txtArtist.Location = new Point(306, 592);
            txtArtist.Name = "txtArtist";
            txtArtist.PlaceholderText = "가수";
            txtArtist.Size = new Size(220, 31);
            txtArtist.TabIndex = 2;
            //
            // txtRating
            //
            txtRating.Location = new Point(532, 592);
            txtRating.MaxLength = 1;
            txtRating.Name = "txtRating";
            txtRating.PlaceholderText = "평점";
            txtRating.Size = new Size(60, 31);
            txtRating.TabIndex = 3;
            //
            // btnAdd
            //
            btnAdd.Location = new Point(598, 590);
            btnAdd.Name = "btnAdd";
            btnAdd.Size = new Size(162, 35);
            btnAdd.TabIndex = 4;
            btnAdd.Text = "추가";
            btnAdd.UseVisualStyleBackColor = true;
            btnAdd.Click += OnAdd;
            //
            // Form1
            //
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(772, 700);
            Controls.Add(listSong);
            Controls.Add(txtTitle);
            Controls.Add(txtArtist);
            Controls.Add(txtRating);
            Controls.Add(btnAdd);
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
    }
}
