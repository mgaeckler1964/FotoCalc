object FotorechnerForm: TFotorechnerForm
  Left = 725
  Top = 248
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Fotorechner'
  ClientHeight = 239
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  PixelsPerInch = 96
  TextHeight = 13
  object LabelDistanz: TLabel
    Left = 232
    Top = 24
    Width = 69
    Height = 13
    Caption = 'Entfernung [m]'
  end
  object Label2: TLabel
    Left = 232
    Top = 56
    Width = 78
    Height = 13
    Caption = 'Brennweite [mm]'
  end
  object LabelFaktor: TLabel
    Left = 232
    Top = 88
    Width = 64
    Height = 13
    Caption = 'Vergrößerung'
  end
  object Label4: TLabel
    Left = 8
    Top = 24
    Width = 83
    Height = 13
    Caption = 'Objektgröße [mm]'
  end
  object Label5: TLabel
    Left = 8
    Top = 56
    Width = 69
    Height = 13
    Caption = 'Bildgröße [mm]'
  end
  object Label6: TLabel
    Left = 8
    Top = 184
    Width = 463
    Height = 13
    Caption = 
      'KB: 24mm * 36mm,   APS: 15,8mm * 23,6mm,   1/1,7": 5,7mm * 7,6mm' +
      ',   1/1,8": 5,32mm * 7,18mm'
  end
  object Label7: TLabel
    Left = 8
    Top = 88
    Width = 47
    Height = 13
    Caption = 'Bildwinkel'
  end
  object Label1: TLabel
    Left = 8
    Top = 120
    Width = 64
    Height = 13
    Caption = 'Hyp. Entf. [m]'
  end
  object Label3: TLabel
    Left = 232
    Top = 120
    Width = 33
    Height = 13
    Caption = 'Blende'
  end
  object Label8: TLabel
    Left = 8
    Top = 152
    Width = 59
    Height = 13
    Caption = 'Min Entf. [m]'
  end
  object Label9: TLabel
    Left = 232
    Top = 152
    Width = 65
    Height = 13
    Caption = 'Max. Entf. [m]'
  end
  object EditDistanz: TEdit
    Left = 320
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 2
    OnChange = EditDistanzChange
  end
  object EditBrennweite: TEdit
    Left = 320
    Top = 56
    Width = 121
    Height = 21
    TabOrder = 3
    OnChange = EditBrennweiteChange
  end
  object EditVergrFaktor: TEdit
    Left = 320
    Top = 88
    Width = 121
    Height = 21
    TabOrder = 4
    OnChange = EditVergrFaktorChange
  end
  object ButtonRechneVergr: TButton
    Left = 448
    Top = 88
    Width = 75
    Height = 25
    Caption = 'Berechnen'
    TabOrder = 7
    OnClick = ButtonRechneVergrClick
  end
  object ButtonRechneDistanz: TButton
    Left = 448
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Berechnen'
    TabOrder = 6
    OnClick = ButtonRechneDistanzClick
  end
  object EditObjektGroesse: TEdit
    Left = 96
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 0
    OnChange = EditGroesseChange
  end
  object EditBildGroesse: TEdit
    Left = 96
    Top = 56
    Width = 121
    Height = 21
    PopupMenu = PopupMenu1
    TabOrder = 1
    OnChange = EditGroesseChange
  end
  object EditBildwinkel: TEdit
    Left = 96
    Top = 88
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 10
  end
  object ButtonNeustart: TButton
    Left = 448
    Top = 208
    Width = 75
    Height = 25
    Caption = 'Neustart'
    TabOrder = 9
    OnClick = ButtonNeustartClick
  end
  object ButtonLanguage: TButton
    Left = 8
    Top = 208
    Width = 75
    Height = 25
    Caption = 'English'
    TabOrder = 8
    OnClick = ButtonLanguageClick
  end
  object EditHyperfokaleDistanz: TEdit
    Left = 96
    Top = 120
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 11
  end
  object EditBlende: TEdit
    Left = 320
    Top = 120
    Width = 121
    Height = 21
    TabOrder = 5
    OnChange = EditBlendeChange
  end
  object EditMinDistanz: TEdit
    Left = 96
    Top = 152
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 12
  end
  object EditMaxDistanz: TEdit
    Left = 320
    Top = 152
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 13
  end
  object PopupMenu1: TPopupMenu
    Left = 392
    Top = 184
    object N1231: TMenuItem
      Caption = '1/2,3"'
      object Breite616mm: TMenuItem
        Caption = 'Breite (6,16mm)'
        OnClick = Breite616mmClick
      end
      object Hhe462mm: TMenuItem
        Caption = 'Höhe (4,62mm)'
        OnClick = Hhe462mmClick
      end
      object Diagonale77mm: TMenuItem
        Caption = 'Diagonale (7,7mm)'
        OnClick = Diagonale77mmClick
      end
    end
    object N1171: TMenuItem
      Caption = '1/1,8 "'
      object Breite718mm: TMenuItem
        Caption = 'Breite (7,18mm)'
        OnClick = Breite718mmClick
      end
      object Hhe532mm: TMenuItem
        Caption = 'Höhe (5,32mm)'
        OnClick = Hhe532mmClick
      end
      object Diagonale893mm: TMenuItem
        Caption = 'Diagonale (8,93mm)'
        OnClick = Diagonale893mmClick
      end
    end
    object N1172: TMenuItem
      Caption = '1/1,7 "'
      object Breite76mm: TMenuItem
        Caption = 'Breite (7,6mm)'
        OnClick = Breite76mmClick
      end
      object Hhe57mm: TMenuItem
        Caption = 'Höhe (5,7mm)'
        OnClick = Hhe57mmClick
      end
      object Diagonale95mm: TMenuItem
        Caption = 'Diagonale (9,5mm)'
        OnClick = Diagonale95mmClick
      end
    end
    object SamsungA551: TMenuItem
      Caption = 'Samsung A55'
      object Breite816mm1: TMenuItem
        Caption = 'Breite (8,16mm)'
        OnClick = Breite816mm1Click
      end
      object Hhe612mm1: TMenuItem
        Caption = 'Höhe (6,12mm)'
        OnClick = Hhe612mm1Click
      end
      object Diagonale1012mm1: TMenuItem
        Caption = 'Diagonale (10,12mm)'
        OnClick = Diagonale1012mm1Click
      end
    end
    object Nikon11: TMenuItem
      Caption = 'Nikon-1'
      object Breite132mm: TMenuItem
        Caption = 'Breite (13,2mm)'
        OnClick = Breite132mmClick
      end
      object Hhe88mm: TMenuItem
        Caption = 'Höhe (8,8mm)'
        OnClick = Hhe88mmClick
      end
      object Diagonale1586mm: TMenuItem
        Caption = 'Diagonale (15,86mm)'
        OnClick = Diagonale1586mmClick
      end
    end
    object MicroFourThirds1: TMenuItem
      Caption = '(Micro) Four Thirds'
      object Breite1731mm: TMenuItem
        Caption = 'Breite (17,31mm)'
        OnClick = Breite1731mmClick
      end
      object Hhe1298mm: TMenuItem
        Caption = 'Höhe (12,98mm)'
        OnClick = Hhe1298mmClick
      end
      object Diagonale2163mm: TMenuItem
        Caption = 'Diagonale (21,63mm)'
        OnClick = Diagonale2163mmClick
      end
    end
    object APSNikon1: TMenuItem
      Caption = 'APS (Nikon)'
      object Breite236mm: TMenuItem
        Caption = 'Breite (23,6mm)'
        OnClick = Breite236mmClick
      end
      object Hhe158mm: TMenuItem
        Caption = 'Höhe (15,8mm)'
        OnClick = Hhe158mmClick
      end
      object Diagonale284mm: TMenuItem
        Caption = 'Diagonale (28,4mm)'
        OnClick = Diagonale284mmClick
      end
    end
    object Kleinbild1: TMenuItem
      Caption = 'Kleinbild'
      object Breite36mm: TMenuItem
        Caption = 'Breite (36mm)'
        OnClick = Breite36mmClick
      end
      object Hhe24mm: TMenuItem
        Caption = 'Höhe (24mm)'
        OnClick = Hhe24mmClick
      end
      object Diagonale4327mm: TMenuItem
        Caption = 'Diagonale (43,27mm)'
        OnClick = Diagonale4327mmClick
      end
    end
  end
end
