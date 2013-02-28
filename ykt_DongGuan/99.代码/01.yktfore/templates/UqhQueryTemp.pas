unit UqhQueryTemp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UQueryTemp, DBActns, ActnList, WorkViews, WVDBBinders, WVCmdReq, Db,
  DBCtrls, Grids, DBGrids, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  ComCtrls, KCDataAccess,WVCommands,SafeCode, WVCtrls, RzDBGrid, RzTabs,
  Buttons;

const
  S_ISQUERY = '��ѯ.';
  S_SeperatedStr = '-';

type
  TfaqhQueryTemp = class(TfaQueryTemp)
  private
    { Private declarations }
    procedure SynCustClass(CustClassComBoBox : TWVComboBox; ParentGB : TGroupBox);
    function CheckQuery(const SrcStr : string) : Boolean;
    function Related(ParentCtrl,ChildCtrl,ParentSub,ChildSub : string) : Boolean;
    function ContainName(Name,SubName : string) : Boolean;
    function GetStr(const Str : string) : string;
    procedure GBExit(Sender : TObject);
    procedure qhCusListPreQuery;
    procedure qhCusClassNamePreQuery;
    procedure qhKindsAndSeatInit;
    procedure btnCustClassConfirm(Sender : TObject);
    procedure btnCustClassCancel(Sender : TObject);
    procedure BindProperIdObjects(WorkComBox : TWVComboBox;
      SourceSL : TStrings; ChosenStr : string; IsQuery : Boolean);
//    procedure qhKindsSeatQuery(WorkField : TWVField);
  protected
    procedure Init; override;
    //����������ظ÷�����ʵ��WorkView����� ������ �ֶε� OnValueChange �¼��Ŀ��ơ�
    procedure qhExchPreQuery(WorkField : TWVField); virtual;
    //����������ظ÷�����ʵ�ֶԽ����� Combobox �ͻ��� �ؼ��� OnDropDown �¼��Ŀ��ơ�
    procedure VarGroupBoxCreate(Sender : TObject);  virtual;
  public
    { Public declarations }
  end;

implementation

uses KSFrameWorks,KSFrameWorkUtils, KSDataDictionary, KSClientConsts, DataTypes;

{$R *.DFM}

{ TfaqhQueryTemp }

procedure TfaqhQueryTemp.BindProperIdObjects(WorkComBox: TWVComboBox;
  SourceSL: TStrings; ChosenStr: string; IsQuery: Boolean);
var
//  IDObjectList : TIdObjectList;
  DataEntry : Integer;
//  tempValue : string;
begin
  if SourceSL = nil then Exit;
  try
    DataEntry := StrToInt(SourceSL.Values[ChosenStr]);
  except
    Exit;
  end;
  with WorkComBox do
  begin
    DataPresentType := '';
    ItemsDataEntry := '';
  end;
  if NeedIdObjectList(DataEntry) = nil then Exit;

  if IsQuery then
    with WorkComBox do
    begin
//      Style := csDropDownList;
      DataPresentType := 'IDOBJECTS';
      SeperatedStr := S_SeperatedStr;
      ItemsDataEntry := '*' + IntToStr(DataEntry);
      WorkView.FindField(WorkComBox.FieldName).Data.SetString('');
      ItemIndex := 0;
    end
  else with WorkComBox do
    begin
//      Style := csDropDownList;
      DataPresentType := 'IDOBJECTS';
      SeperatedStr := S_SeperatedStr;
      ItemsDataEntry := IntToStr(DataEntry);
      WorkView.FindField(WorkComBox.FieldName).DefaultValue := GetFirstItemID(DataEntry);
      WorkView.FindField(WorkComBox.FieldName).Reset;
    end;

end;

procedure TfaqhQueryTemp.btnCustClassCancel(Sender: TObject);
var
  TempWVComBox : TWVComboBox;
begin
  TempWVComBox := TWVComboBox(TButton(Sender).Tag);
  TempWVComBox.Owner.Tag := 1;
  TGroupBox(TButton(Sender).Parent).Visible := False;
  TempWVComBox.SetFocus;
end;

procedure TfaqhQueryTemp.btnCustClassConfirm(Sender: TObject);
var
  ComboxName : string;
  I : Integer;
  S0,S1,S2,S3,S4 : string;
  TempWVComBox,TempWVComBox1 : TWVComboBox;
