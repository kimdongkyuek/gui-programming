namespace G26W07WFCardDealer
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
            card1 = new PictureBox();
            button1 = new Button();
            ((System.ComponentModel.ISupportInitialize)card1).BeginInit();
            SuspendLayout();
            // 
            // card1
            // 
            card1.Image = Properties.Resources.red_joker;
            card1.Location = new Point(2, 2);
            card1.Name = "card1";
            card1.Size = new Size(341, 462);
            card1.SizeMode = PictureBoxSizeMode.Zoom;
            card1.TabIndex = 0;
            card1.TabStop = false;
            // 
            // button1
            // 
            button1.Location = new Point(12, 470);
            button1.Name = "button1";
            button1.Size = new Size(331, 43);
            button1.TabIndex = 1;
            button1.Text = "카드분배";
            button1.UseVisualStyleBackColor = true;
            button1.Click += OnDeal;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(355, 576);
            Controls.Add(button1);
            Controls.Add(card1);
            Name = "Form1";
            Text = "카드딜러";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)card1).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private PictureBox card1;
        private Button button1;
    }
}
