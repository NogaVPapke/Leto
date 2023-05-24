// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
// ���������� ����������:
// ���������� ��� ������ ����������� �����
int n;
// ��������� ��� �������� �����
int Tox;
// ������ ����������
float R;
// ���������� ��� �������� ����������� ������������ �������������
int g;
// ��������� ������ ����������� �������
double min = 100000;
// ���������� ��� ������ �������
double S;
// ---------------------------------------------------------------------------
// ��������� ��� ������� ��������� �����
struct point
{
	double x, y;
};
// ��������� ��� ������ �����
struct otv {
	point a, b, c;
};
// ����������� �������
const int nmax = 100;
//������ ��� ������ ��������� �����
point t[nmax];
// ������� ��� ���������� � �������
inline double sq(double x)
{
	return x*x;
}
// ������� ��� �������� ������� �� ����������� ����������
bool isSect(double x0, double y0, double x1, double y1, double r)
{
	double dx = x0 - x1, dy = y0 - y1;
	dx *= dx;
	dy *= dy;
	if (dx + dy == 0)return false;
	double det = (dx + dy) * sq(r) - sq(x1 * y0 - x0 * y1);

	if (det < 0)return false;
	double t1 = x0 * (x0 - x1) + y0 * (y0 - y1);
	double t2 = (t1 + sqrt(det)) / (dx + dy);
	t1 = (t1 - sqrt(det)) / (dx + dy);
	if (t1 >= 0 && t1 <= 1)return true;
	if (t2 >= 0 && t2 <= 1)return true;
	return false;
}
// ���������� ��� ������ ��������� �� PaintBox1
float curX, curY;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {

}
TColor OColor[5] =
{
		clBlue,
		clYellow,
		clRed,
		clGreen,
		clBlack
};