begin
  //���б�������Ϻ�����ͻ����б�� cbCustClassConfirm
  S0 := '__';
  S1 := '__';
  S2 := '__';
  S3 := '__';
  S4 := '__';
  //�Ӹ�button�����tag���滹ԭ��Ҫ���Ŀͻ���Combox����
  TempWVComBox := TWVComboBox(TButton(Sender).Tag);
  Assert(TempWVComBox <> nil);
  ComboxName := TempWVComBox.Name;
  for I := 0 to Self.ComponentCount - 1 do
  begin
    if Self.Components[I] is TWVComboBox then
      if TWVComboBox(Self.Components[I]).Parent = TButton(Sender).Parent then
      begin
        TempWVComBox1 := Self.Components[I] as TWVComboBox;
        if TempWVComBox1.Name = ComboxName + 'SubClass0' then
        begin
          if (TempWVComBox1.Text <> S_SeperatedStr) and (TempWVComBox1.Text <> '') then
             S0 := Copy(TempWVComBox1.Text,1,2);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass1' then
        begin
          if (TempWVComBox1.Text <> S_SeperatedStr) and (TempWVComBox1.Text <> '') then
             S1 := Copy(TempWVComBox1.Text,1,2);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass2' then
        begin
          if (TempWVComBox1.Text <> S_SeperatedStr) and (TempWVComBox1.Text <> '') then
             S2 := Copy(TempWVComBox1.Text,1,2);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass3' then
        begin
          if (TempWVComBox1.Text <> S_SeperatedStr) and (TempWVComBox1.Text <> '') then
             S3 := Copy(TempWVComBox1.Text,1,2);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass4' then
        begin
          if (TempWVComBox1.Text <> S_SeperatedStr) and (TempWVComBox1.Text <> '') then
             S4 := Copy(TempWVComBox1.Text,1,2);
        end;
      end;
  end;
  {
  with TempWVComBox do
  begin
    DataPresentType := '';
    if Items.IndexOf(S0 + S1 + S2 + S3 + S4) = -1 then
      Items.Insert(0,S0 + S1 + S2 + S3 + S4);
    Style := csDropDownList;
    ItemIndex := 0;
  end;
  }

  TempWVComBox.Style := csDropDown;
  TempWVComBox.DataPresentType := '';
  if S0 + S1 + S2 + S3 + S4 = '__________' then
    TempWVComBox.Text := ''
  else
    TempWVComBox.Text := S0 + S1 + S2 + S3 + S4;
  WorkView.FieldByName(TempWVComBox.FieldName).Data.SetString(TempWVComBox.Text);
  TempWVComBox.Owner.Tag := 1;
  TGroupBox(TButton(Sender).Parent).Visible := False;
  TempWVComBox.SetFocus;
end;

function TfaqhQueryTemp.CheckQuery(const SrcStr: string): Boolean;
begin
  Result := False;
  if Pos(S_ISQUERY,SrcStr)=1 then Result := True;
end;

function TfaqhQueryTemp.ContainName(Name, SubName: string): Boolean;
var
  tempStr : string;
begin
  Result := False;
  if not Length(Name) >= Length(SubName) then Exit;
  tempStr := Copy(Name,Length(Name)-Length(SubName)+1,Length(SubName));
  if tempStr = SubName then Result := True;
end;

procedure TfaqhQueryTemp.GBExit(Sender: TObject);
begin
  if Sender is TGroupBox then
    (Sender as TGroupBox).Visible := False;
end;

function TfaqhQueryTemp.GetStr(const Str: string): string;
begin
  Result := StringReplace(Trim(Str),' ','',[rfReplaceAll]);
end;

procedure TfaqhQueryTemp.Init;
var
  I : Integer;
  tempName : String;
  flag2,flag3,flag4 : Boolean;
begin
  inherited;
  flag2 := True;
  flag3 := True;
  flag4 := True;
  for I := 0 to WorkView.FieldCount - 1 do
  begin
    with WorkView.Fields[I] do
    begin
//      if DataType = kdtObject then OwnObject := True;
      tempName := GetStr(Name);
      if ContainName(tempName,'������') then
      begin
        OnValueChanged := qhExchPreQuery;
      end
      {$IFNDEF KSTRADER}
      else if ContainName(tempName,'�ͻ���') and Flag2 = True  then
      begin
        qhCusListPreQuery;
        Flag2 := False;
      end
      {$ENDIF}
      else if ContainName(tempName,'�ͻ���') and Flag3 = True  then
      begin
        qhCusClassNamePreQuery;
        Flag3 := False;
      end
      else if (ContainName(tempName,'Ʒ��') or
        ContainName(tempName,'ϯλ')) and Flag4 = True then
      begin
        qhKindsAndSeatInit;
        Flag4 := False;
      end;
    end;
  end;
  for I := 0 to Self.ComponentCount - 1 do
    if Components[I] is TWVComboBox then
      with TWVComboBox(Components[I]) do
        if ItemsDataEntry<>'' then Style := csDropDown;
