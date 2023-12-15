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
  try {
    // Если открытый в таком режиме файл с существует, то его исх. содержимое будет стерто и заменено новым.
    // Путь может быть любым.

    Globalization::CultureInfo^ ci = gcnew Globalization::CultureInfo("ru-RU");
    
    // Представляет поток вывода, принимает байты и записывает их в файл
    IO::FileStream^ fs = gcnew IO::FileStream("tst1.txt", IO::FileMode::Append, IO::FileAccess::Write, IO::FileShare::Read);
    // Принимает текст и преобразует его в поток байт.
    IO::StreamWriter^ sw = gcnew IO::StreamWriter(fs);

    sw->WriteLine("Зафиксируем момент в файл {0}.", DateTime::Now.ToString(ci));
    sw->WriteLine("Зафиксируем момент в файл {0}.", DateTime::Now.ToString(ci));

    // Записываем содержимое буфера в файл на жестком диске
    sw->Flush();
    // Очищаем память, выделенную под буфер.
    sw->Close();

  } catch (Exception^ e) {
    Console::WriteLine(e->ToString());
  }

  Console::Read();

  return 0;
}
