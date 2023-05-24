//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//���������� ��� ���� �����
extern int n;
// ��������� ��� �������� �����
extern int Tox;
//������ ����������
extern float R;
//���������� ��� �������� ����������� ������������ �������������
extern int g;
//��������� ��� ������� ����������� �������
extern double min;
//���������� ��� ������ ������� ������������
extern double S;
int a = 2;
int z = 0;
// ����������� �������
const int nmax = 100;
//��������� ��� ������ ��������� �����
struct point {
	double x, y;
};
//��������� ��� ������ �����
struct otv
{
   point a,b,c;
};
//������ ��� ������ ��������� �����
point t[nmax];
//���������� ��� ������ �����
otv tr;
// ������� ��� ���������� � �������
inline double sq(double x)
 {
  return x*x;
 }
//---------------------------------------------------------------------------
// ������� ��� �������� ������� �� ����������� ����������
bool isSect(double x0, double y0, double x1, double y1, double r)
{
	double dx = x0 - x1, dy = y0 - y1;
	dx *= dx;
	dy *= dy;
	if (dx + dy == 0) return false;
	double det = (dx+dy)*sq(r) - sq(x1*y0 - x0*y1);


	if (det < 0) return false;
	double t1 = x0*(x0-x1) + y0*(y0-y1);
	double t2 = (t1 + sqrt(det))/(dx+dy);
	t1 = (t1 - sqrt(det))/(dx+dy);
	if (t1 >= 0 && t1 <= 1) return true;
	if (t2 >= 0 && t2 <= 1) return true;
	return false;
}
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
TColor OColor[5] =
{
		clBlue,
		clYellow,
		clRed,
		clGreen,
		clBlack
};
//---------------------------------------------------------------------------
//������ �������� �����
void __fastcall TForm4::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//������ ������ ����� �� ������������ ���������
void __fastcall TForm4::Button2Click(TObject *Sender)
{
  if (Edit1->Text != "" && Edit2->Text != "")
  {
	for(int i = z; i < n; i++)
	{
	  Form1->PaintBox1->Canvas->Pen->Color = clRed;
	  t[i].x = Form1->PaintBox1->Width - Form1->PaintBox1->Width/2 + StrToFloat(Edit1->Text)*10;
	  t[i].y = Form1->PaintBox1->Width - Form1->PaintBox1->Height/2 - StrToFloat(Edit2->Text)*10;
	  Form1->PaintBox1->Canvas->MoveTo(t[i].x , t[i].y);
	  Form1->PaintBox1->Canvas->Brush->Color = clRed;
	  Form1->PaintBox1->Canvas->Ellipse(t[i].x-4, t[i].y-4, t[i].x+4, t[i].y+4);
	}
    Label1->Caption = ("������� ���������� ����� �"+ IntToStr(a));
	a++;
	Tox++;
	z++;
  }
  else
  {
   ShowMessage("������� ���������� �����");
  }
  if (Tox == n)
  {
	 g = 0;
	 otv tr;
     //�������� ����������� �������� ������������ ����������
	 for (int i = 0; i < n -2; i++)
	 {
		tr.a = t[i];
		for (int j = i + 1; j < n - 1; j++)
		{
		tr.b = t[j];
			for (int k = j + 1; k < n; k++)
			{
				tr.c = t[k];
				if (isSect((tr.a.x - Form1->PaintBox1->Width/2)/10,(tr.a.y - Form1->PaintBox1->Width/2)/10,(tr.b.x - Form1->PaintBox1->Width/2)/10,(tr.b.y-Form1->PaintBox1->Width/2)/10,R) && (isSect((tr.a.x - Form1->PaintBox1->Width/2)/10,(tr.a.y - Form1->PaintBox1->Width/2)/10,(tr.c.x - Form1->PaintBox1->Width/2)/10,(tr.c.y - Form1->PaintBox1->Width/2)/10,R)) && (isSect((tr.b.x - Form1->PaintBox1->Width/2)/10,(tr.b.y - Form1->PaintBox1->Width/2)/10,(tr.c.x - Form1->PaintBox1->Width/2)/10,(tr.c.y - Form1->PaintBox1->Width/2)/10,R)))
				{
				  S = fabs(((t[j].x - Form1->PaintBox1->Width/2)/10-(t[i].x - Form1->PaintBox1->Width/2)/10)*((t[k].y - Form1->PaintBox1->Width/2)/10-(t[i].y - Form1->PaintBox1->Width/2)/10)-((t[k].x - Form1->PaintBox1->Width/2)/10-(t[i].x - Form1->PaintBox1->Width/2)/10)*((t[j].y - Form1->PaintBox1->Width/2)/10-(t[i].y - Form1->PaintBox1->Width/2)/10))/2;
				  if (S!=0)
				  {
					if (S < min)
					{
					   min = S;
					   Form1->Label6->Caption =  	("���������� ������ ����� " +  FloatToStr((t[i].x - Form1->PaintBox1->Width / 2) / 10) + ":" + 	FloatToStr((t[i].y -   Form1->PaintBox1->Width / 2) / 10) * (-1));
					   Form1->Label7->Caption = ("���������� ������ ����� " + FloatToStr((t[j].x - Form1->PaintBox1->Width / 2) / 10) + ":" +  FloatToStr((t[j].y - 	Form1->PaintBox1->Width / 2) / 10) * (-1));
					   Form1->Label8->Caption = ("���������� ������� ����� " + FloatToStr((t[k].x - Form1->PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[k].y - Form1->PaintBox1->Width / 2) / 10)*(-1));
					}
					int h = random(5);
					Form1->PaintBox1->Canvas->Pen->Color = OColor[h];
					Form1->PaintBox1->Canvas->MoveTo(t[i].x ,t[i].y);
					Form1->PaintBox1->Canvas->LineTo(t[j].x ,t[j].y);
					Form1->PaintBox1->Canvas->MoveTo(t[j].x ,t[j].y);
					Form1->PaintBox1->Canvas->LineTo(t[k].x ,t[k].y);
					Form1->PaintBox1->Canvas->MoveTo(t[k].x ,t[k].y);
					Form1->PaintBox1->Canvas->LineTo(t[i].x ,t[i].y);
					g++;
				  }
				}
			}
		}
	  }
	a = 1;
	z = 0;
	Form1->Label4->Caption = ("���� �������������: "+ IntToStr(g));
	if (g != 0){
		Form1->Label5->Caption = ("����������� ������� = "+FloatToStr(min) + " ��^2");
	}
	Close();
  }

}
//---------------------------------------------------------------------------
