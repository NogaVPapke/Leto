// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
// Глобальные переменные:
// Переменная для записи колличества точек
int n;
// Перменная для закрытия формы
int Tox;
// Радиус окружности
float R;
// Переменная для подсчета колличества получившихся треугольников
int g;
// Переменая поиска минимальной площади
double min = 100000;
// Переменная для записи площади
double S;
// ---------------------------------------------------------------------------
// Структура для записии координат точек
struct point
{
	double x, y;
};
// Структура для записи точек
struct otv {
	point a, b, c;
};
// Размерность массива
const int nmax = 100;
//Массив для записи координат точек
point t[nmax];
// Функция для возведения в квадрат
inline double sq(double x)
{
	return x*x;
}
// Функция для проверки стороны на пересечения окружности
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
// Переменные для записи координат на PaintBox1
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
// Рандомное заполнение координат точек
void __fastcall TForm1::Button1Click(TObject *Sender) {
	srand(time(0));
    //Переменная для записи точек
	otv tr;
	g = 0;
	if (Edit1->Text != "" && Edit2->Text != "")
	{
		n = StrToInt(Edit1->Text);
		R = StrToFloat(Edit2->Text);

		if (n >= 0 && R > 0) {
			if ((n != 0 && n != 1 && n != 2) && R <= 30) {
				// росование точек
				for (int i = 0; i < n; i++) {
					PaintBox1->Canvas->Pen->Color = clRed;
					t[i].x = rand() % Form1->PaintBox1->Width;
					t[i].y = rand() % Form1->PaintBox1->Width;
					Form1->PaintBox1->Canvas->MoveTo(t[i].x, t[i].y);
					PaintBox1->Canvas->Brush->Color = clRed;
					PaintBox1->Canvas->Ellipse(t[i].x - 4, t[i].y - 4,t[i].x + 4, t[i].y + 4);
				}
				// Сетка
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
				// Оси
				// X
				Form1->PaintBox1->Canvas->MoveTo(0,(Form1->PaintBox1->Height) / 2);
				Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width,(Form1->PaintBox1->Height) / 2);
				// Y
				Form1->PaintBox1->Canvas->MoveTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height));
				Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height) / (Form1->PaintBox1->Width / 2));
				Button1->Enabled = false;
				Button2->Enabled = false;
				// Круг
				PaintBox1->Canvas->Pen->Color = clBlue;
				PaintBox1->Canvas->Brush->Color = clWhite;
				PaintBox1->Canvas->Brush->Style = bsClear;
				PaintBox1->Canvas->Ellipse((Form1->PaintBox1->Width / 2) - R*10,(Form1->PaintBox1->Height / 2) - R*10,(Form1->PaintBox1->Width / 2) + R*10,(Form1->PaintBox1->Height / 2) + R*10);
                //Проверка пересечения стороной треугольника окружности
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
										Label6->Caption = ("Координаты первой точки " + FloatToStr((t[i].x - 	PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[i].y - PaintBox1->Width / 2) / 10) * (-1));
										Label7->Caption = ("Координаты второй точки " + FloatToStr((t[j].x - PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[j].y - PaintBox1->Width / 2) / 10) * (-1));
										Label8->Caption = ("Координаты третьей точки " +FloatToStr((t[k].x -PaintBox1->Width / 2) / 10) + ":" + FloatToStr((t[k].y - PaintBox1->Width / 2) / 10) * (-1));
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
				Label4->Caption = ("Колл треугольников: " + IntToStr(g));
				if (g != 0) {
					Label5->Caption =
						("Минимальная площадь = " + FloatToStr(min) + " см^2");
				}
			}
			else if ((n == 0 || n == 1 || n == 2) && R <= 30) {
				ShowMessage(
					"Недостаточно точек для построения хотя бы одного треугольника");
			}
			else if (n != 0 && n != 1 && n != 2 && R > 30) {
				ShowMessage("Круг превысил допустимые размеры");
			}
			else {
				ShowMessage(
					"1) Недостаточное точек для построения хотя бы одного треуголника \n2) Круг превысил допустимые размеры");
			}
		}
		else
		{
			ShowMessage("Все значения должны быть положительными");
		}
	}
	else {
		ShowMessage("Введите количество точек и радиус");
	}
}
// ---------------------------------------------------------------------------

// Очистка плоскости
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
// Данные о задании
void __fastcall TForm1::N1Click(TObject *Sender) {
	ShowMessage("На плоскости заданы множество точек и окружность радиусом R с центром в начале координат. Построить множество всех треугольников с вершинами в заданных точках, все три стороны которых пересекаются с окружностью, и найти среди них треугольник с минимальной площадью.");
}

// ---------------------------------------------------------------------------
// Ручной ввод точек
void __fastcall TForm1::Button2Click(TObject *Sender) {
	if (Edit1->Text != "" && Edit2->Text != "") {
		n = StrToInt(Edit1->Text);
		R = StrToFloat(Edit2->Text);
	  if (n >= 0 && R > 0)
	  {
			if ((n != 0 && n != 1 && n != 2) && R <= 30)
			{
			// Сетка
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
			// Оси
			// X
			Form1->PaintBox1->Canvas->MoveTo(0, (Form1->PaintBox1->Height) / 2);
			Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width,(Form1->PaintBox1->Height) / 2);
			// Y
			Form1->PaintBox1->Canvas->MoveTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height));
			Form1->PaintBox1->Canvas->LineTo(Form1->PaintBox1->Width / 2,(Form1->PaintBox1->Height) / (Form1->PaintBox1->Width / 2));
			Button1->Enabled = false;
			Button2->Enabled = false;
			// Круг
			PaintBox1->Canvas->Pen->Color = clBlue;
			PaintBox1->Canvas->Brush->Color = clWhite;
			PaintBox1->Canvas->Brush->Style = bsClear;
			PaintBox1->Canvas->Ellipse((Form1->PaintBox1->Width / 2) - R*10,(Form1->PaintBox1->Height / 2) - R*10,(Form1->PaintBox1->Width / 2) + R*10,(Form1->PaintBox1->Height / 2) + R*10);
			Form4->Label1->Caption = ("Введите координаты точки №1");
			Form4->ShowModal();
			}
			else if ((n == 0 || n == 1 || n == 2) && R <= 30) {
				ShowMessage("Недостаточно точек для построения хотя бы одного треугольника");
			}
			else if (n != 0 && n != 1 && n != 2 && R > 30) {
				ShowMessage("Круг превысил допустимые размеры");
			}
			else {
				ShowMessage("1) Недостаточное точек для построения хотя бы одного треуголника \n2) Круг превысил допустимые размеры");
			}
	  }
	  else
	  {
		 ShowMessage("Все значения должны быть положительными");
	  }
	}
	else
	{
		ShowMessage("Введите количество точек и радиус");
	}
}

// ---------------------------------------------------------------------------
// Координаты расположения курсора
void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y) {
	curX = ((float)X - Form1->PaintBox1->Width / 2) / 10;
	curY = ((float)Y - Form1->PaintBox1->Height / 2) / 10 * (-1);

	Label3->Caption = FormatFloat("0.0", curX) + ":" + FormatFloat("0.0", curY);
}
// ---------------------------------------------------------------------------

// Справка о задании
void __fastcall TForm1::N2Click(TObject *Sender) {
	ShowMessage("1 Клетка = 5 см\n Максимальный радиус круга = 30 см\nДесятичные дроби записывть через запятую");
}
////
// ---------------------------------------------------------------------------