// ---------------------------------------------------------------------------
// ��������� ���������� ��������� �����
void __fastcall TForm1::Button1Click(TObject *Sender) {
	srand(time(0));
    //���������� ��� ������ �����
	otv tr;
	g = 0;
	if (Edit1->Text != "" && Edit2->Text != "")
	{
		n = StrToInt(Edit1->Text);
		R = StrToFloat(Edit2->Text);

		if (n >= 0 && R > 0) {
			if ((n != 0 && n != 1 && n != 2) && R <= 30) {
				// ��������� �����
				for (int i = 0; i < n; i++) {
					PaintBox1->Canvas->Pen->Color = clRed;
					t[i].x = rand() % Form1->PaintBox1->Width;
					t[i].y = rand() % Form1->PaintBox1->Width;
					Form1->PaintBox1->Canvas->MoveTo(t[i].x, t[i].y);
					PaintBox1->Canvas->Brush->Color = clRed;
					PaintBox1->Canvas->Ellipse(t[i].x - 4, t[i].y - 4,t[i].x + 4, t[i].y + 4);
				}
				// �����
				PaintBox1->Canvas->Brush->Color = clWhite;
				PaintBox1->Canvas->Pen->Style = psDot;
				PaintBox1->Canvas->Pen->Color = clBlack;
				for (int i = 0; i < PaintBox1->Width; i += 50) {
					PaintBox1->Canvas->MoveTo(i, 0);
					PaintBox1->Canvas->LineTo(i, PaintBox1->Height);
				}
				for (int i = 0; i < PaintBox1->Height; i += 50) {
					PaintBox1->Canvas->MoveTo(0, i);
					PaintBox1->Canvas->LineTo(PaintBox1->Width, i);
				}
				Form1->PaintBox1->Canvas->Pen->Width = 2;
				// ���
				// X
				Form1->PaintBox1->Canvas->MoveTo(0,(Form1->PaintBox1->Height) / 2);
				Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width,(Form1->PaintBox1->Height) / 2);
				// Y
				Form1->PaintBox1->Canvas->MoveTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height));
				Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height) / (Form1->PaintBox1->Width / 2));
				Button1->Enabled = false;
				Button2->Enabled = false;
				// ����
				PaintBox1->Canvas->Pen->Color = clBlue;
				PaintBox1->Canvas->Brush->Color = clWhite;
				PaintBox1->Canvas->Brush->Style = bsClear;
				PaintBox1->Canvas->Ellipse((Form1->PaintBox1->Width / 2) - R*10,(Form1->PaintBox1->Height / 2) - R*10,(Form1->PaintBox1->Width / 2) + R*10,(Form1->PaintBox1->Height / 2) + R*10);
                //�������� ����������� �������� ������������ ����������
				for (int i = 0; i < n - 2; i++) {
					tr.a = t[i];
					for (int j = i + 1; j < n - 1; j++) {
						tr.b = t[j];
						for (int k = j + 1; k < n; k++) {

							tr.c = t[k];
							if (isSect((tr.a.x - PaintBox1->Width / 2) / 10,(tr.a.y - PaintBox1->Width / 2) / 10,(tr.b.x - PaintBox1->Width / 2) / 10,(tr.b.y - PaintBox1->Width / 2) / 10,R)
								&&(isSect((tr.a.x - PaintBox1->Width / 2)/ 10, (tr.a.y - PaintBox1->Width / 2) / 10,(tr.c.x - PaintBox1->Width / 2) / 10,(tr.c.y - PaintBox1->Width / 2) / 10, R))
								&&(isSect((tr.b.x - PaintBox1->Width / 2) / 10,(tr.b.y - PaintBox1->Width / 2) / 10,(tr.c.x - PaintBox1->Width / 2) / 10,(tr.c.y - PaintBox1->Width / 2) / 10, R)))
							{
							  S = fabs(((t[j].x - PaintBox1->Width / 2) / 10 - (t[i].x - PaintBox1->Width / 2) / 10) * ((t[k].y - PaintBox1->Width / 2) / 10 -(t[i].y - PaintBox1->Width / 2) / 10) -((t[k].x - PaintBox1->Width / 2) / 10 -(t[i].x - PaintBox1->Width / 2) / 10) *((t[j].y - PaintBox1->Width / 2) / 10 -(t[i].y - PaintBox1->Width / 2) / 10)) / 2;
							if (S != 0){
								if (S < min) {
									min = S;
										Label6->Caption = ("���������� ������ ����� " + FloatToStr((t[i].x - 	PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[i].y - PaintBox1->Width / 2) / 10) * (-1));
										Label7->Caption = ("���������� ������ ����� " + FloatToStr((t[j].x - PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[j].y - PaintBox1->Width / 2) / 10) * (-1));
										Label8->Caption = ("���������� ������� ����� " +FloatToStr((t[k].x -PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[k].y - PaintBox1->Width / 2) / 10) * (-1));
									}
									int h = random(5);
									Form1->PaintBox1->Canvas->Pen->Color = OColor[h];
									PaintBox1->Canvas->MoveTo(t[i].x, t[i].y);
									PaintBox1->Canvas->LineTo(t[j].x, t[j].y);
									PaintBox1->Canvas->MoveTo(t[j].x, t[j].y);
									PaintBox1->Canvas->LineTo(t[k].x, t[k].y);
									PaintBox1->Canvas->MoveTo(t[k].x, t[k].y);
									PaintBox1->Canvas->LineTo(t[i].x, t[i].y);
									g++;
								}
							}
						}
					}
				}
				Label4->Caption = ("���� �������������: " + IntToStr(g));
				if (g != 0) {
					Label5->Caption =
						("����������� ������� = " + FloatToStr(min) + " ��^2");
				}
			}
			else if ((n == 0 || n == 1 || n == 2) && R <= 30) {
				ShowMessage(
					"������������ ����� ��� ���������� ���� �� ������ ������������");
			}
			else if (n != 0 && n != 1 && n != 2 && R > 30) {
				ShowMessage("���� �������� ���������� �������");
			}
			else {
				ShowMessage(
					"1) ������������� ����� ��� ���������� ���� �� ������ ����������� \n2) ���� �������� ���������� �������");
			}
		}
		else
		{
			ShowMessage("��� �������� ������ ���� ��������������");
		}
	}
	else {
		ShowMessage("������� ���������� ����� � ������");
	}
}
// ---------------------------------------------------------------------------

