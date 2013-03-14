unit MessageListeners;

interface

uses
  windows, messages, classes;

type
  IMessageListener = Interface
    function SendSelfMessage(Sender : TObject; Message : TMessage) : LRESULT; stdcall;
    function PostSelfMessage(Sender : TObject; Message : TMessage) : BOOL; stdcall;
  end;

type
  TMessageListenerSurport = class(TObject)
  private
    FSender: TObject;
    FList : TInterfaceList;
  public
    constructor Create(ASender : TObject);
    Destructor  Destroy;override;

    procedure   AddListener(Listener : IMessageListener);
    procedure   RemoveListener(Listener : IMessageListener);
    function    Count : Integer;
    procedure   SendListenersMsg(Message : TMessage);
    procedure   PostListenersMsg(Message : TMessage);
    
    property    Sender : TObject read FSender;
  end;


implementation

uses
  LogFile;

{ TMessageListenerSurport }

procedure TMessageListenerSurport.AddListener(Listener: IMessageListener);
begin
  if FList<>nil then FList.add(Listener);
  {$IFDEF Debug}
    writeLog('Remove Messagelistener',lcDebug);
  {$ENDIF}
end;

function TMessageListenerSurport.Count: Integer;
begin
  Result := FList.Count;
end;

constructor TMessageListenerSurport.Create(ASender: TObject);
begin
  inherited Create;
  FSender := ASender;
  FList := TInterfaceList.Create;
end;

destructor TMessageListenerSurport.Destroy;
var
  AList : TObject;
begin
  AList := FList;
  FList := nil;
  AList.Free;
  inherited;
end;

procedure TMessageListenerSurport.PostListenersMsg(Message: TMessage);
var
  I : integer;
begin
  if FList<>nil then
  begin
    FList.Lock;
    try
      //for i:=0 to FList.count-1 do
      // sometimes when it Notified a listener,
      // the listener will be removed from this list
      // there maybe a out of list exception
      for I:=FList.count-1 downto 0 do
        IMessageListener(FList[i]).PostSelfMessage(FSender,Message);
    finally
      FList.UnLock;
    end;
  end;
end;

procedure TMessageListenerSurport.RemoveListener(
  Listener: IMessageListener);
begin
  if FList<>nil then FList.Remove(Listener);
  {$IFDEF Debug}
  writeLog('Add Messagelistener',lcDebug);
  {$ENDIF}
end;

procedure TMessageListenerSurport.SendListenersMsg(Message: TMessage);
var
  I : integer;
begin
  if FList<>nil then
  begin
    FList.Lock;
    try
      //for i:=0 to FList.count-1 do
      // sometimes when it Notified a listener,
      // the listener will be removed from this list
      // there maybe a out of list exception
      for I:=FList.count-1 downto 0 do
        IMessageListener(FList[i]).SendSelfMessage(FSender,Message);
    finally
      FList.UnLock;
    end;
  end;
end;

end.
