namespace G26W07WFCardDealer {
    partial class Form1 {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            card1 = new PictureBox();
            card2 = new PictureBox();
            card3 = new PictureBox();
            card4 = new PictureBox();
            card5 = new PictureBox();
            btnDeal = new Button();
            labelRank = new Label();
            ((System.ComponentModel.ISupportInitialize)card1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)card2).BeginInit();
            ((System.ComponentModel.ISupportInitialize)card3).BeginInit();
            ((System.ComponentModel.ISupportInitialize)card4).BeginInit();
            ((System.ComponentModel.ISupportInitialize)card5).BeginInit();
            SuspendLayout();
            // 
            // card1
            // 
            card1.Image = Properties.Resources.red_joker;
            card1.Location = new Point(20, 2);
            card1.Name = "card1";
            card1.Size = new Size(213, 404);
            card1.SizeMode = PictureBoxSizeMode.Zoom;
            card1.TabIndex = 0;
            card1.TabStop = false;
            // 
            // card2
            // 
            card2.Image = Properties.Resources.red_joker;
            card2.Location = new Point(290, 2);
            card2.Name = "card2";
            card2.Size = new Size(213, 404);
            card2.SizeMode = PictureBoxSizeMode.Zoom;
            card2.TabIndex = 1;
            card2.TabStop = false;
            // 
            // card3
            // 
            card3.Image = Properties.Resources.red_joker;
            card3.Location = new Point(560, 2);
            card3.Name = "card3";
            card3.Size = new Size(213, 404);
            card3.SizeMode = PictureBoxSizeMode.Zoom;
            card3.TabIndex = 2;
            card3.TabStop = false;
            // 
            // card4
            // 
            card4.Image = Properties.Resources.red_joker;
            card4.Location = new Point(830, 2);
            card4.Name = "card4";
            card4.Size = new Size(213, 404);
            card4.SizeMode = PictureBoxSizeMode.Zoom;
            card4.TabIndex = 3;
            card4.TabStop = false;
            // 
            // card5
            // 
            card5.Image = Properties.Resources.red_joker;
            card5.Location = new Point(1100, 2);
            card5.Name = "card5";
            card5.Size = new Size(213, 404);
            card5.SizeMode = PictureBoxSizeMode.Zoom;
            card5.TabIndex = 4;
            card5.TabStop = false;
            // 
            // labelRank
            // 
            labelRank.BackColor = SystemColors.Info;
            labelRank.Font = new Font("맑은 고딕", 20F, FontStyle.Bold, GraphicsUnit.Point);
            labelRank.Location = new Point(20, 425);
            labelRank.Name = "labelRank";
            labelRank.Size = new Size(460, 50);
            labelRank.TabIndex = 6;
            labelRank.Text = "카드를 분배하세요";
            labelRank.TextAlign = ContentAlignment.MiddleCenter;
            // 
            // btnDeal
            // 
            btnDeal.Location = new Point(519, 430);
            btnDeal.Name = "btnDeal";
            btnDeal.Size = new Size(331, 43);
            btnDeal.TabIndex = 5;
            btnDeal.Text = "카드분배";
            btnDeal.UseVisualStyleBackColor = true;
            btnDeal.Click += OnDeal;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1372, 520);
            Controls.Add(labelRank);
            Controls.Add(btnDeal);
            Controls.Add(card5);
            Controls.Add(card4);
            Controls.Add(card3);
            Controls.Add(card2);
            Controls.Add(card1);
            Name = "Form1";
            Text = "카드딜러";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)card1).EndInit();
            ((System.ComponentModel.ISupportInitialize)card2).EndInit();
            ((System.ComponentModel.ISupportInitialize)card3).EndInit();
            ((System.ComponentModel.ISupportInitialize)card4).EndInit();
            ((System.ComponentModel.ISupportInitialize)card5).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private PictureBox card1;
        private PictureBox card2;
        private PictureBox card3;
        private PictureBox card4;
        private PictureBox card5;
        private Button btnDeal;
        private Label labelRank;
    }
}
