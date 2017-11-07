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


		double fieldScale;

		private void Form1_Load(object sender, EventArgs e)
		{
			fieldScale = double.Parse(txbFieldScale.Text);

			Console.WriteLine("縮尺:" + txbFieldScale.Text + "mm/px");
		}

		int map(int x, int in_min, int in_max, int out_min, int out_max)
		{
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}

		int[] startCoordinate = { 0, 0 };

		int[,] velocityVector = { { 0, 0 }, { 0, 0 } };
		int[,] startVector = { { 0, 0 }, { 0, 0 } };
		int[,] routeVector = { { 0, 0 }, { 0, 0 } };
		int[,] endVector = { { 0, 0 }, { 0, 0 } };

		bool isStart = true;

		private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
		{
			int xAxis = e.X;
			int yAxis = pictureBox1.Height - e.Y;

			// 点の描画
			drawEllipseByPoint(xAxis, yAxis, pictureBox1);

			if (isStart)
			{
				// 始点の座標が入力されていない
				// 始点の座標を入力
				startCoordinate[0] = xAxis;
				startCoordinate[1] = yAxis;


				velocityVector[0, 0] = xAxis;
				velocityVector[0, 1] = yAxis;

				isStart = false;
			}
			else
			{
				double arg = Math.Atan2((yAxis - startCoordinate[1]), (xAxis - startCoordinate[0]));
				double radius = (Math.Sqrt(Math.Pow((yAxis - startCoordinate[1]), 2) + Math.Pow((xAxis - startCoordinate[0]), 2)));


				int[] drawingCoordinate = { (int)(((1000.0 / fieldScale) / radius) * (xAxis - startCoordinate[0]) + startCoordinate[0]), (int)(((1000.0 / fieldScale) / radius) * (yAxis - startCoordinate[1]) + startCoordinate[1]) };


				Console.WriteLine("始点: (" + startCoordinate[0] * fieldScale + ", " + startCoordinate[1] * fieldScale + ")");
				Console.WriteLine("終点: (" + drawingCoordinate[0] * fieldScale + ", " + drawingCoordinate[1] * fieldScale + ")");
				Console.WriteLine("長さ: " + radius * fieldScale);
				Console.WriteLine("角度: " + arg);
				Console.WriteLine();

				// 図形の描画
				drawEllipseByPoint(xAxis, yAxis, pictureBox1);
				drawLineByPoint(startCoordinate[0], startCoordinate[1], drawingCoordinate[0], drawingCoordinate[1], pictureBox1);


				velocityVector[1, 0] = drawingCoordinate[0];
				velocityVector[1, 1] = drawingCoordinate[1];

				isStart = true;
			}

		}

		private void button1_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					startVector[i, j] = velocityVector[i, j];
				}
			}
			Console.WriteLine("始点:   {(" + velocityVector[0, 0] * fieldScale + ", " + (velocityVector[0, 1]) * fieldScale + "), (" + velocityVector[1, 0] * fieldScale + ", " + (velocityVector[1, 1]) * fieldScale + ")}");
		}

		private void button4_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					endVector[i, j] = velocityVector[i, j];
				}
			}
			Console.WriteLine("終点:   {(" + velocityVector[0, 0] * fieldScale + ", " + (velocityVector[0, 1]) * fieldScale + "), (" + velocityVector[1, 0] * fieldScale + ", " + (velocityVector[1, 1]) * fieldScale + ")}");
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


		private void btnCal_Click(object sender, EventArgs e)
		{

			//描画先とするImageオブジェクトを作成する
			Bitmap canvas = new Bitmap(pictureBox1.Width, pictureBox1.Height);
			//ImageオブジェクトのGraphicsオブジェクトを作成する
			Graphics g = Graphics.FromImage(canvas);

			//ベジエ曲線の形状を決定する4つの点
			Point point1 = new Point(startVector[0, 0], pictureBox1.Height - startVector[0, 1]);
			Point point2 = new Point(startVector[1, 0], pictureBox1.Height - startVector[1, 1]);
			Point point3 = new Point(routeVector[0, 0], pictureBox1.Height - routeVector[0, 1]);
			Point point4 = new Point(routeVector[1, 0], pictureBox1.Height - routeVector[1, 1]);
			Point point5 = new Point(endVector[0, 0], pictureBox1.Height - endVector[0, 1]);
			Point point6 = new Point(endVector[1, 0], pictureBox1.Height - endVector[1, 1]);

			Point[] curvePoints = { point1, point2, point3, point4, point5, point6 };

			//幅3の青色のPenオブジェクトを作成
			Pen bluePen = new Pen(Color.Blue, 3);
			//テンション0.5（既定値）のカーディナルスプラインを描画
			g.DrawCurve(bluePen, curvePoints, 0.5F);

			//幅3の赤色のPenオブジェクトを作成
			Pen redPen = new Pen(Color.Red, 3);
			//テンション1のカーディナルスプラインを描画
			g.DrawCurve(redPen, curvePoints, 1);

			//幅3の緑色のPenオブジェクトを作成
			Pen greenPen = new Pen(Color.Green, 3);
			//テンション0のカーディナルスプライン（直線となる）を描画
			g.DrawCurve(greenPen, curvePoints, 0);

			//幅1の黄色のPenオブジェクトを作成
			Pen yellowPen = new Pen(Color.Yellow, 1);
			//2番目の点から5番目の点までを通過するカーディナルスプラインを描画
			g.DrawCurve(yellowPen, curvePoints, 1, 3, 0.5F);

			//幅1の黒色のPenオブジェクトを作成
			Pen blackPen = new Pen(Color.Black, 1);
			//テンション1の閉じたカーディナルスプラインを描画
			g.DrawClosedCurve(blackPen, curvePoints, 1, FillMode.Alternate);

			//リソースを解放する
			bluePen.Dispose();
			redPen.Dispose();
			greenPen.Dispose();
			yellowPen.Dispose();
			blackPen.Dispose();
			g.Dispose();

			//PictureBox1に表示する
			pictureBox1.Image = canvas;
		}

		private void button2_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					routeVector[i, j] = velocityVector[i, j];
				}

				Console.WriteLine("中間点: {(" + velocityVector[0, 0] * fieldScale + ", " + (velocityVector[0, 1]) * fieldScale + "), (" + velocityVector[1, 0] * fieldScale + ", " + (velocityVector[1, 1]) * fieldScale + ")}");
			}
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
					this.serialPort1.NewLine = "\r";
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
				
				int x;
				int y;
				int r;




				if (int.Parse(stArrayData[4]) > 0)
				{
					r = (int)(double.Parse(stArrayData[4]) / 2.55);
				}
				else
				{
					r = -1 * (int)(double.Parse(stArrayData[4]) / 2.55);
				}
				r = (int)(double.Parse(stArrayData[4]) / 2.55);
				x = 105 + (int)(r * Math.Cos(int.Parse(stArrayData[3]) * (Math.PI / 180)));
				y = 105 + (int)(r * Math.Sin(int.Parse(stArrayData[3]) * (Math.PI / 180)));
				drawLineByPoint(105, 105, x, y, pcbWheel0);
				labWheelArg0.Text = stArrayData[3];
				labWheelPwm0.Text = stArrayData[4];


				if (int.Parse(stArrayData[6]) > 0)
				{
					r = (int)(double.Parse(stArrayData[6]) / 2.55);
				}
				else
				{
					r = -1 * (int)(double.Parse(stArrayData[6]) / 2.55);
				}
				r = (int)(double.Parse(stArrayData[6]) / 2.55);
				x = 105 + (int)(r * Math.Cos(int.Parse(stArrayData[5]) * (Math.PI / 180)));
				y = 105 + (int)(r * Math.Sin(int.Parse(stArrayData[5]) * (Math.PI / 180)));
				drawLineByPoint(105, 105, x, y, pcbWheel1);
				labWheelArg1.Text = stArrayData[5];
				labWheelPwm1.Text = stArrayData[6];


				if (int.Parse(stArrayData[8]) > 0)
				{
					r = (int)(double.Parse(stArrayData[8]) / 2.55);
				}
				else
				{
					r = -1 * (int)(double.Parse(stArrayData[8]) / 2.55);
				}
				r = (int)(double.Parse(stArrayData[8]) / 2.55);
				x = 105 + (int)(r * Math.Cos(int.Parse(stArrayData[7]) * (Math.PI / 180)));
				y = 105 + (int)(r * Math.Sin(int.Parse(stArrayData[7]) * (Math.PI / 180)));
				drawLineByPoint(105,105,x,y, pcbWheel2);
				labWheelArg2.Text = stArrayData[7];
				labWheelPwm2.Text = stArrayData[8];


				if (int.Parse(stArrayData[10]) > 0)	
				{
					r = (int)(double.Parse(stArrayData[8]) / 2.55);
				}
				else
				{
					r = -1 * (int)(double.Parse(stArrayData[8]) / 2.55);
				}
				r = (int)(double.Parse(stArrayData[10]) / 2.55);
				x = 105 + (int)(r * Math.Cos(int.Parse(stArrayData[9]) * (Math.PI / 180)));
				y = 105 + (int)(r * Math.Sin(int.Parse(stArrayData[9]) * (Math.PI / 180)));
				drawLineByPoint(105,105,x,y, pcbWheel3);
				labWheelArg3.Text = stArrayData[9];
				labWheelPwm3.Text = stArrayData[10];
			}

			receivedData = receivedData.Replace(this.serialPort1.NewLine, "\r\n");
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

	}
}


