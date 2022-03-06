object frmSearchSensors: TfrmSearchSensors
  Left = 0
  Top = 0
  Caption = 'frmSearchSensors'
  ClientHeight = 171
  ClientWidth = 241
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 16
    Top = 16
    Width = 97
    Height = 33
    Caption = 'Com ports :'
    TabOrder = 0
  end
  object Panel2: TPanel
    Left = 16
    Top = 63
    Width = 97
    Height = 34
    Caption = 'Sensors found :'
    TabOrder = 1
  end
  object SensorPanel: TPanel
    Left = 128
    Top = 63
    Width = 97
    Height = 33
    BevelOuter = bvLowered
    TabOrder = 2
  end
  object ComportsPanel: TPanel
    Left = 128
    Top = 16
    Width = 97
    Height = 33
    BevelOuter = bvLowered
    TabOrder = 3
  end
  object Button1: TButton
    Left = 80
    Top = 128
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 4
    OnClick = Button1Click
  end
end
