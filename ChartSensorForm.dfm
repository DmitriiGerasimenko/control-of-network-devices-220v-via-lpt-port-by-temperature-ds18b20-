object frmChartSensor: TfrmChartSensor
  Left = 0
  Top = 0
  Caption = 'frmChartSensor'
  ClientHeight = 286
  ClientWidth = 426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 426
    Height = 286
    Legend.Alignment = laTop
    Legend.LegendStyle = lsValues
    Legend.Visible = False
    Title.Text.Strings = (
      'TChart')
    BottomAxis.LabelsAngle = 90
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 100.000000000000000000
    View3D = False
    Align = alClient
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TFastLineSeries
      Legend.Visible = False
      ShowInLegend = False
      LinePen.Color = 10708548
      LinePen.Style = psDot
      LinePen.Width = 3
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
end
