//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//Переменная для колл точек
extern int n;
// Перменная для закрытия формы
extern int Tox;
//Радиус окружности
extern float R;
//Переменная для подсчета колличества получившихся треугольников
extern int g;
//Пременная для записии минимальной площади
extern double min;
//Переменная для записи площади треугольника
extern double S;
int a = 2;
int z = 0;
// Размерность массива
const int nmax = 100;
//Структура для записи координат точек
struct point {
	double x, y;
};
//Структура для записи точек
struct otv
{
   point a,b,c;
};
//Массив для записи координат точек
point t[nmax];
//Переменная для записи точек
otv tr;
// Функция для возведения в квадрат
inline double sq(double x)
 {
  return x*x;
 }
//---------------------------------------------------------------------------
// Функция для проверки стороны на пересечения окружности
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
//Кнопка закрытия формы
void __fastcall TForm4::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//Кнопка записи точки на координатную плоскость
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
    Label1->Caption = ("Введите координаты точки №"+ IntToStr(a));
	a++;
	Tox++;
	z++;
  }
  else
  {
   ShowMessage("Введите координаты точки");
  }
  if (Tox == n)
  {
	 g = 0;
	 otv tr;
     //Проверка пересечения стороной треугольника окружности
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
					   Form1->Label6->Caption =  	("Координаты первой точки " +  FloatToStr((t[i].x - Form1->PaintBox1->Width / 2) / 10) + ":" + 	FloatToStr((t[i].y -   Form1->PaintBox1->Width / 2) / 10) * (-1));
					   Form1->Label7->Caption = ("Координаты второй точки " + FloatToStr((t[j].x - Form1->PaintBox1->Width / 2) / 10) + ":" +  FloatToStr((t[j].y - 	Form1->PaintBox1->Width / 2) / 10) * (-1));
					   Form1->Label8->Caption = ("Координаты третьей точки " + FloatToStr((t[k].x - Form1->PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[k].y - Form1->PaintBox1->Width / 2) / 10)*(-1));
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
	Form1->Label4->Caption = ("Колл треугольников: "+ IntToStr(g));
	if (g != 0){
		Form1->Label5->Caption = ("Минимальная площадь = "+FloatToStr(min) + " см^2");
	}
	Close();
  }

}
//---------------------------------------------------------------------------
