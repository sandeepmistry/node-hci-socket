#ifndef ___BLUETOOTH_HCI_SOCKET_H___
#define ___BLUETOOTH_HCI_SOCKET_H___

#include <node.h>

#include <nan.h>

class BluetoothHciSocket : public node::ObjectWrap {

public:
  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(New);
  static NAN_METHOD(BindRaw);
  static NAN_METHOD(BindUser);
  static NAN_METHOD(BindControl);
  static NAN_METHOD(IsDevUp);
  static NAN_METHOD(GetDeviceList);
  static NAN_METHOD(SetFilter);
  static NAN_METHOD(Start);
  static NAN_METHOD(Stop);
  static NAN_METHOD(Write);

private:
  BluetoothHciSocket();
  ~BluetoothHciSocket();

  void start();
  int bindRaw(int* devId);
  int bindUser(int* devId);
  void bindControl();
  bool isDevUp();
  void setFilter(char* data, int length);
  void stop();

  void write_(char* data, int length);

  void poll();

  void emitErrnoError();
  int devIdFor(int* devId, bool isUp);
  void kernelDisconnectWorkArounds(int length, char* data);
  bool kernelConnectWorkArounds(char* data, int length);

  static void PollCloseCallback(uv_poll_t* handle);
  static void PollCallback(uv_poll_t* handle, int status, int events);

private:
  Nan::Persistent<v8::Object> This;

  int _mode;
  int _socket;
  int _devId;
  uv_poll_t _pollHandle;
  uint8_t _address[6];
  uint8_t _addressType;

  static Nan::Persistent<v8::FunctionTemplate> constructor_template;
};

#endif
