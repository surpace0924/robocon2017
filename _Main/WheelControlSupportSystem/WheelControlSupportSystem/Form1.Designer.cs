namespace WheelControlSupportSystem
{
	partial class Form1
	{
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows フォーム デザイナーで生成されたコード

		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.button4 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button1 = new System.Windows.Forms.Button();
			this.btnCal = new System.Windows.Forms.Button();
			this.txbFieldScale = new System.Windows.Forms.TextBox();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.tabPage2 = new System.Windows.Forms.TabPage();
			this.label8 = new System.Windows.Forms.Label();
			this.labWheelPwm1 = new System.Windows.Forms.Label();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel2 = new System.Windows.Forms.Panel();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.pcbRightAxis = new System.Windows.Forms.PictureBox();
			this.pcbLeftAxis = new System.Windows.Forms.PictureBox();
			this.pcbWheel3 = new System.Windows.Forms.PictureBox();
			this.pcbWheel2 = new System.Windows.Forms.PictureBox();
			this.pcbWheel1 = new System.Windows.Forms.PictureBox();
			this.pcbWheel0 = new System.Windows.Forms.PictureBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.button5 = new System.Windows.Forms.Button();
			this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.labWheelPwm3 = new System.Windows.Forms.Label();
			this.labWheelPwm0 = new System.Windows.Forms.Label();
			this.labWheelPwm2 = new System.Windows.Forms.Label();
			this.labWheelArg1 = new System.Windows.Forms.Label();
			this.labWheelArg0 = new System.Windows.Forms.Label();
			this.labWheelArg2 = new System.Windows.Forms.Label();
			this.labWheelArg3 = new System.Windows.Forms.Label();
			this.tabControl1.SuspendLayout();
			this.tabPage1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.tabPage2.SuspendLayout();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pcbRightAxis)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbLeftAxis)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel2)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel0)).BeginInit();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Controls.Add(this.tabPage1);
			this.tabControl1.Controls.Add(this.tabPage2);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Margin = new System.Windows.Forms.Padding(4);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(1276, 800);
			this.tabControl1.TabIndex = 0;
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.button4);
			this.tabPage1.Controls.Add(this.button3);
			this.tabPage1.Controls.Add(this.button2);
			this.tabPage1.Controls.Add(this.button1);
			this.tabPage1.Controls.Add(this.btnCal);
			this.tabPage1.Controls.Add(this.txbFieldScale);
			this.tabPage1.Controls.Add(this.pictureBox1);
			this.tabPage1.Location = new System.Drawing.Point(4, 26);
			this.tabPage1.Margin = new System.Windows.Forms.Padding(4);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(4);
			this.tabPage1.Size = new System.Drawing.Size(1268, 770);
			this.tabPage1.TabIndex = 0;
			this.tabPage1.Text = "tabPage1";
			this.tabPage1.UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(364, 15);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(75, 23);
			this.button4.TabIndex = 6;
			this.button4.Text = "button4";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Click += new System.EventHandler(this.button4_Click);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(258, 14);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(75, 23);
			this.button3.TabIndex = 5;
			this.button3.Text = "button3";
			this.button3.UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(132, 15);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 4;
			this.button2.Text = "button2";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(34, 16);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 3;
			this.button1.Text = "button1";
			this.button1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// btnCal
			// 
			this.btnCal.Location = new System.Drawing.Point(470, 14);
			this.btnCal.Name = "btnCal";
			this.btnCal.Size = new System.Drawing.Size(75, 23);
			this.btnCal.TabIndex = 2;
			this.btnCal.Text = "計算";
			this.btnCal.UseVisualStyleBackColor = true;
			this.btnCal.Click += new System.EventHandler(this.btnCal_Click);
			// 
			// txbFieldScale
			// 
			this.txbFieldScale.Location = new System.Drawing.Point(838, 93);
			this.txbFieldScale.Name = "txbFieldScale";
			this.txbFieldScale.Size = new System.Drawing.Size(100, 24);
			this.txbFieldScale.TabIndex = 1;
			this.txbFieldScale.Text = "20.32";
			// 
			// pictureBox1
			// 
			this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
			this.pictureBox1.Location = new System.Drawing.Point(8, 54);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(691, 708);
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseClick);
			// 
			// tabPage2
			// 
			this.tabPage2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.tabPage2.Controls.Add(this.label8);
			this.tabPage2.Controls.Add(this.labWheelArg0);
			this.tabPage2.Controls.Add(this.labWheelPwm0);
			this.tabPage2.Controls.Add(this.labWheelArg2);
			this.tabPage2.Controls.Add(this.labWheelPwm2);
			this.tabPage2.Controls.Add(this.labWheelArg3);
			this.tabPage2.Controls.Add(this.labWheelPwm3);
			this.tabPage2.Controls.Add(this.labWheelArg1);
			this.tabPage2.Controls.Add(this.labWheelPwm1);
			this.tabPage2.Controls.Add(this.panel1);
			this.tabPage2.Controls.Add(this.pcbWheel3);
			this.tabPage2.Controls.Add(this.pcbWheel2);
			this.tabPage2.Controls.Add(this.pcbWheel1);
			this.tabPage2.Controls.Add(this.pcbWheel0);
			this.tabPage2.Controls.Add(this.textBox1);
			this.tabPage2.Controls.Add(this.button5);
			this.tabPage2.Location = new System.Drawing.Point(4, 26);
			this.tabPage2.Margin = new System.Windows.Forms.Padding(4);
			this.tabPage2.Name = "tabPage2";
			this.tabPage2.Padding = new System.Windows.Forms.Padding(4);
			this.tabPage2.Size = new System.Drawing.Size(1268, 770);
			this.tabPage2.TabIndex = 1;
			this.tabPage2.Text = "tabPage2";
			this.tabPage2.UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(162, 166);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(0, 17);
			this.label8.TabIndex = 5;
			// 
			// labWheelPwm1
			// 
			this.labWheelPwm1.AutoSize = true;
			this.labWheelPwm1.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm1.Location = new System.Drawing.Point(131, 96);
			this.labWheelPwm1.Name = "labWheelPwm1";
			this.labWheelPwm1.Size = new System.Drawing.Size(126, 47);
			this.labWheelPwm1.TabIndex = 5;
			this.labWheelPwm1.Text = "label4";
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.panel2);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel1.Location = new System.Drawing.Point(4, 505);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(1258, 259);
			this.panel1.TabIndex = 4;
			// 
			// panel2
			// 
			this.panel2.BackColor = System.Drawing.Color.Silver;
			this.panel2.Controls.Add(this.label2);
			this.panel2.Controls.Add(this.label3);
			this.panel2.Controls.Add(this.label1);
			this.panel2.Controls.Add(this.pcbRightAxis);
			this.panel2.Controls.Add(this.pcbLeftAxis);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Left;
			this.panel2.Location = new System.Drawing.Point(0, 0);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(469, 259);
			this.panel2.TabIndex = 0;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(98, 33);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(21, 17);
			this.label2.TabIndex = 5;
			this.label2.Text = "左";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Meiryo UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label3.Location = new System.Drawing.Point(191, 13);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(62, 20);
			this.label3.TabIndex = 5;
			this.label3.Text = "スティック";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(331, 33);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(21, 17);
			this.label1.TabIndex = 5;
			this.label1.Text = "右";
			// 
			// pcbRightAxis
			// 
			this.pcbRightAxis.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pcbRightAxis.BackgroundImage")));
			this.pcbRightAxis.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbRightAxis.Location = new System.Drawing.Point(239, 53);
			this.pcbRightAxis.Name = "pcbRightAxis";
			this.pcbRightAxis.Size = new System.Drawing.Size(200, 200);
			this.pcbRightAxis.TabIndex = 0;
			this.pcbRightAxis.TabStop = false;
			this.pcbRightAxis.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pcbRightAxis_MouseClick);
			// 
			// pcbLeftAxis
			// 
			this.pcbLeftAxis.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pcbLeftAxis.BackgroundImage")));
			this.pcbLeftAxis.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbLeftAxis.Location = new System.Drawing.Point(4, 53);
			this.pcbLeftAxis.Name = "pcbLeftAxis";
			this.pcbLeftAxis.Size = new System.Drawing.Size(200, 200);
			this.pcbLeftAxis.TabIndex = 0;
			this.pcbLeftAxis.TabStop = false;
			this.pcbLeftAxis.MouseClick += new System.Windows.Forms.MouseEventHandler(this.pcbLeftAxis_MouseClick);
			// 
			// pcbWheel3
			// 
			this.pcbWheel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbWheel3.Location = new System.Drawing.Point(479, 265);
			this.pcbWheel3.Name = "pcbWheel3";
			this.pcbWheel3.Size = new System.Drawing.Size(210, 210);
			this.pcbWheel3.TabIndex = 3;
			this.pcbWheel3.TabStop = false;
			// 
			// pcbWheel2
			// 
			this.pcbWheel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbWheel2.Location = new System.Drawing.Point(263, 265);
			this.pcbWheel2.Name = "pcbWheel2";
			this.pcbWheel2.Size = new System.Drawing.Size(210, 210);
			this.pcbWheel2.TabIndex = 3;
			this.pcbWheel2.TabStop = false;
			// 
			// pcbWheel1
			// 
			this.pcbWheel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbWheel1.Location = new System.Drawing.Point(263, 49);
			this.pcbWheel1.Name = "pcbWheel1";
			this.pcbWheel1.Size = new System.Drawing.Size(210, 210);
			this.pcbWheel1.TabIndex = 3;
			this.pcbWheel1.TabStop = false;
			// 
			// pcbWheel0
			// 
			this.pcbWheel0.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbWheel0.Location = new System.Drawing.Point(479, 49);
			this.pcbWheel0.Name = "pcbWheel0";
			this.pcbWheel0.Size = new System.Drawing.Size(210, 210);
			this.pcbWheel0.TabIndex = 3;
			this.pcbWheel0.TabStop = false;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(8, 7);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(100, 24);
			this.textBox1.TabIndex = 2;
			this.textBox1.Text = "COM6";
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(132, 8);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(75, 23);
			this.button5.TabIndex = 1;
			this.button5.Text = "button5";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// serialPort1
			// 
			this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// labWheelPwm3
			// 
			this.labWheelPwm3.AutoSize = true;
			this.labWheelPwm3.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm3.Location = new System.Drawing.Point(695, 428);
			this.labWheelPwm3.Name = "labWheelPwm3";
			this.labWheelPwm3.Size = new System.Drawing.Size(126, 47);
			this.labWheelPwm3.TabIndex = 5;
			this.labWheelPwm3.Text = "label4";
			// 
			// labWheelPwm0
			// 
			this.labWheelPwm0.AutoSize = true;
			this.labWheelPwm0.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm0.Location = new System.Drawing.Point(695, 96);
			this.labWheelPwm0.Name = "labWheelPwm0";
			this.labWheelPwm0.Size = new System.Drawing.Size(126, 47);
			this.labWheelPwm0.TabIndex = 5;
			this.labWheelPwm0.Text = "label4";
			// 
			// labWheelPwm2
			// 
			this.labWheelPwm2.AutoSize = true;
			this.labWheelPwm2.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm2.Location = new System.Drawing.Point(131, 428);
			this.labWheelPwm2.Name = "labWheelPwm2";
			this.labWheelPwm2.Size = new System.Drawing.Size(126, 47);
			this.labWheelPwm2.TabIndex = 5;
			this.labWheelPwm2.Text = "label4";
			// 
			// labWheelArg1
			// 
			this.labWheelArg1.AutoSize = true;
			this.labWheelArg1.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg1.Location = new System.Drawing.Point(131, 49);
			this.labWheelArg1.Name = "labWheelArg1";
			this.labWheelArg1.Size = new System.Drawing.Size(126, 47);
			this.labWheelArg1.TabIndex = 5;
			this.labWheelArg1.Text = "label4";
			// 
			// labWheelArg0
			// 
			this.labWheelArg0.AutoSize = true;
			this.labWheelArg0.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg0.Location = new System.Drawing.Point(695, 49);
			this.labWheelArg0.Name = "labWheelArg0";
			this.labWheelArg0.Size = new System.Drawing.Size(126, 47);
			this.labWheelArg0.TabIndex = 5;
			this.labWheelArg0.Text = "label4";
			// 
			// labWheelArg2
			// 
			this.labWheelArg2.AutoSize = true;
			this.labWheelArg2.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg2.Location = new System.Drawing.Point(131, 381);
			this.labWheelArg2.Name = "labWheelArg2";
			this.labWheelArg2.Size = new System.Drawing.Size(126, 47);
			this.labWheelArg2.TabIndex = 5;
			this.labWheelArg2.Text = "label4";
			// 
			// labWheelArg3
			// 
			this.labWheelArg3.AutoSize = true;
			this.labWheelArg3.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg3.Location = new System.Drawing.Point(695, 381);
			this.labWheelArg3.Name = "labWheelArg3";
			this.labWheelArg3.Size = new System.Drawing.Size(126, 47);
			this.labWheelArg3.TabIndex = 5;
			this.labWheelArg3.Text = "label4";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 17F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1276, 800);
			this.Controls.Add(this.tabControl1);
			this.Font = new System.Drawing.Font("Meiryo UI", 9.75F);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.tabControl1.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.tabPage1.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.tabPage2.ResumeLayout(false);
			this.tabPage2.PerformLayout();
			this.panel1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pcbRightAxis)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbLeftAxis)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel2)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbWheel0)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPage1;
		private System.Windows.Forms.TabPage tabPage2;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.TextBox txbFieldScale;
		private System.Windows.Forms.Button btnCal;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.PictureBox pcbRightAxis;
		private System.Windows.Forms.PictureBox pcbLeftAxis;
		private System.IO.Ports.SerialPort serialPort1;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.PictureBox pcbWheel0;
		private System.Windows.Forms.PictureBox pcbWheel1;
		private System.Windows.Forms.PictureBox pcbWheel3;
		private System.Windows.Forms.PictureBox pcbWheel2;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label labWheelPwm1;
		private System.Windows.Forms.Label labWheelPwm0;
		private System.Windows.Forms.Label labWheelPwm2;
		private System.Windows.Forms.Label labWheelPwm3;
		private System.Windows.Forms.Label labWheelArg0;
		private System.Windows.Forms.Label labWheelArg2;
		private System.Windows.Forms.Label labWheelArg3;
		private System.Windows.Forms.Label labWheelArg1;
	}
}