// ������� ���������
void __fastcall TForm1::Button3Click(TObject *Sender) {
	PaintBox1->Repaint();
	Form1->PaintBox1->Canvas->Pen->Width = 1;
	Button1->Enabled = true;
	Button2->Enabled = true;
	Tox = 0;
	min = 100000;
	Edit1->Text = "";
	Edit2->Text = "";
	Label4->Caption = "";
	Label5->Caption = "";
	Label6->Caption = "";
	Label7->Caption = "";
	Label8->Caption = "";
}

// ---------------------------------------------------------------------------
// ������ � �������
void __fastcall TForm1::N1Click(TObject *Sender) {
	ShowMessage("�� ��������� ������ ��������� ����� � ���������� �������� R � ������� � ������ ���������. ��������� ��������� ���� ������������� � ��������� � �������� ������, ��� ��� ������� ������� ������������ � �����������, � ����� ����� ��� ����������� � ����������� ��������.");
}

// ---------------------------------------------------------------------------
// ������ ���� �����
void __fastcall TForm1::Button2Click(TObject *Sender) {
	if (Edit1->Text != "" && Edit2->Text != "") {
		n = StrToInt(Edit1->Text);
		R = StrToFloat(Edit2->Text);
	  if (n >= 0 && R > 0)
	  {
			if ((n != 0 && n != 1 && n != 2) && R <= 30)
			{
			// �����
			PaintBox1->Canvas->Brush->Color = clWhite;
			PaintBox1->Canvas->Pen->Style = psDot;
			PaintBox1->Canvas->Pen->Color = clBlack;
			for (int i = 0; i < PaintBox1->Width; i += 50) {
				PaintBox1->Canvas->MoveTo(i, 0);
				PaintBox1->Canvas->LineTo(i, PaintBox1->Height);
			}
			for (int i = 0; i < PaintBox1->Height; i += 50) {
				PaintBox1->Canvas->MoveTo(0, i);
				PaintBox1->Canvas->LineTo(PaintBox1->Width, i);
			}
			Form1->PaintBox1->Canvas->Pen->Width = 2;
			// ���
			// X
			Form1->PaintBox1->Canvas->MoveTo(0, (Form1->PaintBox1->Height) / 2);
			Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width,(Form1->PaintBox1->Height) / 2);
			// Y
			Form1->PaintBox1->Canvas->MoveTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height));
			Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height) / (Form1->PaintBox1->Width / 2));
			Button1->Enabled = false;
			Button2->Enabled = false;
			// ����
			PaintBox1->Canvas->Pen->Color = clBlue;
			PaintBox1->Canvas->Brush->Color = clWhite;
			PaintBox1->Canvas->Brush->Style = bsClear;
			PaintBox1->Canvas->Ellipse((Form1->PaintBox1->Width / 2) - R*10,(Form1->PaintBox1->Height / 2) - R*10,(Form1->PaintBox1->Width / 2) + R*10,(Form1->PaintBox1->Height / 2) + R*10);
			Form4->Label1->Caption = ("������� ���������� ����� �1");
			Form4->ShowModal();
			}
			else if ((n == 0 || n == 1 || n == 2) && R <= 30) {
				ShowMessage("������������ ����� ��� ���������� ���� �� ������ ������������");
			}
			else if (n != 0 && n != 1 && n != 2 && R > 30) {
				ShowMessage("���� �������� ���������� �������");
			}
			else {
				ShowMessage("1) ������������� ����� ��� ���������� ���� �� ������ ����������� \n2) ���� �������� ���������� �������");
			}
	  }
	  else
	  {
		 ShowMessage("��� �������� ������ ���� ��������������");
	  }
	}
	else
	{
		ShowMessage("������� ���������� ����� � ������");
	}
}

// ---------------------------------------------------------------------------
// ���������� ������������ �������
void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y) {
	curX = ((float)X - Form1->PaintBox1->Width / 2) / 10;
	curY = ((float)Y - Form1->PaintBox1->Height / 2) / 10 * (-1);

	Label3->Caption = FormatFloat("0.0", curX) + ":" + FormatFloat("0.0", curY);
}
// ---------------------------------------------------------------------------

// ������� � �������
void __fastcall TForm1::N2Click(TObject *Sender) {
	ShowMessage("1 ������ = 5 ��\n ������������ ������ ����� = 30 ��\n���������� ����� ��������� ����� �������");
}
////
// ---------------------------------------------------------------------------
