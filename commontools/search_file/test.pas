
TTestForm = class(TForm)
	WVComboBox1 : TWVComboBox;
	WVComboBox2 : TWVComboBox;
	WVComboBox3 : TWVComboBox;
	procedure Init; override;
end;

procedure TTestForm.Init;
begin
	{
	FreeIDObjects(-41);
	
	WVComboBox1.ItemsDataEntry := '';
	WVComboBox1.ItemsDataEntry := '*-23';
	}
	showmessage('ok');
end;