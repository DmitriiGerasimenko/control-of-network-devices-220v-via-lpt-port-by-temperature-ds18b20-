object frmLptPortTesting: TfrmLptPortTesting
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Testing Lpt port'
  ClientHeight = 225
  ClientWidth = 276
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 97
    Height = 201
    Caption = 'Lpt pins'
    TabOrder = 0
  end
  object LptPinsCheckBox: TCheckListBox
    Left = 24
    Top = 32
    Width = 65
    Height = 161
    OnClickCheck = LptPinsCheckBoxClickCheck
    ItemHeight = 13
    Items.Strings = (
      'pin(1)'
      'pin(2)'
      'pin(3)'
      'pin(4)'
      'pin(5)'
      'pin(6)'
      'pin(7)'
      'pin(8)'
      'pin(9)'
      'pin(10)'
      'pin(11)'
      'pin(12)')
    TabOrder = 1
  end
  object ButtonClose: TButton
    Left = 143
    Top = 184
    Width = 97
    Height = 25
    Caption = 'Close'
    ModalResult = 1
    TabOrder = 2
  end
  object SetAllPinsBtn: TButton
    Left = 143
    Top = 111
    Width = 97
    Height = 25
    Caption = 'Set all pins'
    TabOrder = 3
    OnClick = SetAllPinsBtnClick
  end
  object ResetAllPins: TButton
    Left = 143
    Top = 142
    Width = 97
    Height = 25
    Caption = 'Reset all pins'
    TabOrder = 4
    OnClick = ResetAllPinsClick
  end
  object GroupBox2: TGroupBox
    Left = 111
    Top = 8
    Width = 154
    Height = 89
    Caption = 'Lpt adress'
    TabOrder = 5
    object Label1: TLabel
      Left = 16
      Top = 40
      Width = 51
      Height = 13
      Caption = 'Adress Lo:'
    end
    object Label2: TLabel
      Left = 16
      Top = 65
      Width = 49
      Height = 13
      Caption = 'Adress Hi:'
    end
    object AdressLo_SpinEdit: TSpinEdit
      Left = 80
      Top = 34
      Width = 57
      Height = 22
      MaxValue = 0
      MinValue = 0
      TabOrder = 0
      Value = 0
      OnChange = AdressLo_SpinEditChange
    end
    object AdressHi_SpinEdit: TSpinEdit
      Left = 80
      Top = 62
      Width = 57
      Height = 22
      MaxValue = 0
      MinValue = 0
      TabOrder = 1
      Value = 0
      OnChange = AdressHi_SpinEditChange
    end
  end
end
