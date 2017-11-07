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
			this.pcbLeftAxis = new System.Windows.Forms.PictureBox();
			this.panel1 = new System.Windows.Forms.Panel();
			this.panel2 = new System.Windows.Forms.Panel();
			this.pcbRightAxis = new System.Windows.Forms.PictureBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.labWheelArg3 = new System.Windows.Forms.Label();
			this.labWheelPwm3 = new System.Windows.Forms.Label();
			this.labWheelArg1 = new System.Windows.Forms.Label();
			this.labWheelPwm1 = new System.Windows.Forms.Label();
			this.timer1 = new System.Windows.Forms.Timer(this.components);
			this.labWheelArg2 = new System.Windows.Forms.Label();
			this.labWheelArg0 = new System.Windows.Forms.Label();
			this.labWheelPwm0 = new System.Windows.Forms.Label();
			this.labWheelPwm2 = new System.Windows.Forms.Label();
			this.pcbVector3 = new System.Windows.Forms.PictureBox();
			this.pcbVector1 = new System.Windows.Forms.PictureBox();
			this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
			this.pcbVector0 = new System.Windows.Forms.PictureBox();
			this.button5 = new System.Windows.Forms.Button();
			this.pcbVector2 = new System.Windows.Forms.PictureBox();
			this.textBox1 = new System.Windows.Forms.TextBox();
			((System.ComponentModel.ISupportInitialize)(this.pcbLeftAxis)).BeginInit();
			this.panel1.SuspendLayout();
			this.panel2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pcbRightAxis)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector3)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector1)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector0)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector2)).BeginInit();
			this.SuspendLayout();
			// 
			// pcbLeftAxis
			// 
			this.pcbLeftAxis.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pcbLeftAxis.BackgroundImage")));
			this.pcbLeftAxis.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbLeftAxis.Location = new System.Drawing.Point(3, 63);
			this.pcbLeftAxis.Name = "pcbLeftAxis";
			this.pcbLeftAxis.Size = new System.Drawing.Size(200, 200);
			this.pcbLeftAxis.TabIndex = 0;
			this.pcbLeftAxis.TabStop = false;
			// 
			// panel1
			// 
			this.panel1.Controls.Add(this.panel2);
			this.panel1.Dock = System.Windows.Forms.DockStyle.Right;
			this.panel1.Location = new System.Drawing.Point(1069, 0);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(207, 800);
			this.panel1.TabIndex = 22;
			// 
			// panel2
			// 
			this.panel2.BackColor = System.Drawing.Color.Gainsboro;
			this.panel2.Controls.Add(this.pcbRightAxis);
			this.panel2.Controls.Add(this.label3);
			this.panel2.Controls.Add(this.pcbLeftAxis);
			this.panel2.Controls.Add(this.label2);
			this.panel2.Controls.Add(this.label1);
			this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.panel2.Location = new System.Drawing.Point(0, 301);
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size(207, 499);
			this.panel2.TabIndex = 0;
			// 
			// pcbRightAxis
			// 
			this.pcbRightAxis.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pcbRightAxis.BackgroundImage")));
			this.pcbRightAxis.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbRightAxis.Location = new System.Drawing.Point(3, 296);
			this.pcbRightAxis.Name = "pcbRightAxis";
			this.pcbRightAxis.Size = new System.Drawing.Size(200, 200);
			this.pcbRightAxis.TabIndex = 0;
			this.pcbRightAxis.TabStop = false;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("Meiryo UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.label3.Location = new System.Drawing.Point(71, 9);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(62, 20);
			this.label3.TabIndex = 5;
			this.label3.Text = "スティック";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(95, 43);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(21, 17);
			this.label2.TabIndex = 5;
			this.label2.Text = "左";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(95, 276);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(21, 17);
			this.label1.TabIndex = 5;
			this.label1.Text = "右";
			// 
			// labWheelArg3
			// 
			this.labWheelArg3.AutoSize = true;
			this.labWheelArg3.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg3.Location = new System.Drawing.Point(759, 557);
			this.labWheelArg3.Name = "labWheelArg3";
			this.labWheelArg3.Size = new System.Drawing.Size(94, 47);
			this.labWheelArg3.TabIndex = 19;
			this.labWheelArg3.Text = "角度";
			// 
			// labWheelPwm3
			// 
			this.labWheelPwm3.AutoSize = true;
			this.labWheelPwm3.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm3.Location = new System.Drawing.Point(759, 604);
			this.labWheelPwm3.Name = "labWheelPwm3";
			this.labWheelPwm3.Size = new System.Drawing.Size(94, 47);
			this.labWheelPwm3.TabIndex = 18;
			this.labWheelPwm3.Text = "出力";
			// 
			// labWheelArg1
			// 
			this.labWheelArg1.AutoSize = true;
			this.labWheelArg1.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg1.Location = new System.Drawing.Point(120, 151);
			this.labWheelArg1.Name = "labWheelArg1";
			this.labWheelArg1.Size = new System.Drawing.Size(94, 47);
			this.labWheelArg1.TabIndex = 17;
			this.labWheelArg1.Text = "角度";
			// 
			// labWheelPwm1
			// 
			this.labWheelPwm1.AutoSize = true;
			this.labWheelPwm1.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm1.Location = new System.Drawing.Point(120, 198);
			this.labWheelPwm1.Name = "labWheelPwm1";
			this.labWheelPwm1.Size = new System.Drawing.Size(94, 47);
			this.labWheelPwm1.TabIndex = 16;
			this.labWheelPwm1.Text = "出力";
			// 
			// timer1
			// 
			this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
			// 
			// labWheelArg2
			// 
			this.labWheelArg2.AutoSize = true;
			this.labWheelArg2.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg2.Location = new System.Drawing.Point(120, 557);
			this.labWheelArg2.Name = "labWheelArg2";
			this.labWheelArg2.Size = new System.Drawing.Size(94, 47);
			this.labWheelArg2.TabIndex = 15;
			this.labWheelArg2.Text = "角度";
			// 
			// labWheelArg0
			// 
			this.labWheelArg0.AutoSize = true;
			this.labWheelArg0.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelArg0.Location = new System.Drawing.Point(759, 151);
			this.labWheelArg0.Name = "labWheelArg0";
			this.labWheelArg0.Size = new System.Drawing.Size(94, 47);
			this.labWheelArg0.TabIndex = 14;
			this.labWheelArg0.Text = "角度";
			// 
			// labWheelPwm0
			// 
			this.labWheelPwm0.AutoSize = true;
			this.labWheelPwm0.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm0.Location = new System.Drawing.Point(759, 198);
			this.labWheelPwm0.Name = "labWheelPwm0";
			this.labWheelPwm0.Size = new System.Drawing.Size(94, 47);
			this.labWheelPwm0.TabIndex = 20;
			this.labWheelPwm0.Text = "出力";
			// 
			// labWheelPwm2
			// 
			this.labWheelPwm2.AutoSize = true;
			this.labWheelPwm2.Font = new System.Drawing.Font("Meiryo UI", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
			this.labWheelPwm2.Location = new System.Drawing.Point(120, 604);
			this.labWheelPwm2.Name = "labWheelPwm2";
			this.labWheelPwm2.Size = new System.Drawing.Size(94, 47);
			this.labWheelPwm2.TabIndex = 13;
			this.labWheelPwm2.Text = "出力";
			// 
			// pcbVector3
			// 
			this.pcbVector3.BackColor = System.Drawing.Color.White;
			this.pcbVector3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbVector3.Location = new System.Drawing.Point(543, 441);
			this.pcbVector3.Name = "pcbVector3";
			this.pcbVector3.Size = new System.Drawing.Size(210, 210);
			this.pcbVector3.TabIndex = 11;
			this.pcbVector3.TabStop = false;
			// 
			// pcbVector1
			// 
			this.pcbVector1.BackColor = System.Drawing.Color.White;
			this.pcbVector1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbVector1.Location = new System.Drawing.Point(252, 151);
			this.pcbVector1.Name = "pcbVector1";
			this.pcbVector1.Size = new System.Drawing.Size(210, 210);
			this.pcbVector1.TabIndex = 10;
			this.pcbVector1.TabStop = false;
			// 
			// serialPort1
			// 
			this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
			// 
			// pcbVector0
			// 
			this.pcbVector0.BackColor = System.Drawing.Color.White;
			this.pcbVector0.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbVector0.Location = new System.Drawing.Point(543, 151);
			this.pcbVector0.Name = "pcbVector0";
			this.pcbVector0.Size = new System.Drawing.Size(210, 210);
			this.pcbVector0.TabIndex = 9;
			this.pcbVector0.TabStop = false;
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(143, 25);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(75, 27);
			this.button5.TabIndex = 7;
			this.button5.Text = "接続";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// pcbVector2
			// 
			this.pcbVector2.BackColor = System.Drawing.Color.White;
			this.pcbVector2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.pcbVector2.Location = new System.Drawing.Point(252, 441);
			this.pcbVector2.Name = "pcbVector2";
			this.pcbVector2.Size = new System.Drawing.Size(210, 210);
			this.pcbVector2.TabIndex = 12;
			this.pcbVector2.TabStop = false;
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(37, 27);
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(100, 24);
			this.textBox1.TabIndex = 8;
			this.textBox1.Text = "COM6";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 17F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.ControlLight;
			this.ClientSize = new System.Drawing.Size(1276, 800);
			this.Controls.Add(this.panel1);
			this.Controls.Add(this.labWheelArg3);
			this.Controls.Add(this.labWheelPwm3);
			this.Controls.Add(this.labWheelArg1);
			this.Controls.Add(this.labWheelPwm1);
			this.Controls.Add(this.labWheelArg2);
			this.Controls.Add(this.labWheelArg0);
			this.Controls.Add(this.labWheelPwm0);
			this.Controls.Add(this.labWheelPwm2);
			this.Controls.Add(this.pcbVector3);
			this.Controls.Add(this.pcbVector1);
			this.Controls.Add(this.pcbVector0);
			this.Controls.Add(this.button5);
			this.Controls.Add(this.pcbVector2);
			this.Controls.Add(this.textBox1);
			this.Font = new System.Drawing.Font("Meiryo UI", 9.75F);
			this.Margin = new System.Windows.Forms.Padding(4);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			((System.ComponentModel.ISupportInitialize)(this.pcbLeftAxis)).EndInit();
			this.panel1.ResumeLayout(false);
			this.panel2.ResumeLayout(false);
			this.panel2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.pcbRightAxis)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector3)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector1)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector0)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.pcbVector2)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.PictureBox pcbLeftAxis;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Panel panel2;
		private System.Windows.Forms.PictureBox pcbRightAxis;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label labWheelArg3;
		private System.Windows.Forms.Label labWheelPwm3;
		private System.Windows.Forms.Label labWheelArg1;
		private System.Windows.Forms.Label labWheelPwm1;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.Label labWheelArg2;
		private System.Windows.Forms.Label labWheelArg0;
		private System.Windows.Forms.Label labWheelPwm0;
		private System.Windows.Forms.Label labWheelPwm2;
		private System.Windows.Forms.PictureBox pcbVector3;
		private System.Windows.Forms.PictureBox pcbVector1;
		private System.IO.Ports.SerialPort serialPort1;
		private System.Windows.Forms.PictureBox pcbVector0;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.PictureBox pcbVector2;
		private System.Windows.Forms.TextBox textBox1;
	}
}