end;

//��̬���ɿͻ������ɴ��ڡ����в�ѯ�����һ����Ҫ��ʾ����Ŀ����
procedure TfaqhQueryTemp.qhCusClassNamePreQuery;
var
  I : Integer;
  TempWVComBox : TWVComboBox;
begin
  try
    for I := 0 to Self.ComponentCount - 1 do
    begin
      if (Self.Components[I] is TWVComboBox) then
      begin
        TempWVComBox := Self.Components[I] as TWVComboBox;
        if ContainName(GetStr(TempWVComBox.FieldName),'�ͻ���') then
        begin
          TempWVComBox.OnDropDown := VarGroupBoxCreate;
          TempWVComBox.MustBeChosen := False;
        end;
      end;
    end;
  except
    //���ο��ܳ��ֵĴ���
  end;
end;

procedure TfaqhQueryTemp.qhCusListPreQuery;
var
  I : Integer;
  TempWVComBox : TWVComboBox;
begin
  //���ݲ���Ա��ȡ�ͻ������б�
  for I := 0 to Self.ComponentCount - 1 do
  begin
    if (Self.Components[I] is TWVComboBox) then
    begin
      TempWVComBox := Self.Components[I] as TWVComboBox;
      if ContainName(GetStr(TempWVComBox.FieldName),'�ͻ���') then
        with TempWVComBox do
        begin
//          Style := csDropDownList;
          DataPresentType := 'IDOBJECTS';
          SeperatedStr := S_SeperatedStr;
          if CheckQuery(GetStr(TempWVComBox.FieldName)) then
            ItemsDataEntry := '*' + IntToStr(deOperator_CustNO)
          else ItemsDataEntry := IntToStr(deOperator_CustNO);
        end;
    end;
  end;
end;

procedure TfaqhQueryTemp.qhExchPreQuery(WorkField : TWVField);
var
  I : Integer;
  TempWVComBox,ParentWVComBox : TWVComboBox;
begin
  //�ҵ�Field��Ӧ�Ľ���ComBox��Ȼ���ڴ��еĺ��ʹ������������Items���档
  //Ϊ���ҳ���Ӧ��ϵ�����ҳ���TableSheet������Parentƥ���жϡ�
  ParentWVComBox := nil;
  for I := 0 to Self.ComponentCount - 1 do
  begin
    if (Self.Components[I] is TWVComboBox) then
    begin
      TempWVComBox := Self.Components[I] as TWVComboBox;
      if TempWVComBox.FieldName = WorkField.Name then
      begin
        ParentWVComBox := TempWVComBox;
        Break;
      end;
    end;
  end;
  if ParentWVComBox = nil then Exit;
  for I := 0 to Self.ComponentCount - 1 do
  begin

    if (Self.Components[I] is TWVComboBox) then
    begin
      TempWVComBox := Self.Components[I] as TWVComboBox;
      if not(Related(ParentWVComBox.FieldName,TempWVComBox.FieldName,'������','Ʒ��')
        or Related(ParentWVComBox.FieldName,TempWVComBox.FieldName,'������','ϯλ'))
         then Continue;
//      TempWVComBox.Tag := Integer(ParentWVComBox);
      if WorkField.Data.AsString = '' then
      begin
        qhKindsAndSeatInit;
        Exit;
      end;
      if ContainName(GetStr(TempWVComBox.FieldName),'Ʒ��') then
        BindProperIdObjects(TempWVComBox,
          FindStringListFormObjectList(UIShareObjList,SLName_Exchange_Kind),
            WorkField.Data.AsString,CheckQuery(GetStr(TempWVComBox.FieldName)))
      else if ContainName(GetStr(TempWVComBox.FieldName),'ϯλ') then
        BindProperIdObjects(TempWVComBox,
          FindStringListFormObjectList(UIShareObjList,SLName_Exchange_Seat),
            WorkField.Data.AsString,CheckQuery(GetStr(TempWVComBox.FieldName)));
  end;
  end;
end;

procedure TfaqhQueryTemp.qhKindsAndSeatInit;
var
  I : Integer;
  TempWVComBox : TWVComboBox;
begin
  for I := 0 to Self.ComponentCount - 1 do
  begin
    if (Self.Components[I] is TWVComboBox) then
    begin
      TempWVComBox := Self.Components[I] as TWVComboBox;
      if ContainName(GetStr(TempWVComBox.FieldName),'Ʒ��') then
      begin
        if CheckQuery(GetStr(TempWVComBox.FieldName)) then
        begin
          with TempWVComBox do
          begin
