object fraAddPClipper: TfraAddPClipper
  Left = 0
  Top = 0
  Width = 443
  Height = 277
  Align = alClient
  TabOrder = 0
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 443
    Height = 49
    Align = alTop
    ParentColor = True
    TabOrder = 0
    object Label2: TLabel
      Left = 1
      Top = 1
      Width = 441
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = 'Portal clip plane:'
      Color = clBtnShadow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      OnClick = Label2Click
    end
    object SpeedButton19: TExtBtn
      Left = 102
      Top = 2
      Width = 11
      Height = 11
      Align = alNone
      CloseButton = False
      Glyph.Data = {
        DE000000424DDE00000000000000360000002800000007000000070000000100
        180000000000A8000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF00
        0000FFFFFFFFFFFF000000000000000000FFFFFFFFFFFF000000FFFFFF000000
        000000000000000000000000FFFFFF0000000000000000000000000000000000
        00000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        0000}
      OnClick = PanelMinClick
    end
    object Label4: TLabel
      Left = 3
      Top = 32
      Width = 28
      Height = 13
      Caption = 'Snap:'
    end
    object sbSnap: TExtBtn
      Left = 33
      Top = 31
      Width = 79
      Height = 15
      Align = alNone
      AllowAllUp = True
      BevelShow = False
      HotTrack = True
      CloseButton = False
      GroupIndex = 2
      Down = True
      Caption = 'Enable'
      Transparent = False
    end
    object cbFixed: TCheckBox
      Left = 1
      Top = 14
      Width = 111
      Height = 17
      Alignment = taLeftJustify
      Caption = 'Fixed plane'
      TabOrder = 0
      OnClick = cbFixedClick
    end
  end
  object paFixed: TPanel
    Left = 0
    Top = 49
    Width = 443
    Height = 56
    Align = alTop
    ParentColor = True
    TabOrder = 1
    Visible = False
    object Label6: TLabel
      Left = 1
      Top = 1
      Width = 441
      Height = 13
      Align = alTop
      Alignment = taCenter
      Caption = 'Fixed plane:'
      Color = clBtnShadow
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      OnClick = Label2Click
    end
    object ExtBtn1: TExtBtn
      Left = 102
      Top = 2
      Width = 11
      Height = 11
      Align = alNone
      CloseButton = False
      Glyph.Data = {
        DE000000424DDE00000000000000360000002800000007000000070000000100
        180000000000A8000000120B0000120B00000000000000000000FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF000000FFFFFFFFFFFFFFFFFF00
        0000FFFFFFFFFFFF000000000000000000FFFFFFFFFFFF000000FFFFFF000000
        000000000000000000000000FFFFFF0000000000000000000000000000000000
        00000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00
        0000}
      OnClick = PanelMinClick
    end
    object Label5: TLabel
      Left = 2
      Top = 17
      Width = 23
      Height = 13
      Caption = 'Size:'
    end
    object Label1: TLabel
      Left = 33
      Top = 18
      Width = 11
      Height = 13
      Caption = 'W'
    end
    object Label3: TLabel
      Left = 34
      Top = 36
      Width = 8
      Height = 13
      Caption = 'H'
    end
    object seSizeW: TMultiObjSpinEdit
      Left = 48
      Top = 16
      Width = 65
      Height = 18
      Increment = 0.5
      MaxValue = 1000
      ValueType = vtFloat
      Value = 10
      AutoSize = False
      TabOrder = 0
    end
    object seSizeH: TMultiObjSpinEdit
      Left = 48
      Top = 34
      Width = 65
      Height = 18
      Increment = 0.5
      MaxValue = 1000
      ValueType = vtFloat
      Value = 10
      AutoSize = False
      TabOrder = 1
    end
  end
end
