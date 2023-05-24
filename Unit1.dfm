object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 613
  ClientWidth = 1060
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 264
    Top = 4
    Width = 601
    Height = 601
    OnMouseMove = PaintBox1MouseMove
  end
  object Label1: TLabel
    Left = 16
    Top = 95
    Width = 30
    Height = 13
    Caption = #1058#1086#1095#1082#1080
  end
  object Label2: TLabel
    Left = 16
    Top = 55
    Width = 32
    Height = 19
    Caption = 'R = '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 17
    Top = 352
    Width = 3
    Height = 13
  end
  object Label4: TLabel
    Left = 8
    Top = 371
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 403
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 8
    Top = 440
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 8
    Top = 462
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 8
    Top = 484
    Width = 4
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 16
    Top = 176
    Width = 169
    Height = 41
    Caption = #1040#1074#1090#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 64
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object Button2: TButton
    Left = 16
    Top = 232
    Width = 169
    Height = 41
    Caption = #1042#1088#1091#1095#1085#1091#1102
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 16
    Top = 288
    Width = 169
    Height = 41
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    TabOrder = 3
    OnClick = Button3Click
  end
  object Edit2: TEdit
    Left = 64
    Top = 57
    Width = 121
    Height = 21
    TabOrder = 4
  end
  object MainMenu1: TMainMenu
    Left = 160
    Top = 552
    object N1: TMenuItem
      Caption = #1047#1072#1076#1072#1085#1080#1077
      OnClick = N1Click
    end
    object N2: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      OnClick = N2Click
    end
  end
end