//            Style := csDropDownList;
            DataPresentType := 'IDOBJECTS';
            SeperatedStr := S_SeperatedStr;
            ItemsDataEntry := '*' + IntToStr(deExchangeKind);
            WorkView.FindField(FieldName).Data.SetString('');
            ItemIndex := 0;
          end;
        end
        else begin
          with TempWVComBox do
          begin
//            Style := csDropDownList;
            DataPresentType := 'IDOBJECTS';
            SeperatedStr := S_SeperatedStr;
            ItemsDataEntry := IntToStr(deExchangeKind);
            WorkView.FindField(FieldName).DefaultValue := GetFirstItemID(deExchangeKind);
            WorkView.FindField(FieldName).Reset;
          end
        end
      end
      else if ContainName(GetStr(TempWVComBox.FieldName),'ϯλ') then
      begin
        if CheckQuery(GetStr(TempWVComBox.FieldName)) then
        begin
          with TempWVComBox do
          begin
//            Style := csDropDownList;
            DataPresentType := 'IDOBJECTS';
            SeperatedStr := S_SeperatedStr;
            ItemsDataEntry := '*' + IntToStr(deExchangeSeat);
            WorkView.FindField(FieldName).Data.SetString('');
            ItemIndex := 0;
          end;
        end
        else begin
          with TempWVComBox do
          begin
//            Style := csDropDownList;
            DataPresentType := 'IDOBJECTS';
            SeperatedStr := S_SeperatedStr;
            ItemsDataEntry := IntToStr(deExchangeSeat);
            WorkView.FindField(FieldName).DefaultValue := GetFirstItemID(deExchangeSeat);
            WorkView.FindField(FieldName).Reset;
          end
        end
      end;
    end;
  end;
end;

function TfaqhQueryTemp.Related(ParentCtrl, ChildCtrl, ParentSub,
  ChildSub: string): Boolean;
begin
  Result := False;
  if ParentCtrl = StringReplace(ChildCtrl,ChildSub,ParentSub,[rfReplaceAll]) then
   Result := True;
end;

procedure TfaqhQueryTemp.SynCustClass( CustClassComBoBox : TWVComboBox;
  ParentGB: TGroupBox);
  procedure FindFixedItem(MatchStr : string; OperatoredObj : TWVComboBox);
  var
    X : Integer;
  begin
    if OperatoredObj.Items.Count > 1 then OperatoredObj.ItemIndex := 0;
    if MatchStr = '' then Exit;
    for X := 0 to OperatoredObj.Items.Count - 1 do
      if Pos(MatchStr,OperatoredObj.Items[X]) = 1 then OperatoredObj.ItemIndex := X;
  end;
var
  ComboxName : string;
  I : Integer;
  tempValue, S0,S1,S2,S3,S4 : string;
  TempWVComBox,TempWVComBox1 : TWVComboBox;
begin
  //���б�������Ϻ�����ͻ����б�� cbCustClassConfirm
  tempValue := '__________';
  tempValue := CustClassComBoBox.Text+ tempValue;
  S0 := Copy(tempValue,1,2);
  S1 := Copy(tempValue,3,2);
  S2 := Copy(tempValue,5,2);
  S3 := Copy(tempValue,7,2);
  S4 := Copy(tempValue,9,2);
  //�Ӹ�button�����tag���滹ԭ��Ҫ���Ŀͻ���Combox����
  TempWVComBox := CustClassComBoBox;
  Assert(TempWVComBox <> nil);
  ComboxName := TempWVComBox.Name;
  for I := 0 to Self.ComponentCount - 1 do
  begin
    if Self.Components[I] is TWVComboBox then
      if TWVComboBox(Self.Components[I]).Parent = ParentGB then
      begin
        TempWVComBox1 := Self.Components[I] as TWVComboBox;
        if TempWVComBox1.Name = ComboxName + 'SubClass0' then
        begin
          FindFixedItem(S0,TempWVComBox1);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass1' then
        begin
          FindFixedItem(S1,TempWVComBox1);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass2' then
        begin
          FindFixedItem(S2,TempWVComBox1);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass3' then
        begin
          FindFixedItem(S3,TempWVComBox1);
        end
        else if TempWVComBox1.Name = ComboxName + 'SubClass4' then
        begin
          FindFixedItem(S4,TempWVComBox1);
        end;
      end;
  end;
end;

