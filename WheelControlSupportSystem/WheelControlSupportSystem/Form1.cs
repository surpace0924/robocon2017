using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WheelControlSupportSystem
{
	public partial class Form1 : Form
	{
		[System.Runtime.InteropServices.DllImport("kernel32.dll")] // この行を追加
		private static extern bool AllocConsole();                 // この行を追加  

		public Form1()
		{
			InitializeComponent();
			AllocConsole();                                        // この行を追加
			timer1.Interval = 50;

			// タイマーを開始
			timer1.Start();
		}
		
		private void Form1_Load(object sender, EventArgs e)
		{
		}

		private void drawEllipseByPoint(int x, int y, PictureBox p)
		{
			//描画先とするImageオブジェクトを作成する
			Bitmap canvas = new Bitmap(p.Width, p.Height);
			//ImageオブジェクトのGraphicsオブジェクトを作成する
			Graphics g = Graphics.FromImage(canvas);

			//先に描いた四角に内接する楕円を黒で描く
			g.FillEllipse(Brushes.Black, x - 5, (p.Height - y) - 5, 10, 10);

			//リソースを解放する
			g.Dispose();

			//PictureBox1に表示する
			p.Image = canvas;
		}


		private void drawLineByPoint(int sx, int sy, int gx, int gy, PictureBox p)
		{
			//描画先とするImageオブジェクトを作成する
			Bitmap canvas = new Bitmap(p.Width, p.Height);
			//ImageオブジェクトのGraphicsオブジェクトを作成する
			Graphics g = Graphics.FromImage(canvas);

			g.FillEllipse(Brushes.Black, sx - 5, (p.Height - sy) - 5, 10, 10);
			g.FillEllipse(Brushes.Black, gx - 5, (p.Height - gy) - 5, 10, 10);
			g.DrawLine(Pens.Black, sx, (p.Height - sy), gx, (p.Height - gy));

			//リソースを解放する
			g.Dispose();

			//PictureBox1に表示する
			p.Image = canvas;
		}
		

		int[] stickVal = { 0, 0, 0 };
		private void pcbLeftAxis_MouseClick(object sender, MouseEventArgs e)
		{
			stickVal[0] = (int)(2.25 * (e.X - 100));
			stickVal[1] = (int)(2.25 * (100 - e.Y));
			drawEllipseByPoint(e.X, 200 - e.Y, pcbLeftAxis);
			Console.WriteLine("(" + stickVal[0] + ", " + stickVal[1] + ", " + stickVal[2] + ")");
		}

		private void pcbRightAxis_MouseClick(object sender, MouseEventArgs e)
		{
			stickVal[2] = (int)(2.25 * (e.X - 100));
			drawEllipseByPoint(e.X, 200 - e.Y, pcbRightAxis);
			Console.WriteLine("(" + stickVal[0] + ", " + stickVal[1] + ", " + stickVal[2] + ")");
		}






		string receivedData = "";
		private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
		{
			// 受信文字列の取得
			try
			{
				receivedData = this.serialPort1.ReadLine();
			}
			catch (Exception ex)
			{
				receivedData = ex.Message;
			}

			// 受信文字列を追加させる
			// Console.WriteLine(receivedData);

			string[] data = convertReceivedDataToArray();

			//Console.WriteLine(data[0]);
			/*
			if (data[0] != "" && data[1] != "")
			{
				drawEllipseByPoint(int.Parse(data[0]), int.Parse(data[1]), pcbLeftAxis);
				//drawEllipseByPoint(int.Parse(data[2]), 200 - int.Parse(data[3]), pcbRightAxis);
			}
			*/
			// Console.WriteLine("(" + data[0] + ", " + data[1] + ", " + data[2] + ", " + data[3] + ")");
		}

		private void button5_Click(object sender, EventArgs e)
		{
			try
			{
				if (serialPort1.IsOpen)
				{
					Console.WriteLine(this.textBox1.Text + " はすでに開かれています。", "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
				}
				else
				{
					// ポート番号文字列=this.textBox1.Text, 115200bps/N81/ハードウェアフロー/UTF8/改行=CR
					this.serialPort1.PortName = this.textBox1.Text;
					this.serialPort1.BaudRate = 57600;
					this.serialPort1.Parity = System.IO.Ports.Parity.None;
					this.serialPort1.DataBits = 8;
					this.serialPort1.StopBits = System.IO.Ports.StopBits.One;
					this.serialPort1.Handshake = System.IO.Ports.Handshake.RequestToSend;
					this.serialPort1.Encoding = Encoding.UTF8;
					this.serialPort1.NewLine = "\n";
					serialPort1.Open();
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "エラー", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
		
		private string[] convertReceivedDataToArray(){
			string[] stArrayData = receivedData.Split(',');
			return stArrayData;
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			
			Console.WriteLine(receivedData);
			// Console.WriteLine(countKeywrod(receivedData, ','));

			string[] stArrayData;

			if(countKeywrod(receivedData, ',') == 10)
			{
				stArrayData = receivedData.Split(',');

				// スティックの位置を表示
				int stickX = 100+(int)(double.Parse(stArrayData[0])/2.25);
				int stickY = 100+(int)(double.Parse(stArrayData[1])/2.25);
				int stickS = 100+(int)(double.Parse(stArrayData[2])/2.25);
				drawEllipseByPoint(stickX, stickY, pcbLeftAxis);
				drawEllipseByPoint(stickS, 100, pcbRightAxis);

				PictureBox[] pcbVector = { pcbVector0, pcbVector1, pcbVector2, pcbVector3 };
				Label[] labWheelArg = { labWheelArg0, labWheelArg1, labWheelArg2, labWheelArg3 };
				Label[] labWheelPwm = { labWheelPwm0, labWheelPwm1, labWheelPwm2, labWheelPwm3 };


				for (int i = 3; i <= 10; i += 2)
				{
	
					int targetAngle = (int.Parse(stArrayData[i]) > 90) ? int.Parse(stArrayData[i]) - 180 : int.Parse(stArrayData[i]);

					int r;

					if (int.Parse(stArrayData[i]) > 90)
					{
						r = -1*(int)(double.Parse(stArrayData[i+1]) / 2.55);
					}
					else
					{
						r = (int)(double.Parse(stArrayData[i+1]) / 2.55);
					}

					int tmpAngle = targetAngle;
					if (i == 7 || i == 9)
					{
						tmpAngle += 180;
					}

					int x = 105 + (int)(r * Math.Cos(targetAngle * (Math.PI / 180)));
					int y = 105 + (int)(r * Math.Sin(targetAngle * (Math.PI / 180)));

					displayWheel(tmpAngle, 105, 105, x, y, pcbVector[(i - 3) / 2]);

					labWheelArg[(i - 3) / 2].Text = targetAngle.ToString();
					labWheelPwm[(i - 3) / 2].Text = r.ToString();
				}
			}

			receivedData = receivedData.Replace(this.serialPort1.NewLine, "\r\n");
		}

		private void displayWheel(int arg, int sx, int sy, int gx, int gy, PictureBox p)
		{
			arg = 360 - arg;
			//描画先とするImageオブジェクトを作成する
			Bitmap canvas = new Bitmap(p.Width, p.Height);
			//ImageオブジェクトのGraphicsオブジェクトを作成する
			Graphics g = Graphics.FromImage(canvas);

			//描画する画像のBitmapオブジェクトを作成
			Bitmap img = new Bitmap("Wheel.gif");

			//ラジアン単位に変換
			double d = arg / (180 / Math.PI);
			//新しい座標位置を計算する
			float x = 87F;
			float y = 130F;
			if (p == pcbVector2 || p == pcbVector3)
			{
				x = 130F;
				y = 87F;
			}
			float x1 = x + img.Width * (float)Math.Cos(d);
			float y1 = y + img.Width * (float)Math.Sin(d);
			float x2 = x - img.Height * (float)Math.Sin(d);
			float y2 = y + img.Height * (float)Math.Cos(d);
			//PointF配列を作成
			PointF[] destinationPoints = {new PointF(x, y),
					new PointF(x1, y1),
					new PointF(x2, y2)};
			//画像を表示
			g.DrawImage(img, destinationPoints);

			//PictureBox1に表示する
			p.Image = canvas;
			

			g.FillEllipse(Brushes.Black, sx - 5, (p.Height - sy) - 5, 10, 10);
			g.FillEllipse(Brushes.Black, gx - 5, (p.Height - gy) - 5, 10, 10);
			g.DrawLine(Pens.Black, sx, (p.Height - sy), gx, (p.Height - gy));


			//リソースを解放する
			g.Dispose();
			img.Dispose();

			//PictureBox1に表示する
			p.Image = canvas;
		}

		private static int countKeywrod(string str, char ch)
		{
       		return str.Length - str.Replace(ch.ToString(), "").Length;
		}

		private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
		{

		}

		private void pictureBox1_Click(object sender, EventArgs e)
		{

		}

		private void tabPage1_Click(object sender, EventArgs e)
		{

		}

		private void button3_Click(object sender, EventArgs e)
		{

		}

		private void txbFieldScale_TextChanged(object sender, EventArgs e)
		{

		}

		private void tabPage2_Click(object sender, EventArgs e)
		{

		}

		private void textBox1_TextChanged(object sender, EventArgs e)
		{

		}

		private void pcbRightAxis_Click(object sender, EventArgs e)
		{

		}

		private void pcbLeftAxis_Click(object sender, EventArgs e)
		{

		}

		private void pcbWheel2_Click(object sender, EventArgs e)
		{

		}

		private void pcbWheel0_Click(object sender, EventArgs e)
		{

		}

		private void button5_Click_1(object sender, EventArgs e)
		{

		}
	}
}


