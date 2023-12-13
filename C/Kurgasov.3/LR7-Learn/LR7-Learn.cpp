#include "pch.h"
#include <exception>

using namespace System;

delegate String^ FirstEventHandler();
delegate void SecondEventHandler(String^);
// Источник событий
ref class EvtSrc {
public:
  event FirstEventHandler^ OnFirstEvent;
  event SecondEventHandler^ OnSecondEvent;

  // Объявляем методы, вызывающие события
  String^ fireOne() {
    OnFirstEvent();
  }
  void raiseTwo(String^ msg) {
    OnSecondEvent(msg);
  }

};

ref class EvtRcv {
  // Получатель должен иметь доступ к испточникам событий, с которыми он работает, чтобы иметь возможность привязать или отвязать обработчик от события.
  EvtSrc^ theSource;
  // У нас есть доступ к 2м событиям (делегатам), теперь к ним можем привязать обработчиков.

public:

  EvtRcv(EvtSrc^ src) {
    if (src == nullptr) {
      throw gcnew ArgumentNullException("Обработчик должен знать источник события");
    }
    theSource = src;
    // В конструкторе же привяжем к событию (делегату) обработчики. Обявление события не объявляет новый тип.
    theSource->OnFirstEvent  /* Вызваем сгенерированный компилятором метод add(), который вызывает статический метод Combine для делегата типа FirstEventHandler, то есть добавляет в список вызовов события список вызовов созданного делегата, в сп. выз которого мы в констуркторе добавляем указатель на обработчик. */ += /* Вызваем создаем экземпляр делегата */gcnew FirstEventHandler(this, &EvtRcv::firstEvent);
    theSource->OnSecondEvent += gcnew SecondEventHandler(this, &EvtRcv::secondEvent);

  }

  String^ firstEvent() {
    String^ str = Console::ReadLine();
    return str;
  }
  void secondEvent(String^ msg) {
    Console::WriteLine("Обработали событие 2, отп. сообщение : " + msg);
  }
};


int main(array<System::String ^> ^args)
{
    // И источник и получатель должны быть объединены, либо в главной ф-ции, либо еще в каком либо классе
  Console::WriteLine("Пример реализации собственного события и его обработчика");
  
  EvtSrc^ src = gcnew EvtSrc();

  EvtRcv^ rcv = gcnew EvtRcv(src);

  Console::WriteLine("Запустим события");
  src->OnSecondEvent -= gcnew SecondEventHandler(rcv, &EvtRcv::secondEvent);
  src->fireOne();
  src->raiseTwo("Я без бутылки разобрался с механизмом событий )");

  String^ s;
  s = Console::ReadLine();
  Console::WriteLine(s);

  delete s;
  s = nullptr;
  if (s == nullptr) Console::Write("0");

  Console::Read();

  return 0;
}