procedure TfaqhQueryTemp.VarGroupBoxCreate(Sender: TObject);
var
  GroupBox : TGroupBox;
  I,J : Integer;
  TempWVComBox,FocusWVCombox : TWVComboBox;
  tempLeft,tempTop : Integer;
  SourceSL : TStringList;
  tempField : TWVField;

  procedure GetAbsolutePos(var Left,Top : Integer; CurrentCtrl,MetaParent : TWinControl);
  var
    ParentCtrl : TWinControl;
  begin
    Assert( CurrentCtrl <> nil);
    Left := CurrentCtrl.Left;
    Top := CurrentCtrl.Top + CurrentCtrl.Height;
    ParentCtrl := CurrentCtrl.Parent;

    while ParentCtrl <> MetaParent do
    begin
      Left := Left + ParentCtrl.Left;
      Top := Top + ParentCtrl.Top;
      ParentCtrl := ParentCtrl.Parent;
    end;

  end;
begin
  //
  TempWVComBox := Sender as TWVComboBox;
  //�����ظ�����GroupBox��
  if TempWVComBox.Tag = 1 then
  begin
    for I := 0 to Self.ComponentCount - 1 do
    begin
      if Self.Components[I] is TGroupBox then
        if TGroupBox(Self.Components[I]).Name = 'GB' + TempWVComBox.Name then
            with  (Self.Components[I] as TGroupBox) do
            begin
              SynCustClass(TempWVComBox,TGroupBox(Self.Components[I]));
              Visible := True;
              SetFocus;
              TWVComboBox(Tag).SetFocus;
            end;
    end;
    Exit;
  end;

  SourceSL := FindStringListFormObjectList(UIShareObjList,SLName_Cust_Class);
  if SourceSL = nil then Exit;
  if SourceSL.Values['CustClsCount'] = '' then Exit;

  TempWVComBox.Tag := 1;
  I := StrToInt(SourceSL.Values['CustClsCount']);
  GroupBox := TGroupBox.Create(Self);
  with GroupBox do
  begin
    Name := 'GB' + TempWVComBox.Name ;
    Caption := '�ͻ�������ѡ��';
    Parent := Self;
    GetAbsolutePos(tempLeft,tempTop,TempWVComBox,Self);
    Left := tempLeft;
    Top := tempTop;
    Height := I * 40 + 40;
    Width := 163;
    OnExit := GBExit;
    Visible := True;
    SetFocus;
  end;
  J := I;
  for J := 0 to J - 1 do
  begin
    with TLabel.Create(Self) do
    begin
      Parent := GroupBox;
      Left := 5;
      Top := 24 + J * 40;
      Width := 48;
      Height := 12;
      Caption := SourceSL.Values['CustCls' + IntToStr(J)];
      Visible := True;
    end;
    FocusWVCombox := TWVComboBox.Create(Self);
    with FocusWVCombox do
    begin
      Name := TempWVComBox.Name + 'SubClass' + IntToStr(J);
      WorkView := Self.WorkView;
      tempField := TWVField.Create(WorkView.WorkFields);
      tempField.Name := FocusWVCombox.Name + 'OwnedField';
      tempField.DataType := kdtString;
      FieldName := tempField.Name;

      Parent := GroupBox;
      Left := 58;
      Top := 20 + J * 40;
      Width := 100;
      Height := 20;
      //�ͻ����б���Ŀ���ֵ�
      case J of
        0 : ItemsDataEntry := '*1001';
        1 : ItemsDataEntry := '*1002';
        2 : ItemsDataEntry := '*1003';
        3 : ItemsDataEntry := '*1004';
        4 : ItemsDataEntry := '*1005';
      end;
//      Style := csDropDownList;
      Text := '';
      Visible := True;
    end;
    if J = 0 then
    begin
      FocusWVCombox.SetFocus;
      GroupBox.Tag := Integer(FocusWVCombox);
    end;
    //����workview ��field������֧�ֻس���tab��ת��

  end;
  with TImageButton.Create(Self) do
  begin
    Parent := GroupBox;
    Width := 45;
    Height := 25;
    Left := (GroupBox.ClientWidth - Width * 2 - 20) div 2 ;
    Top := 7 + I * 40;
    Caption := '&O ȷ��';
    Tag := Integer(TempWVComBox);
    OnClick := btnCustClassConfirm;
  end;

  with TImageButton.Create(Self) do
  begin
    Parent := GroupBox;
    Width := 45;
    Height := 25;
    Left := (GroupBox.ClientWidth - Width * 2 - 20) div 2  + Width + 20;
    Top := 7 + I * 40;
    Caption := '&C ȡ��';
    Tag := Integer(TempWVComBox);
    OnClick := btnCustClassCancel;
  end;
end;

end.
